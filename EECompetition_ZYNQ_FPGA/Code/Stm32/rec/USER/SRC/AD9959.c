#include "ad9959.h"
 
u8 CSR_DATA0[1] = {0x10};     // 开 CH0
u8 CSR_DATA1[1] = {0x20};      // 开 CH1
u8 CSR_DATA2[1] = {0x40};      // 开 CH2
u8 CSR_DATA3[1] = {0x80};      // 开 CH3		
																	
u8 FR1_DATA[3] = {0xD0,0x00,0x00};//20倍频 Charge pump control = 75uA FR1<23> -- VCO gain control =0时 system clock below 160 MHz; 
u8 FR2_DATA[2] = {0x00,0x00};//default Value = 0x0000
u8 CFR_DATA[3] = {0x00,0x03,0x00};//default Value = 0x000302	   
																	
u8 CPOW0_DATA[2] = {0x00,0x00};//default Value = 0x0000   @ = POW/2^14*360
																	


u8 LSRR_DATA[2] = {0x00,0x00};//default Value = 0x----
																	
u8 RDW_DATA[4] = {0x00,0x00,0x00,0x00};//default Value = 0x--------
																	
u8 FDW_DATA[4] = {0x00,0x00,0x00,0x00};//default Value = 0x--------

u32 SinFre[5] = {0, 10000, 25000, 20000000};
u32 SinAmp[5] = {1023, 1023, 1023, 1023};
u32 SinPhr[5] = {4095,  4095, 4095, 4095};

//AD9959初始化
void Init_AD9959(void)  
{ 
		
		
	Intserve();  //IO口初始化
  IntReset();  //AD9959复位  
	
  WriteData_AD9959(FR1_ADD,3,FR1_DATA,1);//写功能寄存器1
//  WriteData_AD9959(FR2_ADD,2,FR2_DATA,0);
 // WriteData_AD9959(CFR_ADD,3,CFR_DATA,1);
//  WriteData_AD9959(CPOW0_ADD,2,CPOW0_DATA,0);
//  WriteData_AD9959(ACR_ADD,3,ACR_DATA,0);
//  WriteData_AD9959(LSRR_ADD,2,LSRR_DATA,0);
//  WriteData_AD9959(RDW_ADD,2,RDW_DATA,0);
//  WriteData_AD9959(FDW_ADD,4,FDW_DATA,1);
   //写入初始频率
	Write_frequence(3,SinFre[3]);
	Write_frequence(0,SinFre[0]); 
	Write_frequence(1,SinFre[1]);
	Write_frequence(2,SinFre[2]);
	
//	Write_frequence(3,50);
//	Write_frequence(0,50);
//	Write_frequence(1,50);
//	Write_frequence(2,50);

	Write_Phase(3, SinPhr[3]);
	Write_Phase(0, SinPhr[0]);
	Write_Phase(1, SinPhr[1]);
	Write_Phase(2, SinPhr[2]);
	
	Write_Amplitude(3, SinAmp[3]);
	Write_Amplitude(0, SinAmp[0]);
	Write_Amplitude(1, SinAmp[1]);
	Write_Amplitude(2, SinAmp[2]);
} 
//延时
void delay1 (u32 length)
{
	length = length*12;
   while(length--);
}
//IO口初始化
void Intserve(void)		   
{   
		PWRD=0;
    CS = 1;
    SCLK = 0;
    UPDATE = 0;
    PS0 = 0;
    PS1 = 0;
    PS2 = 0;
    PS3 = 0;
    SDIO0 = 0;
    SDIO1 = 0;
    SDIO2 = 0;
    SDIO3 = 0;
}
//AD9959复位
void IntReset(void)	  
{
  Reset = 0;
	delay1(1);
	Reset = 1;
	delay1(30);
	Reset = 0;
}
 //AD9959更新数据
void IO_Update(void)  
{
	UPDATE = 0;
	delay1(2);
	UPDATE = 1;
	delay1(4);
	UPDATE = 0;
}
/*--------------------------------------------
函数功能：控制器通过SPI向AD9959写数据
RegisterAddress: 寄存器地址
NumberofRegisters: 所含字节数
*RegisterData: 数据起始地址
temp: 是否更新IO寄存器
----------------------------------------------*/
void WriteData_AD9959(u8 RegisterAddress, u8 NumberofRegisters, u8 *RegisterData,u8 temp)
{
	u8	ControlValue = 0;
	u8	ValueToWrite = 0;
	u8	RegisterIndex = 0;
	u8	i = 0;

	ControlValue = RegisterAddress;
//写入地址
	SCLK = 0;
	CS = 0;	 
	for(i=0; i<8; i++)
	{
		SCLK = 0;
		if(0x80 == (ControlValue & 0x80))
		SDIO0= 1;	  
		else
		SDIO0= 0;	  
		SCLK = 1;
		ControlValue <<= 1;
	}
	SCLK = 0;
//写入数据
	for (RegisterIndex=0; RegisterIndex<NumberofRegisters; RegisterIndex++)
	{
		ValueToWrite = RegisterData[RegisterIndex];
		for (i=0; i<8; i++)
		{
			SCLK = 0;
			if(0x80 == (ValueToWrite & 0x80))
			SDIO0= 1;	  
			else
			SDIO0= 0;	  
			SCLK = 1;
			ValueToWrite <<= 1;
		}
		SCLK = 0;		
	}	
	if(temp==1)
	IO_Update();	
  CS = 1;
} 
/*---------------------------------------
函数功能：设置通道输出频率
Channel:  输出通道
Freq:     输出频率
---------------------------------------*/
void Write_frequence(u8 Channel,u32 Freq)
{	 
		u8 CFTW0_DATA[4] ={0x00,0x00,0x00,0x00};	//中间变量
	  u32 Temp;            
	  Temp=(u32)Freq*8.589934592;	   //将输入频率因子分为四个字节  4.294967296=(2^32)/500000000
	  CFTW0_DATA[3]=(u8)Temp;
	  CFTW0_DATA[2]=(u8)(Temp>>8);
	  CFTW0_DATA[1]=(u8)(Temp>>16);
	  CFTW0_DATA[0]=(u8)(Temp>>24);
	  if(Channel==0)	  
	  {
			WriteData_AD9959(CSR_ADD,1,CSR_DATA0,1);//控制寄存器写入CH0通道
      WriteData_AD9959(CFTW0_ADD,4,CFTW0_DATA,1);//CTW0 address 0x04.输出CH0设定频率
		}
	  else if(Channel==1)	
	  {
			WriteData_AD9959(CSR_ADD,1,CSR_DATA1,1);//控制寄存器写入CH1通道
      WriteData_AD9959(CFTW0_ADD,4,CFTW0_DATA,1);//CTW0 address 0x04.输出CH1设定频率	
	  }
	  else if(Channel==2)	
	  {
			WriteData_AD9959(CSR_ADD,1,CSR_DATA2,1);//控制寄存器写入CH2通道
      WriteData_AD9959(CFTW0_ADD,4,CFTW0_DATA,1);//CTW0 address 0x04.输出CH2设定频率	
	  }
	  else if(Channel==3)	
	  {
			WriteData_AD9959(CSR_ADD,1,CSR_DATA3,1);//控制寄存器写入CH3通道
      WriteData_AD9959(CFTW0_ADD,4,CFTW0_DATA,3);//CTW0 address 0x04.输出CH3设定频率	
	  }																																																																										 
	
} 
/*---------------------------------------
函数功能：设置通道输出幅度
Channel:  输出通道
Ampli:    输出幅度
---------------------------------------*/
void Write_Amplitude(u8 Channel, u16 Ampli)
{ 
	u16 A_temp;//=0x23ff;
	u8 ACR_DATA[3] = {0x00,0x00,0x00};//default Value = 0x--0000 Rest = 18.91/Iout 
	
  A_temp=Ampli|0x1000;
	ACR_DATA[2] = (u8)A_temp;  //低位数据
  ACR_DATA[1] = (u8)(A_temp>>8); //高位数据
  if(Channel==0)
  {
		WriteData_AD9959(CSR_ADD,1,CSR_DATA0,1); 
    WriteData_AD9959(ACR_ADD,3,ACR_DATA,1); 
	}
  else if(Channel==1)
  {
		WriteData_AD9959(CSR_ADD,1,CSR_DATA1,1); 
    WriteData_AD9959(ACR_ADD,3,ACR_DATA,1);
	}
  else if(Channel==2)
  {
	  WriteData_AD9959(CSR_ADD,1,CSR_DATA2,1); 
    WriteData_AD9959(ACR_ADD,3,ACR_DATA,1); 
	}
  else if(Channel==3)
  {
		WriteData_AD9959(CSR_ADD,1,CSR_DATA3,1); 
    WriteData_AD9959(ACR_ADD,3,ACR_DATA,1); 
	}
}
/*---------------------------------------
函数功能：设置通道输出相位
Channel:  输出通道
Phase:    输出相位,范围：0~16383(对应角度：0°~360°)
---------------------------------------*/
void Write_Phase(u8 Channel,u16 Phase)
{
	u16 P_temp=0;
  P_temp=(u16)Phase;
	CPOW0_DATA[1]=(u8)P_temp;
	CPOW0_DATA[0]=(u8)(P_temp>>8);
	if(Channel==0)
  {
		WriteData_AD9959(CSR_ADD,1,CSR_DATA0,0); 
    WriteData_AD9959(CPOW0_ADD,2,CPOW0_DATA,0);
  }
  else if(Channel==1)
  {
		WriteData_AD9959(CSR_ADD,1,CSR_DATA1,0); 
    WriteData_AD9959(CPOW0_ADD,2,CPOW0_DATA,0);
  }
  else if(Channel==2)
  {
		WriteData_AD9959(CSR_ADD,1,CSR_DATA2,0); 
    WriteData_AD9959(CPOW0_ADD,2,CPOW0_DATA,0);
  }
  else if(Channel==3)
  {
		WriteData_AD9959(CSR_ADD,1,CSR_DATA3,0); 
    WriteData_AD9959(CPOW0_ADD,2,CPOW0_DATA,0);
  }
}	 
void Fre_Modulation(u8 Channel, u8 Modul_Level,  u32 *Fre_Value)
{
	u8 i;
	u32 ValueToWrite;
	u8 CFTW0_DATA[4] ={0x00,0x00,0x00,0x00};	//中间变量
  u32 Temp;            
 	   //将输入频率因子分为四个字节  4.294967296=(2^32)/500000000
	if(Channel==0)
  	WriteData_AD9959(CSR_ADD,1,CSR_DATA0,1);//控制寄存器写入CH0通道
	else if(Channel==1)
  	WriteData_AD9959(CSR_ADD,1,CSR_DATA1,1);//控制寄存器写入CH0通道
	else if(Channel==2)
  	WriteData_AD9959(CSR_ADD,1,CSR_DATA2,1);//控制寄存器写入CH0通道
	else if(Channel==3)
  	WriteData_AD9959(CSR_ADD,1,CSR_DATA3,1);//控制寄存器写入CH0通道
	
  if (Modul_Level==2)	
	FR1_DATA[1]= FR1_DATA[1] | 0x00;
	else if (Modul_Level==4)	
	FR1_DATA[1]= FR1_DATA[1] | 0x01;
	else if (Modul_Level==8)	
	FR1_DATA[1]= FR1_DATA[1] | 0x02;
	else if (Modul_Level==16)	
	FR1_DATA[1]= FR1_DATA[1] | 0x03;
	WriteData_AD9959(FR1_ADD,3,FR1_DATA,1);//CTW0 address 0x04.输出CH0设定频率
	
	CFR_DATA[0]=CFR_DATA[0] | (0x02<<6);  //调频设置
	WriteData_AD9959(CFR_ADD,3,CFR_DATA,1);//CTW0 address 0x04.输出CH0设定频率
	
		for (i=0; i<16; i++)
	{
		ValueToWrite = Fre_Value[i];
	  Temp=(u32)ValueToWrite*8.589934592;
	  CFTW0_DATA[3]=(u8)Temp;
	  CFTW0_DATA[2]=(u8)(Temp>>8);
	  CFTW0_DATA[1]=(u8)(Temp>>16);
	  CFTW0_DATA[0]=(u8)(Temp>>24);
		if (i==0)
		{
			 WriteData_AD9959(CFTW0_ADD,4,CFTW0_DATA,1);//CTW0 address 0x04.输出CH0设定频率
	  }
		else
		{
		   WriteData_AD9959((CW1_ADD+i-1),4,CFTW0_DATA,1);//CTW0 address 0x04.输出CH0设定频率
		}
	} 
	
	
}

void Amp_Modulation(u8 Channel, u8 Modul_Level,  u16 *Amp_Value)
{
	u8 i;
	u16 ValueToWrite;
  u32 A_temp; 
	u8 ACR_DATA[4] = {0x00,0x00,0x00,0x00};//default Value = 0x--0000 Rest = 18.91/Iout 
	
 
	 

	
 	   
	if(Channel==0)
  	WriteData_AD9959(CSR_ADD,1,CSR_DATA0,1);//控制寄存器写入CH0通道
	else if(Channel==1)
  	WriteData_AD9959(CSR_ADD,1,CSR_DATA1,1);//控制寄存器写入CH0通道
	else if(Channel==2)
  	WriteData_AD9959(CSR_ADD,1,CSR_DATA2,1);//控制寄存器写入CH0通道
	else if(Channel==3)
  	WriteData_AD9959(CSR_ADD,1,CSR_DATA3,1);//控制寄存器写入CH0通道
	
  if (Modul_Level==2)	
	FR1_DATA[1]= FR1_DATA[1] | 0x00;
	else if (Modul_Level==4)	
	FR1_DATA[1]= FR1_DATA[1] | 0x01;
	else if (Modul_Level==8)	
	FR1_DATA[1]= FR1_DATA[1] | 0x02;
	else if (Modul_Level==16)	
	FR1_DATA[1]= FR1_DATA[1] | 0x03;
	WriteData_AD9959(FR1_ADD,3,FR1_DATA,1);//调制级设置
	
	CFR_DATA[0]=CFR_DATA[0] | (0x01<<6);  //调幅设置
	WriteData_AD9959(CFR_ADD,3,CFR_DATA,1);//CTW0 address 0x04.输出CH0设定频率
	
		for (i=0; i<16; i++)
	{
		ValueToWrite = Amp_Value[i];
	  
		
		
	  if (i==0)
		{
		//	A_temp =(u32) ValueToWrite;
			ValueToWrite= ValueToWrite|0x1000;
			ACR_DATA[2] = (u8) ValueToWrite;  //低位数据
			ACR_DATA[1] = (u8) (ValueToWrite>>8);  //低位数据
			//ACR_DATA[0] = (u8) ValueToWrite>>16;  //高位数据
		  WriteData_AD9959(ACR_ADD,3,ACR_DATA,1); 
	  }
		else
		{
			A_temp =(u32)(ValueToWrite<<22);
			ACR_DATA[3] = (u8) A_temp;  //低位数据
			ACR_DATA[2] = (u8)(A_temp>>8);  //低位数据
			ACR_DATA[1] = (u8)(A_temp>>16);  //低位数据
			ACR_DATA[0] = (u8)(A_temp>>24); //高位数据
		  WriteData_AD9959((CW1_ADD+i-1),4,ACR_DATA,1);//CTW0 address 0x04.输出CH0设定频率
		}
	} 
	
	
}

/*函数功能：设置通道相位调制输出
Channel:  输出通道
Pha_Value:    输出相位,范围：0~16383(对应角度：0°~360°)
---------------------------------------*/
 
void Pha_Modulation(u8 Channel, u8 Modul_Level,  u16 *Pha_Value)
{
	u8 i;
	u16 ValueToWrite;
  u32 P_temp; 
	 	   
	if(Channel==0)
  	WriteData_AD9959(CSR_ADD,1,CSR_DATA0,1);//控制寄存器写入CH0通道
	else if(Channel==1)
  	WriteData_AD9959(CSR_ADD,1,CSR_DATA1,1);//控制寄存器写入CH0通道
	else if(Channel==2)
  	WriteData_AD9959(CSR_ADD,1,CSR_DATA2,1);//控制寄存器写入CH0通道
	else if(Channel==3)
  	WriteData_AD9959(CSR_ADD,1,CSR_DATA3,1);//控制寄存器写入CH0通道
	
  if (Modul_Level==2)	
	FR1_DATA[1]= FR1_DATA[1] | 0x00;
	else if (Modul_Level==4)	
	FR1_DATA[1]= FR1_DATA[1] | 0x01;
	else if (Modul_Level==8)	
	FR1_DATA[1]= FR1_DATA[1] | 0x02;
	else if (Modul_Level==16)	
	FR1_DATA[1]= FR1_DATA[1] | 0x03;
	WriteData_AD9959(FR1_ADD,3,FR1_DATA,1);//调制级设置
	
	CFR_DATA[0]=CFR_DATA[0] | (0x03<<6);  //调相设置
	WriteData_AD9959(CFR_ADD,3,CFR_DATA,1);//CTW0 address 0x04.输出CH0设定频率
	
		for (i=0; i<16; i++)
	{
		ValueToWrite = Pha_Value[i];
	  
		
		
	  if (i==0)
		{
 
			CPOW0_DATA[1] = (u8) ValueToWrite;  //低位数据
		  CPOW0_DATA[0] = (u8) (ValueToWrite>>8);  //高位数据
			WriteData_AD9959(CPOW0_ADD,2,CPOW0_DATA,1); 
	  }
		else
		{
			P_temp =(u32)(ValueToWrite<<18);
			CPOW0_DATA[1] = (u8)(P_temp>>16);  //低位数据
			CPOW0_DATA[0]= (u8)(P_temp>>24); //高位数据
		  WriteData_AD9959((CW1_ADD+i-1),2,CPOW0_DATA,1);//CTW0 address 0x04.输出CH0设定频率
		}
	} 
	
	
}

void Fre_Sweep(u8 Channel, u32 S_Fre,  u32 E_Fre)
{
	u32 Temp; 
	u8 CFTW0_DATA[4] = {0x00,0x00,0x00,0x00};	//中间变量
	u8 RDW_DATA[4]   = {0x00,0x00,0x00,0x00};	//中间变量
  u8 LSRR_DATA[2] =  {0x00,0x00};
  if(Channel==0)
  	WriteData_AD9959(CSR_ADD,1,CSR_DATA0,1);//控制寄存器写入CH0通道
	else if(Channel==1)
  	WriteData_AD9959(CSR_ADD,1,CSR_DATA1,1);//控制寄存器写入CH1通道
	else if(Channel==2)
  	WriteData_AD9959(CSR_ADD,1,CSR_DATA2,1);//控制寄存器写入CH2通道
	else if(Channel==3)
  	WriteData_AD9959(CSR_ADD,1,CSR_DATA3,1);//控制寄存器写入CH3通道
	
 
 
	
	CFR_DATA[0]=CFR_DATA[0] | (0x02<<6);  //扫频
	CFR_DATA[1]=CFR_DATA[1] | (0x01<<6);  //扫频使能
	WriteData_AD9959(CFR_ADD,3,CFR_DATA,1);//CTW0 address 0x04.输出CH0设定频率
	
	 
	  Temp=(u32)S_Fre*8.589934592;
	  CFTW0_DATA[3]=(u8)Temp;
	  CFTW0_DATA[2]=(u8)(Temp>>8);
	  CFTW0_DATA[1]=(u8)(Temp>>16);
	  CFTW0_DATA[0]=(u8)(Temp>>24);
  	WriteData_AD9959(CFTW0_ADD,4,CFTW0_DATA,1);//CTW0 address 0x04.输出CH0设定频率
	  
	  Temp=(u32)E_Fre*8.589934592;
	  CFTW0_DATA[3]=(u8)Temp;
	  CFTW0_DATA[2]=(u8)(Temp>>8);
	  CFTW0_DATA[1]=(u8)(Temp>>16);
	  CFTW0_DATA[0]=(u8)(Temp>>24);
  	WriteData_AD9959(CW1_ADD,4,CFTW0_DATA,1); 
		
   
		Temp=(u32)(E_Fre-S_Fre )*0.343597383;
		RDW_DATA[3]=(u8)Temp;
	  RDW_DATA[2]=(u8)(Temp>>8);
	  RDW_DATA[1]=(u8)(Temp>>16);
	  RDW_DATA[0]=(u8)(Temp>>24);
		WriteData_AD9959(RDW_ADD,4,RDW_DATA,1);//RDW address 0x08.设定RDW
		
		WriteData_AD9959(FDW_ADD,4,RDW_DATA,1);
		
		LSRR_DATA[0]=100;
		LSRR_DATA[1]=100;
		
		WriteData_AD9959(LSRR_ADD,2,LSRR_DATA,1);
}

void Amp_Sweep(u8 Channel, u16 S_Amp,  u16 E_Amp)
{
	u8 ACR_DATA[4] = {0x00,0x00,0x00,0x00};//default Value = 0x--0000 Rest = 18.91/Iout 
	u32 temp;
	u8 CW1_DATA[4]   = {0x00,0x00,0x00,0x00};	//中间变量
	u8 RDW_DATA[4]   = {0x00,0x00,0x00,0x00};	//中间变量
	u8 FDW_DATA[4]   = {0x00,0x00,0x00,0x00};	//中间变量
  u8 LSRR_DATA[2] =  {0x00,0x00};
  if(Channel==0)
  	WriteData_AD9959(CSR_ADD,1,CSR_DATA0,1);//控制寄存器写入CHx通道
	else if(Channel==1)
  	WriteData_AD9959(CSR_ADD,1,CSR_DATA1,1);//控制寄存器写入CHx通道
	else if(Channel==2)
  	WriteData_AD9959(CSR_ADD,1,CSR_DATA2,1);//控制寄存器写入CHx通道
	else if(Channel==3)
  	WriteData_AD9959(CSR_ADD,1,CSR_DATA3,1);//控制寄存器写入CHx通道
	
	CFR_DATA[0]=CFR_DATA[0] | (0x01<<6);  //扫幅
	CFR_DATA[1]=CFR_DATA[1] | (0x01<<6);  //扫幅使能
	WriteData_AD9959(CFR_ADD,3,CFR_DATA,1);//CTW0 address 0x04.输出CH0设定频率
	
	 
	
	 
	ACR_DATA[2] = (u8)S_Amp;  //低位数据
	ACR_DATA[1] = (u8)(S_Amp>>8);  //低位数据
 
	WriteData_AD9959(ACR_ADD,3,ACR_DATA,1); 
	
	temp =(u32)(E_Amp<<22);
	CW1_DATA[3] = (u8) temp;  //低位数据
	CW1_DATA[2] = (u8)(temp>>8);  //低位数据
	CW1_DATA[1] = (u8)(temp>>16);  //低位数据
	CW1_DATA[0] = (u8)(temp>>24); //高位数据
	WriteData_AD9959(CW1_ADD,4,CW1_DATA,1);//CTW0 address 0x04.输出CH0设定频率
	
	 
	temp =(u32)(0x10<<22);
	RDW_DATA[3] = (u8) temp;  //低位数据
	RDW_DATA[2] = (u8)(temp>>8);  //低位数据
	RDW_DATA[1] = (u8)(temp>>16);  //低位数据
	RDW_DATA[0] = (u8)(temp>>24); //高位数据
	
	WriteData_AD9959(RDW_ADD,4,RDW_DATA,1);//RDW address 0x08.设定RDW
	
	temp =(u32)(0x10<<22);
	FDW_DATA[3] = (u8) temp;  //低位数据
	FDW_DATA[2] = (u8)(temp>>8);  //低位数据
	FDW_DATA[1] = (u8)(temp>>16);  //低位数据
	FDW_DATA[0] = (u8)(temp>>24); //高位数据
	WriteData_AD9959(FDW_ADD,4,FDW_DATA,1);
	
	LSRR_DATA[0]=80;
	LSRR_DATA[1]=80;
	WriteData_AD9959(LSRR_ADD,2,LSRR_DATA,1);
}


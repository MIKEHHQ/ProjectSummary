#include "ad9959.h"
 
u8 CSR_DATA0[1] = {0x10};     // �� CH0
u8 CSR_DATA1[1] = {0x20};      // �� CH1
u8 CSR_DATA2[1] = {0x40};      // �� CH2
u8 CSR_DATA3[1] = {0x80};      // �� CH3		
																	
u8 FR1_DATA[3] = {0xD0,0x00,0x00};//20��Ƶ Charge pump control = 75uA FR1<23> -- VCO gain control =0ʱ system clock below 160 MHz; 
u8 FR2_DATA[2] = {0x00,0x00};//default Value = 0x0000
u8 CFR_DATA[3] = {0x00,0x03,0x00};//default Value = 0x000302	   
																	
u8 CPOW0_DATA[2] = {0x00,0x00};//default Value = 0x0000   @ = POW/2^14*360
																	


u8 LSRR_DATA[2] = {0x00,0x00};//default Value = 0x----
																	
u8 RDW_DATA[4] = {0x00,0x00,0x00,0x00};//default Value = 0x--------
																	
u8 FDW_DATA[4] = {0x00,0x00,0x00,0x00};//default Value = 0x--------

u32 SinFre[5] = {0, 10000, 25000, 20000000};
u32 SinAmp[5] = {1023, 1023, 1023, 1023};
u32 SinPhr[5] = {4095,  4095, 4095, 4095};

//AD9959��ʼ��
void Init_AD9959(void)  
{ 
		
		
	Intserve();  //IO�ڳ�ʼ��
  IntReset();  //AD9959��λ  
	
  WriteData_AD9959(FR1_ADD,3,FR1_DATA,1);//д���ܼĴ���1
//  WriteData_AD9959(FR2_ADD,2,FR2_DATA,0);
 // WriteData_AD9959(CFR_ADD,3,CFR_DATA,1);
//  WriteData_AD9959(CPOW0_ADD,2,CPOW0_DATA,0);
//  WriteData_AD9959(ACR_ADD,3,ACR_DATA,0);
//  WriteData_AD9959(LSRR_ADD,2,LSRR_DATA,0);
//  WriteData_AD9959(RDW_ADD,2,RDW_DATA,0);
//  WriteData_AD9959(FDW_ADD,4,FDW_DATA,1);
   //д���ʼƵ��
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
//��ʱ
void delay1 (u32 length)
{
	length = length*12;
   while(length--);
}
//IO�ڳ�ʼ��
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
//AD9959��λ
void IntReset(void)	  
{
  Reset = 0;
	delay1(1);
	Reset = 1;
	delay1(30);
	Reset = 0;
}
 //AD9959��������
void IO_Update(void)  
{
	UPDATE = 0;
	delay1(2);
	UPDATE = 1;
	delay1(4);
	UPDATE = 0;
}
/*--------------------------------------------
�������ܣ�������ͨ��SPI��AD9959д����
RegisterAddress: �Ĵ�����ַ
NumberofRegisters: �����ֽ���
*RegisterData: ������ʼ��ַ
temp: �Ƿ����IO�Ĵ���
----------------------------------------------*/
void WriteData_AD9959(u8 RegisterAddress, u8 NumberofRegisters, u8 *RegisterData,u8 temp)
{
	u8	ControlValue = 0;
	u8	ValueToWrite = 0;
	u8	RegisterIndex = 0;
	u8	i = 0;

	ControlValue = RegisterAddress;
//д���ַ
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
//д������
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
�������ܣ�����ͨ�����Ƶ��
Channel:  ���ͨ��
Freq:     ���Ƶ��
---------------------------------------*/
void Write_frequence(u8 Channel,u32 Freq)
{	 
		u8 CFTW0_DATA[4] ={0x00,0x00,0x00,0x00};	//�м����
	  u32 Temp;            
	  Temp=(u32)Freq*8.589934592;	   //������Ƶ�����ӷ�Ϊ�ĸ��ֽ�  4.294967296=(2^32)/500000000
	  CFTW0_DATA[3]=(u8)Temp;
	  CFTW0_DATA[2]=(u8)(Temp>>8);
	  CFTW0_DATA[1]=(u8)(Temp>>16);
	  CFTW0_DATA[0]=(u8)(Temp>>24);
	  if(Channel==0)	  
	  {
			WriteData_AD9959(CSR_ADD,1,CSR_DATA0,1);//���ƼĴ���д��CH0ͨ��
      WriteData_AD9959(CFTW0_ADD,4,CFTW0_DATA,1);//CTW0 address 0x04.���CH0�趨Ƶ��
		}
	  else if(Channel==1)	
	  {
			WriteData_AD9959(CSR_ADD,1,CSR_DATA1,1);//���ƼĴ���д��CH1ͨ��
      WriteData_AD9959(CFTW0_ADD,4,CFTW0_DATA,1);//CTW0 address 0x04.���CH1�趨Ƶ��	
	  }
	  else if(Channel==2)	
	  {
			WriteData_AD9959(CSR_ADD,1,CSR_DATA2,1);//���ƼĴ���д��CH2ͨ��
      WriteData_AD9959(CFTW0_ADD,4,CFTW0_DATA,1);//CTW0 address 0x04.���CH2�趨Ƶ��	
	  }
	  else if(Channel==3)	
	  {
			WriteData_AD9959(CSR_ADD,1,CSR_DATA3,1);//���ƼĴ���д��CH3ͨ��
      WriteData_AD9959(CFTW0_ADD,4,CFTW0_DATA,3);//CTW0 address 0x04.���CH3�趨Ƶ��	
	  }																																																																										 
	
} 
/*---------------------------------------
�������ܣ�����ͨ���������
Channel:  ���ͨ��
Ampli:    �������
---------------------------------------*/
void Write_Amplitude(u8 Channel, u16 Ampli)
{ 
	u16 A_temp;//=0x23ff;
	u8 ACR_DATA[3] = {0x00,0x00,0x00};//default Value = 0x--0000 Rest = 18.91/Iout 
	
  A_temp=Ampli|0x1000;
	ACR_DATA[2] = (u8)A_temp;  //��λ����
  ACR_DATA[1] = (u8)(A_temp>>8); //��λ����
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
�������ܣ�����ͨ�������λ
Channel:  ���ͨ��
Phase:    �����λ,��Χ��0~16383(��Ӧ�Ƕȣ�0��~360��)
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
	u8 CFTW0_DATA[4] ={0x00,0x00,0x00,0x00};	//�м����
  u32 Temp;            
 	   //������Ƶ�����ӷ�Ϊ�ĸ��ֽ�  4.294967296=(2^32)/500000000
	if(Channel==0)
  	WriteData_AD9959(CSR_ADD,1,CSR_DATA0,1);//���ƼĴ���д��CH0ͨ��
	else if(Channel==1)
  	WriteData_AD9959(CSR_ADD,1,CSR_DATA1,1);//���ƼĴ���д��CH0ͨ��
	else if(Channel==2)
  	WriteData_AD9959(CSR_ADD,1,CSR_DATA2,1);//���ƼĴ���д��CH0ͨ��
	else if(Channel==3)
  	WriteData_AD9959(CSR_ADD,1,CSR_DATA3,1);//���ƼĴ���д��CH0ͨ��
	
  if (Modul_Level==2)	
	FR1_DATA[1]= FR1_DATA[1] | 0x00;
	else if (Modul_Level==4)	
	FR1_DATA[1]= FR1_DATA[1] | 0x01;
	else if (Modul_Level==8)	
	FR1_DATA[1]= FR1_DATA[1] | 0x02;
	else if (Modul_Level==16)	
	FR1_DATA[1]= FR1_DATA[1] | 0x03;
	WriteData_AD9959(FR1_ADD,3,FR1_DATA,1);//CTW0 address 0x04.���CH0�趨Ƶ��
	
	CFR_DATA[0]=CFR_DATA[0] | (0x02<<6);  //��Ƶ����
	WriteData_AD9959(CFR_ADD,3,CFR_DATA,1);//CTW0 address 0x04.���CH0�趨Ƶ��
	
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
			 WriteData_AD9959(CFTW0_ADD,4,CFTW0_DATA,1);//CTW0 address 0x04.���CH0�趨Ƶ��
	  }
		else
		{
		   WriteData_AD9959((CW1_ADD+i-1),4,CFTW0_DATA,1);//CTW0 address 0x04.���CH0�趨Ƶ��
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
  	WriteData_AD9959(CSR_ADD,1,CSR_DATA0,1);//���ƼĴ���д��CH0ͨ��
	else if(Channel==1)
  	WriteData_AD9959(CSR_ADD,1,CSR_DATA1,1);//���ƼĴ���д��CH0ͨ��
	else if(Channel==2)
  	WriteData_AD9959(CSR_ADD,1,CSR_DATA2,1);//���ƼĴ���д��CH0ͨ��
	else if(Channel==3)
  	WriteData_AD9959(CSR_ADD,1,CSR_DATA3,1);//���ƼĴ���д��CH0ͨ��
	
  if (Modul_Level==2)	
	FR1_DATA[1]= FR1_DATA[1] | 0x00;
	else if (Modul_Level==4)	
	FR1_DATA[1]= FR1_DATA[1] | 0x01;
	else if (Modul_Level==8)	
	FR1_DATA[1]= FR1_DATA[1] | 0x02;
	else if (Modul_Level==16)	
	FR1_DATA[1]= FR1_DATA[1] | 0x03;
	WriteData_AD9959(FR1_ADD,3,FR1_DATA,1);//���Ƽ�����
	
	CFR_DATA[0]=CFR_DATA[0] | (0x01<<6);  //��������
	WriteData_AD9959(CFR_ADD,3,CFR_DATA,1);//CTW0 address 0x04.���CH0�趨Ƶ��
	
		for (i=0; i<16; i++)
	{
		ValueToWrite = Amp_Value[i];
	  
		
		
	  if (i==0)
		{
		//	A_temp =(u32) ValueToWrite;
			ValueToWrite= ValueToWrite|0x1000;
			ACR_DATA[2] = (u8) ValueToWrite;  //��λ����
			ACR_DATA[1] = (u8) (ValueToWrite>>8);  //��λ����
			//ACR_DATA[0] = (u8) ValueToWrite>>16;  //��λ����
		  WriteData_AD9959(ACR_ADD,3,ACR_DATA,1); 
	  }
		else
		{
			A_temp =(u32)(ValueToWrite<<22);
			ACR_DATA[3] = (u8) A_temp;  //��λ����
			ACR_DATA[2] = (u8)(A_temp>>8);  //��λ����
			ACR_DATA[1] = (u8)(A_temp>>16);  //��λ����
			ACR_DATA[0] = (u8)(A_temp>>24); //��λ����
		  WriteData_AD9959((CW1_ADD+i-1),4,ACR_DATA,1);//CTW0 address 0x04.���CH0�趨Ƶ��
		}
	} 
	
	
}

/*�������ܣ�����ͨ����λ�������
Channel:  ���ͨ��
Pha_Value:    �����λ,��Χ��0~16383(��Ӧ�Ƕȣ�0��~360��)
---------------------------------------*/
 
void Pha_Modulation(u8 Channel, u8 Modul_Level,  u16 *Pha_Value)
{
	u8 i;
	u16 ValueToWrite;
  u32 P_temp; 
	 	   
	if(Channel==0)
  	WriteData_AD9959(CSR_ADD,1,CSR_DATA0,1);//���ƼĴ���д��CH0ͨ��
	else if(Channel==1)
  	WriteData_AD9959(CSR_ADD,1,CSR_DATA1,1);//���ƼĴ���д��CH0ͨ��
	else if(Channel==2)
  	WriteData_AD9959(CSR_ADD,1,CSR_DATA2,1);//���ƼĴ���д��CH0ͨ��
	else if(Channel==3)
  	WriteData_AD9959(CSR_ADD,1,CSR_DATA3,1);//���ƼĴ���д��CH0ͨ��
	
  if (Modul_Level==2)	
	FR1_DATA[1]= FR1_DATA[1] | 0x00;
	else if (Modul_Level==4)	
	FR1_DATA[1]= FR1_DATA[1] | 0x01;
	else if (Modul_Level==8)	
	FR1_DATA[1]= FR1_DATA[1] | 0x02;
	else if (Modul_Level==16)	
	FR1_DATA[1]= FR1_DATA[1] | 0x03;
	WriteData_AD9959(FR1_ADD,3,FR1_DATA,1);//���Ƽ�����
	
	CFR_DATA[0]=CFR_DATA[0] | (0x03<<6);  //��������
	WriteData_AD9959(CFR_ADD,3,CFR_DATA,1);//CTW0 address 0x04.���CH0�趨Ƶ��
	
		for (i=0; i<16; i++)
	{
		ValueToWrite = Pha_Value[i];
	  
		
		
	  if (i==0)
		{
 
			CPOW0_DATA[1] = (u8) ValueToWrite;  //��λ����
		  CPOW0_DATA[0] = (u8) (ValueToWrite>>8);  //��λ����
			WriteData_AD9959(CPOW0_ADD,2,CPOW0_DATA,1); 
	  }
		else
		{
			P_temp =(u32)(ValueToWrite<<18);
			CPOW0_DATA[1] = (u8)(P_temp>>16);  //��λ����
			CPOW0_DATA[0]= (u8)(P_temp>>24); //��λ����
		  WriteData_AD9959((CW1_ADD+i-1),2,CPOW0_DATA,1);//CTW0 address 0x04.���CH0�趨Ƶ��
		}
	} 
	
	
}

void Fre_Sweep(u8 Channel, u32 S_Fre,  u32 E_Fre)
{
	u32 Temp; 
	u8 CFTW0_DATA[4] = {0x00,0x00,0x00,0x00};	//�м����
	u8 RDW_DATA[4]   = {0x00,0x00,0x00,0x00};	//�м����
  u8 LSRR_DATA[2] =  {0x00,0x00};
  if(Channel==0)
  	WriteData_AD9959(CSR_ADD,1,CSR_DATA0,1);//���ƼĴ���д��CH0ͨ��
	else if(Channel==1)
  	WriteData_AD9959(CSR_ADD,1,CSR_DATA1,1);//���ƼĴ���д��CH1ͨ��
	else if(Channel==2)
  	WriteData_AD9959(CSR_ADD,1,CSR_DATA2,1);//���ƼĴ���д��CH2ͨ��
	else if(Channel==3)
  	WriteData_AD9959(CSR_ADD,1,CSR_DATA3,1);//���ƼĴ���д��CH3ͨ��
	
 
 
	
	CFR_DATA[0]=CFR_DATA[0] | (0x02<<6);  //ɨƵ
	CFR_DATA[1]=CFR_DATA[1] | (0x01<<6);  //ɨƵʹ��
	WriteData_AD9959(CFR_ADD,3,CFR_DATA,1);//CTW0 address 0x04.���CH0�趨Ƶ��
	
	 
	  Temp=(u32)S_Fre*8.589934592;
	  CFTW0_DATA[3]=(u8)Temp;
	  CFTW0_DATA[2]=(u8)(Temp>>8);
	  CFTW0_DATA[1]=(u8)(Temp>>16);
	  CFTW0_DATA[0]=(u8)(Temp>>24);
  	WriteData_AD9959(CFTW0_ADD,4,CFTW0_DATA,1);//CTW0 address 0x04.���CH0�趨Ƶ��
	  
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
		WriteData_AD9959(RDW_ADD,4,RDW_DATA,1);//RDW address 0x08.�趨RDW
		
		WriteData_AD9959(FDW_ADD,4,RDW_DATA,1);
		
		LSRR_DATA[0]=100;
		LSRR_DATA[1]=100;
		
		WriteData_AD9959(LSRR_ADD,2,LSRR_DATA,1);
}

void Amp_Sweep(u8 Channel, u16 S_Amp,  u16 E_Amp)
{
	u8 ACR_DATA[4] = {0x00,0x00,0x00,0x00};//default Value = 0x--0000 Rest = 18.91/Iout 
	u32 temp;
	u8 CW1_DATA[4]   = {0x00,0x00,0x00,0x00};	//�м����
	u8 RDW_DATA[4]   = {0x00,0x00,0x00,0x00};	//�м����
	u8 FDW_DATA[4]   = {0x00,0x00,0x00,0x00};	//�м����
  u8 LSRR_DATA[2] =  {0x00,0x00};
  if(Channel==0)
  	WriteData_AD9959(CSR_ADD,1,CSR_DATA0,1);//���ƼĴ���д��CHxͨ��
	else if(Channel==1)
  	WriteData_AD9959(CSR_ADD,1,CSR_DATA1,1);//���ƼĴ���д��CHxͨ��
	else if(Channel==2)
  	WriteData_AD9959(CSR_ADD,1,CSR_DATA2,1);//���ƼĴ���д��CHxͨ��
	else if(Channel==3)
  	WriteData_AD9959(CSR_ADD,1,CSR_DATA3,1);//���ƼĴ���д��CHxͨ��
	
	CFR_DATA[0]=CFR_DATA[0] | (0x01<<6);  //ɨ��
	CFR_DATA[1]=CFR_DATA[1] | (0x01<<6);  //ɨ��ʹ��
	WriteData_AD9959(CFR_ADD,3,CFR_DATA,1);//CTW0 address 0x04.���CH0�趨Ƶ��
	
	 
	
	 
	ACR_DATA[2] = (u8)S_Amp;  //��λ����
	ACR_DATA[1] = (u8)(S_Amp>>8);  //��λ����
 
	WriteData_AD9959(ACR_ADD,3,ACR_DATA,1); 
	
	temp =(u32)(E_Amp<<22);
	CW1_DATA[3] = (u8) temp;  //��λ����
	CW1_DATA[2] = (u8)(temp>>8);  //��λ����
	CW1_DATA[1] = (u8)(temp>>16);  //��λ����
	CW1_DATA[0] = (u8)(temp>>24); //��λ����
	WriteData_AD9959(CW1_ADD,4,CW1_DATA,1);//CTW0 address 0x04.���CH0�趨Ƶ��
	
	 
	temp =(u32)(0x10<<22);
	RDW_DATA[3] = (u8) temp;  //��λ����
	RDW_DATA[2] = (u8)(temp>>8);  //��λ����
	RDW_DATA[1] = (u8)(temp>>16);  //��λ����
	RDW_DATA[0] = (u8)(temp>>24); //��λ����
	
	WriteData_AD9959(RDW_ADD,4,RDW_DATA,1);//RDW address 0x08.�趨RDW
	
	temp =(u32)(0x10<<22);
	FDW_DATA[3] = (u8) temp;  //��λ����
	FDW_DATA[2] = (u8)(temp>>8);  //��λ����
	FDW_DATA[1] = (u8)(temp>>16);  //��λ����
	FDW_DATA[0] = (u8)(temp>>24); //��λ����
	WriteData_AD9959(FDW_ADD,4,FDW_DATA,1);
	
	LSRR_DATA[0]=80;
	LSRR_DATA[1]=80;
	WriteData_AD9959(LSRR_ADD,2,LSRR_DATA,1);
}


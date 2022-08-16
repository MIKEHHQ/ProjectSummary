#include "stm32f10x.h"
#include "systemconfig.h" 
#include "common.h"
#include "ad9959.h"
#include "TM1637.h" 
#include "key.h" 
#include "led.h"
//#define chazhi 9

u8 keyc;
extern u8 start_Rec;
extern u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
unsigned char RegisterData[4] = {0,0,0,0};
u16 ampcode1[chazhi]={537,575,639,703,767,831,895,959,1023,959,895,831,767,703,639,575,537};
u16 ampcode0[chazhi]={500,463,415,367,319,271,223,175,127,175,223,271,319,367,415,463,500};

void Delay_us(u32 us);

u8 volatile code[4*numcnt];
u16 volatile amcode[4*numcnt*chazhi];
u8 flag=0;
u8 cnt=0;

u8 previouskey=0;
u8 nums[numcnt]={'E','F',0,0,0,0};

void numcode(void);
void code2am(void);
int main(void)
{	
	 u8 n=0;
//	u8 send=1;
 u32 Fre_module[16] ;
 u16 Amp_module[16] ;
 u16 Pha_module[16] ;
 u8 i,Type;
//u8 AFP_Select;
//u8 Modul_Level;
//u8 RU_RD;
//u8 PPC;
  Type=0;  //输出方式：0：无调制 1：调频 2：调幅 3：调相 4：扫频 5：扫幅 6：扫相
  SystemConfiguration();		    //系统初始化
  for (i=0;i<16;i++)
	{
	Fre_module[i]=0;
	Amp_module[i]=0;
	Pha_module[i]=0;	
	}
	Init_AD9959();
//  AFP_Select=0x02; //0:No modulation 1:调幅 2：调频 3：调相
 // Modul_Level=0; // 0：2 level 1: 4 level 2: 8 level 3: 16 level
 // RU_RD=0;
	while(1)
	{
		
		keyc=Key_Scan();
		if(keyc == '*' )
			{
				Write_frequence(3,20000000);
				LED0=!LED0;
			}
			if(keyc == '#')
			{
				Write_frequence(3,23000000);
				LED0=!LED0;
			}
			if(keyc == 'D')
			{
				Write_frequence(3,25000000);
				LED0=!LED0;
			}
			if(USART_RX_STA)
			{
				TM1637_display( USART_RX_BUF[1], USART_RX_BUF[2],USART_RX_BUF[3],USART_RX_BUF[4],0);
			
			}
			if(!USART_RX_STA)
			{
				TM1637_display( 0,0,0,0,0);
			}
		}
	if (Type==1)    //调频输出
	{
  Fre_module[0]=10000000;
	Fre_module[1]=11000000;
	Fre_module[2]=12000000;
	Fre_module[3]=13000000;
	Fre_Modulation(1, 4, Fre_module);  //参数1：通道选择，数值写：0或1或2或3 参数2： 调制级，数值写：2或4或8或16
	 
	while(1)
	{
	   
	    PS2=0;
		  PS3=0;
	   	Delay_us(15);	   //延时 300ms
      PS2=0;
		  PS3=1;
	    Delay_us(15);	
		  PS2=1;
		  PS3=0;
	    Delay_us(15);	
		  PS2=1;
		  PS3=1;
		
	    Delay_us(15);	
	  }
	}
	else if (Type==2)
	{
  Amp_module[0]=1023; //   0~1023(对应：0~最大电平)
	Amp_module[1]=512;
	Amp_module[2]=256;
	Amp_module[3]=0;
	
  Amp_Modulation(1, 4, Amp_module);  //参数1：通道选择，数值写：0或1或2或3 参数2： 调制级，数值写：2或4或8或16
	 
	while(1)
	{
	   
	    PS2=0;
		  PS3=0;
	   //	Delay_us(15);	   //延时 300ms
     // PS2=0;
		  PS3=1;
	    //Delay_us(15);	
		  PS2=1;
		 PS3=0;
		 // PS3=0;
	  //  Delay_us(15);	
		  //PS2=1;
		  //PS3=0;
		 //  PS2=1;
	   // Delay_us(15);	
	  }
	}
	
	else if (Type==3)
	{
  Pha_module[0]=0; // 0~16383(对应角度：0°~360°)
	Pha_module[1]=4095;
	Pha_module[2]=8191;
	Pha_module[3]=16383;
	Pha_Modulation(1, 4, Pha_module);  //参数1：通道选择，数值写：0或1或2或3 参数2： 调制级，数值写：2或4或8或16
	 
	while(1)
	{
	   
	    PS2=0;
		  PS3=0;
	   	Delay_us(15);	   //延时 300ms
      PS2=0;
		  PS3=1;
	    Delay_us(15);	
		  PS2=1;
		  PS3=0;
	    Delay_us(15);	
		  PS2=1;
		  PS3=1;
	    Delay_us(15);	
	  }
	}
	
	else if (Type==4)
	{
   
	Fre_Sweep(1, 10000000, 15000000);  //参数1：通道选择，数值写：0或1或2或3 参数2： 调制级，数值写：2或4或8或16
	 
	while(1)
	{
	   
	    PS1=0;
	
     	Delay_us(100);	   //延时 300ms
      
		  PS1=1;
	    Delay_us(100);	
		 
	}
	}
	
	
	else if (Type==5)
	{
   
 	Amp_Sweep(1, 512, 1000);  //参数1：通道选择，数值写：0或1或2或3 参数2： 调制级，数值写：2或4或8或16
	 
	while(1)
	{
	   
	    PS1=1;
	   	Delay_us(120);	   //延时 300ms
  	  PS1=0;
	    Delay_us(120);	
		 
	}
	}
}
 
void numcode()
{
	u8 a=0;
	//u8 cnt=0;
	for(a=0;a<numcnt;a++)
	{
		//for(s=0;s<4;s++)
		//{
		
			switch(nums[a])
			{
				case 0:{
					code[0]=0;
					code[4*a+1]=0;
					code[4*a+2]=0;
					code[4*a+3]=0;
				}break;
				case 1:{
					code[4*a]=0;
					code[4*a+1]=0;
					code[4*a+2]=0;
					code[4*a+3]=1;
				}break;
				case 2:{
					code[4*a]=0;
					code[4*a+1]=0;
					code[4*a+2]=1;
					code[4*a+3]=0;
				}break;
				case 3:{
					code[4*a]=0;
					code[4*a+1]=0;
					code[4*a+2]=1;
					code[4*a+3]=1;
				}break;
				case 4:{
					code[4*a]=0;
					code[4*a+1]=1;
					code[4*a+2]=0;
					code[4*a+3]=0;
				}break;
				case 5:{
					code[4*a]=0;
					code[4*a+1]=1;
					code[4*a+2]=0;
					code[4*a+3]=1;
				}break;
				case 6:{
					code[4*a]=0;
					code[4*a+1]=1;
					code[4*a+2]=1;
					code[4*a+3]=0;
				}break;
				case 7:{
					code[4*a]=0;
					code[4*a+1]=1;
					code[4*a+2]=1;
					code[4*a+3]=1;
				}break;	
				case 8:{
					code[4*a]=1;
					code[4*a+1]=0;
					code[4*a+2]=0;
					code[4*a+3]=0;
				}break;
				case 9:{
					code[4*a]=1;
					code[4*a+1]=0;
					code[4*a+2]=0;
					code[4*a+3]=1;
				}break;	
				case 'E':{
				code[4*a]=1;
					code[4*a+1]=1;
					code[4*a+2]=1;
					code[4*a+3]=0;
				}break;	
				case 'F':{
				code[4*a]=1;
					code[4*a+1]=1;
					code[4*a+2]=1;
					code[4*a+3]=1;
				}break;	
				default:break;
			}
			cnt++;	
		//}
	}

}

void code2am(void)
{
	u16 p=0,l=0;
	for(p=0,l=0;p<numcnt*4*chazhi && l<numcnt*4;p+=chazhi,l++)
	{
		if(code[l]==1)
		{
			
				amcode[p]=ampcode1[p];
			amcode[p+1]=ampcode1[p+1];
			amcode[p+2]=ampcode1[p+2];
			amcode[p+3]=ampcode1[p+3];
			amcode[p+4]=ampcode1[p+4];
			amcode[p+5]=ampcode1[p+5];
			amcode[p+6]=ampcode1[p+6];
			amcode[p+7]=ampcode1[p+7];
			amcode[p+8]=ampcode1[p+8];
			amcode[p+9]=ampcode1[p+9];
			amcode[p+10]=ampcode1[p+10];
			amcode[p+11]=ampcode1[p+11];
			amcode[p+12]=ampcode1[p+12];
			amcode[p+13]=ampcode1[p+13];
			amcode[p+14]=ampcode1[p+14];
			amcode[p+15]=ampcode1[p+15];
			amcode[p+16]=ampcode1[p+16];
			//amcode[p+17]=576;
//							amcode[p]=511;
//			amcode[p+1]=575;
//			amcode[p+2]=511;
//			amcode[p+3]=639;
//			amcode[p+4]=703;
//			amcode[p+5]=767;
//			amcode[p+6]=639;
//			amcode[p+7]=895;
//			amcode[p+9]=1023;
//			amcode[p+11]=895;
//			amcode[p+13]=767;
//			amcode[p+15]=639;
//			amcode[p+17]=576;
		
		}
		else if(code[l]==0)
		{
			
//				amcode[p]=464;
//			amcode[p+1]=415;
//			amcode[p+2]=319;
//			amcode[p+3]=223;
//			amcode[p+4]=127;
//			amcode[p+5]=223;
//			amcode[p+6]=319;
//			amcode[p+7]=415;
//			amcode[p+8]=464;
				amcode[p]=ampcode0[p];
			amcode[p+1]=ampcode0[p+1];
			amcode[p+2]=ampcode0[p+2];
			amcode[p+3]=ampcode0[p+3];
			amcode[p+4]=ampcode0[p+4];
			amcode[p+5]=ampcode0[p+5];
			amcode[p+6]=ampcode0[p+6];
			amcode[p+7]=ampcode0[p+7];
			amcode[p+8]=ampcode0[p+8];
			amcode[p+9]=ampcode0[p+9];
			amcode[p+10]=ampcode0[p+10];
			amcode[p+11]=ampcode0[p+11];
			amcode[p+12]=ampcode0[p+12];
			amcode[p+13]=ampcode0[p+13];
			amcode[p+14]=ampcode0[p+14];
			amcode[p+15]=ampcode0[p+15];
			amcode[p+16]=ampcode0[p+16];
		}
	
	}


}

 

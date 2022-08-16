#include "stm32f10x.h"
#include "stdio.h"
#include "common.h"

static u8  fac_us=0; //us��ʱ������
static u16 fac_ms=0; //ms��ʱ������


/*******************************************************************************
* ��������       :  
* ��������       : Printf֧�ִ���   printf("����a��ֵ��: %d\r\n\r\n",a);
* ��ڲ���       : ��
* ���ڲ���       : ��
*******************************************************************************/
#if 1
#pragma import(__use_no_semihosting)             
                
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
 
_sys_exit(int x) //����_sys_exit()�Ա���ʹ�ð�����ģʽ   
{ 
	x = x; 
} 

int fputc(int ch, FILE *f)//�ض���fputc���� 
{      
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET); 
    USART_SendData(USART1,(uint8_t)ch);   
	return ch;
}
#endif 

/*******************************************************************************
* ��������       : Delay_Init
* ��������       : ��ʱ��ʼ������
* ��ڲ���       : ��
* ���ڲ���       : ��
*******************************************************************************/
void Delay_Init(void)
{
	SysTick->CTRL&=0xfffffffb;//bit2���,ѡ���ⲿʱ��  HCLK/8
	fac_us=9;		    
	fac_ms=(u16)fac_us*1000;
}								    

/*******************************************************************************
* ��������       : DelayMs
* ��������       : ��ʱ������72M������ms<=1864
* ��ڲ���       : ms ��ʱ��С
* ���ڲ���       : ��
*******************************************************************************/
void Delay_ms(u16 ms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=(u32)ms*fac_ms; //ʱ�����(SysTick->LOADΪ24bit)
	SysTick->VAL =0x00;            //��ռ�����
	SysTick->CTRL=0x01 ;           //��ʼ����  
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16))); //�ȴ�ʱ�䵽��   
	SysTick->CTRL=0x00;                //�رռ�����
	SysTick->VAL =0X00;                //��ռ�����	  	    
}   

/*******************************************************************************
* ��������       : DelayUs
* ��������       : ��ʱ������72M������ms<=1864000
* ��ڲ���       : us ��ʱ��С
* ���ڲ���       : ��
*******************************************************************************/
void Delay_us(u32 us)
{		
	u32 temp;	    	 
	SysTick->LOAD=us*fac_us; //ʱ�����	  		 
	SysTick->VAL=0x00;        //��ռ�����
	SysTick->CTRL=0x01 ;      //��ʼ���� 	 
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16))); //�ȴ�ʱ�䵽��   
	SysTick->CTRL=0x00;                //�رռ�����
	SysTick->VAL =0X00;                //��ռ�����	 
}







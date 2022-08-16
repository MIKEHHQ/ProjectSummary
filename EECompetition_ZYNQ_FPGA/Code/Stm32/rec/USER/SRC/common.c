#include "stm32f10x.h"
#include "stdio.h"
#include "common.h"

static u8  fac_us=0; //us延时倍乘数
static u16 fac_ms=0; //ms延时倍乘数


/*******************************************************************************
* 函数名称       :  
* 功能描述       : Printf支持代码   printf("变量a的值是: %d\r\n\r\n",a);
* 入口参数       : 无
* 出口参数       : 无
*******************************************************************************/
#if 1
#pragma import(__use_no_semihosting)             
                
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
 
_sys_exit(int x) //定义_sys_exit()以避免使用半主机模式   
{ 
	x = x; 
} 

int fputc(int ch, FILE *f)//重定义fputc函数 
{      
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET); 
    USART_SendData(USART1,(uint8_t)ch);   
	return ch;
}
#endif 

/*******************************************************************************
* 函数名称       : Delay_Init
* 功能描述       : 延时初始化函数
* 入口参数       : 无
* 出口参数       : 无
*******************************************************************************/
void Delay_Init(void)
{
	SysTick->CTRL&=0xfffffffb;//bit2清空,选择外部时钟  HCLK/8
	fac_us=9;		    
	fac_ms=(u16)fac_us*1000;
}								    

/*******************************************************************************
* 函数名称       : DelayMs
* 功能描述       : 延时函数，72M条件下ms<=1864
* 入口参数       : ms 延时大小
* 出口参数       : 无
*******************************************************************************/
void Delay_ms(u16 ms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=(u32)ms*fac_ms; //时间加载(SysTick->LOAD为24bit)
	SysTick->VAL =0x00;            //清空计数器
	SysTick->CTRL=0x01 ;           //开始倒数  
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16))); //等待时间到达   
	SysTick->CTRL=0x00;                //关闭计数器
	SysTick->VAL =0X00;                //清空计数器	  	    
}   

/*******************************************************************************
* 函数名称       : DelayUs
* 功能描述       : 延时函数，72M条件下ms<=1864000
* 入口参数       : us 延时大小
* 出口参数       : 无
*******************************************************************************/
void Delay_us(u32 us)
{		
	u32 temp;	    	 
	SysTick->LOAD=us*fac_us; //时间加载	  		 
	SysTick->VAL=0x00;        //清空计数器
	SysTick->CTRL=0x01 ;      //开始倒数 	 
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16))); //等待时间到达   
	SysTick->CTRL=0x00;                //关闭计数器
	SysTick->VAL =0X00;                //清空计数器	 
}







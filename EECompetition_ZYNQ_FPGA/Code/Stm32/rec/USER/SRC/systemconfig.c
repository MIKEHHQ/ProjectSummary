
#include  <stm32f10x.h>
#include "systemconfig.h"


/*******************************************************************************
* 函数名称       : RCC_Configuration
* 功能描述       : 配置外设时钟.
* 入口参数       : 无
* 出口参数       : 无
*******************************************************************************/
void RCC_Configuration(void)
{
 

	//使能GPIO时钟
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE); 

	//使能复用功能时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	//USART1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	//延时初始化
	Delay_Init(); 
					 
}

/*******************************************************************************
* 函数名称       : GPIO_Configuration
* 功能描述       : 配置项目中所有用到的GPIO
* 入口参数       : 无
* 出口参数       : 无
*******************************************************************************/

void Init_AD9959_Gpio(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);//使能SWJ，禁止JTAG 即能用PB3 PB4 PA15做普通IO， PA13 PA14被SW占用
//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_NoJTRST , ENABLE);//使能SWJ，使能JTAG，即PB4 做普通IO，但JTAG没有复位。
//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable , ENABLE);//禁止SWJ，禁止 JTAG，即PB3 PB4 PA13 PA14 PA15做普通IO，但不用采用SW或JTAG进行调试
	
	
 	GPIO_InitStructure.GPIO_Pin =0xffff; // GPIO_Pin_15|GPIO_Pin_14|GPIO_Pin_13|GPIO_Pin_12|GPIO_Pin_9|GPIO_Pin_8|GPIO_Pin_7;  //LED1,LED2
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin =0xffff; // GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		  //key
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}


void SystemConfiguration(void)
{	
	RCC_Configuration(); 
  Init_AD9959_Gpio();
	led_init();
	TM_Init();
	Key_Init();
	uart_init(115200);
	TIM3_Int_Init(1999,7199);
 
}




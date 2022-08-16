
#include  <stm32f10x.h>
#include "systemconfig.h"


/*******************************************************************************
* ��������       : RCC_Configuration
* ��������       : ��������ʱ��.
* ��ڲ���       : ��
* ���ڲ���       : ��
*******************************************************************************/
void RCC_Configuration(void)
{
 

	//ʹ��GPIOʱ��
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE); 

	//ʹ�ܸ��ù���ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	//USART1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	//��ʱ��ʼ��
	Delay_Init(); 
					 
}

/*******************************************************************************
* ��������       : GPIO_Configuration
* ��������       : ������Ŀ�������õ���GPIO
* ��ڲ���       : ��
* ���ڲ���       : ��
*******************************************************************************/

void Init_AD9959_Gpio(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);//ʹ��SWJ����ֹJTAG ������PB3 PB4 PA15����ͨIO�� PA13 PA14��SWռ��
//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_NoJTRST , ENABLE);//ʹ��SWJ��ʹ��JTAG����PB4 ����ͨIO����JTAGû�и�λ��
//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable , ENABLE);//��ֹSWJ����ֹ JTAG����PB3 PB4 PA13 PA14 PA15����ͨIO�������ò���SW��JTAG���е���
	
	
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




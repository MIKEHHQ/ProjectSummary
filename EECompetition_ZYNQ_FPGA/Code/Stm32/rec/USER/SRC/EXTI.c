//#include "EXTI.h"

//void Exti_Init(void)
//{
//	GPIO_InitTypeDef GPIO_InitStructure;
// 	EXTI_InitTypeDef EXTI_InitStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//使能PORTA,PORTE时钟

//	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;//KEY0,时钟
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //设置成上拉输入
// 	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOE2,3,4

//	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;//KEY1，数据
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //设置成上拉输入
// 	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOE2,3,4
//	
//	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//中断使能
//	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0);	//将IO口与中断线连接起来
//	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
//	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
//	
//	EXTI_Init(&EXTI_InitStructure);
//	
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;
//	NVIC_Init(&NVIC_InitStructure);
//}


//void EXTI0_IRQHandler(void)
//{
//	static u8 mydata[48];
//	static u8 datain=0;
//	static u8 mycnt=0;
//	Delay_ms(10);
//	if(KEY0 == 1)
//	{
//		mycnt+=1;
//		datain=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1);
//		mydata[mycnt]=datain;
//	}
//	EXTI_ClearITPendingBit(EXTI_Line0);
//}

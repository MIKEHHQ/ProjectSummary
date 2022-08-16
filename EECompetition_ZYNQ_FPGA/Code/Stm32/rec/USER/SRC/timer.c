#include "timer.h"
#include "led.h"
#include "AD9959.h"
#include "uart.h"
#include "TM1637.h"
//通用定时器3中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!

 //u8 keyc =0;
 extern u8 volatile code[4*numcnt];
 extern u16 volatile amcode[4*numcnt*chazhi];
 extern u8 flag;
 extern  u16 USART_RX_STA;       //接收状态标记	  

void TIM3_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能
	
	//定时器TIM3初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器


	TIM_Cmd(TIM3, ENABLE);  //使能TIMx					 
}
//定时器3中断服务程序
void TIM3_IRQHandler(void)   //TIM3中断
{
	static u16 cnt2 = 0;
	
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
		{
			if(USART_RX_STA)
			{
				cnt2++;
			}
			if(cnt2==25)
			{
				TM1637_display(0,0,0,0,0);
				cnt2=0;
				USART_RX_STA=0;
			}
			//LED0=!LED0;
//			if(flag)
//			{
//				Write_Amplitude(0,amcode[cnt]);
//				Delay_us(100);
//				cnt++;
//			}

//			if(flag)
//			{
//					if(code[cnt]==1)
//				{
//					Write_Amplitude(0,1023);
//					IO_Update();
//					Delay_ms(200);
//				
//				}else
//				{
//					Write_Amplitude(0,512);
//					IO_Update();
//					Delay_ms(200);
//				}
//			}
//			if(cnt>=chazhi*4*numcnt)
//			{
//				cnt=0;
//			}
			
			
//			LED0=!LED0;
//			if(flag)
//			{
//				if(code[cnt]==0)
//				{
//					Dac1_Set_Vol(1000);
//				}
//				else
//				{
//					Dac1_Set_Vol(2000);
//				}
//			}
			
//			Dac1_Set_Vol(code[cnt]);
//			cnt
			//keyc= Key_Scan();
			//USART_SendData(USART1, keyc);//向串口1发送数据
			//while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
		//LED1=!LED1;
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  //清除TIMx更新中断标志 
		}
}













#include "timer.h"
#include "led.h"
#include "AD9959.h"
#include "uart.h"
#include "TM1637.h"
//ͨ�ö�ʱ��3�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!

 //u8 keyc =0;
 extern u8 volatile code[4*numcnt];
 extern u16 volatile amcode[4*numcnt*chazhi];
 extern u8 flag;
 extern  u16 USART_RX_STA;       //����״̬���	  

void TIM3_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��
	
	//��ʱ��TIM3��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�

	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���


	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx					 
}
//��ʱ��3�жϷ������
void TIM3_IRQHandler(void)   //TIM3�ж�
{
	static u16 cnt2 = 0;
	
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //���TIM3�����жϷ������
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
			//USART_SendData(USART1, keyc);//�򴮿�1��������
			//while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
		//LED1=!LED1;
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  //���TIMx�����жϱ�־ 
		}
}













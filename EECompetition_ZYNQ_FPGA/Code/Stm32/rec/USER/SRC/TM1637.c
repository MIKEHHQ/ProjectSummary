#include "TM1637.h"

unsigned tab[] = 
{
        0x3F,/*0*/
        0x06,/*1*/
        0x5B,/*2*/
        0x4F,/*3*/
        0x66,/*4*/
        0x6D,/*5*/
        0x7D,/*6*/
        0x07,/*7*/
        0x7F,/*8*/
        0x6F,/*9*/
        0x77,/*10 A*/
        0x7C,/*11 b*/
        0x58,/*12 c*/
        0x5E,/*13 d*/
        0x79,/*14 E*/
        0x71,/*15 F*/
        0x76,/*16 H*/
        0x38,/*17 L*/
        0x54,/*18 n*/
        0x73,/*19 P*/
        0x3E,/*20 U*/
	0x00,/*21 黑屏*/
}; 
void TM_Init()
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA, ENABLE);	 //使能PB,PE端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;				// SCLK 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				 //IO
	 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
}

void TM1637_start(void)
{
	 CLK=1;
	 DIO=1;
	 Delay_us(2);
	 DIO=0;
}


//IIC应答
void TM1637_ack(void)
{
	uchar i;
	CLK=0;
	Delay_us(5);
	 //DIO=1;    
	while(DIO==1&&(i<250))i++;
	CLK=1;
	Delay_us(2);
	CLK=0;
}

//IIC停止
void TM1637_stop(void)
{
	 CLK=0;
	 Delay_us(2);
	 DIO=0;
	 Delay_us(2);
	 CLK=1;
	 Delay_us(2);
	 DIO=1;
	 Delay_us(2);
}

//写数据函数
void TM1637_Write(unsigned char DATA)   
{
	unsigned char i;   
	for(i=0;i<8;i++)        
	{
		CLK=0;     
		if(DATA & 0x01)
			DIO=1;
		else DIO=0;
	 	Delay_us(3);
		DATA=DATA>>1;      
		CLK=1;
	 	Delay_us(3);
	}  
	//TM1637_ack();
}


 
//按顺序显示
void TM1637_display(uchar a,uchar b,uchar c,uchar d,uchar h)
{

	TM1637_start();
	TM1637_Write(0x40);//写数据+自动地址加1+普通模式
	TM1637_ack();
	TM1637_stop(); 
	TM1637_start();
	TM1637_Write(0xc0);//设置显示首地址即第一个LED
	TM1637_ack();

	TM1637_Write(tab[a]);
	TM1637_ack();
	TM1637_Write(tab[b]|h<<7);//h为1时显示时钟中间的两点
	TM1637_ack();
	TM1637_Write(tab[c]);
	TM1637_ack();
	TM1637_Write(tab[d]);
	TM1637_ack();

	TM1637_stop(); 
	TM1637_start();
	TM1637_Write(0x89);//开显示，2/16亮度
	TM1637_ack();
	TM1637_stop();
}


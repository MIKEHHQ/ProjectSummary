#ifndef _TM1637_H
#define _TM1637_H
#include "sys.h"
#include "common.h"
//#include "delay.h"
//#include "key.h"
#define uint unsigned int 
#define uchar unsigned char
#define CLK  PBout(15)  //定义模拟IIC总线的时钟线
#define DIO   PAout(8) //定义模拟IIC总线的数据线
  

 
void TM_Init(void);
//IIC开始
void TM1637_start(void);


//IIC应答
void TM1637_ack(void);
//IIC停止
void TM1637_stop(void);

//写数据函数
void TM1637_Write(unsigned char DATA);

 
//按顺序显示
void TM1637_display(uchar a,uchar b,uchar c,uchar d,uchar h);

#endif


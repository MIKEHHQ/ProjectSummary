#ifndef _TM1637_H
#define _TM1637_H
#include "sys.h"
#include "common.h"
//#include "delay.h"
//#include "key.h"
#define uint unsigned int 
#define uchar unsigned char
#define CLK  PBout(15)  //����ģ��IIC���ߵ�ʱ����
#define DIO   PAout(8) //����ģ��IIC���ߵ�������
  

 
void TM_Init(void);
//IIC��ʼ
void TM1637_start(void);


//IICӦ��
void TM1637_ack(void);
//IICֹͣ
void TM1637_stop(void);

//д���ݺ���
void TM1637_Write(unsigned char DATA);

 
//��˳����ʾ
void TM1637_display(uchar a,uchar b,uchar c,uchar d,uchar h);

#endif


#ifndef __COMMON_H
#define __COMMON_H
#include "stm32f10x.h"
#include "bitband.h"


//#define  DataAOut(x)  GPIOA->ODR =x;
//#define  DataAIn      GPIOA->IDR ;
#define chazhi 17
#define numcnt 6
#define  DataBOut(x)  GPIOB->ODR =x;
#define  DataBIn      GPIOB->IDR ;
void Delay_Init(void);
void Delay_ms(u16 ms);
void Delay_us(u32 us);


 
#endif





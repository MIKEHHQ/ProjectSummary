#ifndef __SYSTEMCONFIG_H
#define __SYSTEMCONFIG_H
#include "stm32f10x.h"
#include "led.h"
#include "timer.h"
#include "TM1637.h"
#include "key.h"
#include "uart.h"

void RCC_Configuration(void);

void GPIO_Configuration(void);

void NVIC_Configuration(void);

void SystemConfiguration(void);


 

//void Delay_ms(u16 ms);

//void Delay_Init(void);


#endif


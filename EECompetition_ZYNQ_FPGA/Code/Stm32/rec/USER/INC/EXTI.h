#ifndef _EXTI_H
#define _EXTI_H
#include "common.h"

#define KEY0  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)//��ȡ����0


void Exti_Init(void);



#endif
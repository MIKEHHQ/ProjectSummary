#ifndef _KEY_H
#define _KEY_H	 

#include <stm32f10x.h>
//#include "usart.h"
#include "sys.h"


#define uint unsigned int 
#define uchar unsigned char

void Key_Init(void);
int  Key_Scan(void);
void Key_Test(void) ;

#endif


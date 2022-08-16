#ifndef _AD9959_H_
#define _AD9959_H_

#include "bitband.h"
#include "stdio.h"
#include "stm32f10x.h"
//AD9959寄存器地址定义
#define CSR_ADD   0x00   //CSR 通道选择寄存器
#define FR1_ADD   0x01   //FR1 功能寄存器1
#define FR2_ADD   0x02   //FR2 功能寄存器2
#define CFR_ADD   0x03   //CFR 通道功能寄存器
#define CFTW0_ADD 0x04   //CTW0 通道频率转换字寄存器
#define CPOW0_ADD 0x05   //CPW0 通道相位转换字寄存器
#define ACR_ADD   0x06   //ACR 幅度控制寄存器
#define LSRR_ADD  0x07   //LSR 通道线性扫描寄存器
#define RDW_ADD   0x08   //RDW 通道线性向上扫描寄存器
#define FDW_ADD   0x09   //FDW 通道线性向下扫描寄存器
#define CW1_ADD   0x0A   //CW1 通道字寄存器
#define CW2_ADD   0x0B   //CW2 通道字寄存器
#define CW3_ADD   0x0C   //CW3 通道字寄存器
#define CW4_ADD   0x0D   //CW4 通道字寄存器
#define CW5_ADD   0x0E   //CW5 通道字寄存器
#define CW6_ADD   0x0F   //CW6 通道字寄存器
#define CW7_ADD   0x10   //CW7 通道字寄存器
#define CW8_ADD   0x11   //CW8 通道字寄存器
#define CW9_ADD   0x12   //CW9 通道字寄存器
#define CW10_ADD   0x13   //CW10 通道字寄存器
#define CW11_ADD   0x14   //CW11 通道字寄存器
#define CW12_ADD   0x15   //CW12 通道字寄存器
#define CW13_ADD   0x16   //CW13 通道字寄存器
#define CW14_ADD   0x17   //CW14 通道字寄存器
#define CW15_ADD   0x18   //CW15 通道字寄存器


//AD9959管脚宏定义
#define  PS0       BIT_ADDR(GPIOA_ODR_Addr,0)
#define  PS1       BIT_ADDR(GPIOA_ODR_Addr,1)
#define  PS2       BIT_ADDR(GPIOA_ODR_Addr,2)
#define  PS3       BIT_ADDR(GPIOA_ODR_Addr,3)
#define  SDIO0		 BIT_ADDR(GPIOA_ODR_Addr,4)
#define  SDIO1		 BIT_ADDR(GPIOA_ODR_Addr,5)
#define  SDIO2		 BIT_ADDR(GPIOA_ODR_Addr,6)
#define  SDIO3		 BIT_ADDR(GPIOA_ODR_Addr,7)
#define  UPDATE	   BIT_ADDR(GPIOA_ODR_Addr,11)
#define  CS			   BIT_ADDR(GPIOA_ODR_Addr,12)
//#define  SCLK		   BIT_ADDR(GPIOA_ODR_Addr,10)
//#define  Reset		 BIT_ADDR(GPIOA_ODR_Addr,9)
//#define  PWRD			 BIT_ADDR(GPIOA_ODR_Addr,8)
#define  SCLK		   BIT_ADDR(GPIOB_ODR_Addr,14)
#define  Reset		 BIT_ADDR(GPIOB_ODR_Addr,13)
#define  PWRD			 BIT_ADDR(GPIOB_ODR_Addr,12)
 
void IntReset(void);	  //AD9959复位
void IO_Update(void);   //AD9959更新数据
void Intserve(void);		   //IO口初始化
void WriteData_AD9959(u8 RegisterAddress, u8 NumberofRegisters, u8 *RegisterData,u8 temp);
void Init_AD9959(void);
void Write_frequence(u8 Channel,u32 Freq);
void Write_Amplitude(u8 Channel, u16 Ampli);
void Write_Phase(u8 Channel,u16 Phase);

void Fre_Modulation(u8 Channel, u8 Modul_Level,  u32 *Fre_Value);
void Amp_Modulation(u8 Channel, u8 Modul_Level,  u16 *Amp_Value);
void Pha_Modulation(u8 Channel, u8 Modul_Level,  u16 *Pha_Value);

void Fre_Sweep(u8 Channel, u32 S_Fre,  u32 E_Fre);
void Amp_Sweep(u8 Channel, u16 S_Amp,  u16 E_Amp);















#endif

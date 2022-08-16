#ifndef _AD9959_H_
#define _AD9959_H_

#include "bitband.h"
#include "stdio.h"
#include "stm32f10x.h"
//AD9959�Ĵ�����ַ����
#define CSR_ADD   0x00   //CSR ͨ��ѡ��Ĵ���
#define FR1_ADD   0x01   //FR1 ���ܼĴ���1
#define FR2_ADD   0x02   //FR2 ���ܼĴ���2
#define CFR_ADD   0x03   //CFR ͨ�����ܼĴ���
#define CFTW0_ADD 0x04   //CTW0 ͨ��Ƶ��ת���ּĴ���
#define CPOW0_ADD 0x05   //CPW0 ͨ����λת���ּĴ���
#define ACR_ADD   0x06   //ACR ���ȿ��ƼĴ���
#define LSRR_ADD  0x07   //LSR ͨ������ɨ��Ĵ���
#define RDW_ADD   0x08   //RDW ͨ����������ɨ��Ĵ���
#define FDW_ADD   0x09   //FDW ͨ����������ɨ��Ĵ���
#define CW1_ADD   0x0A   //CW1 ͨ���ּĴ���
#define CW2_ADD   0x0B   //CW2 ͨ���ּĴ���
#define CW3_ADD   0x0C   //CW3 ͨ���ּĴ���
#define CW4_ADD   0x0D   //CW4 ͨ���ּĴ���
#define CW5_ADD   0x0E   //CW5 ͨ���ּĴ���
#define CW6_ADD   0x0F   //CW6 ͨ���ּĴ���
#define CW7_ADD   0x10   //CW7 ͨ���ּĴ���
#define CW8_ADD   0x11   //CW8 ͨ���ּĴ���
#define CW9_ADD   0x12   //CW9 ͨ���ּĴ���
#define CW10_ADD   0x13   //CW10 ͨ���ּĴ���
#define CW11_ADD   0x14   //CW11 ͨ���ּĴ���
#define CW12_ADD   0x15   //CW12 ͨ���ּĴ���
#define CW13_ADD   0x16   //CW13 ͨ���ּĴ���
#define CW14_ADD   0x17   //CW14 ͨ���ּĴ���
#define CW15_ADD   0x18   //CW15 ͨ���ּĴ���


//AD9959�ܽź궨��
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
 
void IntReset(void);	  //AD9959��λ
void IO_Update(void);   //AD9959��������
void Intserve(void);		   //IO�ڳ�ʼ��
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

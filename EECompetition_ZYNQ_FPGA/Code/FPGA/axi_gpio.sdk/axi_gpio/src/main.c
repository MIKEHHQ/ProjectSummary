//****************************************Copyright (c)***********************************//
//原子哥在线教学平台：www.yuanzige.com
//技术支持：www.openedv.com
//淘宝店铺：http://openedv.taobao.com
//关注微信公众平台微信号："正点原子"，免费获取ZYNQ & FPGA & STM32 & LINUX资料。
//版权所有，盗版必究。
//Copyright(C) 正点原子 2018-2028
//All rights reserved
//----------------------------------------------------------------------------------------
// File name:           main.c
// Last modified Date:  2019/10/14 17:01:36
// Last Version:        V1.1
// Descriptions:        调用AXI_GPIO IP核，使用中断机制，实现PL按键控制PS端LED
//----------------------------------------------------------------------------------------
// Created by:          正点原子
// Created date:        2019/10/14 17:01:36
// Version:             V1.0
// Descriptions:        The original version
//
//----------------------------------------------------------------------------------------
//****************************************************************************************//

#include "stdio.h"
#include "xparameters.h"
#include "xgpiops.h"
#include "xgpio.h"
#include "xscugic.h"
#include "xil_exception.h"
#include "xil_printf.h"
#include "sleep.h"

//宏定义
#define SCUGIC_ID	XPAR_SCUGIC_0_DEVICE_ID		//中断控制器 ID
#define GPIOPS_ID   XPAR_XGPIOPS_0_DEVICE_ID   	//PS端  GPIO器件 ID
#define AXI_GPIO_ID XPAR_AXI_GPIO_0_DEVICE_ID	//PL端  AXI GPIO器件 ID
#define GPIO_INT_ID XPAR_FABRIC_GPIO_0_VEC_ID	//PL端  AXI GPIO中断 ID

#define MIO_LED     0   						//PS LED 连接到 MIO0
#define KEY_CHANNEL 1							//PL按键使用AXI GPIO通道1
#define KEY_MASK    XGPIO_IR_CH1_MASK 			//通道1的位定义

//函数声明
void instance_init();							//初始化器件驱动
void axi_gpio_handler(void *CallbackRef);		//中断服务函数

//全局变量
XScuGic 		 scugic_inst;					//中断控制器  驱动实例
XScuGic_Config * scugic_cfg_ptr; 				//中断控制器  配置信息
XGpioPs          gpiops_inst;     				//PS端 GPIO 驱动实例
XGpioPs_Config * gpiops_cfg_ptr; 				//PS端 GPIO 配置信息
XGpio            axi_gpio_inst;					//PL端 AXI GPIO 驱动实例

int led_value = 1;								//LED显示状态

int main()
{
    printf("AXI GPIO INTERRUPT TEST!\n");

    //初始化各器件驱动
    instance_init();

    //配置PS GPIO
    XGpioPs_SetDirectionPin(&gpiops_inst, MIO_LED, 1);		//设置 PS GPIO 为输出
    XGpioPs_SetOutputEnablePin(&gpiops_inst, MIO_LED, 1);	//使能LED输出
    XGpioPs_WritePin(&gpiops_inst, MIO_LED, led_value);		//点亮LED

    //配置PL AXI GPIO
    XGpio_SetDataDirection(&axi_gpio_inst, KEY_CHANNEL, 1); //设置PL AXI GPIO通道1为输入
    XGpio_InterruptEnable(&axi_gpio_inst, KEY_MASK);		//使能通道1中断
    XGpio_InterruptGlobalEnable(&axi_gpio_inst);			//使能AXI GPIO全局中断

    //设置中断优先级和触发类型(高电平触发)
    XScuGic_SetPriorityTriggerType(&scugic_inst, GPIO_INT_ID, 0xA0, 0x1);
    //关联中断ID和中断处理函数
    XScuGic_Connect(&scugic_inst, GPIO_INT_ID, axi_gpio_handler, &axi_gpio_inst);
    //使能AXI GPIO中断
    XScuGic_Enable(&scugic_inst, GPIO_INT_ID);

    //设置并打开中断异常处理功能
    Xil_ExceptionInit();
    Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
    		(Xil_ExceptionHandler)XScuGic_InterruptHandler, &scugic_inst);
    Xil_ExceptionEnable();

    while(1);

    return 0;
}

//初始化各器件驱动
void instance_init()
{
    //初始化中断控制器驱动
	scugic_cfg_ptr = XScuGic_LookupConfig(SCUGIC_ID);
    XScuGic_CfgInitialize(&scugic_inst, scugic_cfg_ptr, scugic_cfg_ptr->CpuBaseAddress);

    //初始化PS端  GPIO驱动
    gpiops_cfg_ptr = XGpioPs_LookupConfig(GPIOPS_ID);
    XGpioPs_CfgInitialize(&gpiops_inst, gpiops_cfg_ptr, gpiops_cfg_ptr->BaseAddr);

    //初始化PL端  AXI GPIO驱动
    XGpio_Initialize(&axi_gpio_inst, AXI_GPIO_ID);
}

//PL端 AXI GPIO 中断服务(处理)函数
void axi_gpio_handler(void *CallbackRef)
{
	int key_value = 1;
	XGpio *GpioPtr = (XGpio *)CallbackRef;

	print("Interrupt Detected!\n");
	XGpio_InterruptDisable(GpioPtr, KEY_MASK);				//关闭AXI GPIO中断使能
	key_value = XGpio_DiscreteRead(GpioPtr, KEY_CHANNEL);	//读取按键数据
	if(key_value == 0){										//判断按键按下
		led_value = ~led_value;
		XGpioPs_WritePin(&gpiops_inst, MIO_LED, led_value);	//改变LED显示状态
	}
	sleep(1);												//延时1s,按键消抖
	XGpio_InterruptClear(GpioPtr, KEY_MASK);				//清除中断
	XGpio_InterruptEnable(GpioPtr, KEY_MASK);				//使能AXI GPIO中断
}

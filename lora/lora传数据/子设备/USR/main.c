/******************************************************************
 * 文件：main.c
 * 功能：主函数入口
 * 日期：2018-02-16
 * 作者：zx
 * 版本：Ver.1.0 | 最初版本
 * 官博：http://fengmeitech.club
 * Copyright (C) 2017 zx. All rights reserved.
*******************************************************************/
#include "stdio.h"
#include "Delay.h"
#include "uart.h"
#include "LED.h"
#include "SPIx.h"
#include "SX1278.h"
#include "OLED_I2C.h"
#include "bsp_i2c_gpio.h"

int main(void)
{
		u8 tx = 0;
	/*初始化各外设*/ 
    initSysTick();  
    initUART();           //波特率9600
    initSPIx(SPI2);
    initSX1278();
		i2c_CfgGpio();
		OLED_Init();
		OLED_Fill(0x00);/*清屏*/
    while (1)
    {
        transmitPackets(&tx,1);		
				++tx;
				OLED_ShowStr(0,0,(unsigned char *)tx,16);
				printf("hello,now is %d\n",tx);
        Delay_ms(1000);
    }
}


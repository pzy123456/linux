#ifndef __LCD_H_
#define __LCD_H_
/**********************************
当使用的是4位数据传输的时候定义，
使用8位取消这个定义
**********************************/
//#define LCD1602_4PINS

/**********************************
包含头文件
**********************************/
#include<reg51.h>

//---重定义关键词---//
#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint 
#define uint unsigned int
#endif

/**********************************
PIN口定义
**********************************/
#define LCD1602_DATAPINS P0
sbit LCD1602_E=P2^7;
sbit LCD1602_RW=P2^5;
sbit LCD1602_RS=P2^6;

/******************************串口1的波特率********************************/
//T1作波特率发生器
//在波特率加倍情况下 
#define BAUD_57600    			256 - (OSC_FREQ/192L)/57600L    // 254 FF
#define BAUD_28800    			256 - (OSC_FREQ/192L)/28800L    // 254 FE
#define BAUD_19200    			256 - (OSC_FREQ/192L)/19200L    // 253 FD
#define BAUD_14400    			256 - (OSC_FREQ/192L)/14400L    // 252 FC
#define BAUD_9600     			256 - (OSC_FREQ/192L)/9600L     // 250 FA

#define TIMER0_H   (65536-1800)/256//定时2Ms
#define TIMER0_L   (65536-1800)%256

#define SYS_Fosc        12000000  //晶振频率			   
#define COMM_BAUD_RATE  9600      //串口波特率

#define OSC_FREQ        12000000  //12000000  
/**********************************
函数声明
**********************************/
/*在51单片机12MHZ时钟下的延时函数*/
void Lcd1602_Delay1ms(uint c);   //误差 0us
/*LCD1602写入8位命令子函数*/
void LcdWriteCom(uchar com);
/*LCD1602写入8位数据子函数*/	
void LcdWriteData(uchar dat)	;
/*LCD1602初始化子程序*/		
void LcdInit();						  

#endif

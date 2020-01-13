#ifndef __LCD_H_
#define __LCD_H_
/**********************************
��ʹ�õ���4λ���ݴ����ʱ���壬
ʹ��8λȡ���������
**********************************/
//#define LCD1602_4PINS

/**********************************
����ͷ�ļ�
**********************************/
#include<reg51.h>

//---�ض���ؼ���---//
#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint 
#define uint unsigned int
#endif

/**********************************
PIN�ڶ���
**********************************/
#define LCD1602_DATAPINS P0
sbit LCD1602_E=P2^7;
sbit LCD1602_RW=P2^5;
sbit LCD1602_RS=P2^6;

/******************************����1�Ĳ�����********************************/
//T1�������ʷ�����
//�ڲ����ʼӱ������ 
#define BAUD_57600    			256 - (OSC_FREQ/192L)/57600L    // 254 FF
#define BAUD_28800    			256 - (OSC_FREQ/192L)/28800L    // 254 FE
#define BAUD_19200    			256 - (OSC_FREQ/192L)/19200L    // 253 FD
#define BAUD_14400    			256 - (OSC_FREQ/192L)/14400L    // 252 FC
#define BAUD_9600     			256 - (OSC_FREQ/192L)/9600L     // 250 FA

#define TIMER0_H   (65536-1800)/256//��ʱ2Ms
#define TIMER0_L   (65536-1800)%256

#define SYS_Fosc        12000000  //����Ƶ��			   
#define COMM_BAUD_RATE  9600      //���ڲ�����

#define OSC_FREQ        12000000  //12000000  
/**********************************
��������
**********************************/
/*��51��Ƭ��12MHZʱ���µ���ʱ����*/
void Lcd1602_Delay1ms(uint c);   //��� 0us
/*LCD1602д��8λ�����Ӻ���*/
void LcdWriteCom(uchar com);
/*LCD1602д��8λ�����Ӻ���*/	
void LcdWriteData(uchar dat)	;
/*LCD1602��ʼ���ӳ���*/		
void LcdInit();						  

#endif

#ifndef _USART2_H
#define _USART2_H

#include "stm32f10x.h"

extern  char Rx_Buff[1000];
extern u8 ok_flag;
extern u8 Rx_count;


void USART2_Config(u32 baud);
void SendTlink(char *s);
void UART2_Sendstring(char *s);



#endif


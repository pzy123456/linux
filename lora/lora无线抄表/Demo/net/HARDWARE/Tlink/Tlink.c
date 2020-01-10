#include "Tlink.h"
#include <string.h>
#include "Usart2.h"
#include <stdio.h>
unsigned char Tx_Buff[100];
/*
	函数功能：发送数据到Tlink
	参数：  结构体指针（传感器数据和线圈）
	返回数据：无
*/
void SendDeviceState(Device *pDeviceBlock)
{
		memset(Tx_Buff, 0, sizeof(Tx_Buff)); //发送数据之前，先情况接收数组，数据在串口中接收。
		sprintf((char *)Tx_Buff,"PZY:%d,%d,%d.#",pDeviceBlock->temp,pDeviceBlock->humi,pDeviceBlock->coil);
	  Usart_SendString(USART2,(char *)Tx_Buff,strlen(Tx_Buff));
}




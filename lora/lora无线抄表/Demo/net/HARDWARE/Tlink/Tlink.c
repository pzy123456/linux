#include "Tlink.h"
#include <string.h>
#include "Usart2.h"
#include <stdio.h>
unsigned char Tx_Buff[100];
/*
	�������ܣ��������ݵ�Tlink
	������  �ṹ��ָ�루���������ݺ���Ȧ��
	�������ݣ���
*/
void SendDeviceState(Device *pDeviceBlock)
{
		memset(Tx_Buff, 0, sizeof(Tx_Buff)); //��������֮ǰ��������������飬�����ڴ����н��ա�
		sprintf((char *)Tx_Buff,"PZY:%d,%d,%d.#",pDeviceBlock->temp,pDeviceBlock->humi,pDeviceBlock->coil);
	  Usart_SendString(USART2,(char *)Tx_Buff,strlen(Tx_Buff));
}




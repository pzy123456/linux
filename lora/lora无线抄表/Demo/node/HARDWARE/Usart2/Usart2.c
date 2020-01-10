#include "Usart2.h"
#include "esp8266.h"
#include <string.h>

char Rx_Buff[1000];
u8 ok_flag = 0;
u8 Rx_count = 0;

static void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	 /* 嵌套向量中断控制器组选择 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* 配置USART为中断源 */
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
  /* 抢断优先级*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* 子优先级 */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* 使能中断 */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStructure);
}


void USART2_Config(u32 baud)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	//PA2,Tx
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//PA3 ,Rx
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = baud;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART2, &USART_InitStructure);
	
	// 串口中断优先级配置
	NVIC_Configuration();
	
	USART_ClearFlag(USART2, USART_IT_RXNE);
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
	USART_Cmd(USART2,ENABLE);
}
void Recv_AT_Mode(void)
{
	//判断ESP8266是否返回'OK'、'>'、'ready' 
	if(strstr((char *)Rx_Buff,"OK")||strstr((char *)Rx_Buff,"CONNECT")||strstr((char *)Rx_Buff,"ready")||strstr((char *)Rx_Buff,">"))
	{
		memset(Rx_Buff,0,sizeof(Rx_Buff));
		ok_flag = 1;
		Rx_count = 0;
	}
	else
	{
		Rx_count++;
		if(Rx_count >= 200)
		{
			Rx_count = 0;
			memset(Rx_Buff,0,sizeof(Rx_Buff));
		}
	}
}

void USART2_IRQHandler(void)
{
	u8 Res; 	
	if(USART_GetITStatus(USART2, USART_IT_RXNE))
	{
		Res = USART_ReceiveData(USART2);
		Rx_Buff[Rx_count] = Res;
		
		if(AT_Mode == 1)
		{
			Recv_AT_Mode();
		}
//		else if(AT_Mode == 0)
//		{
//			Recv_normal_Mode();
//		}
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);
	}
}

void UART2_Sendstring(char *s)
{
	while(*s)
	{
		USART_SendData(USART2,*s++);
		//知道发送完成，在继续发送
		while(USART_GetITStatus(USART2, USART_IT_TC) == RESET);
	}
}


void SendTlink(char *s)
{
	memset(Rx_Buff,0,sizeof(Rx_Buff));
	UART2_Sendstring(s);
}


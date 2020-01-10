#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "Usart2.h"
#include "SPIx.h"
#include "SX1278.h"
#include "esp8266.h"
#include "NodeBus.h"
#include "Tlink.h"
#include <string.h>
#include <stdio.h>
/************************************************
实验名称：LoRa抄表网关设备
实验过程：
主机-》从机-》主机
					从机IO0是用来接收中断引脚，收到数据有电平变化
实验目的：主机给从机发送指令，接收子设备发来的指令进行解析数据
					发给Tlink云平台进行显示
************************************************/
#define AP_ID "F6R07XYUJMJP27XJ"
   
//定义这个结构体是为了从机传来的数据用来存储
DeviceState DeviceBlock_StructureArray[2] = {0};//因为从机地址是两位以内所以用2来开
Device DeviceBlock = {0};
int main(void)
 {	
	 u8 i = 0;
	 delay_init();	    //延时函数初始化	  
	 LED_Init();		  	//初始化与LED连接的硬件接口
	 initSPIx(SPI2);
	 uart_init(115200);
	 USART2_Config(115200);
	 initSX1278();
	 printf("init ok\r\n");
//	 ESP8266_GPIO_Init();
//	 ESP8266Mode_init();
//	 printf("wifi ok\r\n");
//	 Usart_SendString(USART2,AP_ID,strlen(AP_ID));
//	 printf("tlink ok\r\n");
	while(1)
	{

		if(++i > 30)
		{
			/*主机给从机发送指令*/
			SendMasterCommand(SLAVE1_ADDR,OP_R_SENSOR,PRAM_R_ALL);
			/*接收从机应答*/
			RecvSlaveAck(SLAVE1_ADDR,OP_R_SENSOR,PRAM_R_ALL,DeviceBlock_StructureArray);
			/*延时一段时间*/
			delay_ms(1000);
			/*接收从机应答*/
			while(RecvSlaveAck(SLAVE1_ADDR,OP_R_SENSOR,PRAM_R_ALL,DeviceBlock_StructureArray) != Frame_OK && i++ < 10)
			{
				delay_ms(100);//间隔3s采集一次从机数据
			}
			i = 0;
			//把从机采集的数据给主机的结构体并且显示出来
			//DeviceBlock.coil = DeviceBlock_StructureArray[SLAVE1_ADDR].Coils;
			DeviceBlock.humi = DeviceBlock_StructureArray[SLAVE1_ADDR].Humi;
			DeviceBlock.temp = DeviceBlock_StructureArray[SLAVE1_ADDR].Temp;

			//printf("DeviceBlock.coil = %d\r\n",DeviceBlock.coil);
			printf("DeviceBlock.humi = %d\r\n",DeviceBlock.humi);
			printf("DeviceBlock.temp = %d\r\n",DeviceBlock.temp);
			//采集完从机的数据，然后发送格式上传到Tlink
			SendDeviceState(&DeviceBlock);
				
		}
			LED0 = !LED0;
			delay_ms(30);
	}
	
	
 }



	

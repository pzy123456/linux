#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "SPIx.h"
#include "SX1278.h"
#include "NodeBus.h"
#include "dht11.h"
#include "OLED_I2C.h"
#include "bsp_i2c_gpio.h" 
#include "relay.h"
/************************************************
项目名称：LoRa抄表子设备实验
实验目的：读取传感器数据，发送网关设备
************************************************/

   
//定义这个结构体是为了从机传来的数据用来存储
DeviceState DeviceBlock_StructureArray = {0};//因为从机地址已经确认
//pDevice pDeviceBlock = {0};//存储传感器数值
int main(void)
 {	
	 u8 i = 0;
	 unsigned char temp_buff[10];
	 unsigned char humi_buff[10];
	 delay_init();	    //延时函数初始化	  
	 LED_Init();		  	//初始化与LED连接的硬件接口
	 initSPIx(SPI2);
	 uart_init(115200);
	 initSX1278();
	 i2c_CfgGpio();
	 OLED_Init();
	 OLED_Fill(0x00);
	 while(!DHT11_Init())
	 {
			printf("dht11 error\n");
	 }
		OLED_ShowStr(0,0,(unsigned char*)"temp:   %",2);//16*8的字体所以一行16个字
		OLED_ShowStr(0,2,(unsigned char*)"humi:   C",2);
	while(1)
	{
		if(++i > 10)
		{
			DHT11_Read_Data(&DeviceBlock_StructureArray.Temp,&DeviceBlock_StructureArray.Humi);
			sprintf((char *)temp_buff,"%d",DeviceBlock_StructureArray.Temp);
			sprintf((char *)humi_buff,"%d",DeviceBlock_StructureArray.Humi);
			OLED_ShowStr(40,0,temp_buff,2);
			OLED_ShowStr(40,2,humi_buff,2);
		
			
		//处理主机的应答
			processMasterAsk(&DeviceBlock_StructureArray);
			i = 0;
		}
		
		
//		//根据主机发来的设备块的参数设置继电器的状态
//		if(DeviceBlock_StructureArray.Coils & 0x01)
//		{
//			//继电器断开
//			RELAY_ON;
//		}
//		else{
//			//继电器吸合
//			RELAY_OFF;
//		}
		
		LED0 = !LED0;
		delay_ms(1000);
	}
 }



	

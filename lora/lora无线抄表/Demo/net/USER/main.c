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
ʵ�����ƣ�LoRa���������豸
ʵ����̣�
����-���ӻ�-������
					�ӻ�IO0�����������ж����ţ��յ������е�ƽ�仯
ʵ��Ŀ�ģ��������ӻ�����ָ��������豸������ָ����н�������
					����Tlink��ƽ̨������ʾ
************************************************/
#define AP_ID "F6R07XYUJMJP27XJ"
   
//��������ṹ����Ϊ�˴ӻ����������������洢
DeviceState DeviceBlock_StructureArray[2] = {0};//��Ϊ�ӻ���ַ����λ����������2����
Device DeviceBlock = {0};
int main(void)
 {	
	 u8 i = 0;
	 delay_init();	    //��ʱ������ʼ��	  
	 LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
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
			/*�������ӻ�����ָ��*/
			SendMasterCommand(SLAVE1_ADDR,OP_R_SENSOR,PRAM_R_ALL);
			/*���մӻ�Ӧ��*/
			RecvSlaveAck(SLAVE1_ADDR,OP_R_SENSOR,PRAM_R_ALL,DeviceBlock_StructureArray);
			/*��ʱһ��ʱ��*/
			delay_ms(1000);
			/*���մӻ�Ӧ��*/
			while(RecvSlaveAck(SLAVE1_ADDR,OP_R_SENSOR,PRAM_R_ALL,DeviceBlock_StructureArray) != Frame_OK && i++ < 10)
			{
				delay_ms(100);//���3s�ɼ�һ�δӻ�����
			}
			i = 0;
			//�Ѵӻ��ɼ������ݸ������Ľṹ�岢����ʾ����
			//DeviceBlock.coil = DeviceBlock_StructureArray[SLAVE1_ADDR].Coils;
			DeviceBlock.humi = DeviceBlock_StructureArray[SLAVE1_ADDR].Humi;
			DeviceBlock.temp = DeviceBlock_StructureArray[SLAVE1_ADDR].Temp;

			//printf("DeviceBlock.coil = %d\r\n",DeviceBlock.coil);
			printf("DeviceBlock.humi = %d\r\n",DeviceBlock.humi);
			printf("DeviceBlock.temp = %d\r\n",DeviceBlock.temp);
			//�ɼ���ӻ������ݣ�Ȼ���͸�ʽ�ϴ���Tlink
			SendDeviceState(&DeviceBlock);
				
		}
			LED0 = !LED0;
			delay_ms(30);
	}
	
	
 }



	

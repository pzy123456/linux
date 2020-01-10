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
��Ŀ���ƣ�LoRa�������豸ʵ��
ʵ��Ŀ�ģ���ȡ���������ݣ����������豸
************************************************/

   
//��������ṹ����Ϊ�˴ӻ����������������洢
DeviceState DeviceBlock_StructureArray = {0};//��Ϊ�ӻ���ַ�Ѿ�ȷ��
//pDevice pDeviceBlock = {0};//�洢��������ֵ
int main(void)
 {	
	 u8 i = 0;
	 unsigned char temp_buff[10];
	 unsigned char humi_buff[10];
	 delay_init();	    //��ʱ������ʼ��	  
	 LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
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
		OLED_ShowStr(0,0,(unsigned char*)"temp:   %",2);//16*8����������һ��16����
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
		
			
		//����������Ӧ��
			processMasterAsk(&DeviceBlock_StructureArray);
			i = 0;
		}
		
		
//		//���������������豸��Ĳ������ü̵�����״̬
//		if(DeviceBlock_StructureArray.Coils & 0x01)
//		{
//			//�̵����Ͽ�
//			RELAY_ON;
//		}
//		else{
//			//�̵�������
//			RELAY_OFF;
//		}
		
		LED0 = !LED0;
		delay_ms(1000);
	}
 }



	

#ifndef _ESP8266_H_
#define _ESP8266_H_

extern unsigned char  AT_Mode;     //��ATָ���ģʽ ���ڱ�ʾ����������Wifiģ���ģʽ  �Դ��ڽ������ݽ��в�ͬ�Ĵ���



/******��OneNet�������������ݶԽ�ʱ������ */
#define AT          "AT\r\n"	
#define CWMODE      "AT+CWMODE=1\r\n"		//STAģʽ
#define wifi_RST    "AT+RST\r\n"
#define CIFSR       "AT+CIFSR\r\n"
#define CWJAP       "AT+CWJAP=\"Honorv10\",\"123456789\"\r\n"	//ssid: onenet ���룺��
#define CIPSTART    "AT+CIPSTART=\"TCP\",\"112.74.142.132\",8647\r\n"	//Tlink�Ʒ�����
//#define CIPSTART    "AT+CIPSTART=\"TCP\",\"183.230.40.33\",80\r\n"		//HTTP������183.230.40.33/80    
#define CIPMODE0    "AT+CIPMODE=0\r\n"		//��͸��ģʽ
#define CIPMODE1    "AT+CIPMODE=1\r\n"		//͸��ģʽ
#define CIPSEND     "AT+CIPSEND\r\n"   
#define Out_CIPSEND     "+++" 
#define CIPSTATUS   "AT+CIPSTATUS\r\n"		//����״̬��ѯ

void ESP8266_Init(void);

void ESP8266_Clear(void);

void SendCmd(char* cmd, char* result, int timeOut);

unsigned char *ESP8266_GetIPD(unsigned short timeOut);

void ESP8266_SendData(unsigned char *data, unsigned short len);

void ESP8266Mode_init(void);

void ESP8266_GPIO_Init(void);

void USART_Write(unsigned char *cmd, int len);

#endif

#ifndef _ESP8266_H_
#define _ESP8266_H_

extern unsigned char  AT_Mode;     //发AT指令的模式 用于表示程序处于配置Wifi模块的模式  对串口接收数据进行不同的处理



/******与OneNet服务器进行数据对接时的配置 */
#define AT          "AT\r\n"	
#define CWMODE      "AT+CWMODE=1\r\n"		//STA模式
#define wifi_RST    "AT+RST\r\n"
#define CIFSR       "AT+CIFSR\r\n"
#define CWJAP       "AT+CWJAP=\"Honorv10\",\"123456789\"\r\n"	//ssid: onenet 密码：空
#define CIPSTART    "AT+CIPSTART=\"TCP\",\"112.74.142.132\",8647\r\n"	//Tlink云服务器
//#define CIPSTART    "AT+CIPSTART=\"TCP\",\"183.230.40.33\",80\r\n"		//HTTP服务器183.230.40.33/80    
#define CIPMODE0    "AT+CIPMODE=0\r\n"		//非透传模式
#define CIPMODE1    "AT+CIPMODE=1\r\n"		//透传模式
#define CIPSEND     "AT+CIPSEND\r\n"   
#define Out_CIPSEND     "+++" 
#define CIPSTATUS   "AT+CIPSTATUS\r\n"		//网络状态查询

void ESP8266_Init(void);

void ESP8266_Clear(void);

void SendCmd(char* cmd, char* result, int timeOut);

unsigned char *ESP8266_GetIPD(unsigned short timeOut);

void ESP8266_SendData(unsigned char *data, unsigned short len);

void ESP8266Mode_init(void);

void ESP8266_GPIO_Init(void);

void USART_Write(unsigned char *cmd, int len);

#endif

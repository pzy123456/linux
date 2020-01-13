//1/////////////////////////////////////////////////
#include<reg52.h>
#include<intrins.h>
#include"CSBCJ.h"
#include"TIME.h"
#include"DFPlayer.h"


sbit KEYa = P2^6;
sbit KEYb = P2^5;
sbit KEYc = P2^4;
sbit LED1 = P1^1;
sbit LED2 = P1^0;

unsigned char liangdu;//亮度 一二 长按停止运行

#define DENG1  0
#define DENG2  1

unsigned char kaiguan;//开机状态
#define GUANJI 0
#define KAIJI  1

extern unsigned char ganshane = 0;//学习 休息
#define XUEXI 0
#define XIUXI 1
#define BUGAN 2
unsigned char i;

unsigned char yaozuozima;//需要坐姿吗
#define XUYAO 1
#define BUYAO 0

unsigned char boshane;//在休息模式下正播放的声音
#define MEIBO  0
#define YANCAO 1
#define ERGE   2
#define GUSHI 3

unsigned char needsetup;
#define YES 1
#define NO  0

void xueximoshi();
void xiuximoshi();

void liangdujia()
{
	liangdu++;
	if(liangdu > DENG2) liangdu = DENG1;
	if(liangdu == DENG1) {LED1 = 1; LED2 = 0;}
	if(liangdu == DENG2) {LED1 = 0; LED2 = 1;}
}
void off()
{
	kaiguan = GUANJI;
	liangdu = GUANJI;
	LED1 = LED2 = 0;

	Trig = 0;
	Echo = 0;
	EA = 0;
	Uart_SendCMD(0x16,0,0x00);//mp3 停止播放
}
void setup()
{
	T50ms = 0;
	Tsecgetcm = 0;
	Tsec = 0;
	Txuexishijian = 0;

	yaozuozima = XUYAO;
	boshane = MEIBO;

	CM = GET = 0;
	Trig = 0;
	Echo = 0;

	//Serial_init();
	//CSBINIT();
	CLOCKINIT();
	EA = 1;
}
void getKEYa()
{
	if(KEYa==0)
	{
		Delay_Ms(20);
		if(kaiguan == GUANJI)
		{
			if(KEYa==0)
			{
				liangdujia();//liangdu将变成1灯亮
				setup();
				kaiguan = KAIJI;
				ganshane = XUEXI;
			}
			while(KEYa==0);
		}
		else//KAIJI
		{
			i=0;
			while(KEYa==0)
			{
				Delay_Ms(20);
				i++;
				if(i>50)
				{
					off();
					Delay_Ms(1000);
					return;
				}
			}
			if(i<50) liangdujia();
			while(KEYa==0);
		}
	}
}
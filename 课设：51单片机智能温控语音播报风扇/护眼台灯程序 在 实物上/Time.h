//3////////////////////////////////////////////
unsigned char T50ms;
//sbit miao = P2^6;
unsigned char Tsec;
unsigned char Tsecgetcm;//sec
unsigned char Tmin;
unsigned char Txuexishijian;//min
#define Ttingzhixuexi 100
unsigned int  Ttemp;

void CLOCKINIT()
{
	TMOD = 0x01;//十六位定时器
	TH0 = 0x4C;
	TL0 = 0x00;//50ms
	ET0 = 1;
	TR0 = 1;
}
void CLOCK_INT() interrupt 1
{
	TH0 = 0x4c;
	TL0 = 0x00;
	T50ms++;
	if(T50ms > 19)
	{
		Tsec++;
		Tsecgetcm++;
		//miao = ~ miao;
		T50ms = 0;
		Txuexishijian++;
	}
	if(Tsec > 59)
	{
		Tmin++;
		//Txuexishijian++;
		Tsec = 0;
	}
}
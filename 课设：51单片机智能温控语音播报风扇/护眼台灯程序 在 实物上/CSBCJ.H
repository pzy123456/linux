//2/////////////////////////////////////////////
sbit Trig = P2^0;
sbit Echo = P2^1;

unsigned int CM = 0;//×î´ó255cm
unsigned int GET = 0;
void CSBINIT()
{
	TMOD = 0x11;
	TH1 = 0;
	TL1 = 0;
	ET1 = 0;/////////////////////////////////zhegeshisha
	Trig = 0;
}
void GetCM()
{
	Trig = 1;
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
	Trig = 0;
	while(Echo == 0);
	TR1 = 1;
	while(Echo == 1);
	TR1 = 0;
	Echo = 0;
	CM = (float)((TH1*256 + TL1) * 1.085) * 0.017;
	if(CM > 100)
		CM = 0;
	TH1 = TL1 = 0;
}
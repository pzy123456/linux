/*******************************************************************************
* ʵ����			   :�¿ظ�Ӧ����ʵ��
* ʹ�õ�IO	     : 
* ʵ��Ч��       :��������¶Ȳ�ͬ���ʵ����ڷ��ȵ�ǿ��
*	ע��					 ��
*******************************************************************************/

#include "reg51.h"
#include "lcd.h"
#include "temp.h"

sbit key1 = P3^1;//�������޼�
sbit key2 = P3^0;//�������޼�
sbit key3 = P3^2;//�������޼�
sbit key4 = P3^3;//�������޼�
sbit fun_pwm = P1^0;
sbit Irstatus = P1^1;
void LcdDisplay(int);
code char NUM[] = "0123456789";
uchar string[] = "H:36 L:30";  //Ĭ�ϳ�ʼ������������ֵ
int wendu;
int H = 36;
int Hmax = 99;
int L = 30;
int Lmin = 0;
uchar high_pwm;
uchar pwm_t=0;
void timer0_init();
void keyross();
/*******************************************************************************
* ������         : main
* ��������		   : ������
* ����           : ��
* ���         	 : ��
*******************************************************************************/

void main()
{
	uchar i;
	int temp;
	LcdInit();			 //��ʼ��LCD1602
	LcdWriteCom(0x88);	//д��ַ 80��ʾ��ʼ��ַ��8��λ��
	LcdWriteData('C'); 
	LcdWriteCom(0x40+0x80);
	for(i=0;i<9;i++)
	{
		LcdWriteData(string[i]);	
	} 
	while(1)
	{	
		//Irstatus = 0;
		wendu = Ds18b20ReadTemp();
		LcdDisplay(wendu);
		Lcd1602_Delay1ms(30);
		keyross();
		timer0_init();
		temp=wendu*0.0625; //ȥ��165�д����ע��
		if(temp >= H && Irstatus == 1) //�¶�ֵ�������ޣ�����ȫ������3��
		{
			LcdWriteCom(0x8b);
			LcdWriteData(NUM[3]);
			TR0=1;
			high_pwm = 255;
		}
		else if(temp >= ((H-L)/2 + L) && temp <= H && temp >= L && Irstatus == 1)//�¶�ֵ����һ��û�г�������ֵ����������2��
		{
			LcdWriteCom(0x8b);
			LcdWriteData(NUM[2]);
			TR0=1;
			high_pwm = 150;
		}	
		else if(temp >= L && temp <= ((H-L)/2 + L) && Irstatus == 1)//�¶�ֵ��������ֵû�г���һ��ֵ����������1��
		{
			LcdWriteCom(0x8b);
			LcdWriteData(NUM[1]);
			TR0=1;
			high_pwm = 75;
		}	
		
		else if(temp < L || Irstatus == 0)//�¶�ֵû��������ֵ�����Ȳ�����
		{
			LcdWriteCom(0x8b);
			LcdWriteData(NUM[0]);
			TR0=0;
			high_pwm = 255;
			fun_pwm = 0;
		}	
		
	}
}
/*******************************************************************************
* ������         : timer0_init
* ��������		   : T0��ʼ��
* ����           : ��
* ���         	 : ��
*******************************************************************************/
void timer0_init()
{
	TMOD |= 0x01;//������ʽ1��16λ
	TH0=0xF4;//3ms�����жϣ�Լ300Hz
	TL0=0xDA;
	TR0=1;
	ET0=1;
	EA=1;
}
/*******************************************************************************
* ������         : keyross
* ��������		   : ����������
* ����           : ��
* ���         	 : ��
*******************************************************************************/
void keyross()
{
	 if(key1==0)
	{
		Lcd1602_Delay1ms(30);
		if(key1==0)
		{
			H++;
			if(H > Hmax)//����
			{
					LcdWriteCom(0x42+0x80);
					LcdWriteData('-');	
					LcdWriteCom(0x43+0x80);
					LcdWriteData('-');	
			}
			else 
			{
					LcdWriteCom(0x42+0x80);
					LcdWriteData(NUM[H/10]);	
					LcdWriteCom(0x43+0x80);
					LcdWriteData(NUM[H%10]);
			}								
		} 
		while(!key1);
	}  
	 if(key2==0)
	{
		Lcd1602_Delay1ms(30);
		if(key2==0)
		{
			H--;
			if(H < L)
			{
				LcdWriteCom(0x42+0x80);
				LcdWriteData('-');	
				LcdWriteCom(0x43+0x80);
				LcdWriteData('-');
			}
			else
			{
				LcdWriteCom(0x42+0x80);
				LcdWriteData(NUM[H/10]);	
				LcdWriteCom(0x43+0x80);
				LcdWriteData(NUM[H%10]);	
			}
		} 
		while(!key2);
	}
	if(key3==0)
	{
		Lcd1602_Delay1ms(30);
		if(key3==0)
		{
			L++;
			if(L > H)
			{
				LcdWriteCom(0x47+0x80);
				LcdWriteData('-');	
				LcdWriteCom(0x48+0x80);
				LcdWriteData('-');	
			}
			else
			{
				LcdWriteCom(0x47+0x80);
				LcdWriteData(NUM[L/10]);	
				LcdWriteCom(0x48+0x80);
				LcdWriteData(NUM[L%10]);	
			}
		} 
		while(!key3);
	}
	
	if(key4==0)
	{
		Lcd1602_Delay1ms(30);
		if(key4==0)
		{
			L--;
			if(L < Lmin)
			{
				LcdWriteCom(0x47+0x80);
				LcdWriteData('-');	
				LcdWriteCom(0x48+0x80);
				LcdWriteData('-');
			}
			else
			{
				LcdWriteCom(0x47+0x80);
				LcdWriteData(NUM[L/10]);	
				LcdWriteCom(0x48+0x80);
				LcdWriteData(NUM[L%10]);	
			}
		} 
		while(!key4);
	}
}

/*******************************************************************************
* ������         : LcdDisplay()
* ��������		   : LCD��ʾ��ȡ�����¶�
* ����           : v
* ���         	 : ��
*******************************************************************************/
void LcdDisplay(int temp) //lcd��ʾ
{
    
  uchar ds18b20_datas[] = {0, 0, 0, 0, 0}; //������ʾds18b20��ʾ����
	float tp;  
	if(temp < 0)				//���¶�ֵΪ����
  	{
	  LcdWriteCom(0x80);		//д��ַ 80��ʾ��ʼ��ַ
	  LcdWriteData('-');  		//��ʾ��
		//��Ϊ��ȡ���¶���ʵ���¶ȵĲ��룬���Լ�1����ȡ�����ԭ��
		temp=temp-1;
		temp=~temp;
		tp=temp;
		temp=tp*0.0625*100+0.5;	
		//������С�����*100��+0.5���������룬��ΪC���Ը�����ת��Ϊ���͵�ʱ���С����
		//��������Զ�ȥ���������Ƿ����0.5����+0.5֮�����0.5�ľ��ǽ�1�ˣ�С��0.5�ľ�
		//����.5��������С������档
   	}
 	else
  	{			
	  	LcdWriteCom(0x80);		//д��ַ 80��ʾ��ʼ��ַ
	    LcdWriteData('+'); 		//��ʾ��
			tp=temp;//��Ϊ���ݴ�����С�������Խ��¶ȸ���һ�������ͱ���
			//����¶���������ô����ô������ԭ����ǲ���������
			temp=tp*0.0625*100+0.5;	
			//������С�����*100��+0.5���������룬��ΪC���Ը�����ת��Ϊ���͵�ʱ���С����
			//��������Զ�ȥ���������Ƿ����0.5����+0.5֮�����0.5�ľ��ǽ�1�ˣ�С��0.5�ľ�
			//�����0.5��������С������档
	}
	ds18b20_datas[0] = temp / 10000;
	ds18b20_datas[1] = temp % 10000 / 1000;
	ds18b20_datas[2] = temp % 1000 / 100;
	ds18b20_datas[3] = temp % 100 / 10;
	ds18b20_datas[4] = temp % 10;
	

	//ds18b20����ʾ����
	LcdWriteCom(0x82);		  //д��ַ 80��ʾ��ʼ��ַ
	LcdWriteData('0'+ds18b20_datas[0]); //��λ 
	
	LcdWriteCom(0x83);		 //д��ַ 80��ʾ��ʼ��ַ
	LcdWriteData('0'+ds18b20_datas[1]); //ʮλ

	LcdWriteCom(0x84);		//д��ַ 80��ʾ��ʼ��ַ
	LcdWriteData('0'+ds18b20_datas[2]); //��λ 

	LcdWriteCom(0x85);		//д��ַ 80��ʾ��ʼ��ַ
	LcdWriteData('.'); 		//��ʾ ��.��

	LcdWriteCom(0x86);		 //д��ַ 80��ʾ��ʼ��ַ
	LcdWriteData('0'+ds18b20_datas[3]); //��ʾС����  

	LcdWriteCom(0x87);		 //д��ַ 80��ʾ��ʼ��ַ
	LcdWriteData('0'+ds18b20_datas[4]); //��ʾС����
}
/*******************************************************************************
* ������         : timer0 interrupt
* ��������		   : T0�жϺ���
* ����           : ��
* ���         	 : ��
*******************************************************************************/
void timer0(void) interrupt 1 using 1
{
	TH0=0xF4;
	TL0=0xDA;
	pwm_t++;//��ʱ����+1
	if(pwm_t == 255)//һ�����嵽��
	{
		pwm_t = 0;//��ʱ�������¼���
	}
	 if(pwm_t <= high_pwm)//�����ں͸ߵ�ƽռ�ձ����ʱ
	{
			fun_pwm = 1;//ʹ��PWM
	}
	else
	{
			fun_pwm = 0;//ʧ��PWM
	}
}
/*******************************************************************************
* ʵ����			   :�������������������¿ط���ʵ��
* ʹ�õ�IO	     : 
* ʵ��Ч��       :1602��ʾ�¶ȣ�����ģ�鲥���¶�ֵ�����ȵ�
*	ע��					 ��
*******************************************************************************/

#include "reg51.h"
#include "lcd.h"
#include "temp.h"


sbit key1 = P3^5;//�������޼�  
sbit key2 = P3^4;//�������޼�  
sbit key3 = P3^2;//�������޼�
sbit key4 = P3^3;//�������޼�
sbit fun_pwm = P1^0;
sbit Irstatus = P1^1;
//sbit low_level = P1^2;
//sbit high_level = P1^3;
void LcdDisplay(int);
uchar Send_buf[10] = {0};
code char NUM[] = "0123456789";
uchar string[] = "H:36 L:10";  //Ĭ�ϳ�ʼ������������ֵ
int wendu;
int H = 36;
int Hmax = 99;
int L = 10;
int Lmin = 0;
uchar high_pwm;
uchar pwm_t=0;
void timer0_init();
void Serial_init();
void keyross();
void Uart_PutByte(uchar ch);
void SendCmd(uchar len);
void DoSum(uchar *Str, uchar len);
void Uart_SendCMD(uchar CMD ,uchar feedback , uint dat);
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
	Uart_SendCMD(0x0f , 0 , 0x0101) ;//���ŵ�һ��,���������¶�ֵ���趨������ֵ
	while(1)
	{	
		//low_level = 0;
		//high_level = 1;
		wendu = Ds18b20ReadTemp();
		LcdDisplay(wendu);
		Lcd1602_Delay1ms(30);
		keyross();
		Serial_init();
		timer0_init();
		temp=wendu*0.0625; //ȥ��165�д����ע��
		if(temp >= H && Irstatus == 1) //�¶�ֵ�������ޣ�����ȫ������3��
		{
			LcdWriteCom(0x8b);
			LcdWriteData(NUM[3]);
			TR0=1;
			high_pwm = 255;
			Uart_SendCMD(0x0f , 0 , 0x0102) ;//���ŵڶ���,�������ŷ���ȫ������
		}
		else if(temp >= ((H-L)/2 + L) && temp <= H && temp >= L && Irstatus == 1)//�¶�ֵ����һ��û�г�������ֵ����������2��
		{
			LcdWriteCom(0x8b);
			LcdWriteData(NUM[2]);
			TR0=1;
			high_pwm = 150;
			Uart_SendCMD(0x0f , 0 , 0x0103) ;//���ŵ�����,�������ŷ��ȵڶ���
		}	
		else if(temp >= L && temp <= ((H-L)/2 + L) && Irstatus == 1)//�¶�ֵ��������ֵû�г���һ��ֵ����������1��
		{
			LcdWriteCom(0x8b);
			LcdWriteData(NUM[1]);
			TR0=1;
			high_pwm = 75;
			Uart_SendCMD(0x0f , 0 , 0x0104) ;//���ŵ�����,�������ŷ��ȵ�һ��
		}	
		
		else if(temp < L || Irstatus == 0)//�¶�ֵû��������ֵ�����Ȳ�����
		{
			LcdWriteCom(0x8b);
			LcdWriteData(NUM[0]);
			TR0=0;
			high_pwm = 255;
			fun_pwm = 0;
			Uart_SendCMD(0x0f , 0 , 0x0105) ;//���ŵ�����,�������ŷ��Ȳ�����
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
	TH0=0xF4;
	TL0=0xDA;
	TR0=1;
	ET0=1;
	EA=1;
}
/*******************************************************************************
* ������         :UsartInit()
* ��������		   :���ô���
* ����           : ��
* ���         	 : ��
*******************************************************************************/
void UsartInit()
{
	SCON=0X50;			//����Ϊ������ʽ1
	TMOD=0X20;			//���ü�����������ʽ2
	PCON=0X00;			//�����ʼӱ�
	TH1=0XFD;				//��������ʼֵ���ã�ע�Ⲩ������9600��
	TL1=0XFD;
	ES=0;						//�򿪽����ж�
	REN = 0;				//����ʹ��
	TR1=1;					//�򿪼�����
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
					Uart_SendCMD(0x0f , 0 , 0x0106) ;//���ŵ����ף����������¶������趨ֵ�������趨���ֵ���������趨
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
				Uart_SendCMD(0x0f , 0 , 0x0107) ;//���ŵ����ף����������¶������趨ֵС�������趨ֵ���������趨
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
				Uart_SendCMD(0x0f , 0 , 0x0108) ;//���ŵڰ��ף����������¶������趨ֵ���������趨ֵ���������趨
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
				Uart_SendCMD(0x0f , 0 , 0x0109) ;//���ŵھ��ף����������¶������趨ֵС�������趨��Сֵ���������趨
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
/********************************************************************************************
 - ���������� ���ڷ���һ���ֽ�
 - ����ģ�飺 �ⲿ
 - ����˵����
 - ����˵����
 - ע��	      
********************************************************************************************/
void Uart_PutByte(uchar ch)
{
    SBUF  = ch;
    while(!TI){;}
    TI = 0;
}

/*****************************************************************************************************
 - ���������� ���ڷ���һ֡����
 - ����ģ�飺 �ڲ� 
 - ����˵���� 
 - ����˵���� 
 - ע����     
*****************************************************************************************************/
void SendCmd(uchar len)
{
    uchar i = 0 ;

    Uart_PutByte(0x7E); //��ʼ
    for(i=0; i<len; i++)//����
    {
		Uart_PutByte(Send_buf[i]) ;
    }
    Uart_PutByte(0xEF) ;//����
}

/********************************************************************************************
 - �������������У��
 - ����ģ�飺
 - ����˵����
 - ����˵����
 - ע��      ��У���˼·����
             ���͵�ָ�ȥ����ʼ�ͽ��������м��6���ֽڽ����ۼӣ����ȡ����
             ���ն˾ͽ����յ���һ֡���ݣ�ȥ����ʼ�ͽ��������м�������ۼӣ��ټ��Ͻ��յ���У��
             �ֽڡ��պ�Ϊ0.�����ʹ�����յ���������ȫ��ȷ��
********************************************************************************************/
void DoSum( uchar *Str, uchar len)
{
    uint xorsum = 0;
    uchar i;

    for(i=0; i<len; i++)
    {
        xorsum  = xorsum + Str[i];
    }
	xorsum     = 0 -xorsum;
	*(Str+i)   = (uchar)(xorsum >>8);
	*(Str+i+1) = (uchar)(xorsum & 0x00ff);
}


/********************************************************************************************
 - ���������� �������ⷢ������[�������ƺͲ�ѯ]
 - ����ģ�飺 �ⲿ
 - ����˵���� CMD:��ʾ����ָ������ָ�����������ѯ�����ָ��
              feedback:�Ƿ���ҪӦ��[0:����ҪӦ��1:��ҪӦ��]
              data:���͵Ĳ���
 - ����˵����
 - ע��       
********************************************************************************************/
void Uart_SendCMD(uchar CMD ,uchar feedback , uint dat)
{
    Send_buf[0] = 0xff;    //�����ֽ� 
    Send_buf[1] = 0x06;    //����
    Send_buf[2] = CMD;     //����ָ��
    Send_buf[3] = feedback;//�Ƿ���Ҫ����
    Send_buf[4] = (uchar)(dat >> 8);//datah
    Send_buf[5] = (uchar)(dat);     //datal
    DoSum(&Send_buf[0],6);        //У��
    SendCmd(8);       //���ʹ�֡����
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
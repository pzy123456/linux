/*******************************************************************************
* ʵ����			   :�¶���ʾʵ��
* ʹ�õ�IO	     : 
* ʵ��Ч��       :1602��ʾ�¶�
*	ע��					 ��
*******************************************************************************/

#include "reg51.h"
#include "lcd.h"
#include "temp.h"

sbit key1 = P3^1;//���ü�
sbit key2 = P3^0;//���ü�
sbit key3 = P3^2;//��λ��ʼֵ
sbit key4 = P3^3;//����ȷ��
sbit beep = P1^5;
void LcdDisplay(int);
//void keyross();
uchar string[] = "up:36 down:5";  //Ĭ�ϳ�ʼ������������ֵ
uchar flag = 0;  
void keyross();
/*******************************************************************************
* ������         : main
* ��������		   : ������
* ����           : ��
* ���         	 : ��
*******************************************************************************/

void main()
{
	
	LcdInit();			 //��ʼ��LCD1602
	LcdWriteCom(0x88);	//д��ַ 80��ʾ��ʼ��ַ��8��λ��
	LcdWriteData('C');  
	while(1)
	{
		LcdDisplay(Ds18b20ReadTemp());
		Lcd1602_Delay1ms(1000);
		/*
		if(j <= 5) //С�ڵ���5ʱ ��������
			flag = 1;	
		else //������
			flag = 0;
			
		if(flag)
		{
			beep =~beep;
			Lcd1602_Delay1ms(1);
		}
		*/
		
	}
}
/*******************************************************************************
* ������         : keyross
* ��������		   : ����������
* ����           : ��
* ���         	 : ��
*******************************************************************************/
void keyross()
{
	 char j=0,n=1,m,p;
	 if(key1==0)
	{
		Lcd1602_Delay1ms(30);
		if(key1==0)
		{
			j++;
			LcdWriteCom(0x44+0x80);
			m = string[4]+j;
			LcdWriteData(m);	
			if(m > '9')
			{
				j=0;
				LcdWriteCom(0x43+0x80);
				p = string[3]+n;
				LcdWriteData(p);
			}
		} 
		while(!key1);
	}  
	if(key2==0)
	{
		Lcd1602_Delay1ms(30);
		
		if(key2==0)
		{
			j--;
			LcdWriteCom(0x44+0x80);
			LcdWriteData(string[4]-j);	
			if(string[4]-j<'0')
			{
				j=9;
				LcdWriteCom(0x43+0x80);
				LcdWriteData(string[3]-n);
			}
		} 
		while(!key2);
	}   
if(key3==0)
	{
		Lcd1602_Delay1ms(30);
		
		if(key3==0)
		{
			LcdWriteCom(0x43+0x80);
			LcdWriteData(string[3]);
			LcdWriteCom(0x44+0x80);
			LcdWriteData(string[4]);
			
			LcdWriteCom(0x51+0x80);
			LcdWriteData(string[11]);				
		} 
		while(!key3);
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
	uchar i;
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
	
	
	//��ʾ���ޣ�����ֵ		
	LcdWriteCom(0x40+0x80);
	for(i=0;i<12;i++)
	{
		LcdWriteData(string[i]);	
	}
  keyross();
}


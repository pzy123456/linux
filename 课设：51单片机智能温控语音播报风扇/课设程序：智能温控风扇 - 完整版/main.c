/*******************************************************************************
* 实验名			   :温控感应风扇实验
* 使用的IO	     : 
* 实验效果       :根据外界温度不同，适当调节风扇的强度
*	注意					 ：
*******************************************************************************/

#include "reg51.h"
#include "lcd.h"
#include "temp.h"

sbit key1 = P3^1;//设置上限加
sbit key2 = P3^0;//设置上限减
sbit key3 = P3^2;//设置下限加
sbit key4 = P3^3;//设置下限减
sbit fun_pwm = P1^0;
sbit Irstatus = P1^1;
void LcdDisplay(int);
code char NUM[] = "0123456789";
uchar string[] = "H:36 L:30";  //默认初始化的上限下限值
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
* 函数名         : main
* 函数功能		   : 主函数
* 输入           : 无
* 输出         	 : 无
*******************************************************************************/

void main()
{
	uchar i;
	int temp;
	LcdInit();			 //初始化LCD1602
	LcdWriteCom(0x88);	//写地址 80表示初始地址第8个位置
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
		temp=wendu*0.0625; //去看165行代码的注释
		if(temp >= H && Irstatus == 1) //温度值超过上限，风扇全速运行3挡
		{
			LcdWriteCom(0x8b);
			LcdWriteData(NUM[3]);
			TR0=1;
			high_pwm = 255;
		}
		else if(temp >= ((H-L)/2 + L) && temp <= H && temp >= L && Irstatus == 1)//温度值超过一半没有超过上限值，风扇运行2挡
		{
			LcdWriteCom(0x8b);
			LcdWriteData(NUM[2]);
			TR0=1;
			high_pwm = 150;
		}	
		else if(temp >= L && temp <= ((H-L)/2 + L) && Irstatus == 1)//温度值超过下限值没有超过一半值，风扇运行1挡
		{
			LcdWriteCom(0x8b);
			LcdWriteData(NUM[1]);
			TR0=1;
			high_pwm = 75;
		}	
		
		else if(temp < L || Irstatus == 0)//温度值没超过下限值，风扇不运行
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
* 函数名         : timer0_init
* 函数功能		   : T0初始化
* 输入           : 无
* 输出         	 : 无
*******************************************************************************/
void timer0_init()
{
	TMOD |= 0x01;//工作方式1，16位
	TH0=0xF4;//3ms产生中断，约300Hz
	TL0=0xDA;
	TR0=1;
	ET0=1;
	EA=1;
}
/*******************************************************************************
* 函数名         : keyross
* 函数功能		   : 按键处理函数
* 输入           : 无
* 输出         	 : 无
*******************************************************************************/
void keyross()
{
	 if(key1==0)
	{
		Lcd1602_Delay1ms(30);
		if(key1==0)
		{
			H++;
			if(H > Hmax)//上限
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
* 函数名         : LcdDisplay()
* 函数功能		   : LCD显示读取到的温度
* 输入           : v
* 输出         	 : 无
*******************************************************************************/
void LcdDisplay(int temp) //lcd显示
{
    
  uchar ds18b20_datas[] = {0, 0, 0, 0, 0}; //定义显示ds18b20显示数组
	float tp;  
	if(temp < 0)				//当温度值为负数
  	{
	  LcdWriteCom(0x80);		//写地址 80表示初始地址
	  LcdWriteData('-');  		//显示负
		//因为读取的温度是实际温度的补码，所以减1，再取反求出原码
		temp=temp-1;
		temp=~temp;
		tp=temp;
		temp=tp*0.0625*100+0.5;	
		//留两个小数点就*100，+0.5是四舍五入，因为C语言浮点数转换为整型的时候把小数点
		//后面的数自动去掉，不管是否大于0.5，而+0.5之后大于0.5的就是进1了，小于0.5的就
		//算由.5，还是在小数点后面。
   	}
 	else
  	{			
	  	LcdWriteCom(0x80);		//写地址 80表示初始地址
	    LcdWriteData('+'); 		//显示正
			tp=temp;//因为数据处理有小数点所以将温度赋给一个浮点型变量
			//如果温度是正的那么，那么正数的原码就是补码它本身
			temp=tp*0.0625*100+0.5;	
			//留两个小数点就*100，+0.5是四舍五入，因为C语言浮点数转换为整型的时候把小数点
			//后面的数自动去掉，不管是否大于0.5，而+0.5之后大于0.5的就是进1了，小于0.5的就
			//算加上0.5，还是在小数点后面。
	}
	ds18b20_datas[0] = temp / 10000;
	ds18b20_datas[1] = temp % 10000 / 1000;
	ds18b20_datas[2] = temp % 1000 / 100;
	ds18b20_datas[3] = temp % 100 / 10;
	ds18b20_datas[4] = temp % 10;
	

	//ds18b20的显示数据
	LcdWriteCom(0x82);		  //写地址 80表示初始地址
	LcdWriteData('0'+ds18b20_datas[0]); //百位 
	
	LcdWriteCom(0x83);		 //写地址 80表示初始地址
	LcdWriteData('0'+ds18b20_datas[1]); //十位

	LcdWriteCom(0x84);		//写地址 80表示初始地址
	LcdWriteData('0'+ds18b20_datas[2]); //个位 

	LcdWriteCom(0x85);		//写地址 80表示初始地址
	LcdWriteData('.'); 		//显示 ‘.’

	LcdWriteCom(0x86);		 //写地址 80表示初始地址
	LcdWriteData('0'+ds18b20_datas[3]); //显示小数点  

	LcdWriteCom(0x87);		 //写地址 80表示初始地址
	LcdWriteData('0'+ds18b20_datas[4]); //显示小数点
}
/*******************************************************************************
* 函数名         : timer0 interrupt
* 函数功能		   : T0中断函数
* 输入           : 无
* 输出         	 : 无
*******************************************************************************/
void timer0(void) interrupt 1 using 1
{
	TH0=0xF4;
	TL0=0xDA;
	pwm_t++;//定时周期+1
	if(pwm_t == 255)//一个脉冲到了
	{
		pwm_t = 0;//定时周期重新计数
	}
	 if(pwm_t <= high_pwm)//当周期和高电平占空比相等时
	{
			fun_pwm = 1;//使能PWM
	}
	else
	{
			fun_pwm = 0;//失能PWM
	}
}
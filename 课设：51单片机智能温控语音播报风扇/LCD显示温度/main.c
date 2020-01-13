/*******************************************************************************
* 实验名			   :温度显示实验
* 使用的IO	     : 
* 实验效果       :1602显示温度
*	注意					 ：
*******************************************************************************/

#include "reg51.h"
#include "lcd.h"
#include "temp.h"

sbit key1 = P3^1;//设置加
sbit key2 = P3^0;//设置减
sbit key3 = P3^2;//复位初始值
sbit key4 = P3^3;//设置确认
sbit beep = P1^5;
void LcdDisplay(int);
//void keyross();
uchar string[] = "up:36 down:5";  //默认初始化的上限下限值
uchar flag = 0;  
void keyross();
/*******************************************************************************
* 函数名         : main
* 函数功能		   : 主函数
* 输入           : 无
* 输出         	 : 无
*******************************************************************************/

void main()
{
	
	LcdInit();			 //初始化LCD1602
	LcdWriteCom(0x88);	//写地址 80表示初始地址第8个位置
	LcdWriteData('C');  
	while(1)
	{
		LcdDisplay(Ds18b20ReadTemp());
		Lcd1602_Delay1ms(1000);
		/*
		if(j <= 5) //小于等于5时 蜂鸣器响
			flag = 1;	
		else //否则不响
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
* 函数名         : keyross
* 函数功能		   : 按键处理函数
* 输入           : 无
* 输出         	 : 无
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
* 函数名         : LcdDisplay()
* 函数功能		   : LCD显示读取到的温度
* 输入           : v
* 输出         	 : 无
*******************************************************************************/
void LcdDisplay(int temp) //lcd显示
{
    
  uchar ds18b20_datas[] = {0, 0, 0, 0, 0}; //定义显示ds18b20显示数组
	uchar i;
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
	
	
	//显示上限，下限值		
	LcdWriteCom(0x40+0x80);
	for(i=0;i<12;i++)
	{
		LcdWriteData(string[i]);	
	}
  keyross();
}


/*******************************************************************************
* 实验名			   :可以语音播报的智能温控风扇实验
* 使用的IO	     : 
* 实验效果       :1602显示温度，语音模块播报温度值，风扇档
*	注意					 ：
*******************************************************************************/

#include "reg51.h"
#include "lcd.h"
#include "temp.h"


sbit key1 = P3^5;//设置上限加  
sbit key2 = P3^4;//设置上限减  
sbit key3 = P3^2;//设置下限加
sbit key4 = P3^3;//设置下限减
sbit fun_pwm = P1^0;
sbit Irstatus = P1^1;
//sbit low_level = P1^2;
//sbit high_level = P1^3;
void LcdDisplay(int);
uchar Send_buf[10] = {0};
code char NUM[] = "0123456789";
uchar string[] = "H:36 L:10";  //默认初始化的上限下限值
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
	Uart_SendCMD(0x0f , 0 , 0x0101) ;//播放第一首,用来播放温度值及设定的上下值
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
		temp=wendu*0.0625; //去看165行代码的注释
		if(temp >= H && Irstatus == 1) //温度值超过上限，风扇全速运行3挡
		{
			LcdWriteCom(0x8b);
			LcdWriteData(NUM[3]);
			TR0=1;
			high_pwm = 255;
			Uart_SendCMD(0x0f , 0 , 0x0102) ;//播放第二首,用来播放风扇全速运行
		}
		else if(temp >= ((H-L)/2 + L) && temp <= H && temp >= L && Irstatus == 1)//温度值超过一半没有超过上限值，风扇运行2挡
		{
			LcdWriteCom(0x8b);
			LcdWriteData(NUM[2]);
			TR0=1;
			high_pwm = 150;
			Uart_SendCMD(0x0f , 0 , 0x0103) ;//播放第三首,用来播放风扇第二档
		}	
		else if(temp >= L && temp <= ((H-L)/2 + L) && Irstatus == 1)//温度值超过下限值没有超过一半值，风扇运行1挡
		{
			LcdWriteCom(0x8b);
			LcdWriteData(NUM[1]);
			TR0=1;
			high_pwm = 75;
			Uart_SendCMD(0x0f , 0 , 0x0104) ;//播放第四首,用来播放风扇第一档
		}	
		
		else if(temp < L || Irstatus == 0)//温度值没超过下限值，风扇不运行
		{
			LcdWriteCom(0x8b);
			LcdWriteData(NUM[0]);
			TR0=0;
			high_pwm = 255;
			fun_pwm = 0;
			Uart_SendCMD(0x0f , 0 , 0x0105) ;//播放第五首,用来播放风扇不运行
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
	TH0=0xF4;
	TL0=0xDA;
	TR0=1;
	ET0=1;
	EA=1;
}
/*******************************************************************************
* 函数名         :UsartInit()
* 函数功能		   :设置串口
* 输入           : 无
* 输出         	 : 无
*******************************************************************************/
void UsartInit()
{
	SCON=0X50;			//设置为工作方式1
	TMOD=0X20;			//设置计数器工作方式2
	PCON=0X00;			//波特率加倍
	TH1=0XFD;				//计数器初始值设置，注意波特率是9600的
	TL1=0XFD;
	ES=0;						//打开接收中断
	REN = 0;				//串口使能
	TR1=1;					//打开计数器
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
					Uart_SendCMD(0x0f , 0 , 0x0106) ;//播放第六首：用来播放温度上限设定值过上限设定最大值，请重新设定
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
				Uart_SendCMD(0x0f , 0 , 0x0107) ;//播放第七首：用来播放温度上限设定值小于下限设定值，请重新设定
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
				Uart_SendCMD(0x0f , 0 , 0x0108) ;//播放第八首：用来播放温度下限设定值大于上限设定值，请重新设定
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
				Uart_SendCMD(0x0f , 0 , 0x0109) ;//播放第九首：用来播放温度下限设定值小于下限设定最小值，请重新设定
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
/********************************************************************************************
 - 功能描述： 串口发送一个字节
 - 隶属模块： 外部
 - 参数说明：
 - 返回说明：
 - 注：	      
********************************************************************************************/
void Uart_PutByte(uchar ch)
{
    SBUF  = ch;
    while(!TI){;}
    TI = 0;
}

/*****************************************************************************************************
 - 功能描述： 串口发送一帧数据
 - 隶属模块： 内部 
 - 参数说明： 
 - 返回说明： 
 - 注：无     
*****************************************************************************************************/
void SendCmd(uchar len)
{
    uchar i = 0 ;

    Uart_PutByte(0x7E); //起始
    for(i=0; i<len; i++)//数据
    {
		Uart_PutByte(Send_buf[i]) ;
    }
    Uart_PutByte(0xEF) ;//结束
}

/********************************************************************************************
 - 功能描述：求和校验
 - 隶属模块：
 - 参数说明：
 - 返回说明：
 - 注：      和校验的思路如下
             发送的指令，去掉起始和结束。将中间的6个字节进行累加，最后取反码
             接收端就将接收到的一帧数据，去掉起始和结束。将中间的数据累加，再加上接收到的校验
             字节。刚好为0.这样就代表接收到的数据完全正确。
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
 - 功能描述： 串口向外发送命令[包括控制和查询]
 - 隶属模块： 外部
 - 参数说明： CMD:表示控制指令，请查阅指令表，还包括查询的相关指令
              feedback:是否需要应答[0:不需要应答，1:需要应答]
              data:传送的参数
 - 返回说明：
 - 注：       
********************************************************************************************/
void Uart_SendCMD(uchar CMD ,uchar feedback , uint dat)
{
    Send_buf[0] = 0xff;    //保留字节 
    Send_buf[1] = 0x06;    //长度
    Send_buf[2] = CMD;     //控制指令
    Send_buf[3] = feedback;//是否需要反馈
    Send_buf[4] = (uchar)(dat >> 8);//datah
    Send_buf[5] = (uchar)(dat);     //datal
    DoSum(&Send_buf[0],6);        //校验
    SendCmd(8);       //发送此帧数据
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
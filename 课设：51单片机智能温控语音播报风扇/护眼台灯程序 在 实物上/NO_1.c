//0///////////////////////////////////////////////
#include"HEAD.h"

#define no 0
#define yes 1
main()//不是main 而错写成mian竟然也能编译成功（两个警告）！！搞半天不能运行的原因在这
{
	P1 = 0x00;
	KEYa = KEYb = KEYc = 1;
	kaiguan = GUANJI;
	//Uart_SendCMD(0x06,0,0x000f);//音量为十五级
	Uart_SendCMD(0x16,0,0x0000);//mp3 停止播放
loop:
	getKEYa();
	if(kaiguan == KAIJI)
	{
		if(ganshane==XIUXI) xiuximoshi();
		if(ganshane==XUEXI)	xueximoshi();
	}
goto loop;
}



void xueximoshi()
{
	if(needsetup==yes)
	{
		setup();
		needsetup=no;
	}
	if(yaozuozima==XUYAO)
	{
		Uart_SendCMD(0x17,0,0x0001);//循环播放请坐好 将超声波测距模块 对准你的面部 以获取坐姿距离 按B键获取正常坐姿
		while(yaozuozima==XUYAO)
		{
			if(KEYb==0)
			{
				Delay_Ms(15);
				while(KEYb==0)
				{
					GetCM();
					GET = CM;
					if(CM != 0)
						yaozuozima = BUYAO;
				}
			}
			getKEYa();
		}
		Uart_SendCMD(0x16,0,0x00);//mp3 停止播放
	}
	if(KEYb==0)
	{
		Delay_Ms(15);
		while(KEYb==0)
		{
			GetCM();
			GET = CM;
		}
	}
	if(KEYc==0)//长按C键进入休息模式
	{
		i=0;
		while(KEYc==0)
		{
			Delay_Ms(20);
			i++;
			if(i>50)
			{	
				Uart_SendCMD(0x0f,0,0x0501);//播眼保健操
				boshane = YANCAO;
				Txuexishijian = 0;
				ganshane = XIUXI;
				Delay_Ms(1000);
				return;
			}
		}	
	}
	if(Txuexishijian >= Ttingzhixuexi) //学了40sec//40*1min=2400sec
	{
		Uart_SendCMD(0x0f,0,0x0501);//播眼保健操
		boshane = YANCAO;
		Txuexishijian = 0;
		ganshane = XIUXI;
		return;
	}
	if(Tsecgetcm > 2)
	{
		GetCM();//GET还是用老的 之前获取的
		if(CM == 0) return;
		if(CM < GET)//如果刚获取的CM 还小于之前GET 那就是坐近了
		{
			Uart_SendCMD(0x0f,0,0x0401);//播放 请坐好
			Delay_Ms(800);
			Uart_SendCMD(0x16,0,0x00);//mp3 停止播放
		}
		Tsecgetcm = 0;
	}
}




void xiuximoshi()
{
	if(KEYb==0)//按B键停止播放 开始学习
	{
		Delay_Ms(15);
		if(KEYb==0)
		{
			Uart_SendCMD(0x16 , 0, 0x0000);//mp3停止工作
			boshane = MEIBO;
			ganshane = XUEXI;//改成学习模式 学习计时开始
			needsetup=YES;
		}
		while(KEYb==0);
		return;
	}
	if(KEYc==0)//切换成儿歌故事
	{
		Delay_Ms(15);
		if(KEYc==0)
		{
			boshane++;
			if(boshane > GUSHI) boshane = ERGE;
			if(boshane==ERGE ) Uart_SendCMD(0x17,0,0x0002);//儿歌 指定文件夹循环播放
			if(boshane==GUSHI) Uart_SendCMD(0x17,0,0x0003);//切换成故事
		}
		while(KEYc==0);
	}
}
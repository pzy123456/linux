//0///////////////////////////////////////////////
#include"HEAD.h"

#define no 0
#define yes 1
main()//����main ����д��mian��ȻҲ�ܱ���ɹ����������棩��������첻�����е�ԭ������
{
	P1 = 0x00;
	KEYa = KEYb = KEYc = 1;
	kaiguan = GUANJI;
	//Uart_SendCMD(0x06,0,0x000f);//����Ϊʮ�弶
	Uart_SendCMD(0x16,0,0x0000);//mp3 ֹͣ����
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
		Uart_SendCMD(0x17,0,0x0001);//ѭ������������ �����������ģ�� ��׼����沿 �Ի�ȡ���˾��� ��B����ȡ��������
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
		Uart_SendCMD(0x16,0,0x00);//mp3 ֹͣ����
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
	if(KEYc==0)//����C��������Ϣģʽ
	{
		i=0;
		while(KEYc==0)
		{
			Delay_Ms(20);
			i++;
			if(i>50)
			{	
				Uart_SendCMD(0x0f,0,0x0501);//���۱�����
				boshane = YANCAO;
				Txuexishijian = 0;
				ganshane = XIUXI;
				Delay_Ms(1000);
				return;
			}
		}	
	}
	if(Txuexishijian >= Ttingzhixuexi) //ѧ��40sec//40*1min=2400sec
	{
		Uart_SendCMD(0x0f,0,0x0501);//���۱�����
		boshane = YANCAO;
		Txuexishijian = 0;
		ganshane = XIUXI;
		return;
	}
	if(Tsecgetcm > 2)
	{
		GetCM();//GET�������ϵ� ֮ǰ��ȡ��
		if(CM == 0) return;
		if(CM < GET)//����ջ�ȡ��CM ��С��֮ǰGET �Ǿ���������
		{
			Uart_SendCMD(0x0f,0,0x0401);//���� ������
			Delay_Ms(800);
			Uart_SendCMD(0x16,0,0x00);//mp3 ֹͣ����
		}
		Tsecgetcm = 0;
	}
}




void xiuximoshi()
{
	if(KEYb==0)//��B��ֹͣ���� ��ʼѧϰ
	{
		Delay_Ms(15);
		if(KEYb==0)
		{
			Uart_SendCMD(0x16 , 0, 0x0000);//mp3ֹͣ����
			boshane = MEIBO;
			ganshane = XUEXI;//�ĳ�ѧϰģʽ ѧϰ��ʱ��ʼ
			needsetup=YES;
		}
		while(KEYb==0);
		return;
	}
	if(KEYc==0)//�л��ɶ������
	{
		Delay_Ms(15);
		if(KEYc==0)
		{
			boshane++;
			if(boshane > GUSHI) boshane = ERGE;
			if(boshane==ERGE ) Uart_SendCMD(0x17,0,0x0002);//���� ָ���ļ���ѭ������
			if(boshane==GUSHI) Uart_SendCMD(0x17,0,0x0003);//�л��ɹ���
		}
		while(KEYc==0);
	}
}
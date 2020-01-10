#include "NodeBus.h"
#include "SX1278.h"
/*
	该文件网关与子设备的之间的传输协议用的是nodebus
*/


/*
1. CRC16计算方法
	1) 预置 1 个 16 位的寄存器为十六进制FFFF(即全为 1) , 称此寄存器为 CRC寄存器。
	2) 把第一个 8 位二进制数据 (通信信息帧的第一个字节) 与 16 位的 CRC寄存器的低 8 位相异或, 把结果放于 CRC寄存器。
	3) 把 CRC 寄存器的内容右移一位( 朝低位)用 0 填补最高位, 并检查右移后的移出位。
	4) 如果移出位为 0, 重复第 3 步 ( 再次右移一位); 如果移出位为 1, CRC 寄存器与多项式A001 ( 1010 0000 0000 0001) 进行异或。
	5) 重复步骤 3 和步骤 4, 直到右移 8 次,这样整个8位数据全部进行了处理。
	6) 重复步骤 2 到步骤 5, 进行通信信息帧下一个字节的处理。
	7) 将该通信信息帧所有字节按上述步骤计算完成后,得到的16位CRC寄存器的高、低字节进行交换。
	8) 最后得到的 CRC寄存器内容即为 CRC码
*/

//https://blog.csdn.net/kezunhb/article/details/81914771
/*
* 功能：根据ModeBus计算CRC值		
* 参数：
*       SendBuff:待计算数据缓冲区,计算得到的结果存入_pBuf的最后两字节
*       Len:待计算数据长度(字节数)
* 返回值：16位CRC值
*/

static unsigned short GetModeBusCRC16(unsigned char *SendBuff,unsigned int Len)
{
	unsigned short CRCValue = 0xFFFF; //初始化CRC寄存器
	unsigned char i,j= 0;
	for(i = 0;i < Len;i++)
	{
			//进行通信信息帧下一个字节的处理
			CRCValue ^=  *(SendBuff + i); //把第一个 8 位二进制数据 (通信信息帧的第一个字节) 与 16 位的 CRC寄存器的低 8 位相异或
			for(j = 0;j < 8;j++)          //每次处理八位数据
			{
				if((CRCValue & 0x01) == 0x01)//判断右移前最低位是否为1
				{												
					 CRCValue = (CRCValue >> 1)^0xA001;// 如果移出位为 1, CRC 寄存器与多项式A001 ( 1010 0000 0000 0001) 进行异或。
				}else 
				{
					 CRCValue >>= 1;                     // 如果移出位为 0,则直接右移一位
				}	
			}
	}
	   if(CRCValue&0xFF==0)                            //保证CRC最后一个字节不为零
     {
        CRCValue |= 0xA5;
     }
		 return CRCValue;
}

/**
* 功能：计算数组中有效数据的长度
* 参数：
*       pBuffer:待计算数据数组
*       Buff_len:该数组的长度
* 返回值：数组buffer中有效数据个数
*/
unsigned char GetFrameLen(unsigned char *pBuffer,unsigned char Buff_len)
{
	unsigned char len = Buff_len - 1;//从最后一个推最后一个有效数据
	while(len)
	{
		if((*(pBuffer+len)) != 0)           //判断最后非零数据
		{
			break;
		}
		--len;
	}
	return len+1;
}

/*
* 功能：发送数据指令					操作码：（读传感器数据）	
	按照格式：网络地址+从机地址+读/写+数据+校验
* 参数：
*       slave_addr:从机地址
*       op_code:操作码,这里包括OP_W_COILS，OP_R_SENSOR
*       pram:操作码参数，这里包括PRAM_R_TEMPERATURE，PRAM_R_HUMIERATURE，PRAM_R_ALL
* 返回值：None
*/
void SendMasterCommand(unsigned char slave_addr,unsigned char op_code,unsigned char parm)
{
	unsigned char SendBuff[6] = {NET_ADDR,slave_addr,op_code,parm,0,0};
	unsigned short CRC16 = GetModeBusCRC16(SendBuff,4);
	/*计算CRC校验值*/
	SendBuff[4] = (CRC16 >> 8) & 0XFF;
	SendBuff[5] = CRC16 & 0xFF;
	
	/*将sendbuff通过sx1278发送到接收机上*/
	transmitPackets(SendBuff,sizeof(SendBuff));
}

/*
* 功能：接收从机数据					操作码：（读传感器数据）	
	按照格式：网络地址+从机地址+读/写+数据+校验
* 参数：
*       slave_addr:从机地址
*       op_code:操作码
*       pram:操作码参数
*       pdevblock:设备数据块
* 返回值：帧状态
*/
FrameState RecvSlaveAck(unsigned char slave_addr,unsigned char op_code,unsigned char parm,DeviceState* pdevblock)
{
		//接收数据缓冲区
		unsigned char recvbuff[7];
		unsigned char len;
		unsigned char i;
		
		//接收到数据包
		if(receivePackets(recvbuff) == 1)
		{
			if(recvbuff[0] != NET_ADDR)   						//不是本网络地址的数据，扔掉
			{
				return Frame_NetAddr_ERR;
			}
			if(recvbuff[1] != SLAVE1_ADDR)						//不是指定从机地址的数据，扔掉
			{
				return Frame_SlaveAddr_ERR;
			}
			//获取数据
			len = GetFrameLen(recvbuff,sizeof(recvbuff));
			if((GetModeBusCRC16(recvbuff,len-2)) != ((recvbuff[len-2]<<8)|(recvbuff[len-1])))   //与CRC校验匹对
			{
				return Frame_CRC_ERR;	
			}
			//recvbuff[2]是那个操作码
			//如果上面的接收从机数据正确的话，下面的判断操作码和参数
//			if(op_code == OP_W_COILS)
//			{
//				(pdevblock+slave_addr)->Coils = recvbuff[3];
//			}else 
			if(op_code == OP_R_SENSOR)
			{
				for(i=0;i<3;i++)
				{
					switch(parm & (0x01 << i))
					{
						case PRAM_R_TEMPERATURE : (pdevblock+slave_addr)->Temp = recvbuff[3];break;
						case PRAM_R_HUMIDITY    :  (pdevblock+slave_addr)->Humi = recvbuff[4];break;
						//其他传感器
						default                 :                                             break;
					}
				}
			}else{
				//其他操作码
			}		
				return Frame_OK;       //执行到这里说明接收数据成功
		}else{
				/**
			 * 没收到从机发送过来的数据，此时的状态可能是处于等待消息阶段，
			 * 当长时间没有收到数据后，可以命令从机重发或者标注该从机出现问题 
			 */
				return Frame_EMPTY;
		}
	
}


/*
	函数功能：处理主机命令应答
	参数：设备块结构体指针
	返回类型：帧状态
*/
FrameState processMasterAsk(DeviceState *pDeviceBlock)
{
	unsigned char AskRecvBuff[6];
	unsigned char AckRecvBuff[7] = {NET_ADDR,SLAVE1_ADDR};//子设备只需提供网络地址和从机地址
	unsigned char len,i;
	unsigned short CRC16;
	if(receivePackets(AskRecvBuff) == 1)//判断是否接收到主机的数据
	{
		if(AskRecvBuff[0] != NET_ADDR)
		{
			return Frame_NetAddr_ERR;
		}
		if(AskRecvBuff[1] != SLAVE1_ADDR)
		{
			return Frame_SlaveAddr_ERR;
		}
		len = GetFrameLen(AskRecvBuff,sizeof(AskRecvBuff));
		if(GetModeBusCRC16(AskRecvBuff,len - 2) != (AskRecvBuff[len - 2]<<8|AskRecvBuff[len - 1]))
		{
			return Frame_CRC_ERR;
		}
//		if(AskRecvBuff[2] == OP_W_COILS)
//		{
//			AckRecvBuff[2] = OP_W_COILS;//赋值操作码
//			pDevice->Coils = AskRecvBuff[3];//将主机发来的数据
//			AckRecvBuff[3] = pDevice->Coils;//赋值操作参数
//			CRC16 = GetModeBusCRC16(AckRecvBuff,4);
//			AckRecvBuff[4] = CRC16 >> 8;
//			AckRecvBuff[5] = CRC16;
//		}
		if(AskRecvBuff[2] == OP_R_SENSOR)
		{
			AckRecvBuff[2] = OP_R_SENSOR;
			for(i=0;i<3;i++)
			{
				switch(AskRecvBuff[3] & (0x01 << i))
				{
					case PRAM_R_TEMPERATURE:AckRecvBuff[3] = pDeviceBlock->Temp;break;
					case PRAM_R_HUMIDITY   :AckRecvBuff[4] = pDeviceBlock->Humi;break;
					default              :break;
				}
			}
			CRC16 = GetModeBusCRC16(AckRecvBuff,5);
			AckRecvBuff[5] = CRC16 >> 8;
			AckRecvBuff[6] = CRC16;
		}else 
		{
				/*其他操作码可在此扩充*/
		}
		transmitPackets(AckRecvBuff,sizeof(AckRecvBuff));//封包发送给主机
		return Frame_OK;
	}else 
	{
			return Frame_EMPTY; 
	}  
}



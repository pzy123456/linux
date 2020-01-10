#include "NodeBus.h"
#include "SX1278.h"
/*
	���ļ����������豸��֮��Ĵ���Э���õ���nodebus
*/


/*
1. CRC16���㷽��
	1) Ԥ�� 1 �� 16 λ�ļĴ���Ϊʮ������FFFF(��ȫΪ 1) , �ƴ˼Ĵ���Ϊ CRC�Ĵ�����
	2) �ѵ�һ�� 8 λ���������� (ͨ����Ϣ֡�ĵ�һ���ֽ�) �� 16 λ�� CRC�Ĵ����ĵ� 8 λ�����, �ѽ������ CRC�Ĵ�����
	3) �� CRC �Ĵ�������������һλ( ����λ)�� 0 ����λ, ��������ƺ���Ƴ�λ��
	4) ����Ƴ�λΪ 0, �ظ��� 3 �� ( �ٴ�����һλ); ����Ƴ�λΪ 1, CRC �Ĵ��������ʽA001 ( 1010 0000 0000 0001) �������
	5) �ظ����� 3 �Ͳ��� 4, ֱ������ 8 ��,��������8λ����ȫ�������˴���
	6) �ظ����� 2 ������ 5, ����ͨ����Ϣ֡��һ���ֽڵĴ���
	7) ����ͨ����Ϣ֡�����ֽڰ��������������ɺ�,�õ���16λCRC�Ĵ����ĸߡ����ֽڽ��н�����
	8) ���õ��� CRC�Ĵ������ݼ�Ϊ CRC��
*/

//https://blog.csdn.net/kezunhb/article/details/81914771
/*
* ���ܣ�����ModeBus����CRCֵ		
* ������
*       SendBuff:���������ݻ�����,����õ��Ľ������_pBuf��������ֽ�
*       Len:���������ݳ���(�ֽ���)
* ����ֵ��16λCRCֵ
*/

static unsigned short GetModeBusCRC16(unsigned char *SendBuff,unsigned int Len)
{
	unsigned short CRCValue = 0xFFFF; //��ʼ��CRC�Ĵ���
	unsigned char i,j= 0;
	for(i = 0;i < Len;i++)
	{
			//����ͨ����Ϣ֡��һ���ֽڵĴ���
			CRCValue ^=  *(SendBuff + i); //�ѵ�һ�� 8 λ���������� (ͨ����Ϣ֡�ĵ�һ���ֽ�) �� 16 λ�� CRC�Ĵ����ĵ� 8 λ�����
			for(j = 0;j < 8;j++)          //ÿ�δ����λ����
			{
				if((CRCValue & 0x01) == 0x01)//�ж�����ǰ���λ�Ƿ�Ϊ1
				{												
					 CRCValue = (CRCValue >> 1)^0xA001;// ����Ƴ�λΪ 1, CRC �Ĵ��������ʽA001 ( 1010 0000 0000 0001) �������
				}else 
				{
					 CRCValue >>= 1;                     // ����Ƴ�λΪ 0,��ֱ������һλ
				}	
			}
	}
	   if(CRCValue&0xFF==0)                            //��֤CRC���һ���ֽڲ�Ϊ��
     {
        CRCValue |= 0xA5;
     }
		 return CRCValue;
}

/**
* ���ܣ�������������Ч���ݵĳ���
* ������
*       pBuffer:��������������
*       Buff_len:������ĳ���
* ����ֵ������buffer����Ч���ݸ���
*/
unsigned char GetFrameLen(unsigned char *pBuffer,unsigned char Buff_len)
{
	unsigned char len = Buff_len - 1;//�����һ�������һ����Ч����
	while(len)
	{
		if((*(pBuffer+len)) != 0)           //�ж�����������
		{
			break;
		}
		--len;
	}
	return len+1;
}

/*
* ���ܣ���������ָ��					�����룺�������������ݣ�	
	���ո�ʽ�������ַ+�ӻ���ַ+��/д+����+У��
* ������
*       slave_addr:�ӻ���ַ
*       op_code:������,�������OP_W_COILS��OP_R_SENSOR
*       pram:������������������PRAM_R_TEMPERATURE��PRAM_R_HUMIERATURE��PRAM_R_ALL
* ����ֵ��None
*/
void SendMasterCommand(unsigned char slave_addr,unsigned char op_code,unsigned char parm)
{
	unsigned char SendBuff[6] = {NET_ADDR,slave_addr,op_code,parm,0,0};
	unsigned short CRC16 = GetModeBusCRC16(SendBuff,4);
	/*����CRCУ��ֵ*/
	SendBuff[4] = (CRC16 >> 8) & 0XFF;
	SendBuff[5] = CRC16 & 0xFF;
	
	/*��sendbuffͨ��sx1278���͵����ջ���*/
	transmitPackets(SendBuff,sizeof(SendBuff));
}

/*
* ���ܣ����մӻ�����					�����룺�������������ݣ�	
	���ո�ʽ�������ַ+�ӻ���ַ+��/д+����+У��
* ������
*       slave_addr:�ӻ���ַ
*       op_code:������
*       pram:���������
*       pdevblock:�豸���ݿ�
* ����ֵ��֡״̬
*/
FrameState RecvSlaveAck(unsigned char slave_addr,unsigned char op_code,unsigned char parm,DeviceState* pdevblock)
{
		//�������ݻ�����
		unsigned char recvbuff[7];
		unsigned char len;
		unsigned char i;
		
		//���յ����ݰ�
		if(receivePackets(recvbuff) == 1)
		{
			if(recvbuff[0] != NET_ADDR)   						//���Ǳ������ַ�����ݣ��ӵ�
			{
				return Frame_NetAddr_ERR;
			}
			if(recvbuff[1] != SLAVE1_ADDR)						//����ָ���ӻ���ַ�����ݣ��ӵ�
			{
				return Frame_SlaveAddr_ERR;
			}
			//��ȡ����
			len = GetFrameLen(recvbuff,sizeof(recvbuff));
			if((GetModeBusCRC16(recvbuff,len-2)) != ((recvbuff[len-2]<<8)|(recvbuff[len-1])))   //��CRCУ��ƥ��
			{
				return Frame_CRC_ERR;	
			}
			//recvbuff[2]���Ǹ�������
			//�������Ľ��մӻ�������ȷ�Ļ���������жϲ�����Ͳ���
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
						//����������
						default                 :                                             break;
					}
				}
			}else{
				//����������
			}		
				return Frame_OK;       //ִ�е�����˵���������ݳɹ�
		}else{
				/**
			 * û�յ��ӻ����͹��������ݣ���ʱ��״̬�����Ǵ��ڵȴ���Ϣ�׶Σ�
			 * ����ʱ��û���յ����ݺ󣬿�������ӻ��ط����߱�ע�ôӻ��������� 
			 */
				return Frame_EMPTY;
		}
	
}


/*
	�������ܣ�������������Ӧ��
	�������豸��ṹ��ָ��
	�������ͣ�֡״̬
*/
FrameState processMasterAsk(DeviceState *pDeviceBlock)
{
	unsigned char AskRecvBuff[6];
	unsigned char AckRecvBuff[7] = {NET_ADDR,SLAVE1_ADDR};//���豸ֻ���ṩ�����ַ�ʹӻ���ַ
	unsigned char len,i;
	unsigned short CRC16;
	if(receivePackets(AskRecvBuff) == 1)//�ж��Ƿ���յ�����������
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
//			AckRecvBuff[2] = OP_W_COILS;//��ֵ������
//			pDevice->Coils = AskRecvBuff[3];//����������������
//			AckRecvBuff[3] = pDevice->Coils;//��ֵ��������
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
				/*������������ڴ�����*/
		}
		transmitPackets(AckRecvBuff,sizeof(AckRecvBuff));//������͸�����
		return Frame_OK;
	}else 
	{
			return Frame_EMPTY; 
	}  
}



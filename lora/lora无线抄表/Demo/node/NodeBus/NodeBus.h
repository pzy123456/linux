#ifndef _NODEBUS_H
#define _NODEBUS_H

#include "stm32f10x.h"

/*������غ궨��*/
#define NET_ADDR           0xA5    //�����ַ
#define SLAVE1_ADDR        0x01    //���豸1��ַ
#define BROADCAST_ADDR     0xFF    //�㲥��ַ

/*��������غ궨��*/
#define OP_W_COILS         0x02    //д�̵���״̬
#define OP_R_SENSOR        0x01    //������������

/*������غ궨��*/
#define PRAM_R_TEMPERATURE 0x01    //ֻ��ȡ�¶�
#define PRAM_R_HUMIDITY    0x02    //ֻ��ȡʪ��
//#define PRAM_R_LUX         0x04    //ֻ��ȡ����ǿ��
#define PRAM_R_ALL         0x03    //��ȡ���д�����

#define PRAM_W_RELAY1      0x01    //���ϼ̵���1,�����Ͽ���λȡ������
#define PRAM_W_RELAY2      0x02    //���ϼ̵���2,�����Ͽ���λȡ������

/*ö��֡״̬*/
typedef enum{
	Frame_OK = 0x00,							//����֡��ȷ
	Frame_NetAddr_ERR = 0x01,			//�Ǳ������ַ����
	Frame_SlaveAddr_ERR = 0x02,		//�ӻ���ַ����
	Frame_CRC_ERR = 0x03,					//�������ݳ���
	Frame_EMPTY = 0xff			      //û�н��յ�����
}FrameState;

/*�оٴ�����*/
typedef struct{
	/**
     * ������������˵������������ǰ����Ӹ����ӻ�������״̬
     * �磺unsigned char SlaveStatus[256];
     * ÿ�������Ա����Ӧһ���ӻ���״̬������������㡢ͨ���쳣�ȵ�
     * ����û�����
     * */  
	//unsigned char Coils;//��Ȧ״̬
	unsigned char Humi; //�¶�
	unsigned char Temp; //ʪ��
}DeviceState;

void SendMasterCommand(unsigned char slave_addr,unsigned char op_code,unsigned char parm);
FrameState RecvSlaveAck(unsigned char slave_addr,unsigned char op_code,unsigned char parm,DeviceState* pdevblock);
FrameState processMasterAsk(DeviceState *pDevice);


#endif

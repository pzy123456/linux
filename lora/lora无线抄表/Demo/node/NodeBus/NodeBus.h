#ifndef _NODEBUS_H
#define _NODEBUS_H

#include "stm32f10x.h"

/*网络相关宏定义*/
#define NET_ADDR           0xA5    //网络地址
#define SLAVE1_ADDR        0x01    //子设备1地址
#define BROADCAST_ADDR     0xFF    //广播地址

/*操作码相关宏定义*/
#define OP_W_COILS         0x02    //写继电器状态
#define OP_R_SENSOR        0x01    //读传感器数据

/*参数相关宏定义*/
#define PRAM_R_TEMPERATURE 0x01    //只读取温度
#define PRAM_R_HUMIDITY    0x02    //只读取湿度
//#define PRAM_R_LUX         0x04    //只读取光线强度
#define PRAM_R_ALL         0x03    //读取所有传感器

#define PRAM_W_RELAY1      0x01    //吸合继电器1,如果想断开按位取反即可
#define PRAM_W_RELAY2      0x02    //吸合继电器2,如果想断开按位取反即可

/*枚举帧状态*/
typedef enum{
	Frame_OK = 0x00,							//数据帧正确
	Frame_NetAddr_ERR = 0x01,			//非本网络地址出错
	Frame_SlaveAddr_ERR = 0x02,		//从机地址错误
	Frame_CRC_ERR = 0x03,					//检验数据出错
	Frame_EMPTY = 0xff			      //没有接收到数据
}FrameState;

/*列举传感器*/
typedef struct{
	/**
     * 对于主机端来说，还可以在最前面添加各个从机的运行状态
     * 如：unsigned char SlaveStatus[256];
     * 每个数组成员都对应一个从机的状态，比如电量不足、通信异常等等
     * 这里没有添加
     * */  
	//unsigned char Coils;//线圈状态
	unsigned char Humi; //温度
	unsigned char Temp; //湿度
}DeviceState;

void SendMasterCommand(unsigned char slave_addr,unsigned char op_code,unsigned char parm);
FrameState RecvSlaveAck(unsigned char slave_addr,unsigned char op_code,unsigned char parm,DeviceState* pdevblock);
FrameState processMasterAsk(DeviceState *pDevice);


#endif

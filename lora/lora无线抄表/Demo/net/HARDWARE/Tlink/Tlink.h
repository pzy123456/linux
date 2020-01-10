#ifndef _TLINK_H
#define _TLINK_H

#include "stm32f10x.h"

typedef struct{
	u8 temp;
	u8 humi;
	u8 coil;
}Device;

void SendDeviceState(Device *pDeviceBlock);

#endif


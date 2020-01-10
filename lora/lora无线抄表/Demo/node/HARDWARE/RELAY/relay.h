#ifndef __RELAY_H
#define __RELAY_H

#include "stm32f10x.h"

#define RELAY_ON    GPIO_SetBits(GPIOC,GPIO_Pin_13)
#define RELAY_OFF   GPIO_ResetBits(GPIOC,GPIO_Pin_13)
void Relay_cfg(void);
#endif


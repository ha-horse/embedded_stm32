# ifndef __DELAY_H__
# define __DELAY_H__

#include "stm32f4xx_hal.h"

void Delay_Init(void);
void DelayUs(uint32_t micros);
void DelayMs(uint32_t mills);

# endif

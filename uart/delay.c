#include "delay.h"
#include "stm32f4xx_hal.h"

static uint32_t multiplier;
void Delay_Init(void)
{
	/* while loop takes 4 cycles */
	/* for 1 us delay, we need to divide with 4M */
	multiplier = HAL_RCC_GetHCLKFreq() / 4000000; 
}

void DelayUs(uint32_t micros)
{
	if(multiplier * micros < 10)
		micros = 1;
	else
		/* multiply micro with multipliter */
    micros = multiplier * micros - 10;
    /* 4 cycles for one loop */
  while(micros--);
}
 
 
void DelayMs(uint32_t mills)
{
	/* multiply mills with multipliter */
	mills = multiplier * mills * 1000 - 10;
	/* 4 cycles for one loop */
	while(mills--);
}

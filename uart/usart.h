#ifndef _USART_H
#define _USART_H
#include "stm32f4xx_hal.h"


extern UART_HandleTypeDef UART1_Handler;
extern UART_HandleTypeDef UART2_Handler;

void Usart1Init(uint32_t bound);
void Usart2Init(uint32_t bound);

#endif /* __USART_H__ */

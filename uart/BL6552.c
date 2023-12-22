#include "BL6552.h"



static uint32_t ms_t1 = 10;
static uint32_t us_t3 = 110;
static uint32_t us_t4 = 1;
	
void BL6552Read(uint8_t * read_addr, uint32_t *read_data)
{
	uint8_t read_cmd = READ_CMD;

	uint8_t receive_data_L;
	uint8_t receive_data_M;
	uint8_t receive_data_H;
	uint8_t receive_data_SUM;
	uint8_t receive_verify;
	uint32_t data = 0;
	
	HAL_UART_DeInit(&UART2_Handler);
	Usart2Init(9600);
	HAL_UART_Transmit(&UART2_Handler, (unsigned char *)&read_cmd, 1, 1000);
	DelayMs(ms_t1);
	HAL_UART_Transmit(&UART2_Handler, (unsigned char *)&read_addr, 1, 1000);
	DelayUs(us_t3);
	HAL_UART_Receive(&UART2_Handler, (unsigned char *)&receive_data_L, 1, 1000);
	DelayUs(us_t4);
	HAL_UART_Receive(&UART2_Handler, (unsigned char *)&receive_data_M, 1, 1000);
	DelayUs(us_t4);
	HAL_UART_Receive(&UART2_Handler, (unsigned char *)&receive_data_H, 1, 1000);
	DelayUs(us_t4);
	HAL_UART_Receive(&UART2_Handler, (unsigned char *)&receive_data_SUM, 1, 1000);
//	receive_verify = (*read_addr + receive_data_L + receive_data_M + receive_data_H)& 0xff;
//	if((~receive_verify) == receive_data_SUM)
//		*read_data = 0x11;
////		*read_data = (uint32_t)(receive_data_L);
//	else
//		*read_data = 0x00;
	data = (uint32_t)(receive_data_L + (receive_data_M << 8)+(receive_data_H<<16));
	read_data = &data;
//	HAL_UART_DeInit(&UART2_Handler);	
}
	
void BL6552Write(uint8_t * write_addr, uint32_t *write_data)
{
	uint8_t write_cmd = WRITE_CMD;

	uint8_t send_data_L = (*write_data);
	uint8_t send_data_M;
	uint8_t send_data_H;
	uint8_t send_data_SUM;
	
	HAL_UART_DeInit(&UART2_Handler);
	Usart2Init(9600);
	HAL_UART_Transmit(&UART2_Handler, (unsigned char *)&write_cmd, 1, 1000);
	DelayMs(ms_t1);
	HAL_UART_Transmit(&UART2_Handler, (unsigned char *)&write_addr, 1, 1000);
	DelayMs(ms_t1);
	HAL_UART_Transmit(&UART2_Handler, (unsigned char *)&send_data_L, 1, 1000);
	DelayMs(ms_t1);
	HAL_UART_Transmit(&UART2_Handler, (unsigned char *)&send_data_M, 1, 1000);
	DelayMs(ms_t1);
	HAL_UART_Transmit(&UART2_Handler, (unsigned char *)&send_data_H, 1, 1000);
	DelayMs(ms_t1);
	HAL_UART_Transmit(&UART2_Handler, (unsigned char *)&send_data_SUM, 1, 1000);
	HAL_UART_DeInit(&UART2_Handler);
}

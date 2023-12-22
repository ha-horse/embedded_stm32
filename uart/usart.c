#include "usart.h"


UART_HandleTypeDef UART1_Handler; //UART¾ä±ú
UART_HandleTypeDef UART2_Handler; //UART¾ä±ú


void Usart1Init(uint32_t bound)
{	
	//UART ³õÊ¼»¯ÉèÖÃ
	UART1_Handler.Instance=USART1;					   
	UART1_Handler.Init.BaudRate=bound;				    
	UART1_Handler.Init.WordLength=UART_WORDLENGTH_8B;   
	UART1_Handler.Init.StopBits=UART_STOPBITS_1;	    
	UART1_Handler.Init.Parity=UART_PARITY_NONE;		    
	UART1_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;   
	UART1_Handler.Init.Mode=UART_MODE_TX_RX;		    
	UART1_Handler.Init.OverSampling = UART_OVERSAMPLING_16;
	HAL_UART_Init(&UART1_Handler);
	
//	HAL_UART_Receive_IT(&UART1_Handler, (u8 *)aRxBuffer, RXBUFFERSIZE);//¸Ãº¯Êý»á¿ªÆô½ÓÊÕÖÐ¶Ï£º±êÖ¾Î»UART_IT_RXNE£¬²¢ÇÒÉèÖÃ½ÓÊÕ»º³åÒÔ¼°½ÓÊÕ»º³å½ÓÊÕ×î´óÊý¾ÝÁ¿
  
}

void Usart2Init(uint32_t bound)
{
	UART2_Handler.Instance=USART2;					   
	UART2_Handler.Init.BaudRate=bound;				    
	UART2_Handler.Init.WordLength=UART_WORDLENGTH_8B;  
	UART2_Handler.Init.StopBits=UART_STOPBITS_1;	    
	UART2_Handler.Init.Parity=UART_PARITY_NONE;		    
	UART2_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;   
	UART2_Handler.Init.Mode=UART_MODE_TX_RX;		    
	UART2_Handler.Init.OverSampling = UART_OVERSAMPLING_16;
	HAL_UART_Init(&UART2_Handler);
}


void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	GPIO_InitTypeDef GPIO_Initure;
	
	if(huart->Instance==USART1)
	{
		__HAL_RCC_GPIOA_CLK_ENABLE();			
		__HAL_RCC_USART1_CLK_ENABLE();			
	
		GPIO_Initure.Pin=GPIO_PIN_9 | GPIO_PIN_10;			
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;		
		GPIO_Initure.Pull=GPIO_NOPULL;
		GPIO_Initure.Speed=GPIO_SPEED_FAST;		
		GPIO_Initure.Alternate=GPIO_AF7_USART1;	
		HAL_GPIO_Init(GPIOA, &GPIO_Initure);	   	
	}
	else if(huart->Instance==USART2)
	{
		__HAL_RCC_GPIOD_CLK_ENABLE();			
		__HAL_RCC_USART2_CLK_ENABLE();			
	
		GPIO_Initure.Pin=GPIO_PIN_5 | GPIO_PIN_6;			//PD5 PD6
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;		
		GPIO_Initure.Pull=GPIO_NOPULL;			
		GPIO_Initure.Speed=GPIO_SPEED_FAST;		
		GPIO_Initure.Alternate=GPIO_AF7_USART2;	
		HAL_GPIO_Init(GPIOD,&GPIO_Initure);	   	
	}
}


void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);
  }
  else if(uartHandle->Instance==USART2)
  {
    /* Peripheral clock disable */
    __HAL_RCC_USART2_CLK_DISABLE();

    /**USART2 GPIO Configuration
    PD5     ------> USART2_TX
    PD6     ------> USART2_RX
    */
    HAL_GPIO_DeInit(GPIOD, GPIO_PIN_5|GPIO_PIN_6);
  }
}



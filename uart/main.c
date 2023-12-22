#include "usart.h"
#include "stdio.h"
#include "BL6552.h"

#define HAL_UART_MODULE_ENABLED
#define HAL_USART_MODULE_ENABLED

#pragma import(__use_no_semihosting) 

struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout; 
void _sys_exit(int x) 
{ 
	x = x; 
} 

int fputc(int c, FILE *stream)
{
    HAL_UART_Transmit(&UART1_Handler, (unsigned char *)&c, 1, 1000);   
    return c;
}

void SystemClockConfig(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Macro to configure the PLL multiplication factor
  */
  __HAL_RCC_PLL_PLLM_CONFIG(8);

  /** Macro to configure the PLL clock source
  */
  __HAL_RCC_PLL_PLLSOURCE_CONFIG(RCC_PLLSOURCE_HSI);

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	
	HAL_RCC_OscConfig(&RCC_OscInitStruct);

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
	
	HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0);
}


void SysTick_Handler(void)
{
	
}


int main(void)
{
//	unsigned char c = '?';
	uint32_t receive_data1=0;
	uint32_t receive_data2=0;
	uint32_t receive_data3=0;
	uint8_t addr_c = 0x0D;
	uint8_t addr_b = 0x0E;
	uint8_t addr_a = 0x0F;
	
	HAL_Init(); 
	SystemClockConfig();
	Usart1Init(115200);
	Delay_Init();
	
	//Usart2Init(9600);

	BL6552Read(&addr_c, &receive_data1);
	printf("IC_RMS(0x) = %x\n", receive_data1);
	BL6552Read(&addr_b, &receive_data2);
	printf("IB_RMS(0x) = %x\n", receive_data2);
	BL6552Read(&addr_a, &receive_data3);
	printf("IA_RMS(0x) = %x\n", receive_data3);

}

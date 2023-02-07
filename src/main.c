#include "main.h"
#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"

// TIM4 - APB1 42 MHz
static void TIM4_config()
{
	TIM_TimeBaseInitTypeDef TIMER_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); // Enable the Timer4 Clock
	
}


// Функция программной задержки
static void Soft_Delay(volatile uint32_t number)
{
  while(number--);
}

void blink(void *pvParameters)
{
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
  GPIO_InitTypeDef  ledinit;  // создаем структуру

  ledinit.GPIO_Mode = GPIO_Mode_OUT;  // направление - выход
  ledinit.GPIO_OType = GPIO_OType_PP;  // Двухтактный выход
  ledinit.GPIO_PuPd = GPIO_PuPd_NOPULL;  // Без подтяжки
  ledinit.GPIO_Speed = GPIO_Speed_2MHz;  // Скорость низкая
  ledinit.GPIO_Pin = GPIO_Pin_13; // Светодиод на 15м выводе

  GPIO_Init(GPIOC, &ledinit);
  while(1)
  {
    GPIO_SetBits(GPIOC, GPIO_Pin_13);
    Soft_Delay(0x00FFFFFF);
    GPIO_ResetBits(GPIOC, GPIO_Pin_13);
    Soft_Delay(0x00FFFFFF);
  }
}

int main (void) 
{
  xTaskCreate(blink, "Blink", 128, NULL, 2, NULL);
  vTaskStartScheduler();
  while(1) 
  {
    
  }
}

void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

static void HardwareSetup() 
{
	RCC_AHB1PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	
	GPIO_InitTypeDef GPIO_InitStructure;  // создаем структуру
	
// LED
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;  // направление - выход
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  // Двухтактный выход
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;  // Без подтяжки
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;  // Скорость низкая
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13; // Светодиод на 15м выводе
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	
}
	
	

/*  */
GPIO_InitTypeDef GPIO_InitStructure;
	PORTA_DATA4_OUT = PORTA_DATA5_OUT = PORTA_DATA6_OUT = PORTA_DATA7_OUT = 1;
	PORTB_DATA4_OUT = PORTB_DATA5_OUT = PORTB_DATA6_OUT = PORTB_DATA7_OUT = 1;

	GPIO_InitStructure.GPIO_Pin = PORTA_DATA_OUT_PINS;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORTA_DATA_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = PORTB_DATA_OUT_PINS;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORTB_DATA_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = PORTA_DATA_IN_PINS;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(PORTA_DATA_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = PORTB_DATA_IN_PINS;
	GPIO_Init(PORTB_DATA_PORT, &GPIO_InitStructure);

	CLIMATE_HEATER_EN = 0;
	GPIO_InitStructure.GPIO_Pin = CLIMATE_HEATER_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(CLIMATE_HEATER_PORT, &GPIO_InitStructure);

	CLIMATE_COOLER_EN = 0;
	GPIO_InitStructure.GPIO_Pin = CLIMATE_COOLER_PIN;
	GPIO_Init(CLIMATE_COOLER_PORT, &GPIO_InitStructure);
}

































void vApplicationTickHook()
{

}

void vApplicationStackOverflowHook(TaskHandle_t handle, char *name) {
(void)handle;
	for (;;){}
}

#ifdef  USE_FULL_ASSERT

void assert_failed(uint8_t *file, uint32_t line)
{
  
}
#endif /* USE_FULL_ASSERT */


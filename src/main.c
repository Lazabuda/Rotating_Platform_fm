#include "main.h"
#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"


void blink(void *pvParameters)
{
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
  GPIO_InitTypeDef  GPIO_InitStructure;  // создаем структуру

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;  // направление - выход
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  // Двухтактный выход
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;  // Без подтяжки
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;  // Скорость низкая
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13; // Светодиод на 15м выводе

  GPIO_Init(GPIOC, &GPIO_InitStructure);
  while(1)
  {
    GPIO_SetBits(GPIOC, GPIO_Pin_13);
	  vTaskDelay(100);
    GPIO_ResetBits(GPIOC, GPIO_Pin_13);
	  vTaskDelay(100);
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


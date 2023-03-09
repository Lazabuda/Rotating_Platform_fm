#include "main.h"
#include "hardware.h"

void testUART(void *pvParameters)
{
  UART_init();
  while (1)
  {
    USART1_send(100);
    vTaskDelay(200);
  }
}

void blink(void *pvParameters)
{
  Init_TIM2();
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
    Delay(30000);
    GPIO_ResetBits(GPIOC, GPIO_Pin_13);
    Delay(30000);
  }
}

int main (void) 
{
  xTaskCreate(blink, "Blink", 128, NULL, 2, NULL);
  xTaskCreate(testUART, "testUart", 128, NULL, 2, NULL);
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


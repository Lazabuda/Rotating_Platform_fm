/*
--- Here will be the description of the firmware ---
*/

//-----------Includes, defines, global variables-------------

#include "main.h"
#include "hardware.h"
#include "HX711.h"

uint32_t read_value = 0; // 32 bit value from ADC (Load Cell)

//------------------FreeRTOS functions------------------------

void weighting(void *pvParameters) // Get values from ADC and send them to the UART1
{
  HX711_init();
  UART_init();
  while (1)
  {
    read_value = get_weight();
    USART1_send(read_value);
    vTaskDelay(200);
  }
}

void blink(void *pvParameters) // Init the C13 LED and turn the LED on in particular condition
{
  Init_TIM2();
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
  GPIO_InitTypeDef  GPIO_InitStructure;  // Create the structure

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;  // Direction - output
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  // Push-Pull output
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;  // No push, no pull
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;  // Low speed
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13; // Led on the 13 pin

  GPIO_Init(GPIOC, &GPIO_InitStructure); // Itin Pin C13
  while(1)
  {
    if (read_value > 8000000)
    {
      GPIO_SetBits(GPIOC, GPIO_Pin_13);
    }
    else
    {
      GPIO_ResetBits(GPIOC, GPIO_Pin_13);
    }
  }
}

int main (void) 
{
  xTaskCreate(blink, "Blink", 128, NULL, 2, NULL);
  xTaskCreate(weighting, "weighting", 128, NULL, 2, NULL);
  vTaskStartScheduler();
  while(1) 
  {
    
  }
}

//---------------------------SERVICE FUNCTIONS-----------------------------------

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


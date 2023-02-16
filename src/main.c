#include "main.h"
#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"

//DELAY DEFINES
#define SYSCLOCK 84000000

//DELAY DEFINES END
void Init_TIM2(void);
void Delay(uint32_t delay);


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

  Init_TIM2();

  while(1)
  {
    GPIO_SetBits(GPIOC, GPIO_Pin_13);
	  Delay(25); //delay in ms
    GPIO_ResetBits(GPIOC, GPIO_Pin_13);
	  Delay(25);
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


void Init_TIM2(void) // Initialization Timer function
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); // Enable the Timer2 Clock BUS

	TIM_TimeBaseInitTypeDef TIM2_Delay; //create a TIM structure

	TIM2_Delay.TIM_Prescaler = 80 - 1; // The prescaler can divide the counter clock frequency by any factor between 1 and 65536 page 318/847
	TIM2_Delay.TIM_CounterMode = TIM_CounterMode_Up;
	TIM2_Delay.TIM_Period = 0;
	TIM2_Delay.TIM_ClockDivision = TIM_CKD_DIV1;

	TIM_TimeBaseInit(TIM2, &TIM2_Delay);
	TIM_Cmd(TIM2, ENABLE);
}

void Delay(uint32_t delay)
{
TIM2->ARR = delay;
TIM2->CNT = 0;
while ( TIM2->CNT < delay ) {}
TIM2->ARR = 0;
}

void soft_Delay(volatile uint32_t delay)
{
  while(delay--);
}
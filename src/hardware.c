#include "hardware.h"

void Init_TIM2(void) 												// TIMER 2 INITIALIZATION function
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 			// Enable TIMER 2 BUS

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;					// TIM2 structure

	TIM_TimeBaseStructure.TIM_Prescaler = 80 - 1;					// 1 timer tick - 1 microsecond
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;		// Take timer tick by rise
	TIM_TimeBaseStructure.TIM_Period = 0;							// Set the Autoreload value TIMx->ARR = TIM_TimeBaseInitStruct->TIM_Period ;
																	// into the active auto-Reload Register at the next update event.
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;			// Specifies the clock division.

	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);					// Init structure
	TIM_Cmd(TIM2, ENABLE);											// Enable/Disable the TIM Counter TIMx->CR1 (TIM_CR1_CEN)
}

void Delay(uint32_t delay)
{
	TIM2->ARR = delay;												// Set the Autoreload value TIMx->ARR. Counter will count till this value
	TIM2->CNT = 0;													// Counter starts since this value
	while ( TIM2->CNT < delay ) {}
	TIM2->ARR = 0;													// Reload Autoreload value TIMx->ARR. Counter will count till this value
}

// TIM4 - APB1 42 MHz
static void TIM4_config()
{
	TIM_TimeBaseInitTypeDef TIMER_InitStructure; //create a TIM structure
    NVIC_InitTypeDef NVIC_InitStructure; // NVIC - Nested Vector Interrupt Control, create a structure
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); // Enable the Timer4 Clock
	
//	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
//	TIM_TimeBaseStructure.TIM_Period = (uint16_t)(SystemCoreClock/20000) - 1;
//	TIM_TimeBaseStructure.TIM_Prescaler = 0;
//	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
//	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

//	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);

//	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);

//	TIM_Cmd(TIM4, ENABLE);
	
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
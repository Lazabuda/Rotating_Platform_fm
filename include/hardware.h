#ifndef __HARDWARE_H
#define __HARDWARE_H

#include "main.h"

// DEFINES
#define MCO_pin GPIO_Pin_8
#define MCO_port GPIOA

#define Rx_USART GPIO_Pin_10
#define Tx_USART GPIO_Pin_9
#define USART_PORT GPIOA

void Init_TIM2(void);
void Delay(uint32_t delay);
void show_clock();
void UART_init();
void USART1_send (uint32_t data);

#endif /* __HARDWARE_H */
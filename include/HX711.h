#ifndef __HX711_H
#define __HX711_H

#include "main.h"
#include "hardware.h"

// Define Clock and Data pins
#define HX711_CLK  GPIO_Pin_3 	// B3 - CLOCK
#define HX711_DATA GPIO_Pin_4 	// B3 - DATA
#define HX711_PORT GPIOB		// PORT of CLOCK and DATA pins
#define GAIN 1 					//1 - 128 GAIN A channel, 2 - 32 GAIN B channel, 3 - 64 GAIN A channel

void HX711_init(); // Declaration of HX711_Init function
uint32_t get_weight(); // Declaration of HX711_Value function


#endif /* __HX711_H */
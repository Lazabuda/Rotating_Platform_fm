#include "HX711.h"

uint32_t get_weight()
{
   uint32_t hx711_value = 0; 										// Create a variable for a data from HX711
   GPIO_ResetBits(HX711_PORT, HX711_CLK); 						// By the datasheet, CLK needs to be low before data will be ready to be transmitted

   while (GPIO_ReadInputDataBit(HX711_PORT, HX711_DATA) == 1) 		// When HX711 is ready for work, DATA pin is LOW
   {
	   
   } 
   Delay(10); 														// delay after DATA pin ready to transmit data


   for (uint8_t i = 0; i < 24; i++) 								// 24 BITS of data
   {
      GPIO_SetBits(HX711_PORT, HX711_CLK);						// CLOCK High
      Delay(50);
      hx711_value <<= 1;											// Shift data for a bit
      GPIO_ResetBits(HX711_PORT, HX711_CLK);					// CLOCK Low
      if(GPIO_ReadInputDataBit(HX711_PORT, HX711_DATA) == 1)		// Get a bit from DATA
      {
         hx711_value++;
      }
      Delay(25);
   }
   
   for (int i = 0; i < GAIN; i++)									// GAIN
   {
     GPIO_SetBits(HX711_PORT, HX711_CLK);
     Delay(50);
     GPIO_ResetBits(HX711_PORT, HX711_CLK);
     Delay(50);
   }
	
   hx711_value = hx711_value ^ 0x800000;							// Bitwise exclusive OR. The output 24 bits of data is in 2’s complement format. When input 
																	// differential signal goes out of the 24 bit range, the output data will be saturated at 800000h (MIN) or
																	// 7FFFFFh (MAX), until the input signal comes back to the input range.						

   return hx711_value;
}


void HX711_init() // HX711 Initialization function
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);			// GPIOB BUS Enable
	GPIO_InitTypeDef GPIO_InitStructure;
	
	// HX711 CLK
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;  					// Direction - OUT
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  				// PUSH-PULL Output
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;  				// NO PULLUP/PULLDOWN
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;  				// LOW SPEED
	GPIO_InitStructure.GPIO_Pin = HX711_CLK; 						// SET THE NUMBER OF CLOCK PIN
	GPIO_Init(GPIOB, &GPIO_InitStructure);							// Init structure
	
	// HX711 DATA
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;  					// Direction - IN
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;  				// LOW SPEED
	GPIO_InitStructure.GPIO_Pin = HX711_DATA; 						// SET THE NUMBER OF DATA PIN
	GPIO_Init(GPIOB, &GPIO_InitStructure);							// Init structure
	
	// HX711 CLOCK
	GPIO_SetBits(HX711_PORT, HX711_CLK);
	Delay(70);
	GPIO_ResetBits(HX711_PORT, HX711_CLK);
}

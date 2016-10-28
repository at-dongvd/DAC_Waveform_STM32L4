#include "stm32l476xx.h"
#include <stdint.h>
#include <math.h>

#define radian_per_degree              0.0174532925
int main(void){
  unsigned int i, output;
	signed int temp1 = 0;
  signed int temp2 = 0;
  unsigned int degree = 0;
  // Enable the clock to GPIO Port A	
  RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;   

	RCC->APB1ENR1 |= RCC_APB1ENR1_DAC1EN;
	
	GPIOA->MODER &= ~(0x0F<<(2*4));
	GPIOA->MODER |= 0x0F<<(2*4);
	
	DAC->CR |= DAC_CR_TEN1 | DAC_CR_TEN2;
	DAC->CR |= DAC_CR_TSEL1 | DAC_CR_TSEL2;
	DAC->CR |= DAC_CR_EN1 | DAC_CR_EN2;
	
	output = 0;
	
  // Dead loop & program hangs here
	while(1){
		DAC->DHR12R1 = output;
	  DAC->DHR12R2 = output;
         for(degree = 0; degree < 360; degree++)
         {
             temp1 = (2047 * cos(radian_per_degree * degree));
             temp1 = (2048 - temp1);
             temp2 = (2047 * sin(radian_per_degree * degree));
             temp2 = (2048 - temp2);
						 DAC->DHR12R1 = ((unsigned int)temp1);
             DAC->DHR12R2 = ((unsigned int)temp2);
						 DAC->SWTRIGR |= DAC_SWTRIGR_SWTRIG1 | DAC_SWTRIGR_SWTRIG2;
             for(i=0;i<=10;i++);
         }
     };
}

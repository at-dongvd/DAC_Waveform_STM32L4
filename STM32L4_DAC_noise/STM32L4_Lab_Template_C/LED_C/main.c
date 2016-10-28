#include "stm32l476xx.h"
#include <stdint.h>
#include <math.h>

#define radian_per_degree              0.0174532925
int main(void){
  unsigned int i;
  // Enable the clock to GPIO Port A	
  RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;   

	RCC->APB1ENR1 |= RCC_APB1ENR1_DAC1EN;
	
	GPIOA->MODER &= ~(0x0F<<(2*4));
	GPIOA->MODER |= 0x0F<<(2*4);
	
	DAC->CR |= DAC_CR_TEN1 | DAC_CR_TEN2;
	DAC->CR |= DAC_CR_WAVE1_0; // Noise wave generation enabled
	DAC->CR &= ~(0x0f<<8);
 	DAC->CR |= 0x3FF<<8;
	//DAC->CR |= DAC_CR_WAVE1_1; // Triangle wave generation enabled
	DAC->CR |= DAC_CR_WAVE2_0;
	DAC->CR &= ~(0x0f<<24);
	DAC->CR |= 0x3FF<<24;
	DAC->CR |= DAC_CR_TSEL1 | DAC_CR_TSEL2;
	DAC->CR |= DAC_CR_EN1 | DAC_CR_EN2;
	
	
  // Dead loop & program hangs here
	while(1){
		DAC->SWTRIGR |= DAC_SWTRIGR_SWTRIG1 | DAC_SWTRIGR_SWTRIG2;
		
		for(i=0;i<=10;i++);
     };
}

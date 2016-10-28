#include "stm32l476xx.h"

int main(void){
  unsigned int i, output;
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
		
		DAC->SWTRIGR |= DAC_SWTRIGR_SWTRIG1 | DAC_SWTRIGR_SWTRIG2;
		
		for(i=0;i<=10;i++);
		output++;
		if(output>=0xFFF) output = 0;
	}
}

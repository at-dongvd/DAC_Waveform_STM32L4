//******************** (C) Yifeng ZHU ********************
// @file    main.c
// @author  Yifeng Zhu
// @version V1.0.0
// @date    November-11-2012
// @note    
// @brief   C code for STM32L1xx Discovery Kit
// @note
//          This code is for the book "Embedded Systems with ARM Cortex-M3 
//          Microcontrollers in Assembly Language and C, Yifeng Zhu, 
//          ISBN-10: 0982692625.
// @attension
//          This code is provided for education purpose. The author shall not be 
//          held liable for any direct, indirect or consequential damages, for any 
//          reason whatever. More information can be found from book website: 
//          http://www.eece.maine.edu/~zhu/book
//********************************************************

#include <stdint.h>
#include <math.h>
/* Standard STM32L1xxx driver headers */
#include "stm32l1xx.h"

/* STM32L1xx Discovery Kit:
    - USER Pushbutton: connected to PA0 (GPIO Port A, PIN 0), CLK RCC_AHBENR_GPIOAEN
    - RESET Pushbutton: connected RESET
    - GREEN LED: connected to PB7 (GPIO Port B, PIN 7), CLK RCC_AHBENR_GPIOBEN 
    - BLUE LED: connected to PB6 (GPIO Port B, PIN 6), CLK RCC_AHBENR_GPIOBEN
    - Linear touch sensor/touchkeys: PA6, PA7 (group 2),  PC4, PC5 (group 9),  PB0, PB1 (group 3)
*/



//******************************************************************************************
//* The main program starts here
//******************************************************************************************
int main(void){
  unsigned int i, output;
  // Enable the clock to GPIO Port A	
  RCC->AHBENR |= RCC_AHBENR_GPIOAEN;   

	RCC->APB1ENR |= RCC_APB1ENR_DACEN;
	
	GPIOA->MODER &= ~(0x0F<<(2*4));
	GPIOA->MODER |= 0x0F<<(2*4);
	
	//DAC->CR |= DAC_CR_BOFF1 | DAC_CR_BOFF2;
	DAC->CR |= DAC_CR_TEN1 | DAC_CR_TEN2;
	DAC->CR |= DAC_CR_WAVE1_0; // Noise wave generation enabled
	DAC->CR &= ~(0x0f<<8);
 	DAC->CR |= 0x3FF<<8;
	//DAC->CR |= DAC_CR_WAVE1_1; // Triangle wave generation enabled
	DAC->CR |= DAC_CR_WAVE2_0;
	DAC->CR &= ~(0x0f<<24);
	DAC->CR |= 0x3FF<<24;
	//DAC->CR |= DAC_CR_WAVE2_1;
	DAC->CR |= DAC_CR_TSEL1 | DAC_CR_TSEL2;
	DAC->CR |= DAC_CR_EN1 | DAC_CR_EN2;
	
  // Dead loop & program hangs here
	while(1){
		DAC->SWTRIGR |= DAC_SWTRIGR_SWTRIG1 | DAC_SWTRIGR_SWTRIG2;
		for(i=0;i<=10;i++);
	}
}


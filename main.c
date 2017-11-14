#include <stdint.h>

// See http://hertaville.com/stm32f0-gpio-tutorial-part-1.html but ports are not for the F1
// See https://gist.github.com/iwalpola/6c36c9573fd322a268ce890a118571ca
// See ~/.arduino15/packages/stm32duino/hardware/STM32F1/2017.10.19/system/libmaple/stm32f1/include/series/gpio.h
// See ~/.arduino15/packages/stm32duino/hardware/STM32F1/2017.10.19/system/libmaple/stm32f1/include/series/rcc.h

static inline void delay(int amount)
{
	volatile int i;
	for (i=0; i<amount; i++) {
	}
}

int main ()
{
	volatile static uint32_t * GPIOC_BASE = (uint32_t *) 0x40011000; // General Purpose I/O
	volatile static uint32_t * RCC_BASE = (uint32_t *) 0x40021000; // Reset and Clock Control

	// Reset port C (value 4)
	RCC_BASE[3] |= 1 << 4; // APB2RSTR, Advanced Peripheral Bus 2 Reset Register
	RCC_BASE[3] &= ~(1 << 4);
	// Enable clock for GPIO port 'C'
	RCC_BASE[6] |= 1 << 4; // APB2ENR, Advanced Peripheral Bus 2 Enable Register

	// 'pin mode' is a 4-bit value, meaning that it takes two 32-bit registers
	// to store the modes for all 16 pins in port C. These registers are called
	// CRH (high) and CRL (low). PC13 is 13-8=5 on CRH.
	// Need to set 0x0011, which is push-pull (00), max output speed (11)
	// I'm doing so by first clearing all relevant bits and then set them.
	GPIOC_BASE[1] = ((GPIOC_BASE[1] & ~(0b1111 << (5*4))) | (0b0011 << (5*4)));

	// And blink!
	while (1) {
		GPIOC_BASE[4] = (1 << 13); // BSSR
		delay(1000000);
		//GPIOC_BASE[4] = (1 << (13+16)); // alternative: mirror previous using BRR
		GPIOC_BASE[5] = (1 << 13); // BRR
		delay(1000000); 
	}
}


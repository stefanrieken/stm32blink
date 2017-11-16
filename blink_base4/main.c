#include <stdint.h>

// See http://hertaville.com/stm32f0-gpio-tutorial-part-1.html but ports are not for the F1
// See https://gist.github.com/iwalpola/6c36c9573fd322a268ce890a118571ca
// See ~/.arduino15/packages/stm32duino/hardware/STM32F1/2017.10.19/system/libmaple/stm32f1/include/series/gpio.h
// See ~/.arduino15/packages/stm32duino/hardware/STM32F1/2017.10.19/system/libmaple/stm32f1/include/series/rcc.h

volatile static uint32_t * GPIOC_BASE = (uint32_t *) 0x40011000; // General Purpose I/O
volatile static uint32_t * RCC_BASE = (uint32_t *) 0x40021000; // Reset and Clock Control

static inline void delay(int amount)
{
	volatile int i;
	for (i=0; i<amount; i++);
}

void blink(int onTime, int offTime)
{
	GPIOC_BASE[5] = (1 << 13); // BSSR
	delay(onTime);
	GPIOC_BASE[4] = (1 << 13); // BRR
	delay(offTime); 
}

// Blinks the value of an int, a nybble at a time.
// A long blink '_' serves both as the zero value and positional separator,
// so that e.g. '..._..' forms the number '32' in base 4, which is '14' in decimal.
// The (two-nybble) hexadecimal value 'B2' would be blinked as as '.._... ..'
// Note the positional separator on the high value 'B' but not on the low (<4) value '2'.
//
// To reconstruct the blinks back to hexadecimal one starts with writing down the base-4
// values, e.g.:
// 23 2 -> (2*4)+3 2 -> 11 2 -> B2
//
// To continue to decimal:
// (11*16)+2=178

void blink_num(uint32_t num)
{
	const int LONG = 500000;
	const int SHORT =100000;

	if (num == 0)
	{
		blink(LONG, SHORT);
		return;
	}

	while (num != 0)
	{
		if ((num & 0b1111) == 0)
		{
			blink(LONG, SHORT);
			goto skip;
		}

		int msb = (num >>2) & 0b11; // most significant two bits of low nybble
		for (int i=0; i< msb; i++)
			blink(SHORT, SHORT);
		if (msb != 0) {
			delay(SHORT);
			blink(LONG, SHORT);
		}
		for (int i=0; i< (num & 0b11); i++) // least significant two bits
			blink(SHORT, SHORT);		 

		skip:
		delay(LONG);

		num = num >> 4;
	}
	delay(LONG);
}

int main ()
{
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

	// turn any existing value off
	GPIOC_BASE[4] = (1 << 13); // BRR
	delay(500000); 

	// And blink!
	while (1) {
		blink_num(0x76543210);
		blink_num(0xFEDCBA98);
	}
}


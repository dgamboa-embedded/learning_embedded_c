/* 02_not_your_typical_blinky:  manipulates the RCC AHB1 peripheral clock
 * enable register (RCC_AHB1ENR) in order to enable the bus for GPIOA by
 * setting bit 0 of the register. Then, it clears bits 10 and 11 of GPIOA
 * port mode register using bitwise AND operation and then set the bit fields
 * corresponding to pin 5 (PA5) using the bitwise OR operation. Finally,
 * it sets bit 5 of GPIOA port output register using bitwise OR, then
 * the program reaches an infinite for loop so that it keeps running.
 *
 * - All bit counting in this program is zero indexed.
 * - When a register is referred to as GPIOA... instead of
 *   GPIOx... it means that the program uses pointers to the absolute memory
 *   address of that specific register within the GPIOA boundaries
 *   (Peripheral Base Address + Register Offset). */

#include <stdint.h>


int main(void)
{
	// pointer to the RCC AHB1 peripheral clock enable register --> offset 0x30
	int32_t *RCC_AHB1ENR = (int32_t *) 0x40023830;

	// pointer to the GPIOA port mode register --> offset 0x00
	int32_t *GPIOx_MODER = (int32_t *) 0x40020000;

	// pointer to the GPIOA output data register --> offset 0x14
	int32_t *GPIOx_ODR = (int32_t *) 0x40020014;


	/* Enable the clock for GPIO port A
	 * set the 1st bit of RCC AHB1 peripheral clock enable register (RCC_AHB1ENR)*/
	*RCC_AHB1ENR |= 0x00000001;

	// Clear bits 10 and 11 of GPIOA port mode Register without affecting the reset value
	*GPIOx_MODER &= 0xFFFFF3FF;

	// Set bits 10 and 11 of GPIOA port mode Register to mode: 01 General Purpose output mode
	*GPIOx_MODER |= 0x00000400;

	// Set bit 5 of GPIOA port output data register
	*GPIOx_ODR |= 0x00000020;

    /* Loop forever */
	for(;;);
}

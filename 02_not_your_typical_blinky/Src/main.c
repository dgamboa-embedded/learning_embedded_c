/* 02_not_your_typical_blinky:  manipulates the RCC AHB1 peripheral clock
 * enable register (RCC_AHB1ENR) in order to enable the bus for GPIOA by
 * setting bit 0 of the register. Then, it clears bit positions 10 and 11 of GPIOA
 * port mode register using bitwise AND operation and then set the bit positions
 * corresponding to pin 5 (PA5) using the bitwise OR operation. Finally,
 * it sets bit position 5 of GPIOA port output register using bitwise OR, then
 * the program reaches an infinite for loop for keeping it running.
 *
 * - All bit positions counting in this program is zero indexed, it reflects the reference manual organization.
 * - When a register is referred to as GPIOA... instead of
 *   GPIOx... it means that the program uses pointers to the absolute memory
 *   address of that specific register within the GPIOA boundaries
 *   (Peripheral Base Address + Register Offset). */

#include <stdint.h>

// Symbolic constant for the infinite loop
#define TRUE 1


int main(void)
{
	// pointer to the RCC AHB1 peripheral clock enable register --> offset 0x30
	uint32_t *ptr_ClkCtrlReg = (uint32_t *) 0x40023830;

	// pointer to the GPIOA port mode register --> offset 0x00
	uint32_t *ptr_PortAModeReg = (uint32_t *) 0x40020000;

	// pointer to the GPIOA output data register --> offset 0x14
	uint32_t *ptr_PortAOutReg = (uint32_t *) 0x40020014;


	/* Enable the clock for GPIO port A
	 * set the 1st bit position of RCC AHB1 peripheral clock enable register (RCC_AHB1ENR)*/
	*ptr_ClkCtrlReg |= 0x01;

	// Clear bit positions10 and 11 of GPIOA port mode Register without affecting the reset value
	*ptr_PortAModeReg &= 0xFFFFF3FF;

	// Set bit positions 10 and 11 of GPIOA port mode Register to mode: 01 General Purpose output mode
	*ptr_PortAModeReg |= 0x00000400;

	/* Set bit position 5 of GPIOA port output data register, in this register the last 16 bit positions
	 * are reserved, therefore we only use a mask for the first 16 bits (0-15) of the register, since
	 * the pointer is dereferencing an unsigned 32 bit integer the last 16 bits are masked as zeroes*/
	*ptr_PortAOutReg |= 0x0020;

    /* Loop forever */
	while(TRUE);
}

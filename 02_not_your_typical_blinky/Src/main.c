/* 02_not_your_typical_blinky:
 *
 * This program use a header file called: "peripheral_registers.h" where several
 * structures were created in order to simplify working with specific bit fields
 * of different peripheral registers of the STM32 NUCLEO-F446 development board.
 * Since the peripheral registers are 32-bit sized, each structure makes use of
 * bit field members of type uint32_t. Due to the fact that ARM Cortex-M4 uses
 * little-endian byte ordering by default, Bit field members are ordered
 * sequentially from the least significant bit (LSB) to the most significant
 * bit (MSB).
 *
 * first of all, three pointers of the types defined by the imported structures,
 * are created in order to effectively control peripheral registers using these
 * pointers. It is necessary to assign the real memory addresses with their
 * offset value included, this address must be casted to the appropriate data
 * types in order to compile the program effectively.
 *
 * besides, the program configures the RCC AHB1 peripheral clock enable register
 * (RCC_AHB1ENR) in order to enable the bus for GPIOA peripheral by setting
 * bit 0 of the register by dereferencing the gpioa_en bit field member of a
 * pointer to a structure of type RCC_AHB1_ENR_t imported from
 * peripheral_registers.h header file. Then, bit positions 10 and 11 of GPIOA
 * port mode register get cleared  by dereferencing the pin_5 bit field member
 * of a pointer to a structure of type GPIOx_MODER_t making its value 0 and then
 * configuring it as 1 or 01 since it's 2-bit sized, which means that PA5's mode
 * is configured as output. Finally, it sets bit position 5 of GPIO port A
 * output data register by dereferencing the pin_5 bit field member  of a
 * pointer to a structure of type GPIOx_ODR_t imported from
 * peripheral_registers.h header file, then the program reaches an infinite
 * while loop and keeps running.
 *
 * - The memory addresses of the peripheral registers, their bit positions and
 *   offset values were obtained from the reference manual, this is essential
 *   for assigning the correct addresses to the pointers of the different types
 *   of the imported structures. */

#include <stdint.h>
#include "peripheral_registers.h"

// Symbolic constant for the infinite loop
#define TRUE 1


int main(void)
{
	/* Pointer to the structure of type RCC_AHB1_ENR_t used to configure the
	 * RCC AHB1 peripheral clock enable register */
	RCC_AHB1_ENR_t volatile * const p_ClkCtrlReg  = (RCC_AHB1_ENR_t *)0x40023830;

	/* Pointer to the structure of type GPIOx_MODER_t used to configure the
	 * GPIOA port mode register */
	GPIOx_MODER_t volatile * const p_PortAModeReg = (GPIOx_MODER_t *) 0x40020000;

	/* Pointer to the structure of type GPIOx_ODR_t used to configure the
	 * GPIOA output data register */
	GPIOx_ODR_t volatile * const p_PortAOutReg    = (GPIOx_ODR_t *) 0x40020014;


	/* Enable the clock for GPIO port A
	 * set the 1st bit position of RCC AHB1 peripheral clock enable register */
	p_ClkCtrlReg->gpioa_en = 1U;

	/* Clear bit positions 10 and 11 (pin 5) of GPIOA port mode Register */
	p_PortAModeReg->pin_5  = 0;

	/* Set bit positions 10 and 11 (pin_5) of GPIO port A mode Register to:
	 * 01 General Purpose output mode */
	p_PortAModeReg->pin_5  = 1U;

	/* Set pin 5 of GPIO port A output data register in order to turn ON LD2*/
	p_PortAOutReg->pin_5   = 1U;

    /* Loop forever */
	while(TRUE);
}

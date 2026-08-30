/* 02_not_your_typical_blinky:
 *
 * This program uses a custom header file ("peripheral_registers.h") defining
 * bit field structures to simplify access to specific hardware registers of
 * the STM32 NUCLEO-F446RE development board.
 *
 * Since STM32 peripheral registers are 32 bits wide, each structure utilizes
 * uint32_t bit field members mapped from Least Significant Bit LSB (bit 0)
 * to Most Significant Bit MSB (bit 31), matching the ARM Cortex-M4
 * architecture's little-endian memory layout.
 *
 * Program execution flow:
 * 1. Constant pointers to volatile structures are initialized with the physical
 *    memory addresses of the RCC_AHB1ENR, GPIOA_MODER, and GPIOA_ODR registers.
 * 2. GPIOA clock is enabled by setting the gpioa_en bit field in RCC_AHB1ENR.
 * 3. Pin 5 of GPIOA is configured as General Purpose Output Mode by directly
 *    assigning 1U (0b01) to the 2-bit pin_5 field of GPIOx_MODER_t.
 * 4. Pin 5 of GPIOA Output Data Register (GPIOA_ODR) is set to 1U to turn ON
 *    LD2.
 * 5. The program enters an infinite loop.
 *
 * Register physical memory addresses and bit specifications were obtained
 * directly from the STM32F446xx Reference Manual (RM0390).
 */

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


	/* Enable the clock for GPIO port A set the 1st bit position of
	 * RCC AHB1 peripheral clock enable register (gpioa_en) */
	p_ClkCtrlReg->gpioa_en = 1U;

	/* Set bit positions 10 and 11 (pin_5) of GPIO port A mode Register to:
	 * 0b01 General Purpose output mode */
	p_PortAModeReg->pin_5  = 1U;

	/* Set pin 5 of GPIO port A output data register in order to turn ON LD2*/
	p_PortAOutReg->pin_5   = 1U;

    /* Loop forever */
	while(TRUE);
}

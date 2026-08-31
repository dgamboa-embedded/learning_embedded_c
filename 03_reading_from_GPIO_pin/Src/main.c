/* 03_read_pin_status:
 *
 * This program demonstrates GPIO input reading and real-time output control
 * using bit field structures mapped to STM32 Peripheral Registers.
 *
 * The program reads the logical state of pin PA0 (driven externally to GND
 * or 3V3 using a jumper wire) via the GPIOA Input Data Register (GPIOx_IDR_t)
 * and reflects its state onto pin PA5 (Green User LED LD2) via the
 * Output Data Register (GPIOx_ODR_t).
 *
 * Architectural & Standard Compliance:
 * 1. Hardware Abstraction: Leverages bit field typedefs from
 *    "peripheral_registers.h" to map LSB to MSB register structures, delegating
 *    bitwise operations to the compiler.
 * 2. BARR-C:2018 Standard:
 *    - Pointers follow the 'p_' prefix naming convention.
 *    - Memory-mapped pointers are declared with 'volatile * const' qualifiers.
 *    - Vertical alignment of '=' assignment operators in consecutive
 *      declarations.
 *    - Strict 80-character line limit for high readability.
 *    - Allman formatting for curly braces.
 * 3. Execution Flow:
 *    - Enable GPIOA peripheral clock in RCC_AHB1ENR.
 *    - Configure PA0 as Input Mode (0b00) and PA5 as Output Mode (0b01) in
 *      GPIOA_MODER.
 *    - Continuously evaluate (polling) PA0 in an infinite loop: if PA0 is LOW
 *      (connected to GND), turn OFF LD2 (PA5 = 0); if PA0 is HIGH (connected to
 *      3V3), turn ON LD2 (PA5 = 1).
 */

#include <stdint.h>
#include "peripheral_registers.h"

#define TRUE 1

int main(void)
{
	/* Pointer to the structure of type RCC_AHB1_ENR_t used to configure the
	 * RCC AHB1 peripheral clock enable register */
	RCC_AHB1_ENR_t volatile * const p_ClkCtrlReg     =
			(RCC_AHB1_ENR_t *)0x40023830;

	/* Pointer to the structure of type GPIOx_MODER_t used to configure the
	 * GPIOA port mode register */
	GPIOx_MODER_t volatile * const p_PortAModeReg    =
			(GPIOx_MODER_t *) 0x40020000;

	/* Pointer to the structure of type GPIOx_ODR_t used to configure the
	 * GPIOA output data register */
	GPIOx_ODR_t volatile * const p_PortAOutReg       =
			(GPIOx_ODR_t *) 0x40020014;

	/* Pointer to the structure of type GPIOx_IDR_t used to configure the
	 * GPIOA input data register */
	GPIOx_IDR_t const volatile * const p_PortAInpReg =
			(GPIOx_IDR_t *) 0x40020010;

	/* Enable the clock for GPIO port A
	 * Set the 1st bit position of RCC AHB1 peripheral clock enable register
	 * (RCC_AHB1ENR)*/
	p_ClkCtrlReg->gpioa_en = 1U;

	/* Clear bit field members pin_0 and pin_5 of GPIOA port mode Register
	 * without affecting its reset value:
	 * since the reset state of GPIOA port mode Register is input mode, there is
	 * no need to change the reset value of PA0 (pin_0), but as a good practice
	 * I still clear bit positions 0 and 1 (pin_0). */

	p_PortAModeReg->pin_0  = 0;
	p_PortAModeReg->pin_5  = 0;


	/* Set bit positions 10 and 11 of GPIOA port mode Register (pin_5) to output
	 * mode (0b01). Since the reset state of GPIOA port mode Register is input
	 * mode, there is no need to change the value of pin_0 (PA0) */
	p_PortAModeReg->pin_5  = 1U;

	/* Inside of an infinite loop, read the pin PA0, if is is LOW, turn OFF the
	 * LD2, else, turn it ON */
	while (TRUE)
	{
		//  if pinStatus is 0 (LOW): turn off the LED
		if (!p_PortAInpReg->pin_0)
		{
			/* Turn OFF LD2 by assigning 0 to the pin_5 member of the GPIOA
			 * Output Data Register via dereferencing the structure pointer. */
			p_PortAOutReg->pin_5 = 0;

		}
		else // if pinStatus is not 0 (if it is HIGH) we turn ON the LD2
		{
			/* Turn ON LD2 by assigning 1 to the pin_5 member of the GPIOA
			 * Output Data Register via dereferencing the structure pointer. */
			p_PortAOutReg->pin_5 = 1U;
		}
	}
}

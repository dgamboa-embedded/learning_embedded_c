/* 03_reading_from_GPIO_pin: this program enables the clock for AHB1 connected
 * peripherals such as GPIO port A peripheral. The program also manipulates
 * GPIOA port mode register (GPIOA_MODER) in order to clear bit positions 0
 * and 1 (PA0) and configure them as input mode, and also to set bit positions
 * 10 and 11 (PA5)to be 01 (output mode). Inside of an infinite while loop: we
 * create a variable to read and store the value of the bit position 0 of GPIO
 * input data register. Then if the value is 0 turn off the LD2 (green user led)
 * if it's not 0, turn on LD2.
 *
 * As part of an effort to learn and start implementing BARR-C:2018 coding
 * standard in my source code, I'm leaving a space before and after the use of
 * pointer operators in declarations, but not in other contexts, a pointer's
 * variable name starts with 'p_' to make clear that it's a pointer. Also the
 * assignment operator in a block of adjacent assignment statements is aligned
 * on purpose. Also i follow strictly the rule of maximum 80 characters in each
 * line of code, in order to maintain readability and making it possible to
 * print the source code and work with it. And finally, i'm using the Allman
 * format for curly braces. */

#include <stdint.h>

#define TRUE 1

int main(void)
{
    /* create a pointer to the RCC AHB1 peripheral clock enable register -->
     * offset 0x30 */
	uint32_t volatile * p_ClkCtrlReg        = (uint32_t *) 0x40023830;
    // create a pointer to the GPIOA port mode register --> offset 0x00
	uint32_t volatile * p_PortAModeReg      = (uint32_t *) 0x40020000;
	// create a pointer to the GPIOA output data register --> offset 0x14
	uint32_t volatile * p_PortAOutReg       = (uint32_t *) 0x40020014;
	/* Create a pointer to read-only data from the GPIOA input data register bit
	 * position 0 (PA0) --> offset 0x10 */
	uint32_t const volatile * p_PortAInpReg = (uint32_t *) 0x40020010;

	/* Enable the clock for GPIO port A
	 * Set the 1st bit position of RCC AHB1 peripheral clock enable register
	 * (RCC_AHB1ENR)*/
	*p_ClkCtrlReg |= (1 << 0);

	/* Clear bit positions 10 and 11 of GPIOA port mode Register without
	 * affecting the reset value:
	 * since the reset state of GPIOA port mode Register is input mode, there is
	 * no need to change the reset value for bit positions 0 and 1 (which
	 * determine the mode of PA0), but as a good practice I still reset bit
	 * positions 0 and 1 */
	*p_PortAModeReg &= ~(3 << 10);
	*p_PortAModeReg &= ~(3 << 0);

	/* Set bit positions 10 and 11 of GPIOA port mode Register to mode: 01
	 * General Purpose output mode. since the reset state of GPIOA port mode
	 * Register is input mode, there is no need to change the value for bit
	 * positions 0 and 1 (which determine the mode of PA0)*/
	*p_PortAModeReg |= (1 << 10);

	/* Inside of an infinite loop, read the pin PA0, if is is LOW, turn OFF the
	 * LD2, else, turn it ON */
	while (TRUE)
	{
		/* Extract the value of bit position 0 (PA0) of GPIOA input data
		 * register and save it inside pinStatus */
		uint8_t pinStatus = (uint8_t) *p_PortAInpReg & (1 << 0);

		//  if pinStatus is 0 (LOW): turn off the LED
		if (!pinStatus)
		{
			/* turn OFF LD2 by using bitwise AND, clearing the bit position 5 of
			 * GPIOA port output data register */
			*p_PortAOutReg &= ~(1 << 5);
		}
		else // if pinStatus is not 0 (if it is HIGH) we turn ON the LD2
		{
			*p_PortAOutReg |= (1 << 5);
		}
	}

}

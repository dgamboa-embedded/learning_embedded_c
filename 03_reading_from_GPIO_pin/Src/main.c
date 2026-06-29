

#include <stdint.h>



int main(void)
{
    // create a pointer to the RCC AHB1 peripheral clock enable register --> offset 0x30
	uint32_t *ptr_ClkCtrlReg = (uint32_t *) 0x40023830;
    // create a pointer to the GPIOA port mode register --> offset 0x00
	uint32_t *ptr_PortAModeReg = (uint32_t *) 0x40020000;
	// create a pointer to the GPIOA output data register --> offset 0x14
	uint32_t *ptr_PortAOutReg = (uint32_t *) 0x40020014;
	// reate a pointer to the GPIOA input data register --> offset 0x10
	uint32_t const *ptr_PortAInpReg = (uint32_t *) 0x40020010;

	/* Enable the clock for GPIO port A
	 * set the 1st bit position of RCC AHB1 peripheral clock enable register (RCC_AHB1ENR)*/
	*ptr_ClkCtrlReg |= (1 << 0);

	/* Clear bit positions 10 and 11 of GPIOA port mode Register without affecting the reset value:
	 * since the reset state of GPIOA port mode Register is input mode, there is no need to change the
	 * reset value for bit positions 0 and 1 (which determine the mode of PA0), but as a good practice
	 * I still reset bit positions 0 and 1 */
	*ptr_PortAModeReg &= ~(3 << 10);
	*ptr_PortAModeReg &= ~(3 << 0); // As a good practice i cleared bit positions 0 and 1 (PA0)

	/* Set bit positions 10 and 11 of GPIOA port mode Register to mode: 01 General Purpose output mode.
	 * since the reset state of GPIOA port mode Register is input mode, there is no need to change the
	 * value for bit positions 0 and 1 (which determine the mode of PA0)*/
	*ptr_PortAModeReg |= (1 << 10);

	// inside an infinite loop we read the pin PA0, if is is LOW we turn OFF the LD2, else we turn it ON
	while (1)
	{
		// we extract the value of bit position 0 (PA0) of GPIOA input data register and check if it is 0
		if ((*ptr_PortAInpReg & (1 << 0)) == 0)
		{
			// we turn OFF the LED by using bitwise AND introducing a 0 value in the bit position 5 of GPIOA port output data register
			*ptr_PortAOutReg &= ~(1 << 5);
		}
		else // if PA0 is not 0 (if it is HIGH) we turn ON the LD2
		{
			*ptr_PortAOutReg |= (1 << 5);
		}
	}
}

/*
 * gpio.c
 *
 * Author: Mostafa Alaa
 *
 * Source file of GPIO driver
 */

#include "std_types.h"
#include "stm32f446xe.h"
#include "gpio.h"


/*
 * GPIO_pinInit
 *
 * @Arguments: 1. GPIO_ConfigType structure which has all the desired
 * 				configurations of the pin.
 *
 * @Return: (void) The function has no return.
 */
void GPIO_pinInit(GPIO_ConfigType *a_config)
{
	/* Check if port H is passed, then the only implemented pins are PIN0 and PIN1 */
	if(a_config->port == PORTH)
	{
		if(a_config->pin > 1)
		{
			/*TODO*/
		}
	}

	/*
	 * Setting the pin's mode.
	 *
	 * Note that the port in the a_config is the base address of the desired port
	 * so we cast it to GPIO_Type pointer and access the registers directly.
	 *
	 * Notice also the relation ship between the pin number and the shift value of
	 * its two corresponding MODER bits in the MODER.
	 * (shift value of MODER bits = 2 * pin number)
	 *
	 * 1. Clear the two bits of MODER which corresponds to the bit number.
	 * 2. Put the desired value into the targeted MODER bits.
	 */
	(((GPIO_Type *)a_config->port)->MODER) &= ~(0x03UL << (2 * a_config->pin));
	(((GPIO_Type *)a_config->port)->MODER) |= (a_config->mode << (2 * a_config->pin));


	/*
	 * Setting the pin's pull-up or pull-down.
	 *
	 * The same approach of the MODER is used here.
	 *
	 * 1. Clear the two bits of PUPDR which corresponds to the bit number.
	 * 2. Put the desired value into the targeted PUPDR bits.
	 */
	(((GPIO_Type *)a_config->port)->PUPDR) &= ~(0x03UL << (2 * a_config->pin));
	(((GPIO_Type *)a_config->port)->PUPDR) |= (a_config->pullStatus << (2 * a_config->pin));

	/*TODO*/
}


/*
 * GPIO_setPinValue
 *
 * @Arguments: 1. GPIO_PortType: The desired port.
 * 			   2. GPIO_Pin: The desired pin.
 * 			   3. GPIO_OutputValue: The desired value.
 *
 * @Return: (void) The function has no return.
 */
void GPIO_setPinValue(GPIO_PortType a_port, GPIO_Pin a_pin, GPIO_OutputValue a_value)
{
	/*
	 * writing 1 to either BRy (for reset) or BSy (for set) depending on the passed
	 * of "a_value".
	 *
	 * "y" corresponds to the pin number (y = 0.. 15), in this case it is the passed
	 * value of "a_pin".
	 */
	(((GPIO_Type *)a_port)->BSRR) = 1UL << (a_pin + a_value);
}



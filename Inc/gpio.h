/*
 * gpio.h
 *
 * Author: Mostafa Alaa
 *
 * Header file for GPIO driver
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "std_types.h"


/*
 * GPIO port enum
 *
 * Has all ports
 */
typedef enum
{
	PORTA = 0x40020000UL,		/* GPIOA */
	PORTB = 0x40020400UL,		/* GPIOB */
	PORTC = 0x40020800UL,		/* GPIOC */
	PORTD = 0x40020C00UL,		/* GPIOD */
	PORTE = 0x40021000UL,		/* GPIOE */
	PORTF = 0x40021400UL,		/* GPIOF */
	PORTG = 0x40021800UL,		/* GPIOG */
	PORTH = 0x40021C00UL		/* GPIOH */

}GPIO_PortType;


/*
 * GPIO pin number enum
 *
 * Has all pins.
 *
 * Note that for port H only PIN0 and PIN1 are implemented
 */
typedef enum
{
	PIN0 = 0UL,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7,
	PIN8,
	PIN9,
	PIN10,
	PIN11,
	PIN12,
	PIN13,
	PIN14,
	PIN15

}GPIO_Pin;


/*
 * GPIO pin mode
 *
 * Has the four pin modes
 */
typedef enum
{
	INPUT = 0UL,		/* Input (reset state) */
	OUTPUT,				/* General purpose output mode */
	ALT,				/* Alternate function mode */
	ANALOG				/* Analog mode */

}GPIO_PinMode;


/*
 * GPIO pin pull status
 */
typedef enum
{
	NOPULL = 0UL,		/* No pull-up, pull-down */
	PULLUP,				/* Pull-up */
	PULLDOWN,			/* Pull-Down */

}GPIO_PinPullStatus;


/*
 * GPIO output values
 */
typedef enum
{
	GPIO_HIGH = 16,			/* Outputs high */
	GPIO_LOW = 0			/* Outputs low */

}GPIO_OutputValue;


/*
 * GPIO initialization structure
 *
 * Has all necessary elements for GPIO initialization
 */
typedef struct
{
	GPIO_PortType port;				/* The desired port */
	GPIO_Pin pin;					/* The desired pin */
	GPIO_PinMode mode;				/* The desired pin mode */
	GPIO_PinPullStatus pullStatus;	/* If pull-up or pull-down */
	/*TODO*/

}GPIO_ConfigType;


/*************************************************************
 ******************* Functions Prototypes ********************
 *************************************************************/

/*
 * GPIO_pinInit
 *
 * Initializes a GPIO pin
 *
 * @Arguments: 1. GPIO_ConfigType structure which has all the desired
 * 				configurations of the pin.
 *
 * @Return: (void) The function has no return.
 */
void GPIO_pinInit(GPIO_ConfigType *a_cofig);


/*
 * GPIO_setPinValue
 *
 * Writes pin output value (Atomic set/reset).
 *
 * @Arguments: 1. GPIO_PortType: The desired port.
 * 			   2. GPIO_Pin: The desired pin.
 * 			   3. GPIO_OutputValue: The desired value.
 *
 * @Return: (void) The function has no return.
 */
void GPIO_setPinValue(GPIO_PortType a_port, GPIO_Pin a_pin, GPIO_OutputValue a_value);


#endif /* GPIO_H_ */

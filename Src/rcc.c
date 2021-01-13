/*
 * rcc.c
 *
 * Source file for RCC module driver.
 *
 */

#include "common_macros.h"
#include "rcc_registers.h"
#include "rcc.h"


/********************************************
 *			Functions definitions			*
 ********************************************/

/* Peripherals enablers */

bool RCC_AHB1_enableClock(const AHB1_Peripheral a_peripheral)
{
	/* Set the bit in the AHB1ENR that corresponds to the desired peripheral */
	SET_BIT(RCC_AHB1ENR, a_peripheral);

	/* Return the value of the bit (Should be 1)*/
	return RCC_AHB1ENR & (1 << a_peripheral);
}


bool RCC_AHB2_enableClock(const AHB2_Peripheral a_peripheral)
{
	/* Set the bit in the AHB2ENR that corresponds to the desired peripheral */
	SET_BIT(RCC_AHB2ENR, a_peripheral);

	/* Return the value of the bit (Should be 1)*/
	return RCC_AHB2ENR & (1 << a_peripheral);
}


bool RCC_AHB3_enableClock(const AHB3_Peripheral a_peripheral)
{
	/* Set the bit in the AHB3ENR that corresponds to the desired peripheral */
	SET_BIT(RCC_AHB3ENR, a_peripheral);

	/* Return the value of the bit (Should be 1)*/
	return RCC_AHB3ENR & (1 << a_peripheral);
}


bool RCC_APB1_enableClock(const APB1_Peripheral a_peripheral)
{
	/* Set the bit in the APB1ENR that corresponds to the desired peripheral */
	SET_BIT(RCC_APB1ENR, a_peripheral);

	/* Return the value of the bit (Should be 1)*/
	return RCC_APB1ENR & (1 << a_peripheral);
}


bool RCC_APB2_enableClock(const APB2_Peripheral a_peripheral)
{
	/* Set the bit in the APB2ENR that corresponds to the desired peripheral */
	SET_BIT(RCC_APB2ENR, a_peripheral);

	/* Return the value of the bit (Should be 1)*/
	return RCC_APB2ENR & (1 << a_peripheral);
}

/*
 * *******************************************************
 */

/* Peripherals disablers */

bool RCC_AHB1_disableClock(const AHB1_Peripheral a_peripheral)
{
	/* Set the bit in the AHB1ENR that corresponds to the desired peripheral */
	CLEAR_BIT(RCC_AHB1ENR, a_peripheral);

	/* Return the inverse of the value of the bit (Should be 1)*/
	return !(RCC_AHB1ENR & (1 << a_peripheral));
}


bool RCC_AHB2_disableClock(const AHB2_Peripheral a_peripheral)
{
	/* Set the bit in the AHB2ENR that corresponds to the desired peripheral */
	CLEAR_BIT(RCC_AHB2ENR, a_peripheral);

	/* Return the inverse of the value of the bit (Should be 1)*/
	return !(RCC_AHB2ENR & (1 << a_peripheral));
}


bool RCC_AHB3_disableClock(const AHB3_Peripheral a_peripheral)
{
	/* Set the bit in the AHB3ENR that corresponds to the desired peripheral */
	CLEAR_BIT(RCC_AHB3ENR, a_peripheral);

	/* Return the inverse of the value of the bit (Should be 1)*/
	return !(RCC_AHB3ENR & (1 << a_peripheral));
}


bool RCC_APB1_disableClock(const APB1_Peripheral a_peripheral)
{
	/* Set the bit in the APB1ENR that corresponds to the desired peripheral */
	CLEAR_BIT(RCC_APB1ENR, a_peripheral);

	/* Return the inverse of the value of the bit (Should be 1)*/
	return !(RCC_APB1ENR & (1 << a_peripheral));
}

bool RCC_APB2_disableClock(const APB2_Peripheral a_peripheral)
{
	/* Set the bit in the AHB2ENR that corresponds to the desired peripheral */
	CLEAR_BIT(RCC_APB2ENR, a_peripheral);

	/* Return the inverse of the value of the bit (Should be 1)*/
	return !(RCC_APB2ENR & (1 << a_peripheral));
}

/*
 * *******************************************************
 */

/* Clocks controls and configurations */

bool RCC_HSEBypass(const bool a_bypass)
{
	/* check to bypass oscillator or not */
	if(a_bypass)
	{
		/* Set HSEBYP bit in the RCC_CR to bypass oscillator*/
		RCC_CR |= RCC_CR_HSEBYP;

		/* Return the value of HSEBYP bit */
		if(RCC_CR & RCC_CR_HSEBYP)
		{
			return TRUE;
		}
	}
	else
	{
		/* Clear HSEBYP bit in the RCC_CR */
		RCC_CR &= ~(RCC_CR_HSEBYP);

		/* Return the inverted HSEBYP value */
		return !(RCC_CR & RCC_CR_HSEBYP);
	}
}


bool RCC_setCLockStatus(const ClockType a_clockType, const ClockStatus a_status)
{
	/* Check whether to turn the clock on or off */
	if(a_status == ON)
	{
		/* Turn on desired clock by setting its ON bit in the RCC_CR */
		SET_BIT(RCC_CR, a_clockType);

		/* Pool on the ready flag of the desired clock till the clock
		 * is ready.
		 *
		 * Note that the relation between the ready flag and the ON bit
		 * of each clock is (ready flag = ON bit + 1)
		 */
		while(BIT_IS_CLEAR(RCC_CR, (a_clockType + 1)));
	}
	else if(a_status == OFF)
	{
		/* Turn off desired clock by clearing its ON bit in the RCC_CR */
		CLEAR_BIT(RCC_CR, a_clockType);
	}
	return TRUE;
}


bool RCC_getClockStatus(const ClockType a_clockType)
{
	/* Return the status of the ready flag of the corresponding clock type.
	 *
	 * Note that the relation between the ready flag and the passed ClockType
	 * of each clock is (ready flag = ClockType + 1)
	 */
	return BIT_IS_SET(RCC_CR, (a_clockType + 1));
}


uint8 RCC_getCLockSource(void)
{
	/* Return the value of the SWS bits of the RCC_CFGR */
	return (uint8)((RCC_CFGR & (RCC_CFGR_SWS)) >> 2);
}


sint8 RCC_setCLockSource(const SystemClock a_systemClock)
{
	/* Check if the passed clock is OFF */
	if(a_systemClock == SC_HSI)
	{
		if(!(RCC_getClockStatus(HSI)))
		{
			return -1;
		}
	}
	else if(a_systemClock == SC_HSE)
	{
		if(!(RCC_getClockStatus(HSE)))
		{
			return -1;
		}
	}
	else
	{
		if(!(RCC_getClockStatus(PLL)))
		{
			return -1;
		}
	}

	/* Set the passed clock as system clock by putting its
	 * corresponding value in the SW bits of the RCC_CFGR.
	 *
	 * 00: HSI oscillator selected as system clock
	 * 01: HSE oscillator selected as system clock
	 * 10: PLL_P selected as system clock
	 * 11: PLL_R selected as system clock
	 *
	 * The passed argument equals to the required value of
	 * the two SW bits.
	 */

	/* Firstly, clear the two SW bits */
	RCC_CFGR &= ~RCC_CFGR_SW;

	/* Secondly, put the suitable value in the SW bits */
	RCC_CFGR |= a_systemClock;

	/* Return the system clock after changed */
	return RCC_getCLockSource();
}




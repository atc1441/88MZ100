#include <stdio.h>
#include <stdint.h>
#include "core_cm3.h"
#include "mz100_gpio.h"
#include "mz100_driver.h"
#include "mz100_pinmux.h"
#include "pinmux_reg.h"
#include "gpio_reg.h"

/****************************************************************************//**
 * @brief      Set one GPIO pin direction 
 *
 * @param[in]  gpioNo:  Select the GPIO pin.
 * @param[in]  dir:  Data transfer direction, should be GPIO_INPUT or GPIO_OUTPUT.
 *
 * @return none
 *
 *******************************************************************************/
void GPIO_SetPinDir(GPIO_NO_Type gpioNo, GPIO_Dir_Type dir)
{
  if ( dir )
    GPIO->GPDR.WORDVAL |= (1UL << gpioNo);
  else
    GPIO->GPDR.WORDVAL &= ~(1UL << gpioNo);
}

/****************************************************************************//**
 * @brief      Write one GPIO pin output 
 *
 * @param[in]  gpioNo:  Select the GPIO pin.
 * @param[in]  bitVal:  Value to be write to GPIO pin, should be GPIO_LOW or GPIO_HIGH.
 *
 * @return none
 *
 *******************************************************************************/
void GPIO_WritePinOutput(GPIO_NO_Type gpioNo, GPIO_IO_Type bitVal)
{
	if(bitVal)
		GPIO->GPLR.WORDVAL |= (1UL << gpioNo);
	else
		GPIO->GPLR.WORDVAL &= ~(1UL << gpioNo);
}

/****************************************************************************//**
 * @brief      Read one GPIO pin level of input or output
 *
 * @param[in]  gpioNo:  Select the GPIO pin.
 *
 * @return  Value read from GPIO pin, should be GPIO_IO_LOW or GPIO_IO_HIGH
 *
 *******************************************************************************/
GPIO_IO_Type GPIO_ReadPinLevel(GPIO_NO_Type gpioNo)
{
  uint32_t gpioVal; 

  GPIO_IO_Type retVal;

  /* Get the GPIO pin value regardless of input and output */ 
  gpioVal = GPIO->GPRS.WORDVAL & (0x01 << gpioNo); 

  retVal = (gpioVal? HIGH : LOW);

  return retVal;
}

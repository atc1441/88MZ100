#include <stdio.h>
#include <stdint.h>
#include "core_cm3.h"
#include "mz100_gpio.h"
#include "pinmux_reg.h"
#include "mz100_pinmux.h"

void GPIO_PinMuxFun(GPIO_NO_Type gpioNo, GPIO_PinMuxFunc_Type PinMuxFun)
{
	if(PinMuxFun==0)
	{
		PINMUX->GPIO_PINMUX[gpioNo].BF.FSEL_XR = (PinMuxFun & 0x07);
	}
	else
	{
		PINMUX->GPIO_PINMUX[gpioNo].BF.PIO_PULL_SEL_R = 0;
		PINMUX->GPIO_PINMUX[gpioNo].BF.FSEL_XR = (PinMuxFun & 0x07); 
	}
}

/****************************************************************************//**
 * @brief      GPIO pin mode function define
 *
 * @param[in]  gpioNo:  Select the GPIO pin.
 * @param[in]  gpioPinMode:  GPIO pin mode, should be PINMODE_DEFAULT, PINMODE_PULLUP, 
 *                           PINMODE_PULLDOWN, PINMODE_NOPULL or PINMODE_TRISTATE.
 *                           when this pin is not configured as GPIO function, 
 *                           or the data transfer direction is not input,
 *                           PINMODE_PULLUP, PINMODE_PULLDOWN or PINMODE_TRISTATE has no use.
 *
 * @return none
 *
 *******************************************************************************/
void GPIO_PinModeConfig(GPIO_NO_Type gpioNo, GPIO_PINMODE_Type gpioPinMode)
{
 switch(gpioPinMode)
  {
    case PINMODE_DEFAULT:
      /* Default */
      PINMUX->GPIO_PINMUX[gpioNo].BF.DI_EN = 0;
      PINMUX->GPIO_PINMUX[gpioNo].BF.PIO_PULL_SEL_R = 0;
      break;
      
    case PINMODE_PULLUP:
      /* Pullup */
      PINMUX->GPIO_PINMUX[gpioNo].BF.DI_EN = 0;
      PINMUX->GPIO_PINMUX[gpioNo].BF.PIO_PULL_SEL_R = 1;
      PINMUX->GPIO_PINMUX[gpioNo].BF.PIO_PULLUP_R = 1;
      PINMUX->GPIO_PINMUX[gpioNo].BF.PIO_PULLDN_R = 0;	  
      break;

    case PINMODE_PULLDOWN:
      /* Pulldown */
      PINMUX->GPIO_PINMUX[gpioNo].BF.DI_EN = 0;
      PINMUX->GPIO_PINMUX[gpioNo].BF.PIO_PULL_SEL_R = 1;
      PINMUX->GPIO_PINMUX[gpioNo].BF.PIO_PULLUP_R = 0;
      PINMUX->GPIO_PINMUX[gpioNo].BF.PIO_PULLDN_R = 1;	
      break;

	 case PINMODE_NOPULL:
      /* Nopull */
      PINMUX->GPIO_PINMUX[gpioNo].BF.DI_EN = 0;
      PINMUX->GPIO_PINMUX[gpioNo].BF.PIO_PULL_SEL_R = 1;
      PINMUX->GPIO_PINMUX[gpioNo].BF.PIO_PULLUP_R = 0;
      PINMUX->GPIO_PINMUX[gpioNo].BF.PIO_PULLDN_R = 0;	
      break;

    case PINMODE_TRISTATE:
      /* Tristate */
      PINMUX->GPIO_PINMUX[gpioNo].BF.DI_EN = 1;                                                                        
      PINMUX->GPIO_PINMUX[gpioNo].BF.PIO_PULL_SEL_R = 1;
      PINMUX->GPIO_PINMUX[gpioNo].BF.PIO_PULLUP_R = 0;
      PINMUX->GPIO_PINMUX[gpioNo].BF.PIO_PULLDN_R = 0;	
      break;

    default:
      break;
  }
}


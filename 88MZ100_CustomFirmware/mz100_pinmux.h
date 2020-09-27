#pragma once

#include "mz100.h"
#include "mz100_driver.h"
#include "mz100_gpio.h"

typedef enum
{
  PINMUX_FUNCTION_0 = 0,                   /*!< GPIO pin mux function 0 define */
  PINMUX_FUNCTION_1,                       /*!< GPIO pin mux function 1 define */
  PINMUX_FUNCTION_2,                       /*!< GPIO pin mux function 2 define */
  PINMUX_FUNCTION_3,                       /*!< GPIO pin mux function 3 define */
  PINMUX_FUNCTION_4,                       /*!< GPIO pin mux function 4 define */
  PINMUX_FUNCTION_5,                       /*!< GPIO pin mux function 5 define */
  PINMUX_FUNCTION_6,                       /*!< GPIO pin mux function 6 define */
  PINMUX_FUNCTION_7,                       /*!< GPIO pin mux function 7 define */
}GPIO_PinMuxFunc_Type;

#define PINMUX_GPIO PINMUX_FUNCTION_0
/**  
 *  @brief GPIO pin mode type definition 
 */
typedef enum
{
  PINMODE_DEFAULT = 0,                      /*!< GPIO pin mode default define */
  PINMODE_PULLUP,                          /*!< GPIO pin mode pullup define */
  PINMODE_PULLDOWN,                        /*!< GPIO pin mode pulldown define */
  PINMODE_NOPULL,                          /*!< GPIO pin mode nopull define */
  PINMODE_TRISTATE,                        /*!< GPIO pin mode tristate define */
}GPIO_PINMODE_Type;

/**
 *  @brief Seiral FLASH mode type definition
 */
typedef enum
{
  MODE_SHUTDOWN = 0,                    /*!< SFLASH mode shutdown define */
  MODE_DEFAULT,                         /*!< SFLASH mode default define */
}SFLASH_MODE_Type;


void GPIO_PinMuxFun(GPIO_NO_Type gpioNo, GPIO_PinMuxFunc_Type pinMuxFun);
void GPIO_PinModeConfig(GPIO_NO_Type gpioNo, GPIO_PINMODE_Type gpioPinMode);

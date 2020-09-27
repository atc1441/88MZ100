#pragma once

#include "mz100_driver.h"

#define GPIO_MinNo        GPIO_0
#define GPIO_MaxNo        GPIO_31

typedef enum
{
  GPIO_0,                           /*!< GPIO0  Pin define */
  GPIO_1,                           /*!< GPIO1  Pin define */
  GPIO_2,                           /*!< GPIO2  Pin define */
  GPIO_3,                           /*!< GPIO3  Pin define */
  GPIO_4,                           /*!< GPIO4  Pin define */
  GPIO_5,                           /*!< GPIO5  Pin define */
  GPIO_6,                           /*!< GPIO6  Pin define */
  GPIO_7,                           /*!< GPIO7  Pin define */
  GPIO_8,                           /*!< GPIO8  Pin define */
  GPIO_9,                           /*!< GPIO9  Pin define */
  GPIO_10,                          /*!< GPIO10 Pin define */
  GPIO_11,                          /*!< GPIO11 Pin define */
  GPIO_12,                          /*!< GPIO12 Pin define */
  GPIO_13,                          /*!< GPIO13 Pin define */
  GPIO_14,                          /*!< GPIO14 Pin define */
  GPIO_15,                          /*!< GPIO15 Pin define */
  GPIO_16,                          /*!< GPIO16 Pin define */
  GPIO_17,                          /*!< GPIO17 Pin define */
  GPIO_18,                          /*!< GPIO18 Pin define */
  GPIO_19,                          /*!< GPIO19 Pin define */
  GPIO_20,                          /*!< GPIO20 Pin define */
  GPIO_21,                          /*!< GPIO21 Pin define */
  GPIO_22,                          /*!< GPIO22 Pin define */
  GPIO_23,                          /*!< GPIO23 Pin define */
  GPIO_24,                          /*!< GPIO24 Pin define */
  GPIO_25,                          /*!< GPIO25 Pin define */
  GPIO_26,                          /*!< GPIO26 Pin define */
  GPIO_27,                          /*!< GPIO27 Pin define */
  GPIO_28,                          /*!< GPIO28 Pin define */
  GPIO_29,                          /*!< GPIO29 Pin define */
  GPIO_30,                          /*!< GPIO30 Pin define */
  GPIO_31,                          /*!< GPIO31 Pin define */ 
}GPIO_NO_Type;

/**  
 *  @brief GPIO data direction type definition 
 */
typedef enum
{
  GPIO_INPUT = 0,                             /*!< Set GPIO port data direction as input */  
  GPIO_OUTPUT,	                              /*!< Set GPIO port data direction as output */
}GPIO_Dir_Type;

/**  
 *  @brief GPIO data Input/Output type definition 
 */
typedef enum
{
  LOW = 0,                            /*!< Set GPIO port data Input/Output value as low  */  
  HIGH,	                              /*!< Set GPIO port data Input/Output value as high */
}GPIO_IO_Type;

/**  
 *  @brief GPIO interrut level type definition 
 */
typedef enum
{
  GPIO_INT_RISING_EDGE = 0,                    /*!< Interrupt type: Rising edge */                                       
  GPIO_INT_FALLING_EDGE,                       /*!< Interrupt type: Falling edge */
  GPIO_INT_BOTH_EDGES,                         /*!< Interrupt type: Rising edge and Falling edge */
  GPIO_INT_DISABLE,                            /*!< Disable interrupt */
}GPIO_Int_Type;

void GPIO_SetPinDir(GPIO_NO_Type gpioNo, GPIO_Dir_Type dir);
void GPIO_WritePinOutput(GPIO_NO_Type gpioNo, GPIO_IO_Type bitVal);
GPIO_IO_Type GPIO_ReadPinLevel(GPIO_NO_Type gpioNo);
#pragma once

#include "mz100.h"


void delay(int cnt);

/**
 * @brief Functional State Definition
 */
typedef enum 
{
  DISABLE  = 0, 
  ENABLE   = 1
}FunctionalState;

/**
 * @brief status type definition
 */
typedef enum 
{
  DERROR = 0, 
  DSUCCESS = !DERROR
}Status;

/**
 * @brief Flag status Type definition
 */
typedef enum 
{
  RESET = 0, 
  SET = !RESET
}FlagStatus, IntStatus;

/**
 * @brief Logical status Type definition
 */
typedef enum 
{
  LOGIC_LO = 0, 
  LOGIC_HI = !LOGIC_LO
}LogicalStatus;

/**
 * @brief Active status Type definition
 */
typedef enum 
{
  DEACTIVE = 0, 
  ACTIVE = !DEACTIVE
}ActiveStatus;

/**
 * @brief interrupt mask Type definition
 */
typedef enum 
{
  UNMASK = 0, 
  MASK = 1
}IntMask_Type;

/**
 * @brief Null Type definition
 */
#ifndef NULL
#define NULL   0
#endif

/**  
 *  @brief Interrupt callback function type
 */
typedef void (intCallback_Type)(void);

/**
 * @brief MC200 peripheral type definitions
 */
typedef enum
{
  INT_EXTPIN0,
  INT_EXTPIN1,
  INT_RTC,
  INT_CRC,
  INT_AES,
  INT_I2C0,
  INT_I2C1,
  INT_I2C2,
  INT_DMA_CH0,
  INT_DMA_CH1,
  INT_DMA_CH2,
  INT_DMA_CH3,
  INT_DMA_CH4,
  INT_DMA_CH5,
  INT_DMA_CH6,
  INT_DMA_CH7,
  INT_GPIO,
  INT_SSP0,
  INT_SSP1,
  INT_SSP2,
  INT_QSPI0,
  INT_QSPI1,
  INT_GPT0,
  INT_GPT1,
  INT_GPT2,
  INT_GPT3,
  INT_UART0,
  INT_UART1,
  INT_UART2,
  INT_UART3,
  INT_WDT,
  INT_ADC0,
  INT_ADC1,
  INT_DAC,
  INT_ACOMP,
  INT_SDIO,
  INT_USB,
  INT_RC32M,
  INT_MPU,
  LAST,
}INT_Peripher_Type; 

/*@} end of group DRIVER_Public_Types */


/** @defgroup DRIVER_Public_Constants
 *  @{
 */ 
/** @defgroup DRIVER_FUNCTIONALSTATE    
 *  @{
 */
#define PARAM_FUNCTIONALSTATE(State) (((State) == DISABLE) || ((State) == ENABLE))
/*@} end of group DRIVER_FUNCTIONALSTATE */

/** @defgroup DRIVER_INT_PERIPH    
 *  @{
 */
#define IS_INT_PERIPH(INT_PERIPH)       ((INT_PERIPH) < LAST)
/*@} end of group DRIVER_INT_PERIPH */

/** @defgroup DRIVER_INT_MASK     
 *  @{
 */
#define IS_INTMASK(INTMASK)          (((INTMASK) == MASK) || ((INTMASK) == UNMASK))
/*@} end of group DRIVER_INT_MASK */

/*@} end of group DRIVER_Public_Constants */

/** @defgroup DRIVER_Public_Macro
 *  @{
 */

#define CHECK_PARAM(expr) ((void)0)

/*@} end of group DRIVER_Public_Macro */

/** @defgroup DRIVER_Public_FunctionDeclaration
 *  @brief DRIVER functions declaration
 *  @{
 */
extern  intCallback_Type ** intCbfArra[];
void install_int_callback(INT_Peripher_Type intPeriph, uint32_t intType, intCallback_Type * cbFun);


#pragma once

#include "mz100.h"
#include "mz100_driver.h"

typedef enum
{
  RTC_CNT_VAL_UPDATE_OFF       = 0,   /*!< Counter value register update mode: off */
  RTC_CNT_VAL_UPDATE_AUTO      = 2,   /*!< Counter value register update mode: Auto  */
}RTC_CntValUpdateMode_Type;

/**      
 *  @brief RTC config struct type definition  
 */
typedef struct
{
  RTC_CntValUpdateMode_Type CntValUpdateMode;      /*!< Counter value register update mode:
                                                        RTC_CNT_VAL_UPDATE_OFF (0):  Off
                                                        RTC_CNT_VAL_UPDATE_AUTO (2): Auto   */
  
                                            
  uint32_t clockDivider;                          /*!< Clock divider value(range: 0~15).
                                                       The divided clock is calculated by:
                                                       CLK_div = CLK / (2^clockDivider)*/  
  
  uint32_t uppVal;                                /*!< Counter overflow value */

}RTC_Config_Type;



/*@} end of group RTC_Public_Types definitions */


/** @defgroup RTC_Public_Constants
 *  @{
 */ 

#define RTC_INT_CNT_UPP   0

/*@} end of group RTC_Public_Constants */

/** @defgroup RTC_Public_Macro
 *  @{
 */

/*@} end of group RTC_Public_Macro */


/** @defgroup RTC_Public_FunctionDeclaration
 *  @brief RTC functions statement
 *  @{
 */
void RTC_Init(RTC_Config_Type* rtcConfig);

Status RTC_CounterReset(void);
FunctionalState RTC_GetCntStatus(void);
void RTC_Start(void);
void RTC_Stop(void);

void RTC_SetCounterUppVal( uint32_t uppVal);
uint32_t RTC_GetCounterUppVal(void);
uint32_t RTC_GetCounterVal(void);

void RTC_IntMask(IntMask_Type intMsk);
FlagStatus RTC_GetStatus(void);
void RTC_IntClr(void);

void RTC_IRQHandler(void);

 


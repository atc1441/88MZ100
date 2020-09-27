#pragma once

typedef void( *intfunc )( void );
typedef union { intfunc __fun; void * __ptr; } intvec_elem;

/**
 * \brief Interrupt Number Definition, according to the selected device 
 *        in @ref Library_configuration_section 
 */
typedef enum IRQn
{
/******  Cortex-M3 Processor Exceptions Numbers ***************************************************/
  NonMaskableInt_IRQn         = -14,    /*!< 2 Non Maskable Interrupt                             */
  MemoryManagement_IRQn       = -12,    /*!< 4 Cortex-M3 Memory Management Interrupt              */
  BusFault_IRQn               = -11,    /*!< 5 Cortex-M3 Bus Fault Interrupt                      */
  UsageFault_IRQn             = -10,    /*!< 6 Cortex-M3 Usage Fault Interrupt                    */
  SVCall_IRQn                 = -5,     /*!< 11 Cortex-M3 SV Call Interrupt                       */
  DebugMonitor_IRQn           = -4,     /*!< 12 Cortex-M3 Debug Monitor Interrupt                 */
  PendSV_IRQn                 = -2,     /*!< 14 Cortex-M3 Pend SV Interrupt                       */
  SysTick_IRQn                = -1,     /*!< 15 Cortex-M3 System Tick Interrupt                   */

/******  specific Interrupt Numbers ***************************************************************/
  RTC_IRQn                    = 0,      /*!< RTC Interrupt                                        */
  a1                          = 1,      /*!< UNKNOWN                                              */
  a2                          = 2,      /*!< UNKNOWN                                              */
  RC32M_IRQn                  = 3,      /*!< RC32M Interrupt                                      */
  a3                          = 4,      /*!< UNKNOWN BUT USED                                     */
  a4                          = 5,      /*!< UNKNOWN                                              */
  a5                          = 6,      /*!< UNKNOWN                                              */
  a6                          = 7,      /*!< UNKNOWN                                              */
  ADC_IRQn                    = 8,      /*!< ADC Interrupt                                        */
  a7                          = 9,      /*!< UNKNOWN                                              */
  a8                          = 10,     /*!< UNKNOWN                                              */
  a9                          = 11,     /*!< UNKNOWN                                              */
  AES_IRQn                    = 12,     /*!< AES Interrupt                                        */
  a10                         = 13,     /*!< UNKNOWN                                              */
  a11                         = 14,     /*!< UNKNOWN                                              */
  a12                         = 15,     /*!< UNKNOWN                                              */
  GPIO_IRQn                   = 16,     /*!< GPIO Interrupt                                       */
  a13                         = 17,     /*!< UNKNOWN                                              */
  a14                         = 18,     /*!< UNKNOWN                                              */
  QSPI_IRQn                   = 19,     /*!< QSPI  Interrupt                                      */
  a15                         = 20,     /*!< UNKNOWN                                              */
  a16                         = 21,     /*!< UNKNOWN                                              */
  UART0_IRQn                  = 22,     /*!< UART0 Interrupt                                      */
  UART1_IRQn                  = 23,     /*!< UART1 Interrupt                                      */
  ZIGBEE_IRQn                 = 24,     /*!< ZIGBEE_IRQn                                          */
  a17                         = 25,     /*!< UNKNOWN                                              */
  ZIGBEE1_IRQn                = 24,     /*!< ZIGBEE1_IRQn                                         */
  a18                         = 27,     /*!< UNKNOWN                                              */
  a19                         = 28,     /*!< UNKNOWN                                              */
  a20                         = 29,     /*!< UNKNOWN                                              */
  a21                         = 30,     /*!< UNKNOWN                                              */
  ExtPin0_IRQn                = 31,     /*!< External Pin 0 Interrupt                             */
  ExtPin1_IRQn                = 32,     /*!< External Pin 1 Interrupt                             */
  ExtPin2_IRQn                = 33,     /*!< External Pin 2 Interrupt                             */
  ExtPin3_IRQn                = 34,     /*!< External Pin 3 Interrupt                             */
  ExtPin4_IRQn                = 35,     /*!< External Pin 4 Interrupt                             */
  ExtPin5_IRQn                = 36,     /*!< External Pin 5 Interrupt                             */
  ExtPin6_IRQn                = 37,     /*!< External Pin 6 Interrupt                             */
  ExtPin7_IRQn                = 38,     /*!< External Pin 7 Interrupt                             */
  ExtPin8_IRQn                = 39,     /*!< External Pin 8 Interrupt                             */
  ExtPin9_IRQn                = 40,     /*!< External Pin 9 Interrupt                             */
  ExtPin10_IRQn               = 41,     /*!< External Pin 10 Interrupt                            */
  ExtPin11_IRQn               = 42,     /*!< External Pin 11 Interrupt                            */
  ExtPin12_IRQn               = 43,     /*!< External Pin 12 Interrupt                            */
  ExtPin13_IRQn               = 44,     /*!< External Pin 13 Interrupt                            */
  ExtPin14_IRQn               = 45,     /*!< External Pin 14 Interrupt                            */
  ExtPin15_IRQn               = 46,     /*!< External Pin 15 Interrupt                            */
  ExtPin16_IRQn               = 47,     /*!< External Pin 16 Interrupt                            */
  ExtPin17_IRQn               = 48,     /*!< External Pin 17 Interrupt                            */
  ExtPin18_IRQn               = 49,     /*!< External Pin 18 Interrupt                            */
  ExtPin19_IRQn               = 50,     /*!< External Pin 19 Interrupt                            */
  ExtPin20_IRQn               = 51,     /*!< External Pin 20 Interrupt                            */
  ExtPin21_IRQn               = 52,     /*!< External Pin 21 Interrupt                            */
  ExtPin22_IRQn               = 53,     /*!< External Pin 22 Interrupt                            */
  ExtPin23_IRQn               = 54,     /*!< External Pin 23 Interrupt                            */
  ExtPin24_IRQn               = 55,     /*!< External Pin 24 Interrupt                            */
  ExtPin25_IRQn               = 56,     /*!< External Pin 25 Interrupt                            */
  ExtPin26_IRQn               = 57,     /*!< External Pin 26 Interrupt                            */
  ExtPin27_IRQn               = 58,     /*!< External Pin 27 Interrupt                            */
  ExtPin28_IRQn               = 59,     /*!< External Pin 28 Interrupt                            */
  a22                         = 60,     /*!< UNKNOWN                                              */
  a23                         = 61,     /*!< UNKNOWN                                              */
} IRQn_Type;
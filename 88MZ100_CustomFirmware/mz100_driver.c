#include "mz100_driver.h"
#include "mz100.h"
#include "mz100_uart.h"


void delay(int cnt){
	volatile unsigned int i;
	for ( i = 107*cnt; i; --i );
}

intCallback_Type * extpin0IntCb[]= {NULL};

intCallback_Type * extpin1IntCb[]= {NULL};

/**  
 *  @brief RTC interrupt callback function pointer array
 */
intCallback_Type * rtcIntCb[]= {NULL, NULL, NULL, NULL,NULL,NULL,NULL,NULL};

/**  
 *  @brief CRC interrupt callback function pointer array
 */
intCallback_Type * crcIntCb[]= {NULL, NULL, NULL, NULL,NULL,NULL,NULL,NULL};

/**  
 *  @brief AES interrupt callback function pointer array
 */
intCallback_Type * aesIntCb[]= {NULL, NULL, NULL, NULL,NULL,NULL,NULL,NULL};

/**  
 *  @brief I2C interrupt callback function pointer array
 */
intCallback_Type * i2c0IntCb[]= {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
intCallback_Type * i2c1IntCb[]= {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
intCallback_Type * i2c2IntCb[]= {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};

/**  
 *  @brief DMA interrupt callback function pointer array
 */
intCallback_Type * dmaCh0IntCb[]= {NULL, NULL, NULL, NULL, NULL};
intCallback_Type * dmaCh1IntCb[]= {NULL, NULL, NULL, NULL, NULL};
intCallback_Type * dmaCh2IntCb[]= {NULL, NULL, NULL, NULL, NULL};
intCallback_Type * dmaCh3IntCb[]= {NULL, NULL, NULL, NULL, NULL};
intCallback_Type * dmaCh4IntCb[]= {NULL, NULL, NULL, NULL, NULL};
intCallback_Type * dmaCh5IntCb[]= {NULL, NULL, NULL, NULL, NULL};
intCallback_Type * dmaCh6IntCb[]= {NULL, NULL, NULL, NULL, NULL};
intCallback_Type * dmaCh7IntCb[]= {NULL, NULL, NULL, NULL, NULL};

/**  
 *  @brief GPIO interrupt callback function pointer array
 */
intCallback_Type * gpioIntCb[]= {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};

/**  
 *  @brief SSP interrupt callback function pointer array
 */
intCallback_Type * ssp0IntCb[]= {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
intCallback_Type * ssp1IntCb[]= {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
intCallback_Type * ssp2IntCb[]= {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};

/**  
 *  @brief QSPI interrupt callback function pointer array
 */
intCallback_Type * qspi0IntCb[]= {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
intCallback_Type * qspi1IntCb[]= {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};

/**  
 *  @brief GPT interrupt callback function pointer array
 */
intCallback_Type * gpt0IntCb[]= {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
intCallback_Type * gpt1IntCb[]= {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
intCallback_Type * gpt2IntCb[]= {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
intCallback_Type * gpt3IntCb[]= {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};

/**  
 *  @brief UART interrupt callback function pointer array
 */
intCallback_Type * uart0IntCb[]= {NULL, NULL, NULL, NULL, NULL, NULL};
intCallback_Type * uart1IntCb[]= {NULL, NULL, NULL, NULL, NULL, NULL};
intCallback_Type * uart2IntCb[]= {NULL, NULL, NULL, NULL, NULL, NULL};
intCallback_Type * uart3IntCb[]= {NULL, NULL, NULL, NULL, NULL, NULL};

/**  
 *  @brief WDT interrupt callback function pointer array
 */
intCallback_Type * wdtIntCb[]= {NULL, NULL, NULL, NULL, NULL};

/**  
 *  @brief ADC interrupt callback function pointer array
 */
intCallback_Type * adc0IntCb[]= {NULL, NULL, NULL, NULL, NULL};
intCallback_Type * adc1IntCb[]= {NULL, NULL, NULL, NULL, NULL};

/**  
 *  @brief DAC interrupt callback function pointer array
 */
intCallback_Type * dacIntCb[]= {NULL, NULL, NULL, NULL, NULL};

/**  
 *  @brief COMP interrupt callback function pointer array
 */
intCallback_Type * acompIntCb[]= {NULL, NULL, NULL, NULL};



/**  
 *  @brief SDIO interrupt callback function pointer array
 */
intCallback_Type * sdioIntCb[]= {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                                 NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};

/**  
 *  @brief USB interrupt callback function pointer array
 */
intCallback_Type * usbIntCb[]= {NULL, NULL, NULL};

/**  
 *  @brief RC32M interrupt callback function pointer array
 */
intCallback_Type * rc32mIntCb[]= {NULL, NULL};

/**  
 *  @brief MPU interrupt callback function pointer array
 */
intCallback_Type * mpuIntCb[]= {NULL, NULL, NULL, NULL};

/**  
 *  @brief Digger interrupt callback function pointer array
 */
intCallback_Type ** intCbfArra[] = {extpin0IntCb, extpin1IntCb,
rtcIntCb, crcIntCb, aesIntCb, i2c0IntCb, i2c1IntCb, i2c2IntCb, 
                                    dmaCh0IntCb, dmaCh1IntCb, dmaCh2IntCb, dmaCh3IntCb, dmaCh4IntCb, dmaCh5IntCb, dmaCh6IntCb, dmaCh7IntCb, 
                                    gpioIntCb, ssp0IntCb, ssp1IntCb, ssp2IntCb, qspi0IntCb, qspi1IntCb,
                                    gpt0IntCb, gpt1IntCb, gpt2IntCb, gpt3IntCb, uart0IntCb, uart1IntCb, uart2IntCb, uart3IntCb, 
                                    wdtIntCb, adc0IntCb, adc1IntCb, dacIntCb, 
                                    acompIntCb, sdioIntCb, usbIntCb, rc32mIntCb, mpuIntCb};  

/****************************************************************************//**
 * @brief      Install interrupt callback function for given interrupt type and peripheral 
 *
 * @param[in]  intPeriph:  Select the peripheral, such as INT_UART1,INT_AES
 * @param[in]  intType: Specifies the interrupt type. must be select interrupt enum type 
 *             defined as XXXX_INT_Type(XXXX here is peripher name) in mc200_xxx.h. 
               There is a exception for GPIO,that interrupt type is the GPIO_NO_Type.
 * @param[in]  cbFun:  Pointer to interrupt callback function. The type should be 
 *             void (*fn)(void).
 *
 * @return none
 *
 *******************************************************************************/
void install_int_callback(INT_Peripher_Type intPeriph, uint32_t intType, intCallback_Type * cbFun)
{
  /* Check the parameters */
  CHECK_PARAM(IS_INT_PERIPH(intPeriph));

  intCbfArra[intPeriph][intType] = cbFun;
}
#pragma once

#include <stdint.h>

#ifdef __cplusplus
 extern "C" {
#endif

#define PERI_AHB_BASE         ((uint32_t)0x44000000)            /*!< AHB Peripheral base address */
#define DMA_BASE              ((uint32_t)0x44000000)            /*!< DMA controller base address */
#define USB_BASE              ((uint32_t)0x44001000)            /*!< USB controller base address */
#define SDIO_BASE             ((uint32_t)0x44002000)            /*!< SDIO module base address */
#define FLASHC_BASE           ((uint32_t)0x44003000)            /*!< FALSH controller base address */
#define AES_BASE              ((uint32_t)0x45000000)            /*!< AES module base address */
#define CRC_BASE              ((uint32_t)0x46000000)            /*!< CRC module base address */

#define PERI_APB0_BASE        ((uint32_t)0x46000000)            /*!< APB0 Peripheral base address */
#define I2C0_BASE             ((uint32_t)0x46000000)            /*!< I2C0 module base address */
#define QSPI0_BASE            ((uint32_t)0x4A070000)            /*!< QSPI0 module base address */
#define QSPI1_BASE            ((uint32_t)0x4A070000)            /*!< QSPI0 module base address */
#define SSP0_BASE             ((uint32_t)0x4A050000)            /*!< SPI0 module base address */
#define SSP1_BASE             ((uint32_t)0x4A060000)            /*!< SPI1 module base address */
#define UART0_BASE            ((uint32_t)0x48010000)            /*!< UART0 module base address */
#define UART1_BASE            ((uint32_t)0x48020000)            /*!< UART1 module base address */
#define GPIO_BASE             ((uint32_t)0x4A040000)            /*!< GPIO module base address */
#define GPT0_BASE             ((uint32_t)0x46070000)            /*!< GPT0 module base address */
#define GPT1_BASE             ((uint32_t)0x46080000)            /*!< GPT1 module base address */
#define RC32M_BASE            ((uint32_t)0x48000100)            /*!< RC32M module base address */
#define CAUTOP_BASE           ((uint32_t)0x460B0000)            /*!< CAU TOP base address */
#define ADC0_BASE             ((uint32_t)0x4A030000)            /*!< ADC0 module base address */
#define ADC1_BASE             ((uint32_t)0x460B0100)            /*!< ADC1 module base address */
#define DAC_BASE              ((uint32_t)0x460B0200)            /*!< DAC module base address */
#define ACOMP_BASE            ((uint32_t)0x460B0300)            /*!< ACOMP module base address */

#define PERI_APB1_BASE        ((uint32_t)0x48000000)            /*!< APB1 Peripheral base address */
#define SSP2_BASE             ((uint32_t)0x48000000)            /*!< SPI2 module base address */
#define PINMUX_BASE           ((uint32_t)0x48070000)            /*!< PINMUX module base address */
#define WDT_BASE              ((uint32_t)0x48030000)            /*!< WDT module base address */
#define I2C1_BASE             ((uint32_t)0x48050000)            /*!< I2C1 module base address */
#define I2C2_BASE             ((uint32_t)0x48060000)            /*!< I2C2 module base address */
#define GPT2_BASE             ((uint32_t)0x48070000)            /*!< GPT2 module base address */
#define GPT3_BASE             ((uint32_t)0x48080000)            /*!< GPT3 module base address */
#define RTC_BASE              ((uint32_t)0x48040000)            /*!< RTC module base address */
#define PMU_BASE              ((uint32_t)0x4A080000)            /*!< PMU module base address */
#define SYS_CONTROL_BASE      ((uint32_t)0x480B0000)            /*!< System Control module base address */

/** \brief Configuration of the Cortex-M3 Processor and Core Peripherals */
#define __MPU_PRESENT             1         /*!< MPU present or not                               */
#define __NVIC_PRIO_BITS          4         /*!< Number of Bits used for Priority Levels          */
#define __Vendor_SysTickConfig    0         /*!< Set to 1 if different SysTick Config is used     */

#define DMA           ((dma_reg_t *) DMA_BASE)                /*!< DMA Register */
#define USBC          ((usbc_reg_t *) USB_BASE)               /*!< USBC Register */
#define SDIO          ((sdio_reg_t *) SDIO_BASE)              /*!< SDIO Register */
#define FLASHC        ((flashc_reg_t *) FLASHC_BASE)          /*!< FLASHC Register */
#define AES           ((aes_reg_t *) AES_BASE)                /*!< AES Register */
#define CRC           ((crc_reg_t *) CRC_BASE)                /*!< CRC Register */


#define I2C0          ((i2c_reg_t *) I2C0_BASE)               /*!< I2C0 Register */
#define QSPI0         ((qspi_reg_t *) QSPI0_BASE)             /*!< QSPI0 Register */
#define SSP0          ((ssp_reg_t *) SSP0_BASE)               /*!< SSP0 Register */
#define SSP1          ((ssp_reg_t *) SSP1_BASE)               /*!< SSP1 Register */
#define UART0         ((uart_reg_t *) UART0_BASE)             /*!< UART0 Register */
#define UART1         ((uart_reg_t *) UART1_BASE)             /*!< UART1 Register */
#define GPIO          ((gpio_reg_t *) GPIO_BASE)              /*!< GPIO Register */
#define GPT0          ((gpt_reg_t *) GPT0_BASE)              /*!< GPT0 Register */
#define GPT1          ((gpt_reg_t *) GPT1_BASE)              /*!< GPT1 Register */
#define QSPI1         ((qspi_reg_t *) QSPI1_BASE)             /*!< QSPI1 Register */
#define RC32M         ((rc32m_reg_t *) RC32M_BASE)            /*!< RC32M Register */
#define ADC0          ((adc_reg_t *) ADC0_BASE)               /*!< ADC0 Register */
#define ADC1          ((adc_reg_t *) ADC1_BASE)               /*!< ADC1 Register */
#define DAC           ((dac_reg_t *) DAC_BASE)                /*!< DAC Register */
#define ACOMP         ((acomp_reg_t *) ACOMP_BASE)            /*!< ACOMP Register */

#define SSP2          ((ssp_reg_t *) SSP2_BASE)               /*!< SSP2 Register */
#define PINMUX        ((pinmux_reg_t *) PINMUX_BASE)          /*!< PINMUX Register */
#define UART2         ((uart_reg_t *) UART2_BASE)             /*!< UART2 Register */
#define UART3         ((uart_reg_t *) UART3_BASE)             /*!< UART3 Register */
#define WDT           ((wdt_reg_t *) WDT_BASE)                /*!< WDT Register */
#define I2C1          ((i2c_reg_t *) I2C1_BASE)               /*!< I2C1 Register */
#define I2C2          ((i2c_reg_t *) I2C2_BASE)               /*!< I2C2 Register */
#define GPT2          ((gpt_reg_t *) GPT2_BASE)               /*!< GPT2 Register */
#define GPT3          ((gpt_reg_t *) GPT3_BASE)               /*!< GPT3 Register */
#define RTC           ((rtc_reg_t *) RTC_BASE)                /*!< RTC Register */
#define PMU           ((pmu_reg_t *) PMU_BASE)                /*!< PMU Register */
#define SYS_CTRL      ((sys_ctrl_reg_t *) SYS_CONTROL_BASE)   /*!< SYS_CTRL Register */

#ifdef __cplusplus
}
#endif
#pragma once

#include "mz100_driver.h"
#define CHECK_PARAM(expr) ((void)0)

typedef enum
{
  XFLASH_INTERFACE_QSPI1,        /*!< QSPI1 is selected as the interface to access the flash */     
}XFLASH_Interface_Type;

/**  
 *  @brief XFLASH protection type
 */ 
typedef enum
{
  XFLASH_PROT_NONE         = 0x00,      /*!< None protection */  
  XFLASH_PROT_UPPER_64KB   = 0x04,      /*!< Protect upper 64KB   0x0F0000 ~ 0x0FFFFF */
  XFLASH_PROT_UPPER_128KB  = 0x08,      /*!< Protect upper 128KB  0x0E0000 ~ 0x0FFFFF */
  XFLASH_PROT_UPPER_256KB  = 0x0C,      /*!< Protect upper 256KB  0x0C0000 ~ 0x0FFFFF */
  XFLASH_PROT_UPPER_512KB  = 0x10,      /*!< Protect upper 512KB  0x080000 ~ 0x0FFFFF */
  XFLASH_PROT_LOWER_64KB   = 0x24,      /*!< Protect lower 64KB   0x000000 ~ 0x00FFFF */
  XFLASH_PROT_LOWER_128KB  = 0x28,      /*!< Protect lower 128KB  0x000000 ~ 0x01FFFF */
  XFLASH_PROT_LOWER_256KB  = 0x2C,      /*!< Protect lower 256KB  0x000000 ~ 0x03FFFF */
  XFLASH_PROT_LOWER_512KB  = 0x30,      /*!< Protect lower 512KB  0x000000 ~ 0x07FFFF */
  XFLASH_PROT_ALL          = 0x14,      /*!< Protect all          0x000000 ~ 0x0FFFFF */
  XFLASH_PROT_UPPER_4KB    = 0x44,      /*!< Protect upper 4KB    0x0FF000 ~ 0x0FFFFF */
  XFLASH_PROT_UPPER_8KB    = 0x48,      /*!< Protect upper 8KB    0x0FE000 ~ 0x0FFFFF */
  XFLASH_PROT_UPPER_16KB   = 0x4C,      /*!< Protect upper 16KB   0x0FC000 ~ 0x0FFFFF */
  XFLASH_PROT_UPPER_32KB   = 0x50,      /*!< Protect upper 32KB   0x0F8000 ~ 0x0FFFFF */
  XFLASH_PROT_LOWER_4KB    = 0x64,      /*!< Protect lower 4KB    0x000000 ~ 0x000FFF */
  XFLASH_PROT_LOWER_8KB    = 0x68,      /*!< Protect lower 8KB    0x000000 ~ 0x001FFF */
  XFLASH_PROT_LOWER_16KB   = 0x6C,      /*!< Protect lower 16KB   0x000000 ~ 0x003FFF */
  XFLASH_PROT_LOWER_32KB   = 0x70,      /*!< Protect lower 32KB   0x000000 ~ 0x007FFF */
  XFLASH_PROT_LOWER_960KB  = 0x84,      /*!< Protect lower 960KB  0x000000 ~ 0x0EFFFF */
  XFLASH_PROT_LOWER_896KB  = 0x88,      /*!< Protect lower 896KB  0x000000 ~ 0x0DFFFF */
  XFLASH_PROT_LOWER_768KB  = 0x8C,      /*!< Protect lower 960KB  0x000000 ~ 0x0BFFFF */
  XFLASH_PROT_UPPER_960KB  = 0xA4,      /*!< Protect upper 960KB  0x010000 ~ 0x0FFFFF */
  XFLASH_PROT_UPPER_896KB  = 0xA8,      /*!< Protect upper 896KB  0x020000 ~ 0x0FFFFF */
  XFLASH_PROT_UPPER_768KB  = 0xAC,      /*!< Protect upper 768KB  0x040000 ~ 0x0FFFFF */
  XFLASH_PROT_LOWER_1020KB = 0xC4,      /*!< Protect lower 1020KB 0x000000 ~ 0x0FEFFF */
  XFLASH_PROT_LOWER_1016KB = 0xC8,      /*!< Protect lower 1016KB 0x000000 ~ 0x0FDFFF */
  XFLASH_PROT_LOWER_1008KB = 0xCC,      /*!< Protect lower 1008KB 0x000000 ~ 0x0FBFFF */
  XFLASH_PROT_LOWER_992KB  = 0xD0,      /*!< Protect lower 992KB  0x000000 ~ 0x0F7FFF */
  XFLASH_PROT_UPPER_1020KB = 0xE4,      /*!< Protect upper 1020KB 0x001000 ~ 0x0FFFFF */
  XFLASH_PROT_UPPER_1016KB = 0xE8,      /*!< Protect upper 1016KB 0x002000 ~ 0x0FFFFF */
  XFLASH_PROT_UPPER_1008KB = 0xEC,      /*!< Protect upper 1008KB 0x004000 ~ 0x0FFFFF */
  XFLASH_PROT_UPPER_992KB  = 0xF0,      /*!< Protect upper 992KB  0x008000 ~ 0x0FFFFF */
 }XFLASH_Protection_Type; 

/**  
 *  @brief XFLASH read mode
 */ 
typedef enum
{
  XFLASH_NORMAL_READ,                  /*!< Normal read mode */
  XFLASH_FAST_READ,                    /*!< Fast read mode */
  XFLASH_FAST_READ_DUAL_OUT,           /*!< Fast read dual output mode */
  XFLASH_FAST_READ_DUAL_IO,            /*!< Fast read dual IO mode */
  XFLASH_FAST_READ_QUAD_OUT,           /*!< Fast read quad output mode */
  XFLASH_FAST_READ_QUAD_IO,            /*!< Fast read quad IO mode */
  XFLASH_WORD_FAST_READ_QUAD_IO,       /*!< Word fast read quad IO mode */
  XFLASH_OCTAL_WORD_FAST_READ_QUAD_IO, /*!< Octal word fast read quad IO mode */
}XFLASH_ReadMode_Type; 

/**  
 *  @brief XFLASH program mode
 */ 
typedef enum
{
  XFLASH_PROGRAM_NORMAL,               /*!< Normal page program mode */
  XFLASH_PROGRAM_QUAD,                 /*!< Quad page program mode   */
}XFLASH_ProgramMode_Type; 

typedef enum
{
  QSPI_DATA_PIN_SINGLE,                    /*!< Use 1 serial interface pin  */
  QSPI_DATA_PIN_DUAL,                      /*!< Use 2 serial interface pins */
  QSPI_DATA_PIN_QUAD,                      /*!< Use 4 serial interface pins */
}QSPI_DataPin_Type;

/**
 *  @brief QSPI address pin type
 */
typedef enum
{
  QSPI_ADDR_PIN_SINGLE,                    /*!< Use 1 serial interface pin */
  QSPI_ADDR_PIN_AS_DATA,                   /*!< Use the number of pins as indicated in DATA_PIN */
}QSPI_AddrPin_Type;

/**
 *  @brief QSPI clock mode type
 */
typedef enum
{
  QSPI_POL0_PHA0,                          /*!< Inactive state of serial clock is low, data is latched on the rising edge of the serial clock   */
  QSPI_POL0_PHA1,                          /*!< Inactive state of serial clock is low, data is latched on the falling edge of the serial clock  */
  QSPI_POL1_PHA0,                          /*!< Inactive state of serial clock is high, data is latched on the falling edge of the serial clock */
  QSPI_POL1_PHA1,                          /*!< Inactive state of serial clock is high, data is latched on the rising edge of the serial clock  */
}QSPI_ClkMode_Type;


/**
 *  @brief QSPI capture clock edge type
 */
typedef enum
{
  QSPI_CAPT_EDGE_FIRST,                    /*!< Input data is captured on the first edge of the serial clock  */
  QSPI_CAPT_EDGE_SECOND,                   /*!< Input data is captured on the second edge of the serial clock */
}QSPI_CaptEdge_Type;

/**
 *  @brief QSPI transfer width type
 */
typedef enum
{
  QSPI_BYTE_LEN_1BYTE,                     /*!< 1 byte in each serial interface I/O transfer  */
  QSPI_BYTE_LEN_4BYTE,                     /*!< 4 bytes in each serial interface I/O transfer */
}QSPI_ByteLen_Type;

/**
 *  @brief QSPI prescaler type
 */
typedef enum
{
  QSPI_CLK_DIVIDE_1  = 0x1,                /*!< Serial interface clock prescaler is SPI clock / 1  */
  QSPI_CLK_DIVIDE_2  = 0x2,                /*!< Serial interface clock prescaler is SPI clock / 2  */
  QSPI_CLK_DIVIDE_3  = 0x3,                /*!< Serial interface clock prescaler is SPI clock / 3  */
  QSPI_CLK_DIVIDE_4  = 0x4,                /*!< Serial interface clock prescaler is SPI clock / 4  */
  QSPI_CLK_DIVIDE_5  = 0x5,                /*!< Serial interface clock prescaler is SPI clock / 5  */
  QSPI_CLK_DIVIDE_6  = 0x6,                /*!< Serial interface clock prescaler is SPI clock / 6  */
  QSPI_CLK_DIVIDE_7  = 0x7,                /*!< Serial interface clock prescaler is SPI clock / 7  */
  QSPI_CLK_DIVIDE_8  = 0x8,                /*!< Serial interface clock prescaler is SPI clock / 8  */
  QSPI_CLK_DIVIDE_9  = 0x9,                /*!< Serial interface clock prescaler is SPI clock / 9  */
  QSPI_CLK_DIVIDE_10 = 0xA,                /*!< Serial interface clock prescaler is SPI clock / 10 */
  QSPI_CLK_DIVIDE_11 = 0xB,                /*!< Serial interface clock prescaler is SPI clock / 11 */
  QSPI_CLK_DIVIDE_12 = 0xC,                /*!< Serial interface clock prescaler is SPI clock / 12 */
  QSPI_CLK_DIVIDE_13 = 0xD,                /*!< Serial interface clock prescaler is SPI clock / 13 */
  QSPI_CLK_DIVIDE_14 = 0xE,                /*!< Serial interface clock prescaler is SPI clock / 14 */
  QSPI_CLK_DIVIDE_15 = 0xF,                /*!< Serial interface clock prescaler is SPI clock / 15 */
  QSPI_CLK_DIVIDE_16 = 0x18,               /*!< Serial interface clock prescaler is SPI clock / 16 */
  QSPI_CLK_DIVIDE_18 = 0x19,               /*!< Serial interface clock prescaler is SPI clock / 18 */
  QSPI_CLK_DIVIDE_20 = 0x1A,               /*!< Serial interface clock prescaler is SPI clock / 20 */
  QSPI_CLK_DIVIDE_22 = 0x1B,               /*!< Serial interface clock prescaler is SPI clock / 22 */
  QSPI_CLK_DIVIDE_24 = 0x1C,               /*!< Serial interface clock prescaler is SPI clock / 24 */
  QSPI_CLK_DIVIDE_26 = 0x1D,               /*!< Serial interface clock prescaler is SPI clock / 26 */
  QSPI_CLK_DIVIDE_28 = 0x1E,               /*!< Serial interface clock prescaler is SPI clock / 28 */
  QSPI_CLK_DIVIDE_30 = 0x1F,               /*!< Serial interface clock prescaler is SPI clock / 30 */
}QSPI_PreScale_Type;

/**
 *  @brief QSPI read or write type
 */
typedef enum
{
  QSPI_R_EN,                               /*!< Read data from the serial interface */
  QSPI_W_EN,                               /*!< Write data to the serial interface  */
}QSPI_RW_Type;

/** 
 *  @brief QSPI interrupt type definition
 */
typedef enum
{
  QSPI_XFER_DONE,                          /*!< QSPI transfer done flag */
  QSPI_XFER_RDY,                           /*!< QSPI serial interface transfer ready flag */
  QSPI_RFIFO_DMA_BURST,                    /*!< QSPI read FIFO DMA burst flag */
  QSPI_WFIFO_DMA_BURST,                    /*!< QSPI write FIFO DMA burst flag */
  QSPI_RFIFO_EMPTY,                        /*!< QSPI read FIFO empty flag */
  QSPI_RFIFO_FULL,                         /*!< QSPI read FIFO full flag */
  QSPI_WFIFO_EMPTY,                        /*!< QSPI write FIFO empty flag */
  QSPI_WFIFO_FULL,                         /*!< QSPI write FIFO full flag */
  QSPI_RFIFO_UNDRFLW,                      /*!< QSPI read FIFO underflow flag */
  QSPI_RFIFO_OVRFLW,                       /*!< QSPI read FIFO overflow flag */
  QSPI_WFIFO_UNDRFLW,                      /*!< QSPI write FIFO underflow flag */
  QSPI_WFIFO_OVRFLW,                       /*!< QSPI write FIFO overflow flag */
  QSPI_INT_ALL,                            /*!< All QSPI interrupt flags */
}QSPI_INT_Type; 

/**  
 *  @brief QSPI status bit type definition 
 */
typedef enum
{
  QSPI_STATUS_XFER_RDY,                    /*!< Serial interface transfer ready */
  QSPI_STATUS_RFIFO_EMPTY,	           /*!< Read FIFO empty */
  QSPI_STATUS_RFIFO_FULL,	           /*!< Read FIFO full */
  QSPI_STATUS_WFIFO_EMPTY,	           /*!< Write FIFO empty */
  QSPI_STATUS_WFIFO_FULL,	           /*!< Write FIFO full */
  QSPI_STATUS_RFIFO_UNDRFLW,	           /*!< Read FIFO underflow */
  QSPI_STATUS_RFIFO_OVRFLW,	           /*!< Read FIFO overflow */
  QSPI_STATUS_WFIFO_UNDRFLW,	           /*!< Write FIFO underflow */
  QSPI_STATUS_WFIFO_OVRFLW,	           /*!< Write FIFO overflow */
}QSPI_Status_Type;

/** 
 *  @brief QSPI dma read/write type 
 */
typedef enum
{
  QSPI_DMA_READ = 0,                       /*!< QSPI DMA read  */    
  QSPI_DMA_WRITE,                          /*!< QSPI DMA write */
}QSPI_DMA_Type;

/** 
 *  @brief QSPI dma read/write burst type
 */
typedef enum
{
  QSPI_DMA_1DATA = 0,                      /*!< One data(each of width BYTE_LEN) is available in the Read/Write FIFO before a receive/transmit burst request is made to the DMA   */
  QSPI_DMA_4DATA,                          /*!< Four data(each of width BYTE_LEN) is available in the Read/Write FIFO before a receive/transmit burst request is made to the DMA  */
  QSPI_DMA_8DATA,                          /*!< Eight data(each of width BYTE_LEN) is available in the Read/Write FIFO before a receive/transmit burst request is made to the DMA */
  QSPI_DMA_DISABLE,                        /*!< Disable DMA read/write */    
}QSPI_DMA_Data_Type;

/**
 *  @brief QSPI  global configure type
 */
typedef struct
{
  QSPI_DataPin_Type dataPinMode;           /*!< Configure QSPI data pin */
  QSPI_AddrPin_Type addrPinMode;           /*!< Configure QSPI addr pin */
  QSPI_ClkMode_Type clkMode;               /*!< Configure QSPI clock mode */
  QSPI_CaptEdge_Type captEdge;             /*!< Configure QSPI capture clock edge */
  QSPI_ByteLen_Type byteLen;               /*!< Configure QSPI length each serial transfer */
  QSPI_PreScale_Type preScale;             /*!< Configure QSPI prescaler for serial interface */
}QSPI_CFG_Type;

/** 
 *  @brief QSPI INSTR_CNT type
 */
typedef enum
{
  QSPI_INSTR_CNT_0BYTE,                    /*!< Instrution count: 0 byte  */
  QSPI_INSTR_CNT_1BYTE,                    /*!< Instrution count: 1 byte  */
  QSPI_INSTR_CNT_2BYTE,                    /*!< Instrution count: 2 bytes */
}QSPI_INSTR_CNT_TYPE;

/** 
 *  @brief QSPI ADDR_CNT type
 */
typedef enum
{
  QSPI_ADDR_CNT_0BYTE,                     /*!< Address count: 0 byte  */
  QSPI_ADDR_CNT_1BYTE,                     /*!< Address count: 1 byte  */
  QSPI_ADDR_CNT_2BYTE,                     /*!< Address count: 2 bytes */
  QSPI_ADDR_CNT_3BYTE,                     /*!< Address count: 3 bytes */
  QSPI_ADDR_CNT_4BYTE,                     /*!< Address count: 4 bytes */
}QSPI_ADDR_CNT_TYPE;

/** 
 *  @brief QSPI RM_CNT type
 */
typedef enum
{
  QSPI_RM_CNT_0BYTE,                      /*!< Read mode count: 0 byte  */
  QSPI_RM_CNT_1BYTE,                      /*!< Read mode count: 1 byte  */
  QSPI_RM_CNT_2BYTE,                      /*!< Read mode count: 2 bytes */
}QSPI_RM_CNT_TYPE;

/** 
 *  @brief QSPI DUMMY_CNT type
 */
typedef enum
{
  QSPI_DUMMY_CNT_0BYTE,                    /*!< Dummy count: 0 byte  */
  QSPI_DUMMY_CNT_1BYTE,                    /*!< Dummy count: 1 byte  */
  QSPI_DUMMY_CNT_2BYTE,                    /*!< Dummy count: 2 bytes */
  QSPI_DUMMY_CNT_3BYTE,                    /*!< Dummy count: 3 bytes */
}QSPI_DUMMY_CNT_TYPE;


#define IS_QSPI_ADDR_CNT_TYPE(ADDR_CNT_TYPE)        ((ADDR_CNT_TYPE) <= QSPI_ADDR_CNT_4BYTE)

typedef enum
{
  XFLASH_STATUS_LO,                    /*!< STATUS[7:0]  */
  XFLASH_STATUS_HI,                    /*!< STATUS[15:8] */
}XFLASH_Status_Type; 

    
#define XFLASH_INS_CODE_WE      0x06   /*!< Write enable */
#define XFLASH_INS_CODE_WE_VSR  0x50   /*!< Write enable for volatile status register */
#define XFLASH_INS_CODE_WD      0x04   /*!< Write disable */
#define XFLASH_INS_CODE_RSR1    0x05   /*!< Read status register 1 */
#define XFLASH_INS_CODE_RSR2    0x35   /*!< Read status register 2 */
#define XFLASH_INS_CODE_WSR     0x01   /*!< Write status register */
#define XFLASH_INS_CODE_PP      0x02   /*!< Page program */
#define XFLASH_INS_CODE_QPP     0x32   /*!< Quad page program */
#define XFLASH_INS_CODE_SE      0x20   /*!< Sector(4k) erase */
#define XFLASH_INS_CODE_BE_32K  0x52   /*!< Block(32k) erase */
#define XFLASH_INS_CODE_BE_64K  0xD8   /*!< Block(64k) erase */
#define XFLASH_INS_CODE_CE      0xC7   /*!< Chip erase */
#define XFLASH_INS_CODE_PD      0xB9   /*!< Power down */

#define XFLASH_INS_CODE_RD      0x03   /*!< Read data */
#define XFLASH_INS_CODE_FR      0x0B   /*!< Fast read */
#define XFLASH_INS_CODE_FRDO    0x3B   /*!< Fast read dual output */ 
#define XFLASH_INS_CODE_FRQO    0x6B   /*!< Fast read quad output */ 
#define XFLASH_INS_CODE_FRDIO   0xBB   /*!< Fast read dual IO */
#define XFLASH_INS_CODE_FRQIO   0xEB   /*!< Fast read quad IO */
#define XFLASH_INS_CODE_WFRQIO  0xE7   /*!< Word Fast read quad IO, A0 must be zero */
#define XFLASH_INS_CODE_OWFRQIO 0xE3   /*!< Octal word Fast read quad IO, A[3:0] must be zero */

#define XFLASH_INS_CODE_RPD_DI  0xAB   /*!< Release power down or device ID */
#define XFLASH_INS_CODE_RUID    0x4B   /*!< Read unique ID number */

#define XFLASH_PAGE_SIZE            0x100    /*!< 256 bytes */
#define XFLASH_SECTOR_SIZE          0x1000   /*!< 4KB */
#define XFLASH_32K_BLOCK_SIZE       0x8000   /*!< 32KB */
#define XFLASH_64K_BLOCK_SIZE       0x10000  /*!< 64KB */
#define XFLASH_CHIP_SIZE            0x80000 /*!< 1MB */
#define XFLASH_LAST_SECTOR          ((XFLASH_CHIP_SIZE/XFLASH_SECTOR_SIZE) - 1)
#define XFLASH_LAST_32K_BLOCK       ((XFLASH_CHIP_SIZE/XFLASH_32K_BLOCK_SIZE) - 1)
#define XFLASH_LAST_64K_BLOCK       ((XFLASH_CHIP_SIZE/XFLASH_64K_BLOCK_SIZE) - 1)

#define XFLASH_PAGE_NUM(addr)        ((addr)>>8)

#define XFLASH_PAGE_BEGIN_ADDR(addr) (XFLASH_PAGE_SIZE * XFLASH_PAGE_NUM(addr))
#define XFLASH_PAGE_END_ADDR(addr)   (XFLASH_PAGE_SIZE * (XFLASH_PAGE_NUM(addr)+1) - 1)


void QSPI1_SetRModeCnt(QSPI_RM_CNT_TYPE rmcnt);
void QSPI1_SetDummyCnt(QSPI_DUMMY_CNT_TYPE dummycnt);
void QSPI1_StopTransfer(void) ;
void QSPI1_SetHdrcnt(QSPI_INSTR_CNT_TYPE instrCnt, QSPI_ADDR_CNT_TYPE addrCnt, QSPI_RM_CNT_TYPE rmCnt, QSPI_DUMMY_CNT_TYPE dummyCnt);
uint8_t QSPI1_ReadByte(void);
void QSPI1_WriteByte(uint8_t byte);
 void QSPI1_SetSSEnable(FunctionalState newCmd);
void QSPI1_StartTransfer(QSPI_RW_Type rw);
void QSPI1_SetRMode(uint32_t readMode);
void QSPI1_SetInstr(uint32_t instruct);
void QSPI1_SetAddr(uint32_t address);
void QSPI1_SetAddrCnt(QSPI_ADDR_CNT_TYPE addrcnt);
void QSPI1_SetDInCnt(uint32_t count);
Status QSPI1_FlushFIFO(void);



void XFLASH_SetWriteEnableBit(FunctionalState newCmd);
void XFLASH_WriteEnableVSR(void);
FlagStatus XFLASH_GetBusyStatus(void);
uint8_t XFLASH_GetStatus(XFLASH_Status_Type statusIdx);
Status XFLASH_WriteStatus(uint16_t status);
Status XFLASH_IsSectorBlank(uint32_t sectorNumber);
Status XFLASH_IsBlank(void);
void XFLASH_SelectInterface(XFLASH_Interface_Type interface);
void XFLASH_PowerDown(FunctionalState newCmd);
Status XFLASH_SetProtectionMode(XFLASH_Protection_Type protectMode);
Status XFLASH_EraseAll(void);
Status XFLASH_SectorErase(uint32_t sectorNumber);
Status XFLASH_Block32KErase(uint32_t blockNumber);
Status XFLASH_Block64KErase(uint32_t blockNumber);
Status XFLASH_Erase(uint32_t startAddr, uint32_t endAddr);
uint32_t XFLASH_Read(XFLASH_ReadMode_Type readMode, uint32_t address, uint8_t *buffer, uint32_t num);
uint32_t XFLASH_WordRead(XFLASH_ReadMode_Type readMode, uint32_t address);
uint8_t XFLASH_ByteRead(XFLASH_ReadMode_Type readMode, uint32_t address);
Status XFLASH_PageWrite(XFLASH_ProgramMode_Type programMode, uint32_t address, uint8_t *buffer, uint32_t num);
Status XFLASH_Write(XFLASH_ProgramMode_Type programMode, uint32_t address, uint8_t *buffer, uint32_t num);
Status XFLASH_WordWrite(XFLASH_ProgramMode_Type programMode, uint32_t address, uint32_t data);
Status XFLASH_ByteWrite(XFLASH_ProgramMode_Type programMode, uint32_t address, uint8_t data);
uint64_t XFLASH_GetUniqueID(void);
#include <stdio.h>
#include <stdint.h>
#include "mz100.h"
#include "qspi_reg.h"
#include "xflash.h"
#include "mz100_driver.h"

void QSPI1_SetRModeCnt(QSPI_RM_CNT_TYPE rmcnt)
{
  /* Check the parameter */
  CHECK_PARAM(IS_QSPI_RM_CNT_TYPE(rmcnt));

  QSPI1->HDRCNT.BF.RM_CNT = rmcnt;
}

void QSPI1_SetDummyCnt(QSPI_DUMMY_CNT_TYPE dummycnt)
{
  /* Check the parameter */
  CHECK_PARAM(IS_QSPI_DUMMY_CNT_TYPE(dummycnt));  

  QSPI1->HDRCNT.BF.DUMMY_CNT = dummycnt;
}

void QSPI1_StopTransfer(void) 
{
  /* Wait until QSPI1 ready */
  while(QSPI1->CNTL.BF.XFER_RDY == 0);
  
  /* Wait until wfifo empty */
  while(QSPI1->CNTL.BF.WFIFO_EMPTY == 0);
        
  /* Stop QSPI1 */
  QSPI1->CONF.BF.XFER_STOP = 1;
  
  /* Wait until QSPI1 release start signal */
  while(QSPI1->CONF.BF.XFER_START == 1);
  
  /* De-assert QSPI1 SS */
  QSPI1_SetSSEnable(DISABLE);
}

void QSPI1_SetHdrcnt(QSPI_INSTR_CNT_TYPE instrCnt, QSPI_ADDR_CNT_TYPE addrCnt, QSPI_RM_CNT_TYPE rmCnt, QSPI_DUMMY_CNT_TYPE dummyCnt)
{
  /* Check the parameters */
  CHECK_PARAM(IS_QSPI_INSTR_CNT_TYPE(instrCnt));
  CHECK_PARAM(IS_QSPI_ADDR_CNT_TYPE(addrCnt));
  CHECK_PARAM(IS_QSPI_RM_CNT_TYPE(rmCnt));
  CHECK_PARAM(IS_QSPI_DUMMY_CNT_TYPE(dummyCnt));  

  QSPI1->HDRCNT.BF.INSTR_CNT = instrCnt;
  QSPI1->HDRCNT.BF.ADDR_CNT  = addrCnt;
  QSPI1->HDRCNT.BF.RM_CNT    = rmCnt;
  QSPI1->HDRCNT.BF.DUMMY_CNT = dummyCnt;
}

uint8_t QSPI1_ReadByte(void)
{
  uint8_t data;
  
  /* Wait if RFIFO is empty*/
  while(QSPI1->CNTL.BF.RFIFO_EMPTY == 1);
  
  data = (QSPI1->DIN.BF.DATA_IN & 0xFF);
  return data;
}

void QSPI1_WriteByte(uint8_t byte)
{
  /* Wait unitl WFIFO is not full*/
  while(QSPI1->CNTL.BF.WFIFO_FULL == 1);
  
  QSPI1->DOUT.WORDVAL = (byte & 0xFF);
}

 void QSPI1_SetSSEnable(FunctionalState newCmd)
{
  QSPI1->CNTL.BF.SS_EN = newCmd;
  while(0==QSPI1->CNTL.BF.XFER_RDY);
}

void QSPI1_StartTransfer(QSPI_RW_Type rw)
{
  QSPI1_SetSSEnable(ENABLE);
  QSPI1->CONF.BF.RW_EN = rw;
  QSPI1->CONF.BF.XFER_START = 1;
}  

void QSPI1_SetRMode(uint32_t readMode)
{
  QSPI1->RDMODE.BF.RMODE = readMode;
}

void QSPI1_SetInstr(uint32_t instruct)
{
  QSPI1->INSTR.BF.INSTR = instruct;
}

void QSPI1_SetAddr(uint32_t address)
{
  QSPI1->ADDR.WORDVAL = address;
}

void QSPI1_SetAddrCnt(QSPI_ADDR_CNT_TYPE addrcnt)
{
  /* Check the parameter */
  CHECK_PARAM(IS_QSPI_ADDR_CNT_TYPE(addrcnt));

  QSPI1->HDRCNT.BF.ADDR_CNT = addrcnt;
}

void QSPI1_SetDInCnt(uint32_t count)
{
  QSPI1->DINCNT.BF.DATA_IN_CNT = count;
}

Status QSPI1_FlushFIFO(void)
{
  volatile uint32_t localCnt = 0;

  QSPI1->CONF.BF.FIFO_FLUSH = 1;
    
  /* Wait until Write and Read FIFOs are flushed. */ 
  while(localCnt++ < 0xFFFFFFF)
  {
    if( (QSPI1->CONF.BF.FIFO_FLUSH) == RESET )
    {
      return DSUCCESS;
    }
  }
  
  return DERROR;    
}

void XFLASH_SetWriteEnableBit(FunctionalState newCmd) 
{
  /* Clear QSPI1 FIFO */ 
  QSPI1_FlushFIFO();
  
  /* Set Header count register: instruction counter, address counter, read mode counter and dummy counter */
  QSPI1_SetHdrcnt(QSPI_INSTR_CNT_1BYTE, QSPI_ADDR_CNT_0BYTE, QSPI_RM_CNT_0BYTE, QSPI_DUMMY_CNT_0BYTE);
  
  /* Set data in counter */
  QSPI1_SetDInCnt(0);
  
  if(newCmd == ENABLE)
  {
    /* Set instruction */
    QSPI1_SetInstr(XFLASH_INS_CODE_WE);
  }
  else
  {
    /* Set instruction */
    QSPI1_SetInstr(XFLASH_INS_CODE_WD);
  }
        
  /* Set QSPI1 write */
  QSPI1_StartTransfer(QSPI_W_EN);
  
  /* Stop QSPI1 transfer */
  QSPI1_StopTransfer();
}

/****************************************************************************//**
 * @brief      Write enable for volatile status register
 *
 * @param none
 *
 * @return none
 *
 *******************************************************************************/
void XFLASH_WriteEnableVSR(void)
{
  /* Clear QSPI1 FIFO */ 
  QSPI1_FlushFIFO();
  
  /* Set Header count register: instruction counter, address counter, read mode counter and dummy counter */
  QSPI1_SetHdrcnt(QSPI_INSTR_CNT_1BYTE, QSPI_ADDR_CNT_0BYTE, QSPI_RM_CNT_0BYTE, QSPI_DUMMY_CNT_0BYTE);
  
  /* Set data in counter */
  QSPI1_SetDInCnt(0);
  
  /* Set instruction */
  QSPI1_SetInstr(XFLASH_INS_CODE_WE_VSR);
  
  /* Set QSPI1 write */
  QSPI1_StartTransfer(QSPI_W_EN);
  
  /* Stop QSPI1 transfer */
  QSPI1_StopTransfer();  
}

/****************************************************************************//**
 * @brief      Get the flash busy status
 *
 * @param none
 *
 * @return     Flash busy status
 *
 *******************************************************************************/
FlagStatus XFLASH_GetBusyStatus(void)
{
  FlagStatus funcStatus;  
  
  /* Clear QSPI1 FIFO */ 
  QSPI1_FlushFIFO();  
  
  /* Set Header count register: instruction counter, address counter, read mode counter and dummy counter */
  QSPI1_SetHdrcnt(QSPI_INSTR_CNT_1BYTE, QSPI_ADDR_CNT_0BYTE, QSPI_RM_CNT_0BYTE, QSPI_DUMMY_CNT_0BYTE);
    
  /* Set data in counter */
  QSPI1_SetDInCnt(1);
  
  /* Set QSPI1 data pin mode */
  QSPI1->CONF.BF.DATA_PIN = QSPI_DATA_PIN_SINGLE; 
  
  /* Set instruction */
  QSPI1_SetInstr(XFLASH_INS_CODE_RSR1);
  
  /* Set QSPI1 read */
  QSPI1_StartTransfer(QSPI_R_EN);
  
  /* Get flash busy status */
  funcStatus = (QSPI1_ReadByte() & 0x01) ? SET : RESET;
  
  /* Disable QSPI1 */
  QSPI1_SetSSEnable(DISABLE);  
  
  return funcStatus;
}


/****************************************************************************//**
 * @brief      Get the flash status
 *
* @param[in]   statusIdx:  Status[7:0] or Status[15:8]
 *
 * @return     Specified status
 *
 *******************************************************************************/
uint8_t XFLASH_GetStatus(XFLASH_Status_Type statusIdx)
{
  uint8_t status;
  
  /* Clear QSPI1 FIFO */ 
  QSPI1_FlushFIFO();  
  
  /* Set Header count register: instruction counter, address counter, read mode counter and dummy counter */
  QSPI1_SetHdrcnt(QSPI_INSTR_CNT_1BYTE, QSPI_ADDR_CNT_0BYTE, QSPI_RM_CNT_0BYTE, QSPI_DUMMY_CNT_0BYTE);
  
  /* Set data in counter */
  QSPI1_SetDInCnt(1);
  
  /* Set QSPI1 data pin mode */
  QSPI1->CONF.BF.DATA_PIN = QSPI_DATA_PIN_SINGLE; 
  
  if(statusIdx == XFLASH_STATUS_LO)
  {
    /* Set instruction */
    QSPI1_SetInstr(XFLASH_INS_CODE_RSR1);
  }
  else if(statusIdx == XFLASH_STATUS_HI)
  {
    /* Set instruction */
    QSPI1_SetInstr(XFLASH_INS_CODE_RSR2);
  }
  
  /* Set QSPI1 read */
  QSPI1_StartTransfer(QSPI_R_EN);
  
  /* Get flash busy status */
  status = QSPI1_ReadByte();
  
  /* Disable QSPI1 */
  QSPI1_SetSSEnable(DISABLE);  
  
  return status;
}

/****************************************************************************//**
 * @brief      Write flash status register
 *
 * @param[in]  status:  status
 *
 * @return     DSUCCESS or DERROR
 *
 *******************************************************************************/
Status XFLASH_WriteStatus(uint16_t status)
{
  volatile uint32_t localCnt = 0;
  uint8_t byte;
   
  /* Enable flash write */
  XFLASH_WriteEnableVSR();
  
  /* Set QSPI1 data pin mode */
  QSPI1->CONF.BF.DATA_PIN = QSPI_DATA_PIN_SINGLE; 
  
  /* Set instruction */
  QSPI1_SetInstr(XFLASH_INS_CODE_WSR);    
  
  /* Set QSPI1 write */
  QSPI1_StartTransfer(QSPI_W_EN);
  
  /* Write status[7:0] */
  byte = status & 0xFF;
  QSPI1_WriteByte(byte);
  
  /* Write status[15:8] */
  byte = (status >> 8) & 0xFF;
  QSPI1_WriteByte(byte);
  
  /* Stop QSPI1 transfer */
  QSPI1_StopTransfer();
  
  while(localCnt++ < 100000)
  {
    /* Check flash busy status */ 
    if( XFLASH_GetBusyStatus() == RESET )
    {
      return DSUCCESS;
    }
  }
  
  return DERROR;
}

/****************************************************************************//**
 * @brief      Check sector is blank or not
 *
 * @param[in]  sectorNumber:  Sector to be checked
 *
 * @return     Status
 *
 *******************************************************************************/
Status XFLASH_IsSectorBlank(uint32_t sectorNumber) 
{
  Status funcStatus = DSUCCESS;
  uint32_t sectorAddress;
  uint32_t count;
  uint32_t data;

  if(!(sectorNumber > XFLASH_LAST_SECTOR)) 
  {
    /* Get sector start address */
    sectorAddress = sectorNumber * XFLASH_SECTOR_SIZE;
    
    for(count = 0; count < XFLASH_SECTOR_SIZE; count++)
    {
      data = XFLASH_WordRead(XFLASH_NORMAL_READ, sectorAddress+count);
      if(data != 0xFFFFFFFF) 
      {
        funcStatus = DERROR;
        break;
      }
    }
  } 
  else
  {
    funcStatus = DERROR;
  }

  return funcStatus;
}

/****************************************************************************//**
 * @brief      Check flash is blank or not
 *
 * @param none
 *
 * @return     Status
 *
 *******************************************************************************/
Status XFLASH_IsBlank(void)
{
  Status funcStatus = DSUCCESS;
  uint32_t flashData;
  uint32_t i;
  uint32_t maxWordAddr;
  
  maxWordAddr = XFLASH_CHIP_SIZE >> 2;
  
  for(i=0; i<maxWordAddr; i++)
  {
    flashData = XFLASH_WordRead(XFLASH_NORMAL_READ, i<<2);
    if(flashData != 0xFFFFFFFF)
    {
      funcStatus = DERROR;
      break;
    }
  }
  
  return funcStatus;
}

/*@} end of group XFLASH_Private_Functions */

/** @defgroup XFLASH_Public_Functions
 *  @{
 */

/****************************************************************************//**
 * @brief      Select the interface to the flash
 *
 * @param[in]  interface: the interface type
 *
 * @return     none
 *
 *******************************************************************************/
void XFLASH_SelectInterface(XFLASH_Interface_Type interface)
{
}

/****************************************************************************//**
 * @brief      Set flash power down mode
 *
 * @param[in]  newCmd:  Enable/disable power down mode
 *
 * @return none
 *
 *******************************************************************************/
void XFLASH_PowerDown(FunctionalState newCmd)
{
  /* Clear QSPI1 FIFO */ 
  QSPI1_FlushFIFO();
  
  /* Set Header count register: instruction counter, address counter, read mode counter and dummy counter */
  QSPI1_SetHdrcnt(QSPI_INSTR_CNT_1BYTE, QSPI_ADDR_CNT_0BYTE, QSPI_RM_CNT_0BYTE, QSPI_DUMMY_CNT_0BYTE);
  
  /* Set data in counter */
  QSPI1_SetDInCnt(0);
  
  if(newCmd == ENABLE)
  {
    /* Set instruction */
    QSPI1_SetInstr(XFLASH_INS_CODE_PD);
  }
  else
  {
    /* Set instruction */
    QSPI1_SetInstr(XFLASH_INS_CODE_RPD_DI);
  }
        
  /* Set QSPI1 write */
  QSPI1_StartTransfer(QSPI_W_EN);
  
  /* Stop QSPI1 transfer */
  QSPI1_StopTransfer();
}

/****************************************************************************//**
 * @brief      Set flash protection mode 
 *
 * @param[in]  protectMode:  Protection mode
 *
 * @return     DSUCCESS or DERROR
 *
 *******************************************************************************/
Status XFLASH_SetProtectionMode(XFLASH_Protection_Type protectMode)
{
  volatile uint32_t localCnt = 0;
  
  /* Enable flash write */
  XFLASH_SetWriteEnableBit(ENABLE);
  
  /* Set QSPI1 data pin mode */
  QSPI1->CONF.BF.DATA_PIN = QSPI_DATA_PIN_SINGLE; 
  
  /* Set instruction */
  QSPI1_SetInstr(XFLASH_INS_CODE_WSR);    
  
  /* Set QSPI1 write */
  QSPI1_StartTransfer(QSPI_W_EN);
  
  /* Write protection mode (SEC, TB, BP2, BP1, BP0) */
  QSPI1_WriteByte(protectMode & 0x7F);
  
  /* Write protection mode (CMP) */
  QSPI1_WriteByte((protectMode & 0x80)>>1);
  
  /* Stop QSPI1 transfer */
  QSPI1_StopTransfer();
  
  while(localCnt++ < 100000)
  {
    /* Check flash busy status */ 
    if( XFLASH_GetBusyStatus() == RESET )
    {
      return DSUCCESS;
    }
  }
  
  return DERROR;
}

/****************************************************************************//**
 * @brief      Whole flash erase
 *
 * @param none
 *
 * @return     Status
 *
 *******************************************************************************/
Status XFLASH_EraseAll(void) 
{
  volatile uint32_t localCnt = 0;
    
  /* Enable flash write */
  XFLASH_SetWriteEnableBit(ENABLE);  
  
  /* Set instruction */
  QSPI1_SetInstr(XFLASH_INS_CODE_CE);
  
  /* Set QSPI1 write */
  QSPI1_StartTransfer(QSPI_W_EN);
  
  /* Stop QSPI1 transfer */
  QSPI1_StopTransfer();
  
  while(localCnt++ < 0xFFFFFFF)
  {
    /* Check flash busy status */ 
    if( XFLASH_GetBusyStatus() == RESET )
    {
      return DSUCCESS;
    }
  }
  
  return DERROR;    
}

/****************************************************************************//**
 * @brief      Flash sector erase
 *
 * @param[in]  sectorNumber:  Sector number to be erased
 *
 * @return     DSUCCESS or DERROR
 *
 *******************************************************************************/
Status XFLASH_SectorErase(uint32_t sectorNumber) 
{
  uint32_t sectorAddress;
  volatile uint32_t localCnt = 0;

  if(!(sectorNumber > XFLASH_LAST_SECTOR)) 
  {
    /* Enable flash write */
    XFLASH_SetWriteEnableBit(ENABLE);
    
    /* Get start address for sector to be erased */
    sectorAddress = sectorNumber* XFLASH_SECTOR_SIZE;
    
    /* Set address counter */
    QSPI1_SetAddrCnt(QSPI_ADDR_CNT_3BYTE);
   
    /* Set QSPI1 address pin mode */
    QSPI1->CONF.BF.ADDR_PIN = QSPI_ADDR_PIN_SINGLE;
    
    /* Set address */ 
    QSPI1_SetAddr(sectorAddress);
    
    /* Set instruction */
    QSPI1_SetInstr(XFLASH_INS_CODE_SE);
    
    /* Set QSPI1 write */
    QSPI1_StartTransfer(QSPI_W_EN);
    
    /* Stop QSPI1 transfer */
    QSPI1_StopTransfer();
    
    while(localCnt++ < 1000000)
    {
      /* Check flash busy status */ 
      if( XFLASH_GetBusyStatus() == RESET )
      {
        return DSUCCESS;
      }
    }
  }
  
  return DERROR;
}

/****************************************************************************//**
 * @brief      Flash 32KB block erase
 *
 * @param[in]  sectorNumber:  block number to be erased
 *
 * @return     DSUCCESS or DERROR
 *
 *******************************************************************************/
Status XFLASH_Block32KErase(uint32_t blockNumber) 
{
  uint32_t blockAddress;
  volatile uint32_t localCnt = 0;
  
  if(!(blockNumber > XFLASH_LAST_32K_BLOCK) ) 
  {
    /* Enable flash write */
    XFLASH_SetWriteEnableBit(ENABLE);
    
    /* Get start address of the block to be erased */
    blockAddress = blockNumber * XFLASH_32K_BLOCK_SIZE;
    
    /* Set address counter */
    QSPI1_SetAddrCnt(QSPI_ADDR_CNT_3BYTE);
    
    /* Set QSPI1 address pin mode */
    QSPI1->CONF.BF.ADDR_PIN = QSPI_ADDR_PIN_SINGLE;
    
    /* Set address */ 
    QSPI1_SetAddr(blockAddress);
    
    /* Set instruction */
    QSPI1_SetInstr(XFLASH_INS_CODE_BE_32K);
    
    /* Set QSPI1 write */
    QSPI1_StartTransfer(QSPI_W_EN);
    
    /* Stop QSPI1 transfer */
    QSPI1_StopTransfer();
    
    while(localCnt++ < 2000000)
    {
      /* Check flash busy status */ 
      if( XFLASH_GetBusyStatus() == RESET )
      {
        return DSUCCESS;
      }
    }
  }
  
  return DERROR;
}

/****************************************************************************//**
 * @brief      Flash 64KB block erase
 *
 * @param[in]  sectorNumber:  block number to be erased
 *
 * @return     DSUCCESS or DERROR
 *
 *******************************************************************************/
Status XFLASH_Block64KErase(uint32_t blockNumber) 
{
  uint32_t blockAddress;
  volatile uint32_t localCnt = 0;
  
  if(!(blockNumber > XFLASH_LAST_64K_BLOCK) ) 
  {
    /* Enable flash write */
    XFLASH_SetWriteEnableBit(ENABLE);
    
    /* Get start address of the block to be erased */
    blockAddress = blockNumber * XFLASH_64K_BLOCK_SIZE;
    
    /* Set address counter */
    QSPI1_SetAddrCnt(QSPI_ADDR_CNT_3BYTE);
    
    /* Set QSPI1 address pin mode */
    QSPI1->CONF.BF.ADDR_PIN = QSPI_ADDR_PIN_SINGLE;
    
    /* Set address */ 
    QSPI1_SetAddr(blockAddress);
    
    /* Set instruction */
    QSPI1_SetInstr(XFLASH_INS_CODE_BE_64K);
    
    /* Set QSPI1 write */
    QSPI1_StartTransfer(QSPI_W_EN);
    
    /* Stop QSPI1 transfer */
    QSPI1_StopTransfer();
    
    while(localCnt++ < 2000000)
    {
      /* Check flash busy status */ 
      if( XFLASH_GetBusyStatus() == RESET )
      {
        return DSUCCESS;
      }
    }
  }
  
  return DERROR;
}

/****************************************************************************//**
 * @brief      Erase specfied address of the flash
 *
 * @param[in]  startAddr:  Start address to be erased
 * @param[in]  endAddr:  End address to be erased
 *
 * @return     DSUCCESS or DERROR
 *
 *******************************************************************************/
Status XFLASH_Erase(uint32_t startAddr, uint32_t endAddr) 
{
  uint32_t startSector, endSector, sectorNumber;

  /* Get sector number of start address */
  startSector = (startAddr / XFLASH_SECTOR_SIZE);
  /* Get sector number of end address */
  endSector = (endAddr / XFLASH_SECTOR_SIZE);

  for(sectorNumber = startSector; sectorNumber <= endSector; sectorNumber++)
  {
    if(XFLASH_SectorErase(sectorNumber) == DERROR)
    {
      return DERROR;
    }
  }
  
  return DSUCCESS;
}

/****************************************************************************//**
 * @brief      Read flash from specified address to buffer
 *
 * @param[in]  readMode:  Flash reading mode to be set
 * @param[in]  address:  Flash address to be read
 * @param[in]  buffer:  Buffer to hold data read from flash
 * @param[in]  num:  Number of data to be read from flash
 *
 * @return     Number of data read out from flash, in byte
 *
 *******************************************************************************/
uint32_t XFLASH_Read(XFLASH_ReadMode_Type readMode, uint32_t address, uint8_t *buffer, uint32_t num) 
{
  uint32_t i;
  uint32_t readBytes;
  uint16_t statusLow, statusHigh, statusWrite; 
    
  readBytes = 0;
  
  if( (readMode == XFLASH_FAST_READ_QUAD_OUT) || (readMode == XFLASH_FAST_READ_QUAD_IO)
    ||(readMode == XFLASH_WORD_FAST_READ_QUAD_IO) || (readMode == XFLASH_OCTAL_WORD_FAST_READ_QUAD_IO) )
  {
    statusLow = XFLASH_GetStatus(XFLASH_STATUS_LO);
    statusHigh = XFLASH_GetStatus(XFLASH_STATUS_HI);
    statusWrite = ((statusHigh<<8) | statusLow) | 0x0200;
    XFLASH_WriteStatus(statusWrite);    
  }  
  
  /* Clear QSPI1 FIFO */ 
  QSPI1_FlushFIFO();  

  /* Set Header count register: instruction counter, address counter, read mode counter and dummy counter */
  QSPI1_SetHdrcnt(QSPI_INSTR_CNT_1BYTE, QSPI_ADDR_CNT_3BYTE, QSPI_RM_CNT_0BYTE, QSPI_DUMMY_CNT_0BYTE);
    
  /* Set read mode */
  QSPI1_SetRMode(0);  

  /* Set data in counter */
  QSPI1_SetDInCnt(num);  
  
  /* Set address */ 
  QSPI1_SetAddr(address);
  
  /* Set QSPI1 address pin mode */
  QSPI1->CONF.BF.ADDR_PIN = QSPI_ADDR_PIN_SINGLE;     
  
  /* Set QSPI1 data pin mode */
  QSPI1->CONF.BF.DATA_PIN = QSPI_DATA_PIN_SINGLE;   

  if(readMode == XFLASH_NORMAL_READ)
  {
    /* Set instruction */
    QSPI1_SetInstr(XFLASH_INS_CODE_RD);
  }
  else if(readMode == XFLASH_FAST_READ)
  {
    /* Set instruction */
    QSPI1_SetInstr(XFLASH_INS_CODE_FR);
    
    /* Set dummy counter */
    QSPI1_SetDummyCnt(QSPI_DUMMY_CNT_1BYTE);
  }
  else if(readMode == XFLASH_FAST_READ_DUAL_OUT)
  {
    /* Set instruction */
    QSPI1_SetInstr(XFLASH_INS_CODE_FRDO);
    
    /* Set dummy counter */
    QSPI1_SetDummyCnt(QSPI_DUMMY_CNT_1BYTE);
    
    /* Set QSPI1 data pin mode */
    QSPI1->CONF.BF.DATA_PIN = QSPI_DATA_PIN_DUAL;  
  }
  else if(readMode == XFLASH_FAST_READ_DUAL_IO)
  {
    /* Set instruction */
    QSPI1_SetInstr(XFLASH_INS_CODE_FRDIO);
    
    /* Set read mode counter */
    QSPI1_SetRModeCnt(QSPI_RM_CNT_1BYTE);
    
    /* Set QSPI1 data pin mode */
    QSPI1->CONF.BF.DATA_PIN = QSPI_DATA_PIN_DUAL;
    
    /* Set QSPI1 address pin mode */
    QSPI1->CONF.BF.ADDR_PIN = QSPI_ADDR_PIN_AS_DATA;   
  }    
  else if(readMode == XFLASH_FAST_READ_QUAD_OUT)
  {
    /* Set instruction */
    QSPI1_SetInstr(XFLASH_INS_CODE_FRQO);
    
    /* Set dummy counter */
    QSPI1_SetDummyCnt(QSPI_DUMMY_CNT_1BYTE);
    
    /* Set QSPI1 data pin mode */
    QSPI1->CONF.BF.DATA_PIN = QSPI_DATA_PIN_QUAD;  
  }
  else if(readMode == XFLASH_FAST_READ_QUAD_IO)
  {
    /* Set instruction */
    QSPI1_SetInstr(XFLASH_INS_CODE_FRQIO);
 
    /* Set read mode counter */
    QSPI1_SetRModeCnt(QSPI_RM_CNT_1BYTE);
        
    /* Set dummy counter */
    QSPI1_SetDummyCnt(QSPI_DUMMY_CNT_2BYTE);    
    
    /* Set QSPI1 data pin mode */
    QSPI1->CONF.BF.DATA_PIN = QSPI_DATA_PIN_QUAD;
    
    /* Set QSPI1 address pin mode */
    QSPI1->CONF.BF.ADDR_PIN = QSPI_ADDR_PIN_AS_DATA;      
  }
  else if(readMode == XFLASH_WORD_FAST_READ_QUAD_IO)
  {
    /* Set instruction */
    QSPI1_SetInstr(XFLASH_INS_CODE_WFRQIO);
    
    /* Set read mode counter */
    QSPI1_SetRModeCnt(QSPI_RM_CNT_1BYTE);
        
    /* Set dummy counter */
    QSPI1_SetDummyCnt(QSPI_DUMMY_CNT_1BYTE);    
    
    /* Set QSPI1 data pin mode */
    QSPI1->CONF.BF.DATA_PIN = QSPI_DATA_PIN_QUAD;
    
    /* Set QSPI1 address pin mode */
    QSPI1->CONF.BF.ADDR_PIN = QSPI_ADDR_PIN_AS_DATA;         
  }
  else if(readMode == XFLASH_OCTAL_WORD_FAST_READ_QUAD_IO)
  {
    /* Set instruction */
    QSPI1_SetInstr(XFLASH_INS_CODE_OWFRQIO);
    
    /* Set read mode counter */
    QSPI1_SetRModeCnt(QSPI_RM_CNT_1BYTE);
        
    /* Set QSPI1 data pin mode */
    QSPI1->CONF.BF.DATA_PIN = QSPI_DATA_PIN_QUAD;
    
    /* Set QSPI1 address pin mode */
    QSPI1->CONF.BF.ADDR_PIN = QSPI_ADDR_PIN_AS_DATA;         
  }
    
  /* QSPI1 one-byte length mode */
  QSPI1->CONF.BF.BYTE_LEN = QSPI_BYTE_LEN_1BYTE;
  
  /* Set QSPI1 read */
  QSPI1_StartTransfer(QSPI_R_EN);
    
  for (i=0; i<num; i++)
  {
    /* Waiting for RFIFO not empty */
    while(QSPI1->CNTL.BF.RFIFO_EMPTY == 1);
    
    buffer[i] = (QSPI1->DIN.WORDVAL) & 0xFF;
    readBytes++;
  } 
  
  /* Disable QSPI1 */
  QSPI1_SetSSEnable(DISABLE); 
  
  return readBytes;
}

/****************************************************************************//**
 * @brief      Read a word from specified flash address
 *
 * @param[in]  readMode:  Flash reading mode to be set
 * @param[in]  address:  Flash address to be read
 *
 * @return     Data in word
 *
 *******************************************************************************/
uint32_t XFLASH_WordRead(XFLASH_ReadMode_Type readMode, uint32_t address) 
{
  uint32_t data = 0;
  XFLASH_Read(readMode, address, (uint8_t*)&data, 4);
  return data;
}

/****************************************************************************//**
 * @brief      Read a byte from specified flash address
 *
 * @param[in]  readMode:  Flash reading mode to be set
 * @param[in]  address:  Flash address to be read
 *
 * @return     Data in byte
 *
 *******************************************************************************/
uint8_t XFLASH_ByteRead(XFLASH_ReadMode_Type readMode, uint32_t address) 
{
  uint8_t data = 0;
  XFLASH_Read(readMode, address, (uint8_t*)&data, 1);
  return data;
}

/****************************************************************************//**
 * @brief      Write flash within a page
 *
 * @param[in]  programMode:  Flash program mode to be set
 * @param[in]  address:  Page address
 * @param[in]  buffer:  Buffer data to be programmed to flash
 * @param[in]  num:  Number of data to be programmed to flash
 *
 * @return     DSUCCESS or DERROR
 *
 *******************************************************************************/
Status XFLASH_PageWrite(XFLASH_ProgramMode_Type programMode, uint32_t address, uint8_t *buffer, uint32_t num) 
{
  uint32_t i;
  volatile uint32_t localCnt = 0;
  uint16_t statusLow, statusHigh, statusWrite; 
  
  if(programMode == XFLASH_PROGRAM_QUAD)
  {
    statusLow = XFLASH_GetStatus(XFLASH_STATUS_LO);
    statusHigh = XFLASH_GetStatus(XFLASH_STATUS_HI);
    statusWrite = ((statusHigh<<8) | statusLow) | 0x0200;
    XFLASH_WriteStatus(statusWrite);    
  }    
  
  /* Check address validity */
  if ((XFLASH_PAGE_NUM(address+num-1) > XFLASH_PAGE_NUM(address)) || num == 0)
  {
    return DERROR;
  }
  
  /* Enable flash write */
  XFLASH_SetWriteEnableBit(ENABLE);
  
  /* Set Header count register: instruction counter, address counter, read mode counter and dummy counter */
  QSPI1_SetHdrcnt(QSPI_INSTR_CNT_1BYTE, QSPI_ADDR_CNT_3BYTE, QSPI_RM_CNT_0BYTE, QSPI_DUMMY_CNT_0BYTE);
  
  /* Set QSPI1 address pin mode */
  QSPI1->CONF.BF.ADDR_PIN = QSPI_ADDR_PIN_SINGLE;
  
  /* Set QSPI1 data pin mode */
  QSPI1->CONF.BF.DATA_PIN = QSPI_DATA_PIN_SINGLE;   
  
  /* Set address */ 
  QSPI1_SetAddr(address);
  
  if(programMode == XFLASH_PROGRAM_NORMAL)
  {
    /* Set instruction */
    QSPI1_SetInstr(XFLASH_INS_CODE_PP);    
  }
  else if(programMode == XFLASH_PROGRAM_QUAD)
  {
    /* Set instruction */
    QSPI1_SetInstr(XFLASH_INS_CODE_QPP);    
    
    /* Set QSPI1 data pin mode */
    QSPI1->CONF.BF.DATA_PIN = QSPI_DATA_PIN_QUAD;  
  }
  
  /* QSPI1 one-byte length mode */
  QSPI1->CONF.BF.BYTE_LEN = QSPI_BYTE_LEN_1BYTE;
  
  /* Set QSPI1 write */
  QSPI1_StartTransfer(QSPI_W_EN);
    
  for (i=0; i<num; i++) 
  {
    QSPI1_WriteByte(buffer[i]);
  }
  
  /* Stop QSPI1 transfer */
  QSPI1_StopTransfer();
  
  while(localCnt++ < 1000000)
  {
    /* Check flash busy status */ 
    if( XFLASH_GetBusyStatus() == RESET )
    {
      return DSUCCESS;
    }
  }  

  return DERROR;
}

/****************************************************************************//**
 * @brief      Write flash with any address and size
 *
 * @param[in]  programMode:  Flash program mode to be set
 * @param[in]  address:  Page address
 * @param[in]  buffer:  Buffer data to be programmed to flash
 * @param[in]  num:  Number of data to be programmed to flash
 *
 * @return     DSUCCESS or DERROR
 *
 *******************************************************************************/
Status XFLASH_Write(XFLASH_ProgramMode_Type programMode, uint32_t address, uint8_t *buffer, uint32_t num) 
{
  uint8_t *pBuf;
  uint32_t begPgNum;
  uint32_t endPgNum;
  uint32_t step;
  uint32_t addrCur;
  uint32_t i;
  Status funcStatus = DSUCCESS;  
  
  pBuf = buffer;
  addrCur = address;
  
  /* Get page number of start address */
  begPgNum = XFLASH_PAGE_NUM(address);
  /* Get page number of end address */
  endPgNum = XFLASH_PAGE_NUM(address + num - 1);

  /* Both start address and end address are within the same page */
  if(begPgNum == endPgNum)
  {
    return( XFLASH_PageWrite(programMode, address, buffer, num) );
  } 
  /* Start address and end address are not in the same page */
  else
  {
    /* For first page */
    step = XFLASH_PAGE_END_ADDR(address)-address+1;
    funcStatus = XFLASH_PageWrite(programMode, address, pBuf, step);
    if(funcStatus == DERROR)
    {
      return DERROR;
    }
    
    pBuf += step;
    addrCur += step;

    for(i=begPgNum+1; i<=endPgNum; i++)
    {
      /* For last page */
      if(i == endPgNum)
      {
        step = (address + num) & 0xFF;
        
        /* If step is 0, the last page has 256 bytes data to be writen ( num of data is 0x100 ) */
        if(step == 0)
        {
          step = 0x100;
        }
        
        return( XFLASH_PageWrite(programMode, addrCur, pBuf, step) );
      } 
      else
      {
        funcStatus = XFLASH_PageWrite(programMode, addrCur, pBuf, XFLASH_PAGE_SIZE);
        if(funcStatus == DERROR)
        {
          return DERROR;
        }
        
        pBuf += XFLASH_PAGE_SIZE;
        addrCur += XFLASH_PAGE_SIZE;
      }
    }
  }
  
  return funcStatus;
}

/****************************************************************************//**
 * @brief      Write a word to specified flash address
 *
 * @param[in]  programMode:  Flash program mode to be set
 * @param[in]  address:  Flash address to be programmed
 * @param[in]  data:  Data to be programmed to flash
 *
 * @return     DSUCCESS or DERROR
 *
 *******************************************************************************/
Status XFLASH_WordWrite(XFLASH_ProgramMode_Type programMode, uint32_t address, uint32_t data) 
{
  return XFLASH_Write(programMode, address, (uint8_t*)&data, 4);
}

/****************************************************************************//**
 * @brief      Write a byte to specified flash address
 *
 * @param[in]  address:  Flash address to be programmed
 * @param[in]  data:  Data to be programmed to flash
 *
 * @return     DSUCCESS or DERROR
 *
 *******************************************************************************/
Status XFLASH_ByteWrite(XFLASH_ProgramMode_Type programMode, uint32_t address, uint8_t data) 
{
  return XFLASH_Write(programMode, address, (uint8_t*)&data, 1);
}

/****************************************************************************//**
 * @brief      Get flash unique ID
 *
 * @param none
 *
 * @return     Unique ID
 *
 *******************************************************************************/
uint64_t XFLASH_GetUniqueID(void)
{
  uint64_t uniqueID;
  
  QSPI1_FlushFIFO();  
  
  /* Set Header count register: instruction counter, address counter, read mode counter and dummy counter*/
  QSPI1_SetHdrcnt(QSPI_INSTR_CNT_1BYTE, QSPI_ADDR_CNT_1BYTE, QSPI_RM_CNT_0BYTE, QSPI_DUMMY_CNT_3BYTE);
  
  QSPI1_SetDInCnt(8);
  
  QSPI1_SetAddr(0);
  
  /* Read Unique ID number */
  QSPI1_SetInstr(XFLASH_INS_CODE_RUID);
  
  QSPI1_StartTransfer(QSPI_R_EN);

  uniqueID = QSPI1_ReadByte();
  uniqueID <<= 8;
  uniqueID |= QSPI1_ReadByte();
  uniqueID <<= 8;
  uniqueID |= QSPI1_ReadByte();
  uniqueID <<= 8;
  uniqueID |= QSPI1_ReadByte();
  uniqueID <<= 8;
  uniqueID |= QSPI1_ReadByte();
  uniqueID <<= 8;
  uniqueID |= QSPI1_ReadByte();
  uniqueID <<= 8;
  uniqueID |= QSPI1_ReadByte();
  uniqueID <<= 8;
  uniqueID |= QSPI1_ReadByte();  
  
  QSPI1_SetSSEnable(DISABLE);
  
  return uniqueID;
}
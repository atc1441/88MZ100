#include "mz100.h"
#include "mz100_uart.h"
#include "uart_reg.h"
#include "mz100_driver.h"
#include "mz100_clock.h"

int _write(int file, char *ptr, int len)
{
	UART_SendBytes(1, ptr, len);
    return len;
}

#define UART_INTSTATUS_IID_MODEM       0x00		
#define UART_INTSTATUS_IID_TBEI        0x02
#define UART_INTSTATUS_IID_RBFI        0x04		
#define UART_INTSTATUS_IID_LSI         0x06		
#define UART_INTSTATUS_IID_BYDET       0x07
#define UART_INTSTATUS_IID_RCVRTO      0x0C


static const uint32_t uartAddr[2] = {UART0_BASE,UART1_BASE};

void UART_IntHandler(INT_Peripher_Type intPeriph, UART_ID_Type uartNo);

/****************************************************************************//**
 * @brief      UART interrupt handle
 *
 * @param[in]  intPeriph: Select the peripheral, such as INT_UART0,INT_AES
 * @param[in]  uartNo:  Select the UART port
 *
 * @return none
 *
 *******************************************************************************/
void UART_IntHandler(INT_Peripher_Type intPeriph, UART_ID_Type uartNo)
{
  uint32_t intId;
  volatile uint32_t dummyData __attribute__((unused));

  uart_reg_t * UARTx = (uart_reg_t *)(uartAddr[uartNo]);

  intId = UARTx->IIR_FCR.BF_IIR.IID;

  /* Transmit holding register empty inerrupt */
  if(intId == UART_INTSTATUS_IID_TBEI)
  {
    if(intCbfArra[intPeriph][UART_INTSTATUS_TBEI] != NULL)
    {
      /* Call the callback function */
      intCbfArra[intPeriph][UART_INTSTATUS_TBEI]();
    }
    /* Disable the interrupt if callback function is not setup */
    else
    {
      UARTx->IER_DLH.BF_IER.ETBEI = 0;
    }
  }

  /* Mode status inerrupt */
  if(intId == UART_INTSTATUS_IID_MODEM)
  {
    /* Clear it by reading the UART modem status register */
    dummyData = UARTx->MSR.WORDVAL;

    if(intCbfArra[intPeriph][UART_INTSTATUS_MODEM] != NULL)
    {
      /* Call the callback function */
      intCbfArra[intPeriph][UART_INTSTATUS_MODEM]();
    }
    /* Disable the interrupt if callback function is not setup */
    else
    {
      UARTx->IER_DLH.BF_IER.EDSSI = 0;
    }
  }

  /* Receiver line status inerrupt */
  if(intId == UART_INTSTATUS_IID_LSI)
  {
    if(intCbfArra[intPeriph][UART_INTSTATUS_LSI] != NULL)
    {
      /* Call the callback function */
      intCbfArra[intPeriph][UART_INTSTATUS_LSI]();
    }
    /* Disable the interrupt if callback function is not setup */
    else
    {
      UARTx->IER_DLH.BF_IER.ELSI = 0;
    }

    /* Clear it by reading the UART status register */
    dummyData = UARTx->LSR.WORDVAL;
  }

  /* Received data available interrupt or timeout indication */
  if(intId == UART_INTSTATUS_IID_RBFI)
  {
    if(intCbfArra[intPeriph][UART_INTSTATUS_RBFI] != NULL)
    {
      /* call the callback function */
      intCbfArra[intPeriph][UART_INTSTATUS_RBFI]();
    }
    /* Disable the interrupt if callback function is not setup */
    else
    {
      UARTx->IER_DLH.BF_IER.ERBFI = 0;
    }
  }

  /* Character timeout indication */
  if(intId == UART_INTSTATUS_IID_RCVRTO)
  {
    if(intCbfArra[intPeriph][UART_INTSTATUS_RCVRTO] != NULL)
    {
      /* Call the callback function */
      intCbfArra[intPeriph][UART_INTSTATUS_RCVRTO]();
    }
    /* Disable the interrupt if callback function is not setup */
    else
    {
      UARTx->IER_DLH.BF_IER.ERBFI = 0;
    }
  }

  /* Busy detect indication */
  if(intId == UART_INTSTATUS_IID_BYDET)
  {
    /* Clear it by reading the UART status register */
    dummyData = UARTx->USR.WORDVAL;

    if(intCbfArra[intPeriph][UART_INTSTATUS_BYDET] != NULL)
    {
      /* Call the callback function */
      intCbfArra[intPeriph][UART_INTSTATUS_BYDET]();
    }
    /* Disable the interrupt if callback function is not setup */
    else
    {
      UARTx->IER_DLH.BF_IER.ERBFI = 0;
    }
  }
}
/*@} end of group UART_Private_Functions */

/** @defgroup UART_Public_Functions
 *  @{
 */

/****************************************************************************//**
 * @brief      UART reset
 *
 * @param[in]  uartNo: Select the UART port, should be UART0_ID, UART1_ID,
 *                                                     UART2_ID, UART3_ID
 *
 * @return none
 *
 *******************************************************************************/
void UART_Reset(UART_ID_Type uartNo)
{
  volatile uint32_t delayCycle;
  uart_reg_t * UARTx = (uart_reg_t *)(uartAddr[uartNo]);

  /* Check the parameters */
  CHECK_PARAM(IS_UART_PERIPH(uartNo));

  /* Software reset */
  UARTx->SRR.BF.UR = 1;

  /* delay routine */
  delayCycle = 20000;
  while(delayCycle--);
}

/****************************************************************************//**
 * @brief      Initializes the UART
 *
 * @param[in]  uartNo:  Select the UART port,should be UART0_ID, UART1_ID,
 *                                                     UART2_ID, UART3_ID
 * @param[in]  uartCfgStruct:  Pointer to a UART configuration structure
 *
 * @return none
 *
 *******************************************************************************/
void UART_Init(UART_ID_Type uartNo, UART_CFG_Type* uartCfgStruct)
{
  uint32_t baudRateDivisor;

  uart_reg_t * UARTx = (uart_reg_t *)(uartAddr[uartNo]);

  /* check the parameters */
  CHECK_PARAM(IS_UART_PERIPH(uartNo));
  CHECK_PARAM(IS_UART_BAUDRATE(uartCfgStruct->baudRate));
  CHECK_PARAM(IS_UART_STOPBITS(uartCfgStruct->stopBits));
  CHECK_PARAM(IS_UART_DATABITS(uartCfgStruct->dataBits));
  CHECK_PARAM(IS_UART_PARITY(uartCfgStruct->parity));
  CHECK_PARAM(PARAM_FUNCTIONALSTATE(uartCfgStruct->autoFlowControl));

  /************Configure the Baud Rate*********************************/
  
  /* uart clock is between 1/4 and 1/8 of system clock */
  baudRateDivisor = 32000000 / (16 * uartCfgStruct->baudRate);
  
  /* Enable DLAB to set baud rate */
  UARTx->LCR.BF.DLAB = 0x01;

  /* Config the DLL and DLH registers */
  UARTx->RBR_DLL_THR.BF_DLL.DLL = baudRateDivisor & 0xFF;
  UARTx->IER_DLH.BF_DLH.DLH = (baudRateDivisor >> 0x08)& 0xFF;

  /* Disable DLAB */
  UARTx->LCR.BF.DLAB = 0x0;

  /***********Configure Line control register (LCR)********************/

  /* Set parity */
  if(uartCfgStruct->parity == UART_PARITY_NONE)
  {
    UARTx->LCR.BF.PEN = 0x0;
  }
  else if(uartCfgStruct->parity == UART_PARITY_ODD)
  {
    UARTx->LCR.BF.PEN = 0x01;
    UARTx->LCR.BF.EPS = 0;
  }
  else
  {
    UARTx->LCR.BF.PEN = 0x01;
    UARTx->LCR.BF.EPS = 1;
  }

  /* Set UART Data Length and stop bit */
  UARTx->LCR.BF.DLS = uartCfgStruct->dataBits;
  UARTx->LCR.BF.STOP = uartCfgStruct->stopBits;

  /***********Configure auto flow control register (MCR)*******************/

  /* Configure the auto flow control */
  UARTx->MCR.BF.AFCE = uartCfgStruct->autoFlowControl;

}

/****************************************************************************//**
 * @brief      Get current value of Component Parameter register
 *
 * @param[in]  uartNo:  Select the UART port,should be UART0_ID, UART1_ID,
 *                                                     UART2_ID, UART3_ID
 * @param[in]  lineStatus:  Checks whether the specified UART Line status bit
                       is set or not
 *
 * @return The state value of Component Parameter register
 *
 *******************************************************************************/
FlagStatus UART_GetCompParam(UART_ID_Type uartNo,UART_CompParam_Type compParam)
{
  FlagStatus bitStatus = RESET;
  uart_reg_t * UARTx = (uart_reg_t *)(uartAddr[uartNo]);

  /* Check the parameters */
  CHECK_PARAM(IS_UART_PERIPH(uartNo));

  switch(compParam)
  {
    case UART_COMP_THRE_MODE:
      bitStatus = ((UARTx->CPR.BF.THRE_MODE == 1) ? SET : RESET);
      break;

    case UART_COMP_SIR_MODE:
      bitStatus = ((UARTx->CPR.BF.SIR_MODE == 1) ? SET : RESET);
      break;

    case UART_COMP_SIR_LP_MODE:
      bitStatus = ((UARTx->CPR.BF.SIR_LP_MODE == 1) ? SET : RESET);
      break;

    case UART_COMP_ADDITIONAL_FEAT:
      bitStatus = ((UARTx->CPR.BF.ADDITIONAL_FEAT == 1) ? SET : RESET);
      break;

    case UART_COMP_FIFO_ACCESS:
      bitStatus = ((UARTx->CPR.BF.FIFO_ACCESS == 1) ? SET : RESET);
      break;

    case UART_COMP_FIFO_STAT:
      bitStatus = ((UARTx->CPR.BF.FIFO_STAT == 1) ? SET : RESET);
      break;

    case UART_COMP_SHADOW:
      bitStatus = ((UARTx->CPR.BF.SHADOW == 1) ? SET : RESET);
      break;

    case UART_COMP_UART_ADD_ENCODED_PARAMS:
      bitStatus = ((UARTx->CPR.BF.UART_ADD_ENCODED_PARAMS == 1) ? SET : RESET);
      break;

    case UART_COMP_DMA_EXTRA:
        bitStatus = ((UARTx->CPR.BF.DMA_EXTRA == 1) ? SET : RESET);

    default:
      break;
  }

  return bitStatus;
}

/****************************************************************************//**
 * @brief      Set UART loopback mode
 *
 * @param[in]  uartNo:  Select the UART port,should be UART0_ID, UART1_ID,
 *                                                     UART2_ID, UART3_ID
 * @param[in]  newState: Enable/Disable function state
 *
 * @return none
 *
 *******************************************************************************/
void UART_SetLoopBackMode(UART_ID_Type uartNo, FunctionalState newState)
{
  uart_reg_t * UARTx = (uart_reg_t *)(uartAddr[uartNo]);

  /* Check the parameter */
  CHECK_PARAM(IS_UART_PERIPH(uartNo));
  CHECK_PARAM(PARAM_FUNCTIONALSTATE(newState));

  /* Configurate the loopback */
  UARTx->MCR.BF.LOOPBACK = ((newState == ENABLE)? 0x01 : 0x00);

}

/****************************************************************************//**
 * @brief      Send break characters
 *
 * @param[in]  uartNo:  Select the UART port,should be UART0_ID, UART1_ID,
 *                                                     UART2_ID, UART3_ID
 * @param[in]  newState: Enable/Disable function state
 *
 * @return none
 *
 *******************************************************************************/
void UART_SendBreakCmd(UART_ID_Type uartNo, FunctionalState newState)
{
  uart_reg_t * UARTx = (uart_reg_t *)(uartAddr[uartNo]);

  /* Check the parameter */
  CHECK_PARAM(IS_UART_PERIPH(uartNo));

  /* Send break characters */
  UARTx->LCR.BF.BREAK = ((newState == ENABLE)? 0x01 : 0x00);

}

/****************************************************************************//**
 * @brief      Receive one byte data from the UART peripheral
 *
 * @param[in]  uartNo:  Select the UART port,should be UART0_ID, UART1_ID,
 *                                                     UART2_ID, UART3_ID
 *
 * @return     The received data
 *
 *******************************************************************************/
uint8_t UART_ReceiveByte(UART_ID_Type uartNo)
{
  uart_reg_t * UARTx = (uart_reg_t *)(uartAddr[uartNo]);

  /* Check the parameter */
  CHECK_PARAM(IS_UART_PERIPH(uartNo));

  /* Receive data */
  return (uint8_t)(UARTx->RBR_DLL_THR.BF_RBR.RBR);
}

/****************************************************************************//**
 * @brief      Send one byte data to the UART peripheral
 *
 * @param[in]  uartNo:  Select the UART port,should be UART0_ID, UART1_ID,
 *                                                     UART2_ID, UART3_ID
 * @param[in]  data:  The data to be send
 *
 * @return none
 *
 *******************************************************************************/
void UART_SendByte(UART_ID_Type uartNo, uint8_t data)
{
  uart_reg_t * UARTx = (uart_reg_t *)(uartAddr[uartNo]);

  /* Check the parameter */
  CHECK_PARAM(IS_UART_PERIPH(uartNo));

  /* Send data */
  UARTx->RBR_DLL_THR.WORDVAL = ((uint32_t)data) & 0xFF;
}


void UART_SendBytes(UART_ID_Type uartNo, char *string, int len)
{
  int v7;
  
  uart_reg_t * UARTx = (uart_reg_t *)(uartAddr[uartNo]);

  v7 = 0;
  while ( len )
  {
    if (UARTx->LSR.BF.TEMT)
    {
      UART_SendByte(1, *string++);
      ++v7;
      --len;
    }
  }
}

/****************************************************************************//**
 * @brief      Receive 9 bit data from the UART peripheral, odd parity default.
 *
 * @param[in]  uartNo:  Select the UART port,should be UART0_ID, UART1_ID,
 *                                                     UART2_ID, UART3_ID
 *
 * @return     The received data
 *
 *******************************************************************************/
uint16_t UART_Receive9bits(UART_ID_Type uartNo)
{
	uart_reg_t * UARTx = (uart_reg_t *)(uartAddr[uartNo]);
	uint16_t data;
	uint32_t lsr = 0;
	uint8_t parity = 0;
	int i;

	/* check the parameter */
	CHECK_PARAM(IS_UART_PERIPH(uartNo));

	/* Wait untill data is available */
	do {
		lsr = UARTx->LSR.WORDVAL;
	} while (!(lsr & 0x01));

	/* Receive data */
	data = (uint16_t)UARTx->RBR_DLL_THR.BF_RBR.RBR;

	for (i = 0; i < 8; i++)
		parity ^= ((data >> i) & 0x1);

	/* get bit9 according parity error status */
	data |= (parity ^ ((lsr >> 2) & 0x1)) << 8;

  return (data & 0x1FF);
}

/****************************************************************************//**
 * @brief      Send 9 bit data to the UART peripheral
 *
 * @param[in]  uartNo:  Select the UART port,should be UART0_ID, UART1_ID,
 *                                                     UART2_ID, UART3_ID
 * @param[in]  data:  The data to be send
 *
 * @return none
 *
 *******************************************************************************/
void UART_Send9bits(UART_ID_Type uartNo, uint16_t data)
{
	uart_reg_t * UARTx = (uart_reg_t *)(uartAddr[uartNo]);
	uint8_t parity = 0;
	int i;

	/* check the parameter */
	CHECK_PARAM(IS_UART_PERIPH(uartNo));

	for (i = 0; i < 8; i++)
		parity ^= ((data >> i) & 0x1);

	/* Select Parity according to MSB bit */
	while (UARTx->USR.BF.BUSY)
		;
	UARTx->LCR.BF.EPS = !(((data >> 8) & 0x1) ^ parity);

	/* Send data */
	UARTx->RBR_DLL_THR.WORDVAL = (uint32_t)data & 0xFF;

	/* Set parity back to EVEN */
	while (UARTx->USR.BF.BUSY)
		;
	UARTx->LCR.BF.EPS = 1;
}

/****************************************************************************//**
  * @brief      Send data to the UART peripheral
  *
  * @param[in]  uartNo:  Select the UART port,should be UART1_ID, UART2_ID.
  * @param[in]  buf:  Pointer to data to be send
  *
  * @return none
  *
  *****************************************************************************/
void UART_WriteLine(UART_ID_Type uartNo, uint8_t *buf)
{
	while (*buf) {
		while (UART_GetLineStatus(uartNo, UART_LINESTATUS_TEMT)
		       != SET)
			;
		UART_SendByte(uartNo, *buf++);
       }
}

/****************************************************************************//**
 * @brief      Config UART FIFO function
 *
 * @param[in]  uartNo:  Select the UART port,should be UART0_ID, UART1_ID,
 *                                                     UART2_ID, UART3_ID
 * @param[in]  fifoCfg:  Pointer to a UART_FIFO_CFG_Type Structure
 *
 * @return none
 *
 *******************************************************************************/
void UART_FIFOConfig(UART_ID_Type uartNo, UART_FIFO_Type * fifoCfg)
{
  uart_reg_t * UARTx = (uart_reg_t *)(uartAddr[uartNo]);

  /* Check the parameters */
  CHECK_PARAM(IS_UART_PERIPH(uartNo));
  CHECK_PARAM(IS_UART_FIFOTET(fifoCfg->FIFO_TxEmptyTrigger));
  CHECK_PARAM(IS_UART_FIFORT(fifoCfg->FIFO_RcvrTrigger));
  CHECK_PARAM(PARAM_FUNCTIONALSTATE(fifoCfg->FIFO_Function));
  CHECK_PARAM(PARAM_FUNCTIONALSTATE(fifoCfg->FIFO_ResetTx));
  CHECK_PARAM(PARAM_FUNCTIONALSTATE(fifoCfg->FIFO_ResetRx));

  /* Configure FIFO function */
  UARTx->IIR_FCR.BF_FCR.FIFOE = fifoCfg->FIFO_Function;

  /* Configure the FIFO trigger level */
  if(fifoCfg->FIFO_Function == ENABLE)
  {
    /* Configure FIFO transmit and receive reset */
    UARTx->IIR_FCR.BF_FCR.RFIFOR = fifoCfg->FIFO_ResetRx;
    UARTx->IIR_FCR.BF_FCR.XFIFOR = fifoCfg->FIFO_ResetTx;

    /* Set RX and TX trigger level */
    UARTx->IIR_FCR.BF_FCR.TET = fifoCfg->FIFO_TxEmptyTrigger;
    UARTx->IIR_FCR.BF_FCR.RT = fifoCfg->FIFO_RcvrTrigger;
  }
}

/****************************************************************************//**
 * @brief      Reset uart receive fifo
 *
 * @param[in]  uartNo:  Select the UART port,should be UART0_ID, UART1_ID,
 *                                                     UART2_ID, UART3_ID
 *
 * @return none
 *
 *******************************************************************************/
void UART_ResetRxFifo(UART_ID_Type uartNo)
{
  uart_reg_t * UARTx = (uart_reg_t *)(uartAddr[uartNo]);

  /* Check the parameters */
  CHECK_PARAM(IS_UART_PERIPH(uartNo));

  UARTx->IIR_FCR.BF_FCR.RFIFOR = 1;
}

/****************************************************************************//**
 * @brief      Reset uart transmit fifo
 *
 * @param[in]  uartNo:  Select the UART port,should be UART0_ID, UART1_ID,
 *                                                     UART2_ID, UART3_ID
 *
 * @return none
 *
 *******************************************************************************/
void UART_ResetTxFifo(UART_ID_Type uartNo)
{
  uart_reg_t * UARTx = (uart_reg_t *)(uartAddr[uartNo]);

  /* Check the parameters */
  CHECK_PARAM(IS_UART_PERIPH(uartNo));

  UARTx->IIR_FCR.BF_FCR.XFIFOR = 1;
}

/*************************************************************************//*
 * @brief      set stick parity
 *
 * @param[in]  uartNo:  Select the UART port, should be UART1_ID, UART2_ID.
 *
 * @return none
 *
 ***************************************************************************
*/
void UART_SetStickParity(UART_ID_Type uartNo)
{
	uart_reg_t * UARTx = (uart_reg_t *)(uartAddr[uartNo]);
	UARTx->LCR.BF.RESERVED_5 = 1;
}

/****************************************************************************//**
 * @brief      Get current value of Line Status register
 *
 * @param[in]  uartNo:  Select the UART port,should be UART0_ID, UART1_ID,
 *                                                     UART2_ID, UART3_ID
 * @param[in]  lineStatus:  Checks whether the specified UART Line status bit
                       is set or not
 *
 * @return The state value of UART Line Status register
 *
 *******************************************************************************/
FlagStatus UART_GetLineStatus(UART_ID_Type uartNo,UART_LineStatus_Type lineStatus)
{
  FlagStatus bitStatus = RESET;
  uart_reg_t * UARTx = (uart_reg_t *)(uartAddr[uartNo]);

  /* Check the parameters */
  CHECK_PARAM(IS_UART_PERIPH(uartNo));
  CHECK_PARAM(IS_UART_LINESTATUS_BIT(lineStatus));

  switch(lineStatus)
  {
    case UART_LINESTATUS_DR:
      bitStatus = ((UARTx->LSR.BF.DR == 1) ? SET : RESET);
      break;

    case UART_LINESTATUS_OE:
      bitStatus = ((UARTx->LSR.BF.OE == 1) ? SET : RESET);
      break;

    case UART_LINESTATUS_PE:
      bitStatus = ((UARTx->LSR.BF.PE == 1) ? SET : RESET);
      break;

    case UART_LINESTATUS_FE:
      bitStatus = ((UARTx->LSR.BF.FE == 1) ? SET : RESET);
      break;

    case UART_LINESTATUS_BI:
      bitStatus = ((UARTx->LSR.BF.BI == 1) ? SET : RESET);
      break;

    case UART_LINESTATUS_THRE:
      bitStatus = ((UARTx->LSR.BF.THRE == 1) ? SET : RESET);
      break;

    case UART_LINESTATUS_TEMT:
      bitStatus = ((UARTx->LSR.BF.TEMT == 1) ? SET : RESET);
      break;

    case UART_LINESTATUS_RFE:
      bitStatus = ((UARTx->LSR.BF.RFE == 1) ? SET : RESET);
      break;

    case UART_LINESTATUS_TRANS_ERR:
      bitStatus = ((UARTx->LSR.WORDVAL & 0x9e) ? SET : RESET);

    default:
      break;
  }

  return bitStatus;
}

/****************************************************************************//**
 * @brief      Get current value of UART Modem Status register
 *
 * @param[in]  uartNo:  Select the UART port,should be UART0_ID, UART1_ID,
 *                                                     UART2_ID, UART3_ID
 * @param[in]  modemStatus:  Checks whether the specified UART modem status bit
                       is set or not
 *
 * @return The state value of UART Modem Status register
 *
 *******************************************************************************/
FlagStatus UART_GetModemStatus(UART_ID_Type uartNo,UART_ModemStatus_Type modemStatus)
{
  FlagStatus bitStatus = RESET;
  uart_reg_t * UARTx = (uart_reg_t *)(uartAddr[uartNo]);

  /* Check the parameters */
  CHECK_PARAM(IS_UART_PERIPH(uartNo));
  CHECK_PARAM(IS_UART_MODEMSTATUS_BIT(modemStatus));

  switch(modemStatus)
  {
    case UART_MODEMSTATUS_DCTS:
      bitStatus = ((UARTx->MSR.BF.DCTS == 1) ? SET : RESET);
      break;

    case UART_MODEMSTATUS_DDSR:
      bitStatus = ((UARTx->MSR.BF.DDSR == 1) ? SET : RESET);
      break;

    case UART_MODEMSTATUS_TERI:
      bitStatus = ((UARTx->MSR.BF.TERI == 1) ? SET : RESET);
      break;

    case UART_MODEMSTATUS_DDCD:
      bitStatus = ((UARTx->MSR.BF.DDCD == 1) ? SET : RESET);
      break;

    case UART_MODEMSTATUS_CTS:
      bitStatus = ((UARTx->MSR.BF.CTS == 1) ? SET : RESET);
      break;

    case UART_MODEMSTATUS_DSR:
      bitStatus = ((UARTx->MSR.BF.DSR == 1) ? SET : RESET);
      break;

    case UART_MODEMSTATUS_RI:
      bitStatus = ((UARTx->MSR.BF.RI == 1) ? SET : RESET);
      break;

    case UART_MODEMSTATUS_DCD:
      bitStatus = ((UARTx->MSR.BF.DCD == 1) ? SET : RESET);
      break;

    default:
      break;
  }

  return bitStatus;
}

/****************************************************************************//**
 * @brief      Get current value of UART Status register
 *
 * @param[in]  uartNo:  Select the UART port,should be UART0_ID, UART1_ID,
 *                                                     UART2_ID, UART3_ID
 * @param[in]  uartStatus:  Checks whether the specified UART status bit
                       is set or not
 *
 * @return The state value of UART Status register
 *
 *******************************************************************************/
FlagStatus UART_GetUartStatus(UART_ID_Type uartNo,UART_Status_Type uartStatus)
{
  FlagStatus bitStatus = RESET;
  uart_reg_t * UARTx = (uart_reg_t *)(uartAddr[uartNo]);

  /* Check the parameters */
  CHECK_PARAM(IS_UART_PERIPH(uartNo));
  CHECK_PARAM(IS_UART_STATUS_BIT(uartStatus));

  switch(uartStatus)
  {
    case UART_STATUS_BUSY:
      bitStatus = ((UARTx->USR.BF.BUSY == 1) ? SET : RESET);
      break;

    case UART_STATUS_TFNF:
      bitStatus = ((UARTx->USR.BF.TFNF == 1) ? SET : RESET);
      break;

    case UART_STATUS_TFE:
      bitStatus = ((UARTx->USR.BF.TFE == 1) ? SET : RESET);
      break;

    case UART_STATUS_RFNE:
      bitStatus = ((UARTx->USR.BF.RFNE == 1) ? SET : RESET);
      break;

    case UART_STATUS_RFF:
      bitStatus = ((UARTx->USR.BF.RFF == 1) ? SET : RESET);
      break;

    default:
      break;
  }

  return bitStatus;
}

/****************************************************************************//**
 * @brief      Get current UART interrupt Status
 *
 * @param[in]  uartNo:  Select the UART port,should be UART0_ID, UART1_ID,
 *                                                     UART2_ID, UART3_ID
 * @param[in]  intStatusType:  Checks whether the specified UART interrupt status bit
               is set or not
 *
 * @return The state value of UART Status register
 *
 *******************************************************************************/
IntStatus UART_GetIntStatus(UART_ID_Type uartNo, UART_INTStatus_Type intStatusType)
{
  IntStatus bitStatus = RESET;
  uart_reg_t * UARTx = (uart_reg_t *)(uartAddr[uartNo]);

  /* Check the parameters */
  CHECK_PARAM(IS_UART_PERIPH(uartNo));
  CHECK_PARAM(IS_UART_INT_STATUS_TYPE(intStatusType));

  switch(intStatusType)
  {
    case UART_INTSTATUS_MODEM:
      if(UARTx->IIR_FCR.BF_IIR.IID == UART_INTSTATUS_IID_MODEM)
      {
        bitStatus = SET;
      }
      break;

    case UART_INTSTATUS_LSI:
      if(UARTx->IIR_FCR.BF_IIR.IID == UART_INTSTATUS_IID_LSI)
      {
        bitStatus = SET;
      }
      break;

    case UART_INTSTATUS_TBEI:
      if(UARTx->IIR_FCR.BF_IIR.IID == UART_INTSTATUS_IID_TBEI)
      {
        bitStatus = SET;
      }
      break;

    case UART_INTSTATUS_RBFI:
      if(UARTx->IIR_FCR.BF_IIR.IID == UART_INTSTATUS_IID_RBFI)
      {
        bitStatus = SET;
      }
      break;

    case UART_INTSTATUS_BYDET:
      if(UARTx->IIR_FCR.BF_IIR.IID == UART_INTSTATUS_IID_BYDET)
      {
        bitStatus = SET;
      }
      break;

    case UART_INTSTATUS_RCVRTO:
      if(UARTx->IIR_FCR.BF_IIR.IID == UART_INTSTATUS_IID_RCVRTO)
      {
        bitStatus = SET;
      }
      break;

    case UART_INTSTATUS_ALL:
      if(UARTx->IIR_FCR.BF_IIR.IID != 0x01)
      {
        bitStatus = SET;
      }
      break;

    default:
      break;
  }

  return bitStatus;
}

/****************************************************************************//**
 * @brief      Get current UART receive FIFO level
 *
 * @param[in]  uartNo:  Select the UART port,should be UART0_ID, UART1_ID,
 *                                                     UART2_ID, UART3_ID
 *
 * @return The number of data entries in the receive FIFO
 *
 *******************************************************************************/
uint32_t UART_GetRxFIFOLevel(UART_ID_Type uartNo)
{
  uart_reg_t * UARTx = (uart_reg_t *)(uartAddr[uartNo]);

  /* Check the parameters */
  CHECK_PARAM(IS_UART_PERIPH(uartNo));

  return(UARTx->RFL.BF.RFL);
}

/****************************************************************************//**
 * @brief      Get current UART transmit FIFO level
 *
 * @param[in]  uartNo:  Select the UART port,should be UART0_ID, UART1_ID,
 *                                                     UART2_ID, UART3_ID
 *
 * @return The number of data entries in the transmit FIFO
 *
 *******************************************************************************/
uint32_t UART_GetTxFIFOLevel(UART_ID_Type uartNo)
{
  uart_reg_t * UARTx = (uart_reg_t *)(uartAddr[uartNo]);

  /* Check the parameters */
  CHECK_PARAM(IS_UART_PERIPH(uartNo));

  return(UARTx->TFL.BF.TFL);
}

/****************************************************************************//**
 * @brief      Enable UART SIR function
 *
 * @param[in]  uartNo:  Select the UART port,should be UART0_ID, UART1_ID,
 *                                                     UART2_ID, UART3_ID
 *
 * @return     None
 *
 *******************************************************************************/
void UART_SIR_Enable(UART_ID_Type uartNo)
{
  uart_reg_t * UARTx = (uart_reg_t *)(uartAddr[uartNo]);

  /* Check the parameters */
  CHECK_PARAM(IS_UART_PERIPH(uartNo));

  UARTx->MCR.BF.SIRE = 1;
}

/****************************************************************************//**
 * @brief      Disnable UART SIR function
 *
 * @param[in]  uartNo:  Select the UART port,should be UART0_ID, UART1_ID,
 *                                                     UART2_ID, UART3_ID
 *
 * @return     None
 *
 *******************************************************************************/
void UART_SIR_Disable(UART_ID_Type uartNo)
{
  uart_reg_t * UARTx = (uart_reg_t *)(uartAddr[uartNo]);

  /* Check the parameters */
  CHECK_PARAM(IS_UART_PERIPH(uartNo));

  UARTx->MCR.BF.SIRE = 0;
}

/****************************************************************************//**
 * @brief      Set LPDL register when SIR Low Power reception function
 *
 * @param[in]  uartNo:  Select the UART port,should be UART0_ID, UART1_ID,
 *                                                     UART2_ID, UART3_ID
 *             lpDl:  low power dl register value
 * @return     Status type: DERROR or DSUCCESS
 *
 *******************************************************************************/
Status UART_SIR_SetLPDL(UART_ID_Type uartNo, uint16_t lpDl)
{
  uint8_t tempVal = 0;
  uart_reg_t * UARTx = (uart_reg_t *)(uartAddr[uartNo]);

  /* Check the parameters */
  CHECK_PARAM(IS_UART_PERIPH(uartNo));

  if(0 == UARTx->USR.BF.BUSY)
  {
    tempVal = UARTx->LCR.BF.DLAB;
    UARTx->LCR.BF.DLAB = 1;
    UARTx->LPDLL.BF.LPDLL = (lpDl && 0xff);
    UARTx->LPDLH.BF.LPDLH = ((lpDl>>8) && 0xff);
    UARTx->LCR.BF.DLAB = tempVal;
    return DSUCCESS;
  }
  else
  {
    return DERROR;
  }
}

/****************************************************************************//**
 * @brief      Assert UART RTS bit in MCR if Auto Flow Control Disabled
 *
 * @param[in]  uartNo:  Select the UART port,should be UART0_ID, UART1_ID,
 *                                                     UART2_ID, UART3_ID
 *
 * @return     None
 *
 *******************************************************************************/
void UART_RTS_Assert(UART_ID_Type uartNo)
{
  uart_reg_t * UARTx = (uart_reg_t *)(uartAddr[uartNo]);

  /* Check the parameters */
  CHECK_PARAM(IS_UART_PERIPH(uartNo));

  UARTx->MCR.BF.RTS = 1;
}

/****************************************************************************//**
 * @brief      Deassert UART RTS bit in MCR if Auto Flow Control Disabled
 *
 * @param[in]  uartNo:  Select the UART port,should be UART0_ID, UART1_ID,
 *                                                     UART2_ID, UART3_ID
 *
 * @return     None
 *
 *******************************************************************************/
void UART_RTS_Deassert(UART_ID_Type uartNo)
{
  uart_reg_t * UARTx = (uart_reg_t *)(uartAddr[uartNo]);

  /* Check the parameters */
  CHECK_PARAM(IS_UART_PERIPH(uartNo));

  UARTx->MCR.BF.RTS = 0;
}

void UART_IntMask(UART_ID_Type uartNo,UART_INT_Type intType, IntMask_Type intMask)
{
  uart_reg_t * UARTx = (uart_reg_t *)(uartAddr[uartNo]);

  CHECK_PARAM(IS_UART_PERIPH(uartNo));
  CHECK_PARAM(IS_UART_INT_TYPE(intType));
  CHECK_PARAM(IS_INTMASK(intMask));

  switch(intType)
  {
    case UART_INT_EDSSI:
      UARTx->IER_DLH.BF_IER.EDSSI = ((intMask == UNMASK)? 1 : 0);
      break;

    case UART_INT_ELSI:
      UARTx->IER_DLH.BF_IER.ELSI = ((intMask == UNMASK)? 1 : 0);
      break;

    case UART_INT_ETBEI:
      if(intMask == UNMASK)
      {
        UARTx->IER_DLH.BF_IER.PTIME = 1;
        UARTx->IER_DLH.BF_IER.ETBEI = 1;
      }
      else
      {
        UARTx->IER_DLH.BF_IER.PTIME = 0;
        UARTx->IER_DLH.BF_IER.ETBEI = 0;
      }

      break;

    case UART_INT_ERBFI:
      UARTx->IER_DLH.BF_IER.ERBFI = ((intMask == UNMASK)? 1 : 0);
      break;

    case UART_INT_ALL:
      if(intMask == UNMASK)
      {
        UARTx->IER_DLH.WORDVAL |= 0x8F;
      }
      else
      {
        UARTx->IER_DLH.WORDVAL &= ~0x8F;
      }

      break;

    default:
      break;
  }
}


void UART0_IRQHandler(void)
{
   UART_IntHandler(INT_UART0,UART0_ID);
}

void UART1_IRQHandler(void)
{
   UART_IntHandler(INT_UART1,UART1_ID);
}
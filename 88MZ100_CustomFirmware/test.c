#include <stdio.h>
#include <stdint.h>
#include "core_cm3.h"           
#include "mz100_gpio.h"
#include "xflash.h"
#include "mz100_interrupt.h"
#include "mz100_rtc.h"
#include "mz100_pinmux.h"
#include "mz100_uart.h"
#include "epd.h"

int main(int argc, char *argv[])
{	  
	(*(unsigned int *)0xE000ED08) = 0x20100000;                       // Vector table in RAM and offset 0x4000
	(*(unsigned int *)0xE000E41A) = 0x40;   
	
	UART_Reset(1);
	
	GPIO_PinModeConfig(4, PINMODE_DEFAULT);
	GPIO_PinModeConfig(6, PINMODE_DEFAULT);
	GPIO_PinMuxFun(4, 4);//UART
	GPIO_PinMuxFun(6, 4);//UART
	
	UART_CFG_Type uartcfg;
	uartcfg.baudRate = 115200;
	uartcfg.dataBits = UART_DATABITS_8;
	uartcfg.stopBits = 1;
	uartcfg.parity = UART_PARITY_EVEN;
	uartcfg.autoFlowControl = DISABLE;
	UART_Init(1, &uartcfg);
	
	UART_FIFO_Type uartFifo;
	uartFifo.FIFO_ResetRx = 1;
	uartFifo.FIFO_ResetTx = 1;
	uartFifo.FIFO_Function = 1;
	uartFifo.FIFO_RcvrTrigger = 2;
	uartFifo.FIFO_TxEmptyTrigger = 3;	
	UART_FIFOConfig(1, &uartFifo);
	
	GPIO_PinMuxFun(29, PINMUX_GPIO);
	GPIO_PinMuxFun(3, PINMUX_GPIO);
	GPIO_SetPinDir(29, GPIO_OUTPUT);
	GPIO_SetPinDir(3, GPIO_INPUT);
	
	printf("Welcome\r\n");
	init_epd();		
	
	printPos("88MZ100\nCustom\nfirmware\n",0, 10, 6, EPD_BLACK, EPD_RED);
	printPos("Test",100, 160, 3, EPD_BLACK, EPD_BLACK);
	
	refresh_epd();
	
	int counter = 0;
	while(1==1){		
		printf("Counter: %i\r\n",counter++);
		printf("GPIO27: %i\r\n",GPIO_ReadPinLevel(27));
		
		while(UART_GetUartStatus(1,UART_STATUS_RFNE)){
		printf("UART: %02X\r\n",UART_ReceiveByte(1));
		}

		GPIO_WritePinOutput(29,!GPIO_ReadPinLevel(29));
		delay(10000);
		
	}
	return 0;
}
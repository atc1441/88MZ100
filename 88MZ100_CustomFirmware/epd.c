#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "core_cm3.h"
#include "epd.h"
#include "mz100_gpio.h"
#include "mz100_ssp.h"
#include "mz100_pinmux.h"
#include "font.h"

uint8_t buffer_black[15000];
uint8_t buffer_red[15000];

uint8_t cursor_x, cursor_y, textsize = 4;
uint16_t textcolor = EPD_WHITE,textbgcolor = EPD_WHITE;

void sub_7DA(unsigned int result)
{
  unsigned int v1;

  if ( result )
  {
    if ( result == 1 )
    {
      v1 = ((*(unsigned int *)0x4A080008) & 0xFFFFF9FF) + 512;
    }
    else if ( result == 2 )
    {
      v1 = ((*(unsigned int *)0x4A080008) & 0xFFFFF9FF) + 1024;
    }
    else
    {
      if ( result != 3 )
        return;
      v1 = (*(unsigned int *)0x4A080008) | 0x600;
    }
  }
  else
  {
    v1 = (*(unsigned int *)0x4A080008) & 0xFFFFF9FF;
  }
  (*(unsigned int *)0x4A080008) = v1;
}

void sub_814(unsigned int result, int a2)
{
	unsigned int v2;
	
	if ( result )
	{
	if ( result != 1 )
		return;
	if ( a2 )
	{
		if ( a2 != 1 )
		return;
		v2 = (*(unsigned int *)0x4A080008) | 0x4000;
	}
	else
	{
		v2 = (*(unsigned int *)0x4A080008) & 0xFFFFBFFF;
	}
	}
	else if ( a2 )
	{
	if ( a2 != 1 )
		return;
	v2 = (*(unsigned int *)0x4A080008) | 0x2000;
	}
	else
	{
	v2 = (*(unsigned int *)0x4A080008) & 0xFFFFDFFF;
	}
	(*(unsigned int *)0x4A080008) = v2;
}

void sub_A98(char a1, char a2)
{
	(*(unsigned int *)0x4A080010) &= 0xFFFFF03F | ((a1 & 0x3F) << 6);
	(*(unsigned int *)0x4A080010) &= 0xFFFFFFC0 | (a2 & 0x3F);
}

void init_GPIO_EPD()
{
	SSP_Disable(1);
	GPIO_PinMuxFun(2,  PINMUX_GPIO);
	GPIO_PinMuxFun(23, PINMUX_GPIO);                        // GPIO
	GPIO_PinMuxFun(24, PINMUX_GPIO);
	GPIO_PinMuxFun(26, PINMUX_GPIO);
	GPIO_PinMuxFun(27, PINMUX_GPIO);
	GPIO_SetPinDir(2,  GPIO_OUTPUT);
	GPIO_SetPinDir(23, GPIO_OUTPUT);
	GPIO_SetPinDir(24, GPIO_OUTPUT);
	GPIO_SetPinDir(26, GPIO_OUTPUT);
	GPIO_SetPinDir(27, GPIO_INPUT);
	GPIO_PinModeConfig(27, PINMODE_PULLUP);              
	GPIO_PinMuxFun(12, 6);// SPI
	GPIO_PinMuxFun(13, 6);// SPI
	GPIO_PinMuxFun(22, 6);// SPI    
	
	GPIO_WritePinOutput(2,HIGH);
	GPIO_WritePinOutput(23,HIGH);
	GPIO_WritePinOutput(24,HIGH);
	GPIO_WritePinOutput(26,HIGH);

	SSP_CFG_Type sspCfgStruct;	
	sspCfgStruct.mode = SSP_NORMAL;
	sspCfgStruct.masterOrSlave = SSP_MASTER;
	sspCfgStruct.trMode = SSP_TR_MODE;
	sspCfgStruct.dataSize = SSP_DATASIZE_8;
	sspCfgStruct.sfrmPola = SSP_SAMEFRM_PSP;
	sspCfgStruct.slaveClkRunning = SSP_SLAVECLK_TRANSFER;
	sspCfgStruct.txd3StateEnable = ENABLE;	
	SSP_Init(1, &sspCfgStruct);
	
	SSP_FIFO_Type sspFifoCfg;
	sspFifoCfg.fifoPackMode =  DISABLE;
	sspFifoCfg.rxFifoFullLevel = 0;
	sspFifoCfg.txFifoEmptyLevel = 0;
	sspFifoCfg.rxDmaService = DISABLE;
	sspFifoCfg.txDmaService = DISABLE;
	SSP_FifoConfig(1, &sspFifoCfg);
	
	SPI_Param_Type spiParaStruct;
	spiParaStruct.spiClkPhase = SPI_SCPHA_1;
	spiParaStruct.spiClkPolarity = SPI_SCPOL_LOW;
	SPI_Config(1, &spiParaStruct);
	
	sub_7DA(0);
	sub_814(1, 0);
	sub_A98(1, 1);
	SSP_Enable(1);
	
	delay(1000);
	GPIO_WritePinOutput(24,LOW);
	delay(1000);
	GPIO_WritePinOutput(24,HIGH);
	delay(1000);
}

void EPD_send_spi_cmd(int a1)
{
	GPIO_WritePinOutput(26,LOW);
	GPIO_WritePinOutput(23,LOW);
	SSP_SendData(1, a1);
	GPIO_WritePinOutput(26,HIGH);
	GPIO_WritePinOutput(23,HIGH);
}

void EPD_send_spi_data(int a1)
{
	GPIO_WritePinOutput(23,LOW);
	SSP_SendData(1, a1);
	GPIO_WritePinOutput(23,HIGH);
}

void init_wakeup_EPD()
{
	GPIO_WritePinOutput(2,LOW);
	
	EPD_send_spi_cmd(0x01);
	EPD_send_spi_data(0x03);
	EPD_send_spi_data(0x00);
	
	EPD_send_spi_cmd(0x06);
	EPD_send_spi_data(0x17);
	EPD_send_spi_data(0x17);
	EPD_send_spi_data(0x17);
	
	EPD_send_spi_cmd(0x04);
	
	delay(10);
	while(!GPIO_ReadPinLevel(27));
	
	EPD_send_spi_cmd(0x61);
	EPD_send_spi_data(0x01);
	EPD_send_spi_data(0x90);
	EPD_send_spi_data(0x01);
	EPD_send_spi_data(0x2C);
	
	EPD_send_spi_cmd(0x50);
	EPD_send_spi_data(0x77);
	
	EPD_send_spi_cmd(0x00);
	EPD_send_spi_data(0x07);
	
	EPD_send_spi_cmd(0x40);
	
	delay(10);
	GPIO_WritePinOutput(2,HIGH);
}

void display_refresh_and_sleep()
{
	GPIO_WritePinOutput(2,LOW);
	EPD_send_spi_cmd(0x12);
	delay(10);
	while(!GPIO_ReadPinLevel(27));
	EPD_send_spi_cmd(0x02);
	delay(10);
	while(!GPIO_ReadPinLevel(27));
	EPD_send_spi_cmd(0x07);
	EPD_send_spi_data(0xA5);
	GPIO_WritePinOutput(2,HIGH);
}

void display_send_buffer()
{
	GPIO_WritePinOutput(2,LOW);
	EPD_send_spi_cmd(0x10);
    int v1 = 0;
    do{
      EPD_send_spi_data(~buffer_black[v1]);
	  v1++;
	}
    while ( v1 < 15000 );
	EPD_send_spi_cmd(0x13);
    v1 = 0;
    do{
      EPD_send_spi_data(~buffer_red[v1]);
	  v1++;
	}
    while ( v1 < 15000 );
	GPIO_WritePinOutput(2,HIGH);
}

void drawPixel(int16_t x, int16_t y, uint16_t color)
{
	//x = 400 - x;
	y = 300 - y;
	uint16_t i = x / 8 + y * 400 / 8;
	
	buffer_black[i] = (buffer_black[i] & (0xFF ^ (1 << (7 - x % 8)))); // white
	buffer_red[i] = (buffer_red[i] & (0xFF ^ (1 << (7 - x % 8)))); // white
	if (color == EPD_WHITE) return;
	else if (color == EPD_BLACK) buffer_black[i] = (buffer_black[i] | (1 << (7 - x % 8)));
	else if (color == EPD_RED) buffer_red[i] = (buffer_red[i] | (1 << (7 - x % 8)));
	else
	{
	if ((color & 0xF100) > (0xF100 / 2)) buffer_red[i] = (buffer_red[i] | (1 << (7 - x % 8)));
	else if ((((color & 0xF100) >> 11) + ((color & 0x07E0) >> 5) + (color & 0x001F)) < 3 * 255 / 2)
	{
		buffer_black[i] = (buffer_black[i] | (1 << (7 - x % 8)));
	}
	}
}

void fillRect(int16_t x, int16_t y, int16_t w, int16_t h,uint16_t color)
{
	int x1,y1;
	for (y1 = h; y1 > 0; y1--) {
		for (x1 = w; x1 > 0; x1--) {
			drawPixel(x1+x, y1+y, color);
		}
	}
}

void drawFastVLine(int16_t x, int16_t y, int16_t h,uint16_t color) {
  while (h--) {
	drawPixel(x, y+h, color);
  }
}

void drawChar(int16_t x, int16_t y, unsigned char c,uint16_t color, uint16_t bg, uint8_t size) {
	int8_t i,j;
        for(i=0; i<5; i++ ) {
            uint8_t line = font[c * 5 + i];
            for(j=0; j<8; j++, line >>= 1) {
                if(line & 1) {
                    if(size == 1)
                        drawPixel(x+i, y+j, color);
                    else
                        fillRect(x+i*size, y+j*size, size, size, color);
                } else if(bg != color) {
                    if(size == 1)
                        drawPixel(x+i, y+j, bg);
                    else
                        fillRect(x+i*size, y+j*size, size, size, bg);
                }
            }
        }
        if(bg != color) { 
            if(size == 1) drawFastVLine(x+5, y, 8, bg);
            else          fillRect(x+5*size, y, size, 8*size, bg);
        }
}

void write(uint8_t c) {
    if(c == '\n') {                       
        cursor_x  = 0;                   
        cursor_y += textsize * 8;          
    } else if(c != '\r') { 
        drawChar(cursor_x, cursor_y, c, textcolor, textbgcolor, textsize);
        cursor_x += textsize * 6;     
        }
}

void print(char text[]){
	uint16_t poi = 0;
	while(text[poi] != 0){
	write(text[poi++]);
	}	
}

void printPos(char text[],int x, int y, int size, uint16_t color, uint16_t bgcolor){
	uint16_t poi = 0;
	while(text[poi] != 0){
		
		if(text[poi] == '\n') {                       
			x  = 0;                   
			y += size * 8;          
		} else if(text[poi] != '\r') { 
			drawChar(x, y, text[poi], color, bgcolor, size);
			x += size * 6;     
        }
		poi++;
	}	
}

void init_epd()
{
	memset(buffer_black,0x00,15000);
	memset(buffer_red,0x00,15000);
}

void refresh_epd(){	
	init_GPIO_EPD();
	init_wakeup_EPD();
	display_send_buffer();	
	display_refresh_and_sleep();
}



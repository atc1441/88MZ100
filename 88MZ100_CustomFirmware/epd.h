#pragma once
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define EPD_BLACK     0x0000
#define EPD_WHITE     0xFFFF
#define EPD_RED       0xF800


void init_GPIO_EPD();
void EPD_send_spi_cmd(int a1);
void EPD_send_spi_data(int a1);
void init_wakeup_EPD();
void display_refresh_and_sleep();
void display_send_buffer();
void drawPixel(int16_t x, int16_t y, uint16_t color);
void fillRect(int16_t x, int16_t y, int16_t w, int16_t h,uint16_t color);
void drawFastVLine(int16_t x, int16_t y, int16_t h,uint16_t color);
void drawChar(int16_t x, int16_t y, unsigned char c,uint16_t color, uint16_t bg, uint8_t size);
void write(uint8_t c);
void print(char text[]);
void printPos(char text[],int x, int y, int size, uint16_t color, uint16_t bgcolor);

void init_epd();
void refresh_epd();
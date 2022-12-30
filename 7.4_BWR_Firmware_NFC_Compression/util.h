#ifndef _UTIL_H_
#define _UTIL_H_

#include <stdbool.h>
#include <stdint.h>

void delay(int cnt);
void delay_us(unsigned int result);
uint16_t crc16(uint16_t cur_crc, uint8_t data);
uint32_t measureTemp(void);
uint32_t measureBattery(void);	//return mV

void qspiEraseRange(uint32_t addr, uint32_t len);		//will over-erase to  round up to erase block boundary

void radioShutdown(void);		//experimentally written. suggest reset after use to bring radio back :)

#endif

#pragma once

void ZIGBEE_set_filter(uint16_t dest_pan, uint16_t source_addr, uint32_t own_mac[], uint8_t rx_filter);
void radioSetTxPower(char result);
void RF_init(uint8_t channel);
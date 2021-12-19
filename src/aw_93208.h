#ifndef AW93208_H
#define AW93208_H

#include<Wire.h>

void aw93208_init(void);
void aw93208_read(uint8_t *rx_buff);
void aw_iic_write(uint8_t icAddr, uint16_t regAddr, uint32_t *tx_buffer, uint8_t buffSize);
void aw_iic_read(uint8_t icAddr, uint16_t regAddr, uint32_t *rx_buffer, uint8_t buffSize);

#endif

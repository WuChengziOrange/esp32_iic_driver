#include "aw_93208.h"

void aw93208_init()
{
    Wire1.begin(25, 26);
}

void aw93208_read(uint8_t *rx_buff)
{
    uint8_t buff[4] = {0x1b, 0xa0};
    Wire1.writeTransmission(0x12, buff, 2, false);
    Wire1.readTransmission(0x12, rx_buff, 4, true);
}

static void transTo8(uint16_t regAddr, uint8_t* buf)
{
    buf[0] = regAddr >> 8;
    buf[1] = regAddr & 0xff;
}

static void transTo8(uint32_t tx, uint8_t* buf)
{
    buf[0] = tx >> 24;
    buf[1] = (tx >> 16) & 0xff;
    buf[2] = (tx >> 8) & 0xff;
    buf[3] = tx & 0xff;
}

static void transTo8(uint32_t *tx_buffer, uint8_t size, uint8_t *buf)
{
    for (uint8_t i = 0; i < size; i++) {
        transTo8(tx_buffer[i], &buf[i * 4]);
    }
}

void aw_iic_write(uint8_t icAddr, uint16_t regAddr, uint32_t *tx_buffer, uint8_t buffSize)
{
    uint8_t buffer[100] = {0};
    transTo8(regAddr, buffer);
    transTo8(tx_buffer, buffSize, buffer + 2);
    Wire1.writeTransmission(icAddr, buffer, 4 * buffSize + 2, true);
}

void aw_big_little(uint32_t *buf, uint8_t size)
{
    transTo8(buf, size, (uint8_t *)buf);
}

void aw_iic_read(uint8_t icAddr, uint16_t regAddr, uint32_t *rx_buffer, uint8_t buffSize)
{
    uint8_t buff[2] = {0x1b, 0xa0};
    transTo8(regAddr, buff);
    Wire1.writeTransmission(0x12, buff, 2, false);
    Wire1.readTransmission(0x12, (uint8_t *)rx_buffer, 4 * buffSize, true);
    aw_big_little(rx_buffer, buffSize);
}

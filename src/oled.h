#ifndef OLED_H
#define OLED_H

#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif

#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

void oled_init(void);
void oled_func(void);
void draw_dots(void);
void test_cursor(void);
void draw_slider(uint32_t x, uint32_t y);
#endif
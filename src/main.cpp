#if 1
#include <Arduino.h>
#include <oled.h>
#include <aw_93208.h>
void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
oled_init();
aw93208_init();
}

void loop() {
  // put your main code here, to run repeatedly:
  static uint8_t cnt = 0;
  uint32_t rx_buff[4] = {0};
  uint32_t tx_buff[1] = {1};
  // aw93208_read(rx_buff);
  aw_iic_read(0x12, 0x1ba0, rx_buff, 4);
  Serial.println("\nhello, arduino!");
  for (uint8_t i = 0; i < 4; i++) {
    Serial.printf("%x ",rx_buff[i]);
  }
  oled_func();
  delay(1000);
  cnt++;
  if (cnt == 10) {
    aw_iic_write(0x12, 0x4408, tx_buff, 1);
  }
}

#else

#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);


void setup(void) {
  u8g2.begin();
  u8g2.enableUTF8Print();		// enable UTF8 support for the Arduino print() function
}

void loop(void) {
  u8g2.setFont(u8g2_font_unifont_t_chinese2);  // use chinese2 for all the glyphs of "你好世界"
  u8g2.setFontDirection(0);
  u8g2.clearBuffer();
  u8g2.setCursor(0, 15);
  u8g2.print("Hello World!");
  u8g2.setCursor(0, 40);
  u8g2.print("你好世界");		// Chinese "Hello World"
  u8g2.sendBuffer();

  delay(1000);
}

#endif
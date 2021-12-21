#if 1
#include <Arduino.h>
#include <oled.h>
#include <aw_93208.h>
void setup() {
  // put your setup code here, to run once:
  uint32_t tx_buff[1] = {1};
  Serial.begin(115200);
  oled_init();
  aw93208_init();

  aw_iic_write(0x12, 0x4408, tx_buff, 1);
}

// static void old_loop(void){
// // put your main code here, to run repeatedly:
//   static uint8_t cnt = 0;
//   uint32_t rx_buff[4] = {0};
//   uint32_t tx_buff[1] = {1};
//   // aw93208_read(rx_buff);
//   aw_iic_read(0x12, 0x1ba0, rx_buff, 4);
//   Serial.println("\nhello, arduino!");
//   for (uint8_t i = 0; i < 4; i++) {
//     Serial.printf("%x ",rx_buff[i]);
//   }
//   oled_func();
//   delay(1000);
//   cnt++;
//   if (cnt == 10) {
//     aw_iic_write(0x12, 0x4408, tx_buff, 1);
//   }
//   // draw_dots();
//   test_cursor();
// }

void loop() {
  static bool is_first = false;
  uint32_t rx_buff[2] = {0};
  aw_iic_read(0x12, 0x1e9c, rx_buff, 2);
  if (rx_buff[0]) {
    Serial.printf("\nx: %d, y: %d\n", rx_buff[0], rx_buff[1]);
    is_first = true;
  } else {
    if(is_first) {
      Serial.printf("\nx: %d, y: %d\n", rx_buff[0], rx_buff[1]);
      is_first = false;
    }
  }
  draw_slider(rx_buff[0], rx_buff[1]);
  delay(10);
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
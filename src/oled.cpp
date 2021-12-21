#include <oled.h>


U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void oled_init(void)
{
  u8g2.begin();
  u8g2.enableUTF8Print();		// enable UTF8 support for the Arduino print() function
}

void oled_func(void) {
  u8g2.setFont(u8g2_font_unifont_t_chinese2);  // use chinese2 for all the glyphs of "你好世界"
  u8g2.setFontDirection(0);
  u8g2.clearBuffer();
  u8g2.setCursor(0, 15); //15
  u8g2.print("Hello World!");
  u8g2.setCursor(0, 40);
  u8g2.print("你好世界");		// Chinese "Hello World"
  u8g2.sendBuffer();
}

void test_cursor(void){
  u8g2.clearBuffer();
  u8g2.setFontDirection(0);
  for (int i = 0; i < 128; i++){
    for (int j = 0; j < 64; j++){
      u8g2.setCursor(i, j); // 15
      u8g2.printf("x%d, y%d", i,j);
      u8g2.sendBuffer();
      delay(100);
      u8g2.clearBuffer();
      }
    }
}

void draw_dots(void)
{
  u8g2.clearBuffer();
  // u8g2.setFont(u8g2_font_6x10_tf);
  // u8g2.setFontRefHeightExtendedText();
  // u8g2.setDrawColor(1);
  // u8g2.setFontPosTop();
  // u8g2.setFontDirection(0);
  for (int x = 0; x < 50; x++)
    for (int y = 0; y < 50; y++){
      u8g2_DrawPixel(u8g2.getU8g2(), x, y);
      u8g2.sendBuffer();
      delay(100);
    }
}

/*
  This Library is written for OLED Display
  Author: Bonezegei (Jofel Batutay)
  Date: August 2023 
  Updated: March 2024
*/
#ifndef _BONEZEGEI_SSD1306_H_
#define _BONEZEGEI_SSD1306_H_
#include <Arduino.h>
#include <Wire.h>
#include "Bonezegei_Font.h"

#define SSD1306_ADDRESS_W 0x3C
#define SSD1306_CMD_MODE 0x80
#define SSD1306_DATA_MODE 0x40

class Bonezegei_SSD1306 {
public:
  Bonezegei_SSD1306();
  Bonezegei_SSD1306(int w, int h);
  void begin();
  void sendCommand(uint8_t cmd);
  void sendData(uint8_t data);
  void clear();
  void draw();
  void drawPixel(uint8_t x, uint8_t y, uint8_t pixel);

  void drawFilledRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
  void drawFilledRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t pixel);

  //draw text Fast skips 0
  void setChar8(uint8_t x, uint8_t y, char ch, int bits, uint8_t color);
  void drawChar(int x, int y, char ch, uint8_t color, const char fd[], const int dsc[95][3]);
  void drawText(int x, int y, const char *str, const char fd[], const int dsc[95][3]);
  void drawText(int x, int y, const char *str, Bonezegei_Font fnt);

  //draw text pixel including 0 value
  void _setChar8(uint8_t x, uint8_t y, char ch, int bits, uint8_t color);
  void _drawChar(int x, int y, char ch, uint8_t color, const char fd[], const int dsc[95][3]);
  void drawText(int x, int y, const char *str, uint8_t color, const char fd[], const int dsc[95][3]);

  unsigned char RAM[1024];
  uint16_t width;
  uint16_t height;

  int xRun;
  int yRun;

  Bonezegei_Font Font_Arial8;
  Bonezegei_Font Font_Arial10;
  Bonezegei_Font Font_Arial12;
  Bonezegei_Font Font_Arial14;
};

#endif

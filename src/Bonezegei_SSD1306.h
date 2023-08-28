/*
  This Library is written for OLED Display
  Author: Bonezegei (Jofel Batutay)
  Date: August 2023 
*/
#ifndef _BONEZEGEI_SSD1306_H_
#define _BONEZEGEI_SSD1306_H_
#include <Arduino.h>
#include <Wire.h>
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

  unsigned char RAM[1024];
  uint16_t width;
  uint16_t height;
};

#endif

/*
  This Library is written for OLED Display
  Author: Bonezegei (Jofel Batutay)
  Date: August 2023 
*/
#ifndef _BONEZEGEI_SSD1306_H_
#define _BONEZEGEI_SSD1306_H_
#include <Arduino.h>
#include <Wire.h>
#define SSD1306_ADDRESS_W 0x78
#define SSD1306_ADDRESS_R 0x79 

class Bonezegei_SSD1306 {
public:
  Bonezegei_SSD1306();

  void begin();
  void sendCommand(uint8_t cmd);
  void sendData(uint8_t data);
  
  unsigned char RAM[1024];
};


#endif

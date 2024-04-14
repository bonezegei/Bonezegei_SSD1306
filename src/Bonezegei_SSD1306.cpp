/*
  This Library is written for OLED Display
  Author: Bonezegei (Jofel Batutay)
  Date: August 2023 
*/
#include "Bonezegei_SSD1306.h"

Bonezegei_SSD1306::Bonezegei_SSD1306() {
  width = 128;
  height = 64;
}

Bonezegei_SSD1306::Bonezegei_SSD1306(int w, int h) {
  width = w;
  height = h;
}

void Bonezegei_SSD1306::begin() {
  Font_Arial8 = Bonezegei_Font(arial_8ptBitmaps, arial_8ptDescriptors);
  Font_Arial10 = Bonezegei_Font(arial_10ptBitmaps, arial_10ptDescriptors);
  Font_Arial12 = Bonezegei_Font(arial_12ptBitmaps, arial_12ptDescriptors);
  Font_Arial14 = Bonezegei_Font(arial_14ptBitmaps, arial_14ptDescriptors);


  Wire.begin();
  Wire.setClock(3000000);
  sendCommand(0x40);
  sendCommand(0x8D);
  sendCommand(0x14);
  sendCommand(0x20);
  sendCommand(0x00);
  sendCommand(0xA1);
  sendCommand(0xC8);
  sendCommand(0xDA);
  sendCommand(0x12);
  sendCommand(0x81);
  sendCommand(0xFF);
  sendCommand(0xd9);
  sendCommand(0xF1);
  sendCommand(0xDB);
  sendCommand(0x40);
  sendCommand(0xA4);
  sendCommand(0xA6);
  sendCommand(0x2E);
  sendCommand(0x20);
  sendCommand(0x00);
}

void Bonezegei_SSD1306::sendCommand(uint8_t cmd) {
  Wire.beginTransmission(SSD1306_ADDRESS_W);
  Wire.write(SSD1306_CMD_MODE);
  Wire.write(cmd);
  Wire.endTransmission();
}

void Bonezegei_SSD1306::sendData(uint8_t data) {
  Wire.beginTransmission(SSD1306_ADDRESS_W);
  Wire.write(SSD1306_DATA_MODE);
  Wire.write(data);
  Wire.endTransmission();
}

void Bonezegei_SSD1306::draw() {
  //Reset Address to zero
  sendCommand(0xB0);
  sendCommand(0x00);
  sendCommand(0x10);

  uint8_t byte_height = height / 8;
  int total = width * byte_height;
  for (int a = 0; a < total; a++) {
    sendData(RAM[a]);  // draw Array data
  }
  sendCommand(0xAF);  //display
}

void Bonezegei_SSD1306::drawPixel(uint8_t x, uint8_t y, uint8_t pixel) {
  int iY = (y / 8);  //index Y
  int shift = (y - (iY * 8));
  int index = x + (iY * width);
  unsigned char tmp = 0;

  if (pixel) {
    tmp = RAM[index] | (1 << shift);

  } else {
    unsigned char t = 0;
    t = (1 << shift);
    tmp = RAM[index] & ~t;
  }
  RAM[index] = tmp;
}

void Bonezegei_SSD1306::clear() {
  //Reset Address to zero
  sendCommand(0xB0);
  sendCommand(0x00);
  sendCommand(0x10);

  uint8_t byte_height = height / 8;
  int total = width * byte_height;
  for (int a = 0; a < total; a++) {
    RAM[a] = 0;
    sendData(RAM[a]);  // draw Array data
  }
  sendCommand(0xAF);  //display
}

void Bonezegei_SSD1306::drawFilledRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2) {

  for (int y = 0; y < (y2 - y1); y++) {
    for (int x = 0; x < (x2 - x1); x++) {
      drawPixel(x1 + x, y1 + y, 1);
    }
  }
}

void Bonezegei_SSD1306::drawFilledRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t pixel) {
  for (int y = 0; y < (y2 - y1); y++) {
    for (int x = 0; x < (x2 - x1); x++) {
      drawPixel(x1 + x, y1 + y, pixel);
    }
  }
}


void Bonezegei_SSD1306::setChar8(uint8_t x, uint8_t y, char ch, int bits, uint8_t color) {
  int b = 0;
  for (int a = 7; a > (7 - bits); a--) {
    if (ch & (1 << a)) drawPixel(x + b, y, color);
    b++;
  }
}

void Bonezegei_SSD1306::drawChar(int x, int y, char ch, uint8_t color, const char fd[], const int dsc[95][3]) {
  int b = ch - 32;
  int xLimit = width;
  //int yLimit = 240;

  if (xRun >= (xLimit - 8)) {
    xRun = 0;
    yRun += dsc[b][1] + 2;
  }
  int c = 0;
  if (dsc[b][0] <= 8) {
    for (int a = 0; a < dsc[b][1]; a++) {
      setChar8(xRun, yRun + a, fd[(dsc[b][2] + a)], dsc[b][0], color);
    }
  } else if ((dsc[b][0] > 8) && (dsc[b][0] <= 16)) {
    for (int a = 0; a < (dsc[b][1] * 2); a++) {
      if ((a % 2) == 0) setChar8(xRun, yRun + (a / 2), fd[(dsc[b][2] + a)], 8, color);
      else setChar8(xRun + 8, yRun + (a / 2), fd[(dsc[b][2] + a)], dsc[b][0] - 7, color);
    }
  } else {
    for (int a = 0; a < (dsc[b][1] * 3); a++) {
      if (c == 0) {
        setChar8(xRun, yRun + (a / 3), fd[(dsc[b][2] + a)], dsc[b][0] - 7, color);
      } else if (c == 1) {
        setChar8(xRun + 8, yRun + (a / 3), fd[(dsc[b][2] + a)], 8, color);
      } else if (c == 2) {
        setChar8(xRun + 16, yRun + (a / 3), fd[(dsc[b][2] + a)], 16, color);
      }
      c++;
      if (c >= 3) {
        c = 0;
      }
    }
  }
  xRun += dsc[b][0] + 2;
}

void Bonezegei_SSD1306::drawText(int x, int y, const char *str, const char fd[], const int dsc[95][3]) {
  xRun = x;
  yRun = y;
  while (*str) {
    drawChar(x, y, *str, 1, fd, dsc);
    str += 1;
  }
}

void Bonezegei_SSD1306::drawText(int x, int y, const char *str, Bonezegei_Font fnt) {
  xRun = x;
  yRun = y;
  while (*str) {
    drawChar(x, y, *str, 1, fnt._font_array, fnt._font_desc);
    str += 1;
  }
}


void Bonezegei_SSD1306::_setChar8(uint8_t x, uint8_t y, char ch, int bits, uint8_t color) {
  int b = 0;
  for (int a = 7; a > (7 - bits); a--) {
    if (ch & (1 << a)) drawPixel(x + b, y, color);
    else drawPixel(x + b, y, ~color);
    b++;
  }
}

void Bonezegei_SSD1306::_drawChar(int x, int y, char ch, uint8_t color, const char fd[], const int dsc[95][3]) {
  int b = ch - 32;
  int xLimit = width;
  //int yLimit = 240;

  if (xRun >= (xLimit - 8)) {
    xRun = 0;
    yRun += dsc[b][1] + 2;
  }

  if (dsc[b][0] <= 8) {
    for (int a = 0; a < dsc[b][1]; a++) {
      _setChar8(xRun, yRun + a, fd[(dsc[b][2] + a)], dsc[b][0], color);
    }
  } else {
    for (int a = 0; a < (dsc[b][1] * 2); a++) {
      if ((a % 2) == 0) _setChar8(xRun, yRun + (a / 2), fd[(dsc[b][2] + a)], 8, color);
      else _setChar8(xRun + 8, yRun + (a / 2), fd[(dsc[b][2] + a)], dsc[b][0] - 7, color);
    }
  }
  xRun += dsc[b][0] + 2;
}

void Bonezegei_SSD1306::drawText(int x, int y, const char *str, uint8_t color, const char fd[], const int dsc[95][3]) {
  xRun = x;
  yRun = y;
  while (*str) {
    _drawChar(x, y, *str, color, fd, dsc);
    str += 1;
  }
}

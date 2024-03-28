/*
  This Library is written for OLED Display Font
  Author: Bonezegei (Jofel Batutay)
  Date: MARCH 2024
*/

#ifndef _BONEZEGEI_FONT_H_
#define _BONEZEGEI_FONT_H_
#include "arial8.h"
#include "arial10.h"
#include "arial12.h"
#include "arial14.h"

class Bonezegei_Font {
public:
  Bonezegei_Font() {
  }
  Bonezegei_Font(const char font_array[], const int font_desc[95][3]) {
    _font_array = (char *)font_array;
    for (int b = 0; b < 95; b++) {
      for (int a = 0; a < 3; a++) {
        _font_desc[b][a] = font_desc[b][a];
      }
    }
  }

  char *_font_array;
  int _font_desc[95][3];
};




#endif

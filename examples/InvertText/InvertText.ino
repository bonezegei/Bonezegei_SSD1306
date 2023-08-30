/*
  OLED Iberted Text
  Author: Bonezegei (Jofel Batutay)
  Date: August 2023 
*/

//TextHelloWorld
#include "Bonezegei_SSD1306.h"
Bonezegei_SSD1306 oled(128, 64);

void setup() {
  oled.begin();
  oled.clear();
  oled.drawText(1, 0, "Hello World", arial_8ptBitmaps, arial_8ptDescriptors);
  oled.draw();  //update the screen
}

void loop() {
  String s = "milis:";
  s += millis();

  oled.drawFilledRectangle(0, 19, 127, 30, 1);
  oled.drawText(1, 20, s.c_str(), 0, arial_8ptBitmaps, arial_8ptDescriptors); //invert text set color to 0
  oled.draw();  //update the screen
  delay(1);
}

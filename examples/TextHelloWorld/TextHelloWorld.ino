/*
  OLEd TextHelloWorld
  Author: Bonezegei (Jofel Batutay)
  Date: August 2023 
*/

//TextHelloWorld
#include <Bonezegei_SSD1306.h>
Bonezegei_SSD1306 oled(128, 64);

void setup() {
  oled.begin();
  oled.clear();
  oled.drawText(10, 0, "Hello World", 1, arial_8ptBitmaps, arial_8ptDescriptors);
  oled.draw();  //update the screen
}

void loop() {
  String s = "milis:";
  s += millis();

  oled.drawFilledRectangle(0, 20, 127, 30, 0);
  oled.drawText(0, 20, s.c_str(), 1, arial_8ptBitmaps, arial_8ptDescriptors);
  oled.draw();  //update the screen
  delay(100);
}

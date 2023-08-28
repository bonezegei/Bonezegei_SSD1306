/*
  OLED Rectangle 128x64 SSD1306 OLED
  Author: Bonezegei (Jofel Batutay)
  Date: August 2023 
*/

#include <Bonezegei_SSD1306.h>
Bonezegei_SSD1306 oled(128,64);

void setup() {

  oled.begin();
  oled.clear();

  oled.drawFilledRectangle(20,2,100,15);
  oled.drawFilledRectangle(20,20,100,32);
  oled.draw(); //update the screen
}

void loop() {
}

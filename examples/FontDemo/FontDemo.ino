/*
  OLED Font Demo
  Author: Bonezegei (Jofel Batutay)
  Date: March 2024 
*/

#include <Bonezegei_SSD1306.h>

Bonezegei_SSD1306 oled(128, 64);

void setup() {
  Serial.begin(115200);

  oled.begin();
  oled.clear();
  oled.drawText(1, 0, "Arial8", oled.Font_Arial8);
  oled.drawText(1, 10, "Arial10", oled.Font_Arial10);
  oled.drawText(1, 24, "Arial12", oled.Font_Arial12);
  oled.drawText(1, 40, "Arial14", oled.Font_Arial14);
  oled.draw();  //update the screen
}

void loop() {

}

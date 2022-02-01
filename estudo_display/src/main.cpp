#include <Arduino.h>
#include "TFT_eSPI.h"

TFT_eSPI Display = TFT_eSPI();

void setup() {
  Display.init();
  Display.setTextColor(TFT_RED);
  Display.setTextSize(3);
  Display.drawCentreString("OLA, MUNDO!", 50, 50,4);
}

void loop() {
  // put your main code here, to run repeatedly:
}
#include <Arduino.h>
#include "TFT_eSPI.h"
#include <driver/gpio.h>
#include <driver/pcnt.h>
#include "botoes.h"
#include <rom/gpio.h>
#include "display.h"

//TFT_eSPI Display = TFT_eSPI();
long value = 0;
long value_ant = 0;
IHM Display;
void setup()
{
  Serial.begin(115200);
 // pinMode(35, INPUT);
 // Display.init();
  //Display.fillScreen(TFT_BLUE);
  //Display. setTextSize(3);
 
  Display.InicializaDisplay();
 
}

void loop()
{
  
 /* if(digitalRead(35) == LOW)
  {
    value++;
    delay(200);
  }
  if(value != value_ant)
  {
    Display.drawNumber(value,100,80);
    value_ant = value;
  }
  
  */
}

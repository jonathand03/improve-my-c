#include <Arduino.h>
#include "TFT_eSPI.h"
#include <driver/gpio.h>
#include <driver/pcnt.h>
#include "botoes.h"
#include <rom/gpio.h>
#include "display.h"

//TFT_eSPI Display = TFT_eSPI();

IHM Display;
void setup()
{
  Serial.begin(115200);
  //Display.init();
  //Display.fillScreen(TFT_BLUE);
  //Display.drawCentreString("OLA MUNDO",50,50,4);
  Display.TelaInicializacao();
 
}

void loop()
{
  
 
}

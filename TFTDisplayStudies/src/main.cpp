#include <Arduino.h>
#include "TFT_eSPI.h"
#include <rom/gpio.h>
#include "display.h"
#include "botoes.h"
//TFT_eSPI Display = TFT_eSPI();
int barra = 20;
int cont = 0;
IHM Display;
Button BtBaixo(35,HIGH);
Button BtCima(34,HIGH);
void setup()
{
  Serial.begin(115200);
  Display.InicializaDisplay();
  
 // Display.TelaMenuInicial(1);
  
}

void loop()
{
  
}
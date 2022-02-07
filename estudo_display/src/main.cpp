#include <Arduino.h>
#include "TFT_eSPI.h"
#include <driver/gpio.h>
#include <driver/pcnt.h>
#include "botoes.h"
#include <rom/gpio.h>
#include "display.h"

//TFT_eSPI Display = TFT_eSPI();

Button ALERTA(23, RISING);
void setup()
{
  IHM Teste();
  Serial.begin(115200);
 
}

void loop()
{
  ALERTA.ReadButton();
  Serial.print(estado_botoes_ihm[0]);
  Serial.print(estado_botoes_ihm[1]);
  Serial.print(estado_botoes_ihm[2]);
  Serial.print(estado_botoes_ihm[3]);
  Serial.println(estado_botoes_ihm[4]);
 
  delay(2000);
}

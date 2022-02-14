#include <Arduino.h>
#include "TFT_eSPI.h"
#include <rom/gpio.h>
#include "display.h"
#include "botao.h"
/* Regra de Ouro 
  Ordem dos botões : baixo -> cima -> enter -> standup -> alerta
                      0        1        2         3         4

*/
//TFT_eSPI Display = TFT_eSPI();
int barra = 20;
int cont = 0;
IHM Display;
Button BtBaixo(35,HIGH);
//Button BtCima(34,LOW);
void setup()
{
  Serial.begin(115200);
  Display.InicializaDisplay();
 // pinMode(35,INPUT);
}

void loop()
{
  BtBaixo.ReadButton();
  // if(opcao_atual != opcao_anterior)
  // {
  //   Display.TelaMenuInicial();
  //   opcao_anterior = opcao_atual;
  // }
  //delay(100);
  
}
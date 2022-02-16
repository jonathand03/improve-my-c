#include <Arduino.h>
#include "display.h"
#include "botao.h"
#include "display_logica.h"
/* Regra de Ouro 
  Ordem dos botões : baixo -> cima -> enter -> standup -> alerta
                      0        1        2         3         4

*/


IHM Display;

void setup()
{
  Serial.begin(115200);
  Display.InicializaDisplay();
  pagina_atual = 13;
  
}

void loop()
{
  opcao_atual = 0;
  opcao_anterior = -1;
  Display.NavegacaoMenu();
  //NavegacaoLogica();
  tempo_atual ++;
  if(tempo_atual > tempo_max)
  {
    tempo_atual = 0;
  }
  delay(3000);
 
}
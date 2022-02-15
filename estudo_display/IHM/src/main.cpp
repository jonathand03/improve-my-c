#include <Arduino.h>
#include "TFT_eSPI.h"
#include <rom/gpio.h>
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
  pagina_atual = 11;
}

void loop()
{
  opcao_atual = 0;
  opcao_anterior = -1;
  Display.NavegacaoMenu();
  NavegacaoLogica();
  estado_botoes_ihm[bt_cima] = ligado;
  delay(2000);
  estado_botoes_ihm[bt_cima] = desligado;
  delay(4000);
 
  
}
#include <Arduino.h>
#include "display.h"
#include "botao.h"
#include "display_logica.h"

/* Regra de Ouro 
  Ordem dos botões : baixo -> cima -> enter -> standup -> alerta
                      0        1        2         3         4
  39 cima
  34 enter
  35 standup
*/


IHM Display;
Button btBaixo(25,RISING); // Key 1
Button btCima(39,RISING); // Key 2
Button btEnter(34, RISING); // Key 3
Button btStandup(35, RISING);

void setup()
{
  Serial.begin(115200);
  Display.InicializaDisplay();
}

void loop()
{
  Display.NavegacaoMenu();
  btBaixo.ReadButton();
  btCima.ReadButton();
  btEnter.ReadButton();
  btStandup.ReadButton();
}

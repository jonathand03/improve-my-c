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
Button btBaixo(39,RISING);
Button btCima(34,RISING);
Button btEnter(35, RISING);

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
}

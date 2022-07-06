#include "manager.h"
//#include "display.h"
#include "display_tft.h"
#include "botao.h"
#include "com_ihm.h"
#include <Arduino.h>

int pagina_atual = 0;
int indice_anterior_enter = 0;
int opcao_atual = -1;
int opcao_anterior = -1;

const int bt_baixo = 0;
const int bt_cima = 1;
const int bt_enter = 2;

bool estado_boatao_cima = false;
bool estado_boatao_baixo = false;
bool estado_boatao_enter = false;
bool estado_boatao_standup = false;

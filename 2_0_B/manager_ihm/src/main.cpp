#include <Arduino.h>
#include <com_ihm.h>
#include "botao.h"
#include <Wire.h>
//#include "manager.h"
#include "display_tft.h"
#include "menu.h"

bool elevador_suporte_cir_dir = false;

void setup()
{
    /********************** COMUNICACAO SERIAL ***********************/
    inicializa_interface_com_ihm_cliente(); 
    inicializa_botoes_ihm();               
    inicializa_estado_botoes_ihm();
    registra_interrupcao();
    /***************** DISPLAY ************/
    inicializa_display();
    /**************** TELA ****************/
    menu_inicial();
}

void loop()
{
    /******************* NAVEGAÇÃO ***********************/
    menu_destaque();
    leitura_tecla_baixo();
    leitura_tecla_cima();
    leitura_tecla_enter();
}

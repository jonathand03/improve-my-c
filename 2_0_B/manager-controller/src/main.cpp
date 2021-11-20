#include <Arduino.h>
#include "manager.h"
#include "com_ihm.h"
#include "rom/gpio.h"
#include "steve_debug.h"
#include "sup_circ.h"


void setup() 
{
   // inicializa_modulos_controle();
    inicializa_interface_com_ihm_servidor();
    inicializa_tarefa_alarme();
}


void loop()
{

 // verifica_codigo_recebido();
 Serial.println("Estou na main");
}



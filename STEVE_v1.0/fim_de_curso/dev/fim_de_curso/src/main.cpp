#include <Arduino.h>
#include <stdlib.h>
#include "fim_de_curso.h"
#include "steve_debug.h"

/* ============================ Setup da main ============================*/
void setup() 
{
        Serial.begin(115200);
        inicializa_fim_de_curso();
}

/* ============================ Loop da main ============================*/
void loop()
{
        Serial.println("Estou na main");
        delay(2000);
}


//#endif
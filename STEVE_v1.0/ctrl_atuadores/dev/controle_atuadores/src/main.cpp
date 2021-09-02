
#include <Arduino.h>
#include <stdlib.h>
#include "atuadores.h"
#include "debug.h"

/* ============================ Setup da main ============================*/
void setup() 
{
        Serial.begin(115200);
        inicializa_atuadores();
}

/* ============================ Loop da main ============================*/
void loop()
{
        Serial.println("Estou na main");
        delay(2000);
}


//#endif
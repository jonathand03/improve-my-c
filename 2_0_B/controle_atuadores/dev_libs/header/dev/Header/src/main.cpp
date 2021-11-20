
#include <Arduino.h>
#include <stdlib.h>
#include "debug.h"
#include <giroscopio.h>
#include "inicializa.h"
sensors_event_t dados_mpu[2];
/* ============================ Setup da main ============================*/
void setup() 
{
        Serial.begin(115200);
        inicializa_mpu6050();
        pinMode(LED_BUILTIN, OUTPUT);
}

/* ============================ Loop da main ============================*/
void loop()
{

        mostra_dados_giroscopio(leitura_sensor_mpu(dados_mpu));
        delay(500);
}


//#endif
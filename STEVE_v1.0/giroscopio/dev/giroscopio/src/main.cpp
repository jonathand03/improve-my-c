
#include <Arduino.h>
#include <stdlib.h>
#include "steve_debug.h"
#include <giroscopio.h>

sensors_event_t dados_mpu[2];
/*
 * Setup da main
 */
void setup()
{
        Serial.begin(115200);
      
        pinMode(LED_BUILTIN, OUTPUT);
}

/*
*       Loop da main
*/
void loop()
{
        float value = 5;
        mostra_dados_giroscopio(leitura_sensor_mpu(dados_mpu));
        if (leitura_sensor_mpu(dados_mpu)->gyro.x > value)
        {
                debug("Deu certo!!");
        }
        delay(1000);
        Serial.println("---------------------------------------------- ");
}

//#endif

#include <Arduino.h>
#include <stdlib.h>
#include "steve_debug.h"
#include <giroscopio.h>

Adafruit_MPU6050 Mpu1;
Adafruit_MPU6050 Mpu2;




void setup()
{
        Serial.begin(115200);
        inicializa_sensor_mpu(endereco_mpu_modulo_1,Mpu1);
        inicializa_sensor_mpu(endereco_mpu_modulo_2,Mpu2);
        delay(3000);
}

int i, i1;
void loop()
{
        mostra_dados_giroscopio(leitura_sensor_mpu(Mpu1));
        delay(1000);
                /*
        Serial.println("Vamos inicializar o sensor 1...");
        for(i = 0; i< 10; i++)
        {
                mostra_dados_giroscopio(leitura_sensor_mpu(Mpu1));
                Serial.println("Status do Sensor: ");
                Serial.print(leitura_sensor_mpu(Mpu1).gyro.status);   
                Serial.println();
                delay(1000);
        }
        delay(5000);
        Serial.println("Vamos inicializar o sensor 2...");
        for(i1 = 0; i1< 10; i1++)
        {
                mostra_dados_giroscopio(leitura_sensor_mpu(Mpu2));
                delay(1000);
        }
      
        delay(5000);
        */
}       




#include <Arduino.h>
#include <stdlib.h>
#include "steve_debug.h"
#include <giroscopio.h>
#include<Wire.h>

const int endereco_gyro = ENDERECO_0X68;
Adafruit_MPU6050 Mpu1;

 

 
void setup()
{
        Serial.begin(115200);
        Wire.begin();
        inicializa_sensor_mpu(endereco_gyro, Mpu1);
}
void loop()
{
        mostra_dados_giroscopio(leitura_sensor_mpu(Mpu1));
        delay(100);
}

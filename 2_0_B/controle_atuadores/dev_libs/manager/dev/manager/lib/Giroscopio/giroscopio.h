/*!     @file  giroscopio.h
        @brief Biblioteca para o módulo MPU6050.

        Detalhes:
        As funções dessa lib têm o intuito de 
        capturar os dados gerados pelo MPU6050 e mostrar,
        caso necessário, seus valores no monitor serial.
*/




#ifndef GIROSCOPIO_H
#define GIROSCOPIO_H
#include <stdint.h>
#include <Adafruit_MPU6050.h>

#define ENDERECO_MPU_6050
#ifdef ENDERECO_MPU_6050
#define ENDERECO_0X68 0x68
#define ENDERECO_0X69 0x69
#endif



const uint8_t giroscopio_qtd = 2;
extern const uint8_t endereco_mpu_modulo_1;
extern const uint8_t endereco_mpu_modulo_2;

/* 
*   Área de exportação de funções 
*/

int inicializa_sensor_mpu(int endereco_sensor_mpu, Adafruit_MPU6050 &Sensor);
sensors_event_t leitura_sensor_mpu(Adafruit_MPU6050 &Sensor);
int mostra_dados_giroscopio(sensors_event_t leitura_sensor_mpu);
bool modo_soneca_sensor_mpu(Adafruit_MPU6050 &Sensor, bool status);
int verifica_endereco_sensor();

extern bool ativado;
extern bool desativado;
#endif
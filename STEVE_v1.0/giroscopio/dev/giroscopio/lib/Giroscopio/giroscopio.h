/*!     \file  giroscopio.h
        \brief Biblioteca para o módulo MPU6050.

        Detalhes:
        As funções dessa lib têm o intuito de 
        capturar os dados gerados pelo MPU6050 e mostrar,
        caso necessário, seus valores no monitor serial.
*/




#ifndef GIROSCOPIO_H
#define GIROSCOPIO_H

#include <Adafruit_Sensor.h>

/* 
*   Área de exportação de funções 
*/
int inicializa_mpu6050(void);
sensors_event_t *leitura_sensor_mpu(sensors_event_t *vetor_dados_mpu);
int mostra_dados_giroscopio(sensors_event_t *leitura_sensor_mpu);
int mostra_dados_acelerometro(sensors_event_t *leitura_sensor_mpu);
int formatador_serial_print_giroscopio(float *vetor_eixo_giroscopio);
int formatador_serial_print_acelerometro(float *vetor_eixo_acelerometro);
sensors_event_t *desativa_status_mpu6050(sensors_event_t *vetor_dados_mpu);
sensors_event_t *ativa_status_mpu6050(sensors_event_t *vetor_dados_mpu);

/*! \enum eixos_sensor_mpu
*   \brief Eixos do sensor MPU6050
*  
*    *********
*/
enum eixos_sensor_mpu
{
    x,
    y,
    z
};

/*! \enum dados_mpu
*   \brief Objetos da estrutura do MPU
*  
*    *********
*/
enum dados_mpu
{
    aceleracao,
    giroscopio
};

/*! \enum modo_operacional_sensor
*   \brief Atividade do sensor
*  
*    *********
*/
enum modo_operacional_sensor
{
    ativado,
    desativado
};

#endif
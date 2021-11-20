#include <Arduino.h>
#include "sup_circ.h"
#include "manager.h"
#include "giroscopio.h"
#include "atuadores.h"

Adafruit_MPU6050 GiroSuporteCirculatorio;
Adafruit_MPU6050 GiroBase;

TaskHandle_t SC = NULL;
int a = 0;
void inicializa_tarefa_alarme(void)
{
    inicializa_sensor_mpu(ENDERECO_0X68,GiroSuporteCirculatorio);
    xTaskCreate(alarme_suporte_circulatorio,"SC",10000,NULL, 1,&SC);
}


void alarme_suporte_circulatorio(void *args)
{
    for(;;)
    {
        for(int i = 0; i < qtd_ciclos; i++)
        {
            suporte_circulatorio_subida();
            vTaskDelay(pdMS_TO_TICKS(500));
            suporte_circulatorio_descida();
            vTaskDelay(pdMS_TO_TICKS(500));
        }
        vTaskDelay(pdMS_TO_TICKS(20000));
    }
}

void suporte_circulatorio_subida(void)
{
    while((leitura_sensor_mpu(GiroSuporteCirculatorio).gyro.y*10) < 10 )
    {
        //mostra_dados_giroscopio((leitura_sensor_mpu(GiroSuporteCirculatorio)));
        atuador_avancar(e_atuador_suporte_circu);
    }
    atuador_parar(e_atuador_suporte_circu);
}

void suporte_circulatorio_descida(void)
{
    while((leitura_sensor_mpu(GiroSuporteCirculatorio).gyro.y*10) > 1.5)
    {
        //mostra_dados_giroscopio((leitura_sensor_mpu(GiroSuporteCirculatorio)));
        atuador_recuar(e_atuador_suporte_circu);
    }
    atuador_parar(e_atuador_suporte_circu);
}

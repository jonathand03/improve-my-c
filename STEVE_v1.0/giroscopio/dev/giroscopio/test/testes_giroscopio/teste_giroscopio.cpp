#include <giroscopio.h>
#include <steve_debug.h>
#include <unity.h>

#ifdef UNIT_TEST

Adafruit_MPU6050 Mpu1;
Adafruit_MPU6050 Mpu2;

/*!
*       Casos de Sucesso 
*/
void test_inicializa_sensor_mpu(void)
{
        int verifica_retorno_inicializa_mpu6050;
        int valor_esperado_inicializa_mpu6050 = SUCESSO;

        verifica_retorno_inicializa_mpu6050 = inicializa_sensor_mpu(endereco_mpu_modulo_1,Mpu1);
        TEST_ASSERT_EQUAL(valor_esperado_inicializa_mpu6050, verifica_retorno_inicializa_mpu6050);

}

void test_leitura_sensor_mpu(void)
{
        sensors_event_t verifica_retorno_leitura_sensor_mpu;

        verifica_retorno_leitura_sensor_mpu = leitura_sensor_mpu(Mpu1);
        TEST_ASSERT(verifica_retorno_leitura_sensor_mpu.gyro.status == SUCESSO);
}

void test_mostra_dados_giroscopio(void)
{
        int verifica_retorno_mostra_dados_giroscopio;
        int valor_esperado_retorno_mostra_dados_giroscopio = SUCESSO;

        verifica_retorno_mostra_dados_giroscopio = mostra_dados_giroscopio(leitura_sensor_mpu(Mpu1));
        TEST_ASSERT_EQUAL(valor_esperado_retorno_mostra_dados_giroscopio,verifica_retorno_mostra_dados_giroscopio);
}

/*!
*      Casos de Falha
*/
void test_inicializa_sensor_mpu_falha(void)
{

        int verifica_retorno_inicializa_mpu6050;
        int valor_esperado_inicializa_mpu6050 = SINALIZADOR_ERRO;

        verifica_retorno_inicializa_mpu6050 = inicializa_sensor_mpu(0x72,Mpu1);
        TEST_ASSERT_EQUAL(valor_esperado_inicializa_mpu6050, verifica_retorno_inicializa_mpu6050);
}
void test_leitura_sensor_mpu_falha(void)
{
        sensors_event_t verifica_retorno_leitura_sensor_mpu;

        verifica_retorno_leitura_sensor_mpu = leitura_sensor_mpu(Mpu1);
        TEST_ASSERT(verifica_retorno_leitura_sensor_mpu.gyro.status == SINALIZADOR_ERRO);
}

void setup()
{
        //inicializa_mpu6050();
        UNITY_BEGIN();
        RUN_TEST(test_inicializa_sensor_mpu);
        RUN_TEST(test_inicializa_sensor_mpu_falha);
        RUN_TEST(test_leitura_sensor_mpu_falha);
        UNITY_END();
      
}


void loop()
{
      
}
#endif

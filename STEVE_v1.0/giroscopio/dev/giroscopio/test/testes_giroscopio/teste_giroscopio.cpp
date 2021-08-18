#include <giroscopio.h>
#include <steve_debug.h>
#include <unity.h>

Adafruit_MPU6050 Mpu1;
Adafruit_MPU6050 Mpu2;
Adafruit_MPU6050 Mpu3;


#ifdef UNIT_TEST


/*!
*       Casos de Sucesso 
*/
void test_inicializa_sensor_mpu_sucesso(void)
{
        int verifica_retorno_test_inicializa_sensor_mpu;
        int valor_esperado_test_inicializa_sensor_mpu = SUCESSO;

        verifica_retorno_test_inicializa_sensor_mpu = inicializa_sensor_mpu(endereco_mpu_modulo_1,Mpu1);
        TEST_ASSERT_EQUAL(valor_esperado_test_inicializa_sensor_mpu, verifica_retorno_test_inicializa_sensor_mpu);

}

void test_leitura_sensor_mpu_sucesso(void)
{
        sensors_event_t verifica_retorno_leitura_sensor_mpu;

        verifica_retorno_leitura_sensor_mpu = leitura_sensor_mpu(Mpu1);
        TEST_ASSERT(verifica_retorno_leitura_sensor_mpu.gyro.status == SUCESSO);
}


/*!
*      Casos de Falha
*/
void test_inicializa_sensor_mpu_falha(void)
{

        int verifica_retorno_test_inicializa_sensor_mpu;
        int valor_esperado_test_inicializa_sensor_mpu = SINALIZADOR_ERRO;

        verifica_retorno_test_inicializa_sensor_mpu = inicializa_sensor_mpu(0x72,Mpu1);
        TEST_ASSERT_EQUAL(valor_esperado_test_inicializa_sensor_mpu, verifica_retorno_test_inicializa_sensor_mpu);
}
void test_leitura_sensor_mpu_falha(void)
{
        sensors_event_t verifica_retorno_leitura_sensor_mpu;

        verifica_retorno_leitura_sensor_mpu = leitura_sensor_mpu(Mpu3);
        Serial.println(verifica_retorno_leitura_sensor_mpu.gyro.status);
        TEST_ASSERT(verifica_retorno_leitura_sensor_mpu.gyro.status == SINALIZADOR_ERRO);
}

void setup()
{
        //inicializa_mpu6050();
        UNITY_BEGIN();
        RUN_TEST(test_inicializa_sensor_mpu_sucesso);
        RUN_TEST(test_inicializa_sensor_mpu_falha);
        RUN_TEST(test_leitura_sensor_mpu_sucesso);
        RUN_TEST(test_leitura_sensor_mpu_falha);
        UNITY_END();
      
}


void loop()
{
      
}
#endif

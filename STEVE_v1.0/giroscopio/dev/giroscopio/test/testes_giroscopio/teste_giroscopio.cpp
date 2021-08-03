#include <giroscopio.h>
#include <steve_debug.h>
#include <unity.h>

#ifdef UNIT_TEST

/*!
*       Casos de Sucesso 
*/
void test_inicializa_mpu6050(void)
{
        int verifica_retorno_inicializa_mpu6050;
        int valor_esperado_inicializa_mpu6050 = SUCESSO;

        verifica_retorno_inicializa_mpu6050 = inicializa_mpu6050();
        TEST_ASSERT_EQUAL(valor_esperado_inicializa_mpu6050, verifica_retorno_inicializa_mpu6050);

}

void test_leitura_sensor_mpu_sucesso(void)
{
        sensors_event_t dados_mpu[2];
        sensors_event_t *verifica_retorno_leitura_sensor = NULL;
        int valor_esperado_status_sensor = ativado;

        verifica_retorno_leitura_sensor = leitura_sensor_mpu(dados_mpu);
        TEST_ASSERT_EQUAL(valor_esperado_status_sensor,dados_mpu[giroscopio].gyro.status);
        TEST_ASSERT(verifica_retorno_leitura_sensor != NULL);
}

void test_mostra_dados_giroscopio_sucesso(void)
{
        sensors_event_t dados_mpu[2];
        int verifica_retorno_mostra_dados_giroscopio;
        int valor_esperado_mostra_dados_giroscopio = SUCESSO;
        
        verifica_retorno_mostra_dados_giroscopio = mostra_dados_giroscopio(leitura_sensor_mpu(dados_mpu));
        TEST_ASSERT_EQUAL(valor_esperado_mostra_dados_giroscopio,verifica_retorno_mostra_dados_giroscopio);
}

void test_mostra_dados_acelerometro_sucesso(void)
{
        sensors_event_t dados_mpu[2];
        int verifica_retorno_mostra_dados_acelerometro;
        int valor_esperado_mostra_dados_acelerometro = SUCESSO;
        
        verifica_retorno_mostra_dados_acelerometro = mostra_dados_acelerometro(leitura_sensor_mpu(dados_mpu));
        TEST_ASSERT_EQUAL(valor_esperado_mostra_dados_acelerometro,verifica_retorno_mostra_dados_acelerometro);
}

void test_formatador_serial_print_giroscopio_sucesso(void)
{
        float vetor_artificial_eixos[3] = {1.32, 7.32, -5.3};
        int verifica_retorno_formatador_serial_print_giroscopio;
        int valor_esperado_formatador_serial_print_giroscopio = SUCESSO;

        verifica_retorno_formatador_serial_print_giroscopio = formatador_serial_print_giroscopio(vetor_artificial_eixos);
        TEST_ASSERT_EQUAL(valor_esperado_formatador_serial_print_giroscopio,verifica_retorno_formatador_serial_print_giroscopio);
}

void test_formatador_serial_print_acelerometro_sucesso(void)
{
        float vetor_artificial_eixos[3] = {1, 27.06, -5.3};
        int verifica_retorno_formatador_serial_print_acelerometro;
        int valor_esperado_formatador_serial_print_acelerometro = SUCESSO;
        
        verifica_retorno_formatador_serial_print_acelerometro = formatador_serial_print_acelerometro(vetor_artificial_eixos);
        TEST_ASSERT_EQUAL(valor_esperado_formatador_serial_print_acelerometro,verifica_retorno_formatador_serial_print_acelerometro);
}

/*!
*      Casos de Falha
*/

void test_leitura_sensor_mpu_falha(void)
{

}

void test_mostra_dados_giroscopio_falha(void)
{

}

void test_mostra_dados_acelerometro_falha(void)
{

}

void formatador_serial_print_giroscopio_falha(void)
{

}

void formatador_serial_print_acelerometro_falha(void)
{
}

void setup()
{
        //inicializa_mpu6050();
        UNITY_BEGIN();
        RUN_TEST(test_inicializa_mpu6050);
      
}

int i = 0;
int parada = 10;

void loop()
{
        if(i < parada)
        {
                RUN_TEST(test_leitura_sensor_mpu_sucesso);
                delay(100);
                RUN_TEST(test_mostra_dados_giroscopio_sucesso);
                delay(100);
                RUN_TEST(test_formatador_serial_print_giroscopio_sucesso);
                i++;
                delay(6000); 
        }
        else if(i == parada)
        {
                UNITY_END();
        }
}
#endif
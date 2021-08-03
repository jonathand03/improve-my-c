#include <debug.h>
#include <unity.h>
#include <Arduino.h>
#include <fim_de_curso.h>

#ifdef UNIT_TEST

/*!
        CASOS DE SUCESSO
*/
void test_instalar_servico_isr_sucesso(void)
{
    debug("");
    debug("-------------------------------------------------");
    TEST_ASSERT_EQUAL(SUCESSO, instalar_servico_isr(SINALIZADOR_INSTALACAO_DRIVER));
}

void test_configura_pinos_fim_curso_isr_sucesso(void)
{
    debug("");
    debug("-------------------------------------------------");
    TEST_ASSERT_EQUAL(SUCESSO, configura_pinos_fim_curso_isr(e_fim_curso_suporte_circ));
}

void test_retorna_pino_fim_curso_sucesso(void)
{
    debug("");
    debug("-------------------------------------------------");
    TEST_ASSERT_EQUAL(fim_curso_standup_low, retorna_pino_fim_curso(e_fim_curso_standup_low));
    TEST_ASSERT_EQUAL(fim_curso_standup_high, retorna_pino_fim_curso(e_fim_curso_standup_high));
    TEST_ASSERT_EQUAL(fim_curso_suporte_circ_low, retorna_pino_fim_curso(e_fim_curso_suporte_circ));
    TEST_ASSERT_EQUAL(fim_curso_reserva, retorna_pino_fim_curso(e_fim_curso_reserva));
}

/*!
        CASOS DE FALHA
*/
void test_instalar_servico_isr_falha(void)
{
    debug("");
    debug("-------------------------------------------------");
    gpio_uninstall_isr_service();
    esp_err_t verifica_retorno = instalar_servico_isr(50);
    debug(verifica_retorno);
    TEST_ASSERT(verifica_retorno != ESP_OK);
}

void test_configura_pinos_fim_curso_isr_falha(void)
{
    debug("");
    debug("-------------------------------------------------");
    int verifica_retorno = configura_pinos_fim_curso_isr(e_fim_curso_suporte_circ);
}

void test_retorna_pino_fim_curso_falha(void)
{
}

void setup()
{
    UNITY_BEGIN();
    pinMode(LED_BUILTIN, OUTPUT);
    RUN_TEST(test_instalar_servico_isr_sucesso);
    RUN_TEST(test_configura_pinos_fim_curso_isr_sucesso);
    RUN_TEST(test_retorna_pino_fim_curso_sucesso);
    RUN_TEST(test_instalar_servico_isr_falha);
    UNITY_END();
}

void loop()
{
}
#endif
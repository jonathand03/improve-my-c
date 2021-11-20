#include <unity.h>
#include "display.h"
#include "steve_debug.h"
#include <Arduino.h>
#include <Wire.h>
#ifdef UNIT_TEST


void test_inicializa_display_sucesso(void)
{
    int verfica_retorno_inicializa_display;
    int resultado_esperado_inicializa_display = SUCESSO;

    verfica_retorno_inicializa_display = inicializa_display();
    TEST_ASSERT_EQUAL(resultado_esperado_inicializa_display,verfica_retorno_inicializa_display);
}

void test_mensagem_display_sucesso(void)
{
    int verifica_retorno__mensagem_display;
    int resultado_esperado_mensagem_display = SUCESSO;
    limpa_display();
    verifica_retorno__mensagem_display = mensagem_display("Ola, pessoal",medio);
    TEST_ASSERT_EQUAL(resultado_esperado_mensagem_display,verifica_retorno__mensagem_display);
}

void test_tratamento_texto_display_sucesso(void)
{
    int verifica_retorno_tratamento_texto_display;
    int retorno_esperado_tratamento_texto_display = SUCESSO;
    verifica_retorno_tratamento_texto_display = tratamento_texto_display("esse eh um teste de verificacao do display", pequeno);
    TEST_ASSERT_EQUAL(retorno_esperado_tratamento_texto_display,verifica_retorno_tratamento_texto_display);
}

void test_inicializa_display_falha(void)
{
    int verfica_retorno_inicializa_display_falha;
    int resultado_esperado_inicializa_display_falha = SINALIZADOR_ERRO;

    verfica_retorno_inicializa_display_falha = inicializa_display();
    TEST_ASSERT_EQUAL(resultado_esperado_inicializa_display_falha,verfica_retorno_inicializa_display_falha);
}

void test_mensagem_display_falha(void)
{   
    int verifica_retorno_mensagem_display_falha;
    int retorno_esperado_mensagem_display_falha = SINALIZADOR_ERRO;

    verifica_retorno_mensagem_display_falha = mensagem_display("Esse eh um teste do display falhando", grande);
    TEST_ASSERT_EQUAL(retorno_esperado_mensagem_display_falha,verifica_retorno_mensagem_display_falha);
}

void test_tratamento_texto_display_falha(void)
{
    int verifica_retorno_tratamento_texto_display_falha;
    int retorno_esperado_tratamento_texto_display_falha = SINALIZADOR_ERRO;

    verifica_retorno_tratamento_texto_display_falha = tratamento_texto_display("ijwqeijwqijweijwjijqwiejwq", grande);
    TEST_ASSERT_EQUAL(retorno_esperado_tratamento_texto_display_falha, verifica_retorno_tratamento_texto_display_falha);
}

void setup()
{
    Serial.begin(115200);
    Wire.begin();
    UNITY_BEGIN();
           // RUN_TEST(test_inicializa_display_sucesso);
            //RUN_TEST(test_mensagem_display_sucesso);
            //RUN_TEST(test_tratamento_texto_display_sucesso);
           // RUN_TEST(test_mensagem_display_falha);
           // RUN_TEST(test_tratamento_texto_display_falha);
           // RUN_TEST(test_tratamento_texto_display_falha);
            debug("----------------------------------------");
            RUN_TEST(test_inicializa_display_falha);
            debug("----------------------------------------");
    UNITY_END();
}
void loop()
{

}
#endif
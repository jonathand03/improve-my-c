#include <Arduino.h>
#include <unity.h>
#include <inicializa.h>
#include <atuadores.h>
#include <debug.h>


#ifdef UNIT_TEST
        /* ======================================== Casos de Sucesso ===================================*/
        void test_escrita_atuador_sucesso(void)
        {
                digitalWrite(LED_BUILTIN, HIGH);
                TEST_ASSERT_EQUAL(SUCESSO,escrita_atuador(e_atuador_standup,avanco));
        }

        void test_atuador_avancar_sucesso(void)
        {
                TEST_ASSERT_EQUAL(SUCESSO,atuador_avancar(e_atuador_distancia_assento_encosto));
        }

        void test_atuador_recuar_sucesso(void)
        {
                TEST_ASSERT_EQUAL(SUCESSO,atuador_recuar(e_atuador_inclinacao_encosto));
        }

        /* ======================================== Casos de Falha ===================================*/
        void test_escrita_atuador_falha(void)
        {
                TEST_ASSERT_EQUAL(SINALIZADOR_ERRO,escrita_atuador(e_atuador_standup,5));
        }

        void test_atuador_avancar_falha(void)
        {
                estados_pinos_atuador[e_atuador_distancia_assento_encosto][avanco] = -1;
                TEST_ASSERT_EQUAL(SINALIZADOR_ERRO,atuador_avancar(e_atuador_distancia_assento_encosto));
        }

        void test_atuador_recuar_falha(void)
        {
                estados_pinos_atuador[e_atuador_inclinacao_encosto][recuo] = -255;
                TEST_ASSERT_EQUAL(SINALIZADOR_ERRO,atuador_recuar(e_atuador_inclinacao_encosto));
        }

        /* ================================ Setup de testes ===========================================*/
        void setup()
        {
                UNITY_BEGIN();
                        pinMode(LED_BUILTIN, OUTPUT);
                        debug("-------------------------------------------------------");
                        RUN_TEST(test_escrita_atuador_sucesso);
                        debug("-------------------------------------------------------");
                        RUN_TEST(test_atuador_avancar_sucesso);
                        debug("-------------------------------------------------------");
                        RUN_TEST(test_atuador_recuar_sucesso);
                        debug("-------------------------------------------------------");
                        RUN_TEST(test_escrita_atuador_falha);
                        debug("-------------------------------------------------------");
                        RUN_TEST(test_atuador_avancar_falha);
                        debug("-------------------------------------------------------");
                        RUN_TEST(test_atuador_recuar_falha);
                        debug("-------------------------------------------------------");
                UNITY_END();
        }

        /* ================================== Loop de testes ===========================================*/
        void loop()
        {
                
        }

#endif
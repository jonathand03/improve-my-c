#include "steve_debug.h"
#include <driver/adc.h>
#include <Arduino.h>

// Sinalizador de sucesso
extern const int SUCESSO = 0;
// Sinalizador de Erro
extern const int SINALIZADOR_ERRO = -1;

int pisca_delay(void)
{
        digitalWrite(led, HIGH);
        delay(1000);
        digitalWrite(led, LOW);
        delay(1000);
        return 0;
}
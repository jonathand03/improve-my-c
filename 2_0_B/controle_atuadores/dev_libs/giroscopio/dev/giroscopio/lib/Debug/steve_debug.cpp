#include "steve_debug.h"
#include <driver/adc.h>
#include <Arduino.h>

extern const int SUCESSO = 0; //!< Sinalizador de sucesso
extern const int SINALIZADOR_ERRO = -1; //!< Sinalizador de Erro

/*! \fn int pisca_delay(void)
*   \brief  Função de debug da placa

     *******
*/
int pisca_delay(void)
{
        digitalWrite(led, HIGH);
        delay(1000);
        digitalWrite(led, LOW);
        delay(1000);
        return 0;
}
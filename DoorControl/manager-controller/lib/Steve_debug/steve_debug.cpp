#include "steve_debug.h"
#include <driver/adc.h>
#include <Arduino.h>
extern int cotador_botao = 0;
extern const int SUCESSO = 0; //!< Sinalizador de sucesso
extern const int SINALIZADOR_ERRO = -1; //!< Sinalizador de Erro
const int led = LED_BUILTIN;
/*! \fn int pisca_delay(void)
*   \brief  Função de debug da placa

     *******
*/
void manager_interrupcao_fim_de_curso(void)
{
      Serial.print("Interrupcao gerada");
}


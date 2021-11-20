#include "steve_debug.h"
#include <driver/adc.h>
#include <Arduino.h>

extern const int SUCESSO = 0; //!< Sinalizador de sucesso

extern const int SINALIZADOR_ERRO = -1; //!< Sinalizador de Erro
/*! @fn void manager_interrupcao_fim_de_curso(void)
  * @brief   Função que é chamada quando acontece uma interrupção no pino
  * @param[in] fim_curso É uma enumeração referente ao fim de curso desejado
  * @return Retorna 0 em caso de sucesso, ou -1 em caso de falha
*/
void manager_interrupcao_fim_de_curso(void)
{
     Serial.println("HELLO");
}

int pisca_delay(void)
{
        digitalWrite(led, HIGH);
        delay(1000);
        digitalWrite(led, LOW);
        delay(1000);
        return 0;
}
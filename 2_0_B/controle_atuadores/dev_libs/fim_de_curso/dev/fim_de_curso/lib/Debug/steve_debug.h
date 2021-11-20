#ifndef STEVE_DEBUG_H
#define STEVE_DEBUG_H


extern const int SUCESSO;//!< Sinalizador de sucesso
extern const int SINALIZADOR_ERRO;  //!< Sinalizador de Erro
const int led = 2; //!< LED_BUILTIN

#define  debug(x) Serial.println(x)
int pisca_delay(void);
void manager_interrupcao_fim_de_curso(void);
#endif
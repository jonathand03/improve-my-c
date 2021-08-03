#ifndef STEVE_DEBUG_H
#define STEVE_DEBUG_H


extern const int SUCESSO;
extern const int SINALIZADOR_ERRO;
const int led = 2;

//!< Tornando o Serial print como DEBUG()
#define  debug(x) Serial.println(x)
int pisca_delay(void);
#endif
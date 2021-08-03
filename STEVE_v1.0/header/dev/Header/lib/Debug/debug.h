#ifndef DEBUG_H
#define DEBUG_H

// Sinalizador de sucesso
extern const int SUCESSO;
// Sinalizador de Erro
extern const int SINALIZADOR_ERRO;
const int led = 2;
#define  debug(x) Serial.println(x)
int pisca_delay(void);
#endif
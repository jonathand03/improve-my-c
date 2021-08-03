#ifndef STEVE_DEBUG_H
#define STEVE_DEBUG_H

/*!
        MAPEAMENTO DE PORTAS - DEBUG
*/
const int debug_txd = 17; // [DEBUG]  Porta para debug
const int debug_rxd = 16; // [DEBUG]  Porta para debug

// Sinalizador de sucesso
extern const int SUCESSO;
// Sinalizador de Erro
extern const int SINALIZADOR_ERRO;
const int led = 2;
#define  debug(x) Serial.println(x)
int pisca_delay(void);
#endif
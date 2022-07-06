/*! @file Lib do sistema do suporte circulatório
*
*/


#ifndef SUP_CIRC_H
#define SUP_CIRC_h

#include <Arduino.h>


void padrao_suporte_circulatorio(void);
void aciona_suporte_circ(int angulo, int qtd_ciclos);
void suporte_circulatorio(void *parameters);
void ConfigSupCirc(int angulo, int ciclos, int tempo_prox_ativacao);
void suporte_circulatorio_avancar(void);
void suporte_circulatorio_recuar(void);
void reconfigura_suporte_circulatorio(void);
void imprime_msg(void);



void inicializa_tarefa_alarme(void);
void alarme_suporte_circulatorio(void *args);
void suporte_circulatorio(void);
void suporte_circulatorio_descida(void);
#endif
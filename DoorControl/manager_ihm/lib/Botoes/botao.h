/*! @file botao.h
*   @brief Lib com as funções dos botões do ESP-IHM
*   ****
*/

#ifndef BOTAO_H
#define BOTAO_H
#include <stdint.h>

/* 
*   BOTOES NO IHM
*/
#define COD_BT_CIMA (36)  // KEY 1
#define COD_BT_BAIXO (39) // KEY 2
#define COD_BT_ENTER (34) // KEY 3
#define COD_BT_STADUP (35) // KEY 4
#define COD_BT_PANICO (32) // KEY 5


/*
*   Micro Ajustes
*/
#define COD_AJUSTE_AVANCO (35) // KEY 9
#define COD_AJUSTE_RECUO (36) // KEY 10

enum estado_botao
{
    desligado,
    ligado,
    continua_desligado,
    continua_ligado
};


enum e_botao
{
    e_botao_baixo, 
    e_botao_cima,
    e_botao_enter,
    e_botao_standup,
    e_botao_panico,
    e_qtd_botoes
};

extern int estado_botoes_ihm[e_qtd_botoes];
extern int estado_bt_anterior[5];


void inicializa_botoes_ihm(void);
void inicializa_estado_botoes_ihm(void);
int retorna_pino_botao(e_botao botao);

void registra_interrupcao(void);
void interrupcao_bt_baixo();
void interrupcao_bt_cima();
void interrupcao_bt_enter();
void interrupcao_bt_standup();

void ativa_interrupcao_pino(e_botao botao_intr);
void desativa_interrupcao_pino(e_botao botao_intr);

#endif
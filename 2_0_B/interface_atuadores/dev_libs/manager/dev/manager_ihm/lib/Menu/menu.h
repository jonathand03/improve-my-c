#ifndef MENU_H
#define MENU_H
#include "botao.h"

void assento_ajuste_vertical(void);
void assento_ajuste_horizontal(void);

void encosto_ajuste_inclinacao(void);

void leitura_tecla_cima(void);
void leitura_tecla_baixo(void);
void navegacao_menu(void);
void voltar_pagina(void);
void avancar_pagina(int opcao_atual);

void leitura_tecla_enter(void);
void funcao_angulo(void);
void funcao_qtd_ciclos(void);
void funcao_tempo(void);

void altera_angulo(void);
void altera_qtd_ciclos(void);
void altera_tempo(void);


extern int opcao_atual   ;   // opção em qual o highligh está naquele momento
extern int opcao_anterior ; // opção anterior ao botão apertado
extern int pagina_atual ;    // pagina atual do menu
extern int limite_inf ;      // limite da lista da pagina atual
extern int indice_anterior_enter ;

estado_botao verifica_botao_acionado(e_botao botao_acionado);


#endif
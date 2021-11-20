#ifndef DISPLAY_TFT_H
#define DISPLAY_TFT_H

void inicializa_display(void);
void mensagem_display(const char *msg);
void mensagem_sequencia(const char *msg);
void mensagem_variavel_display(int variavel);
void mensagem_display_com_valor(const char *msg, int valor);
void mostra_configuracoes(const char *msg, int valor);

void menu_inicial(void);
void menu_destaque(void);
void opcao_destacada(int opcao,  int disposicao);
void menu_sc(void);
#endif
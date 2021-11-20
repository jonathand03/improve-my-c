#include "menu.h"
#include "display_tft.h"
#include <Arduino.h>
#include "com_ihm.h"
/*
    Variaveis de navegação
*/

int opcao_atual = 0;     // opção em qual o highligh está naquele momento
int opcao_anterior = -1; // opção anterior ao botão apertado
int pagina_atual = 0;    // pagina atual do menu
int limite_inf = 3;      // limite da lista da pagina atual
int indice_anterior_enter = 0;

enum teclas_menu
{
    bt_baixo,
    bt_cima,
    bt_enter,
    bt_standup,
    bt_panico
};

/******************** VERIFICACAO DE INTERRUPCAO DAS TECLAS DO MENU ******************/

bool estado_botao_cima = false;
bool estado_botao_baixo = false;
bool estado_botao_enter = false;
bool estado_anterior_b = false;

estado_botao verifica_botao_acionado(e_botao botao_acionado)
{
    estado_botao status_atual_verificao = desligado;

    if(estado_botoes_ihm[botao_acionado] == ligado)
    {
        if(estado_bt_anterior[botao_acionado] == desligado )
            status_atual_verificao =  ligado; // retorna ligado
        else
            status_atual_verificao =  continua_ligado; // retorna mantendo ligado
    }
    else
    {
        if(estado_bt_anterior[botao_acionado] == desligado )
            status_atual_verificao = continua_desligado; // retorna mantendo desligado
        else
            status_atual_verificao =  desligado; // retorna desligando
    }
    estado_bt_anterior[botao_acionado] = estado_botoes_ihm[botao_acionado];
    estado_botoes_ihm[botao_acionado] = desligado;
    return status_atual_verificao;
}


/**************************************** TECLAS DE NAVEGACAO ***********************************/
void leitura_tecla_cima(void)
{
    int verifica_botao = verifica_botao_acionado(e_botao_cima);
    if (verifica_botao == ligado) // verifica se é o botao pra cima
    {
        if (opcao_atual == 0)         // se o menu atual for igual o limite maximo superior
            opcao_atual = limite_inf; // menu atual volta para a ultima opçao (lista circular)
        else                          // se nao for menor, menu atual sobe para o item acima
            opcao_atual--;
    }
}

void leitura_tecla_baixo(void)
{
    int verifica_bt_acionado = verifica_botao_acionado(e_botao_baixo);
    if (verifica_bt_acionado == ligado) // verifica se é o botao pra baixo
    {
        if (opcao_atual == limite_inf) // verifica se o menu atual está na ultima posicao
            opcao_atual = 0;           // se sim, o menu atual volta pra primeira opçao (lista circular)
        else
            opcao_atual++; // se não, faz o menu atual descer para posição abaixo
    }
}


void leitura_tecla_enter(void)
{
    int verifica_botao = verifica_botao_acionado(e_botao_enter);
    if(verifica_botao == ligado)
    {
        if(opcao_atual == limite_inf && pagina_atual > 0)
        {
            voltar_pagina();
        }
        else if(pagina_atual == 0)
        {
            avancar_pagina(opcao_atual);
        }
        else
        {
            navegacao_menu();
        }
    }
}




void navegacao_menu(void)
{
        if(pagina_atual == 1)
        {
            switch (opcao_atual)
            {
                case 0:
                    // chama funcao status
                    break;
                case 1: 
                    funcao_angulo();
                    break;
                case 2:
                    funcao_qtd_ciclos();
                    break;
                case 3:
                    funcao_tempo();
                    break;
            }
        }
        else if(pagina_atual == 2)
        {
            switch (opcao_atual)
            {
                case 0:
                    assento_ajuste_vertical();
                    break;
                case 1: 
                    assento_ajuste_horizontal();
                    break;
            }
        }
        else if(pagina_atual == 3)
        {
            switch (opcao_atual)
            {
                case 0:
                    encosto_ajuste_inclinacao();
                    break;
                case 1: 
                    //funcao_angulo();
                    break;
            }
        }      
}


/******************************** ALTERNAR PAGINAS *************************************/

void voltar_pagina(void)
{
    limite_inf = 3;
    pagina_atual = 0;
    opcao_atual = indice_anterior_enter;
    opcao_anterior = -1;
    menu_inicial();
}

void avancar_pagina(int m_atual)
{
    if(opcao_atual == 0)
        limite_inf = 4;
    else if(opcao_atual == 1)
        limite_inf = 2;
    else if(opcao_atual == 2)
        limite_inf = 2;
    else if(opcao_atual == 3)
        limite_inf = 2;
    pagina_atual = m_atual+1;//!< fator de correção de pagina
    indice_anterior_enter = m_atual; //!< caso volte pagina, o highligh volta para antes de entrar no menu
    opcao_atual = 0;
    opcao_destacada(0,10);
}


/***************************** CONFIG SC **************************************/
int angulo_atual = 0;
const int angulo_max = 15;

void funcao_angulo(void)
{
    int angulo_anterior = -1;
    while (verifica_botao_acionado(e_botao_enter) != ligado)
    {
        if (angulo_anterior != angulo_atual)
        {
            mensagem_display_com_valor(" Angulo ",angulo_atual);
            angulo_anterior = angulo_atual;
        }
        altera_angulo();
    }
    opcao_destacada(1, 60);
}

void altera_angulo(void)
{
    int verifica_bt_cima = verifica_botao_acionado(e_botao_cima);
    int verifica_bt_baixo = verifica_botao_acionado(e_botao_baixo);
    if (verifica_bt_cima == ligado) // se botao cima
    {
        if (angulo_atual == angulo_max)
            angulo_atual = 0;
        else
            angulo_atual++;
    }
    else if (verifica_bt_baixo == ligado) // se botao baixo
    {
        if (angulo_atual == 0)
            angulo_atual = angulo_max;
        else
            angulo_atual--;
    }
}
/************************************ CICLOS ******************************/
int qtd_cliclos_atual = 0;
const int qtd_clicos_max = 10;

void funcao_qtd_ciclos(void)
{
    int qtd_cliclos_atual_anterior = -1;
    while (verifica_botao_acionado(e_botao_enter) != ligado)
    {
        if (qtd_cliclos_atual_anterior != qtd_cliclos_atual)
        {
            mensagem_display_com_valor(" Ciclos ",qtd_cliclos_atual);
            qtd_cliclos_atual_anterior = qtd_cliclos_atual;
        }
        altera_qtd_ciclos();
    }                        
    opcao_destacada(2, 110);
}

void altera_qtd_ciclos(void)
{
    int verifica_bt_cima = verifica_botao_acionado(e_botao_cima);
    int verifica_bt_baixo = verifica_botao_acionado(e_botao_baixo);
    if (verifica_bt_cima == ligado) // se botao cima
    {
        if (qtd_cliclos_atual == qtd_clicos_max)
            qtd_cliclos_atual = 0;
        else
            qtd_cliclos_atual++;
    }
    else if (verifica_bt_baixo == ligado) // se botao baixo
    {
        if (qtd_cliclos_atual == 0)
            qtd_cliclos_atual = qtd_clicos_max;
        else
            qtd_cliclos_atual--;
    }
}
/************** TEMPO **********************/
int temp_atual = 0;
const int tempo_max = 3;

void funcao_tempo(void)
{
    int qtd_tempo_anterior = -1;
    while (verifica_botao_acionado(e_botao_enter) != ligado)
    {
        if (qtd_tempo_anterior != temp_atual)
        {
            mensagem_display_com_valor(" Tempo ",temp_atual);
            qtd_tempo_anterior = temp_atual;
        }
        altera_tempo();
    }
    opcao_destacada(3, 160);
}

void altera_tempo(void)
{
    int verifica_bt_cima = verifica_botao_acionado(e_botao_cima);
    int verifica_bt_baixo = verifica_botao_acionado(e_botao_baixo);
    if (verifica_bt_cima == ligado) // se botao cima
    {
        if (temp_atual == tempo_max)
            temp_atual = 0;
        else
            temp_atual++;
    }
    else if (verifica_bt_baixo == ligado) // se botao baixo
    {
        if (temp_atual == 0)
            temp_atual = tempo_max;
        else
            temp_atual--;
    }
}

/************************************* CONFIG  ASSENTO *******************************************/
void assento_ajuste_vertical(void)
{
    mensagem_display("Cima/Baixo -> [Ajustes]");
    mensagem_sequencia("Enter -> [SAIR]");
    while(verifica_botao_acionado(e_botao_enter) != ligado)
    {
        if(verifica_botao_acionado(e_botao_baixo) == ligado)
        {
            desativa_interrupcao_pino(e_botao_baixo);
            //ihm_requisicao_atuador(retorna_pino_botao(e_botao_baixo),COD_ATUADOR_AVANCO);
            //estado_bt_anterior[e_botao_baixo] = desligado;
            mensagem_display("Recuo Vertical: ");
            mensagem_sequencia("[ATIVADO]");
            while(digitalRead(39) !=  LOW)
            {
                
            }
            //ihm_requisicao_atuador(retorna_pino_botao(e_botao_baixo),COD_ATUADOR_DESLIGADO);
            ativa_interrupcao_pino(e_botao_baixo);
            //estado_bt_anterior[e_botao_baixo] = desligado;
            mensagem_display("Recuo Vertical: ");
            mensagem_sequencia("[DESATIVADO]");
        }
        if(verifica_botao_acionado(e_botao_cima) == ligado)
        {
            desativa_interrupcao_pino(e_botao_cima);
            //ihm_requisicao_atuador(retorna_pino_botao(e_botao_cima),COD_ATUADOR_AVANCO);
            //estado_bt_anterior[e_botao_cima] = desligado;
            mensagem_display("Avanco Vertical: ");
            mensagem_sequencia("[ATIVADO]");
            while(digitalRead(36) !=  LOW )
            {

            }
            //ihm_requisicao_atuador(retorna_pino_botao(e_botao_cima),COD_ATUADOR_DESLIGADO);
            ativa_interrupcao_pino(e_botao_cima);
            //estado_bt_anterior[e_botao_cima] = desligado;
            mensagem_display("Avanco Vertical: ");
            mensagem_sequencia("[DESATIVADO]");
        }
    }
    opcao_destacada(0,10);
}

void assento_ajuste_horizontal(void)
{   
    mensagem_display("Cima/Baixo -> [Ajustes]");
    mensagem_sequencia("Enter -> [SAIR]");
    while(verifica_botao_acionado(e_botao_enter) != ligado)
    {
        if(verifica_botao_acionado(e_botao_baixo) == ligado)
        {
            desativa_interrupcao_pino(e_botao_baixo);
            ihm_requisicao_atuador(32,COD_ATUADOR_AVANCO); 
            //estado_bt_anterior[e_botao_baixo] = desligado;
            mensagem_display("Recuo Horizontal: ");
            mensagem_sequencia("[ATIVADO]");
            while(digitalRead(39) != LOW)
            {

            }
            ativa_interrupcao_pino(e_botao_baixo);
            ihm_requisicao_atuador(32,COD_ATUADOR_DESLIGADO);
           //estado_bt_anterior[e_botao_baixo] = desligado;
            mensagem_display("Recuo Horizontal: ");
            mensagem_sequencia("[DESATIVADO]");
        }
        if(verifica_botao_acionado(e_botao_cima) == ligado)
        {
            desativa_interrupcao_pino(e_botao_cima);
           // estado_bt_anterior[e_botao_cima] = desligado;
            mensagem_display("Avanco Horizontal: ");
            mensagem_sequencia("[ATIVADO]");
            while(digitalRead(36) !=  LOW )
            {

            }
            ativa_interrupcao_pino(e_botao_cima);
           // estado_bt_anterior[e_botao_cima] = desligado;
            mensagem_display("Avanco Horizontal: ");
            mensagem_sequencia("[DESATIVADO]");
        }
    }
    opcao_destacada(1,60);
}

void encosto_ajuste_inclinacao(void)
{
    mensagem_display("Cima/Baixo -> [Ajustes]");
    mensagem_sequencia("Enter -> [SAIR]");
    while(verifica_botao_acionado(e_botao_enter) != ligado)
    {
        if(verifica_botao_acionado(e_botao_baixo) == ligado)
        {
            desativa_interrupcao_pino(e_botao_baixo);
            //estado_bt_anterior[e_botao_baixo] = desligado;
            mensagem_display("Recuo Inclinacao: ");
            mensagem_sequencia("[ATIVADO]");
            while(digitalRead(39) != LOW)
            {

            }
            ativa_interrupcao_pino(e_botao_baixo);
            //estado_bt_anterior[e_botao_baixo] = desligado;
            mensagem_display("Recuo Inclinacao: ");
            mensagem_sequencia("[DESATIVADO]");
        }
        if(verifica_botao_acionado(e_botao_cima) == ligado)
        {
            desativa_interrupcao_pino(e_botao_cima);
            //estado_bt_anterior[e_botao_cima] = desligado;
            mensagem_display("Avanco Inclinacao: ");
            mensagem_sequencia("[ATIVADO]");
            while(digitalRead(36) !=  LOW )
            {

            }
            // função desligado aqui
            ativa_interrupcao_pino(e_botao_cima);
           // estado_bt_anterior[e_botao_cima] = desligado;
            mensagem_display("Avanco Inclinacao: ");
            mensagem_sequencia("[DESATIVADO]");
        }
    }
    opcao_destacada(0,10);
}
#include "display_tft.h"
#include <SPI.h>
#include <TFT_eSPI.h>
#include <driver/adc.h>
#include "menu.h"

//[ CONFIGURAÇAO DO SUPORTE CIRCULATORIO] Angulo, numero de ciclos, tempo para proxima execução , 
//[ STATUS ] MODO DE OPERAÇÃO, CONFIGURAÇOES DO SUP CIRC

TFT_eSPI Display = TFT_eSPI(); // Construtor para setar a altura e largura, por padrão é 320x480p


/*! @brief Inicializa o display da interface ihm
*
*/
void inicializa_display(void)
{
    // Configurações da tela

    Display.init();               // inicializa o display paralelo
    Display.setRotation(2);       // seta a rotação para o modo horizontal
    Display.fillScreen(TFT_BLUE); // Seta o fundo padrão do mostrador da tela

    // Configuração da mensagem inicial
    Display.setTextSize(3);
    Display.setTextDatum(MC_DATUM);
    Display.setCursor(65, 125, 2);
    Display.setTextColor(TFT_WHITE);
    Display.println("Steve inicializado");

    //Pressionar alguma tecla para começar o programa
    Display.setTextSize(2);
    Display.setCursor(65, 190, 2);
    Display.setTextColor(TFT_WHITE);
    Display.println("Pressione uma tecla...");
}

void mensagem_display(const char *msg)
{
    Display.fillScreen(TFT_BLUE); // Seta o fundo padrão do mostrador da tela
    // Configuração da mensagem inicial
    Display.setTextSize(2);
    Display.setTextDatum(MC_DATUM);
    Display.setCursor(0, 125, 2);
    Display.setTextColor(TFT_WHITE);
    Display.println(msg);
}

void mensagem_sequencia(const char *msg)
{
    Display.setTextSize(2);
    Display.setTextDatum(MC_DATUM);
    Display.setTextColor(TFT_WHITE);
    Display.println(msg);
}
void mensagem_display_com_valor(const char *msg, int valor)
{
    Display.fillScreen(TFT_BLUE);
    // Configuração da mensagem inicial
    Display.setTextSize(3);
    Display.setTextDatum(MC_DATUM);
    Display.setCursor(65, 125, 2);
    Display.setTextColor(TFT_WHITE);
    Display.print(msg);Display.println(valor);
}


void mostra_configuracoes(const char *msg, int valor)
{
    // Configuração da mensagem inicial
    Display.setTextSize(3);
    Display.setTextDatum(MC_DATUM);
    //Display.setCursor(65, 125, 2);
    Display.setTextColor(TFT_WHITE);
    Display.print(msg);Display.println(valor);
}


void mensagem_variavel_display(int variavel)
{
    Display.fillScreen(TFT_BLUE); // Seta o fundo padrão do mostrador da tela
    // Configuração da mensagem inicial
    Display.setTextSize(3);
    Display.setTextDatum(MC_DATUM);
    Display.setCursor(65, 125, 2);
    Display.setTextColor(TFT_WHITE);
    Display.println(variavel);
}


void menu_inicial(void)
{
    Display.fillScreen(TFT_BLUE); // Seta o fundo padrão do mostrador da tela
    // Configuração da mensagem inicial
    Display.setTextSize(2);
    Display.setTextDatum(MC_DATUM);
    Display.setTextColor(TFT_WHITE);
    Display.setCursor(10, 10, 2);
    Display.println("Suporte Circulatorio");
    Display.setCursor(10, 60, 2);
    Display.println("Assento");
    Display.setCursor(10, 110, 2);
    Display.println("Encosto");
    Display.setCursor(10, 160, 2);
    Display.println("Status");
}

void menu_sc(void)
{
    // TODO: Criar um texto centralizado de menu atual
    Display.fillScreen(TFT_BLUE); // Seta o fundo padrão do mostrador da tela
    // Configuração da mensagem inicial
    Display.setTextSize(2);
    Display.setTextDatum(MC_DATUM);
    Display.setTextColor(TFT_WHITE);
    Display.setCursor(10, 10, 2);
    Display.println("Status");
    Display.setCursor(10, 60, 2);
    Display.println("Angulo");
    Display.setCursor(10, 110, 2);
    Display.println("Qtd Ciclos");
    Display.setCursor(10, 160, 2);
    Display.println("Tempo");
    Display.setCursor(10, 210, 2);
    Display.println("Voltar");
}

void menu_assento(void)
{
     // TODO: Criar um texto centralizado de menu atual
    Display.fillScreen(TFT_BLUE); // Seta o fundo padrão do mostrador da tela
    // Configuração da mensagem inicial
    Display.setTextSize(2);
    Display.setTextDatum(MC_DATUM);
    Display.setTextColor(TFT_WHITE);
    Display.setCursor(10, 10, 2);
    Display.println("Ajuste Vertical");
    Display.setCursor(10, 60, 2);
    Display.println("Ajuste Horizontal");
    Display.setCursor(10, 110, 2);
    Display.println("Voltar");
}

void menu_encosto(void)
{
    Display.fillScreen(TFT_BLUE); // Seta o fundo padrão do mostrador da tela
    // Configuração da mensagem inicial
    Display.setTextSize(2);
    Display.setTextDatum(MC_DATUM);
    Display.setTextColor(TFT_WHITE);
    Display.setCursor(10, 10, 2);
    Display.println("Ajuste Inclinacao");
    Display.setCursor(10, 60, 2);
    Display.println("Ajuste Vertical");
    Display.setCursor(10, 110, 2);
    Display.println("Voltar");
}

void menu_standup(void)
{
    Display.fillScreen(TFT_BLUE); // Seta o fundo padrão do mostrador da tela
    Display.setTextSize(2);
    Display.setTextDatum(MC_DATUM);
    Display.setTextColor(TFT_WHITE);
    Display.setCursor(10, 10, 2);
    Display.println(" ---- STANDUP ----");
    Display.setCursor(10, 60, 2);
    Display.println("Acionar Standup?");
    Display.setCursor(10, 110, 2);
    Display.println("Sim");
    Display.setCursor(10, 160, 2);
    Display.println("Não");

}

const char *menu_pagina_inicial[4] = {"Suporte Circulatorio", "Assento", "Encosto", "Status"};
const char *menu_pagina_sc[5] = {"Status", "Angulo", "Qtd de ciclos", "Tempo", "Voltar"};
const char *menu_pagina_assento[3] = {"Ajuste Vertical", "Ajuste Horizontal", "Voltar"};
const char *menu_pagina_encosto[3] = {"Inclinacao", "Ajuste Vertical", "Voltar"};



void menu_destaque(void)
{
    if(opcao_atual != opcao_anterior)
    {
        if(pagina_atual == 0) // pagina 0
        {
            switch (opcao_atual)
           {
                case 0:
                    menu_inicial();
                    Display.setCursor(10, 10, 2);
                    Display.setTextColor(TFT_BLACK, TFT_WHITE);
                    Display.println(menu_pagina_inicial[0]);
                    break;
                case 1:
                    menu_inicial();
                    Display.setCursor(10, 60, 2);
                    Display.setTextColor(TFT_BLACK, TFT_WHITE);
                    Display.println(menu_pagina_inicial[1]);
                    break;
                case 2:
                    menu_inicial();
                    Display.setCursor(10, 110, 2);
                    Display.setTextColor(TFT_BLACK, TFT_WHITE);
                    Display.println(menu_pagina_inicial[2]);
                    break;
                case 3:
                    menu_inicial();
                    Display.setCursor(10, 160, 2);
                    Display.setTextColor(TFT_BLACK, TFT_WHITE);
                    Display.println(menu_pagina_inicial[3]);
                    break;
           }
        }
        else if(pagina_atual == 1) // pagina 1
        {
            switch (opcao_atual)
            {
                case 0:
                    menu_sc();
                    Display.setCursor(10, 10, 2);
                    Display.setTextColor(TFT_BLACK, TFT_WHITE);
                    Display.println(menu_pagina_sc[0]);
                    break;
                case 1:
                    menu_sc();
                    Display.setCursor(10, 60, 2);
                    Display.setTextColor(TFT_BLACK, TFT_WHITE);
                    Display.println(menu_pagina_sc[1]);
                    break;
                case 2:
                    menu_sc();
                    Display.setCursor(10, 110, 2);
                    Display.setTextColor(TFT_BLACK, TFT_WHITE);
                    Display.println(menu_pagina_sc[2]);
                    break;
                case 3:
                    menu_sc();
                    Display.setCursor(10, 160, 2);
                    Display.setTextColor(TFT_BLACK, TFT_WHITE);
                    Display.println(menu_pagina_sc[3]);
                    break;
                case 4:
                    menu_sc();
                    Display.setCursor(10, 210, 2);
                    Display.setTextColor(TFT_BLACK, TFT_WHITE);
                    Display.println(menu_pagina_sc[4]);
                    break;
            }
        }
        else if(pagina_atual == 2)
        {
            switch (opcao_atual)
            {
                case 0:
                    menu_assento();
                    Display.setCursor(10, 10, 2);
                    Display.setTextColor(TFT_BLACK, TFT_WHITE);
                    Display.println(menu_pagina_assento[0]);
                    break;
                case 1:
                    menu_assento();
                    Display.setCursor(10, 60, 2);
                    Display.setTextColor(TFT_BLACK, TFT_WHITE);
                    Display.println(menu_pagina_assento[1]);
                    break;
                case 2:
                    menu_assento();
                    Display.setCursor(10, 110, 2);
                    Display.setTextColor(TFT_BLACK, TFT_WHITE);
                    Display.println(menu_pagina_assento[2]);
                    break;
            }
        }
        else if(pagina_atual == 3)
        {
           switch (opcao_atual)
           {
               case 0:
                    menu_encosto();
                    Display.setCursor(10, 10, 2);
                    Display.setTextColor(TFT_BLACK, TFT_WHITE);
                    Display.println(menu_pagina_encosto[0]);
               case 1:
                    menu_encosto();
                    Display.setCursor(10, 60, 2);
                    Display.setTextColor(TFT_BLACK, TFT_WHITE);
                    Display.println(menu_pagina_encosto[1]);
                    break;
                case 2:
                    menu_encosto();
                    Display.setCursor(10, 110, 2);
                    Display.setTextColor(TFT_BLACK, TFT_WHITE);
                    Display.println(menu_pagina_encosto[2]);
                    break;
           } 
        }
    }
    opcao_anterior = opcao_atual;  
}

void opcao_destacada(int opcao, int disposicao)
{
    switch (pagina_atual)
    {
        case 1:
            menu_sc();
            Display.setCursor(10, disposicao, 2);
            Display.setTextColor(TFT_BLACK, TFT_WHITE);
            Display.println(menu_pagina_sc[opcao]);
            break;
        case 2:
            menu_assento();
            Display.setCursor(10, disposicao, 2);
            Display.setTextColor(TFT_BLACK, TFT_WHITE);
            Display.println(menu_pagina_assento[opcao]);
        case 3:
            menu_encosto();
            Display.setCursor(10, disposicao, 2);
            Display.setTextColor(TFT_BLACK, TFT_WHITE);
            Display.println(menu_pagina_encosto[opcao]);
    }
}

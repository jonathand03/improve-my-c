#include "display_logica.h"
#include "display.h"
#include "botao.h"

/* Variaveis manipulaveis pelas ações do teclado */
int angulo_atual = 5;
int angulo_max = 15;
int ciclo_atual = 5;
int ciclo_max = 10;
int tempo_atual = 0;
int tempo_max = 5;

/* Funções de leitura de teclado e interação com o usuário */
void NavegacaoLogica(void)
{
    if(pagina_atual == 11) // se SC
    {
        AnguloConfig();
    }
    if(pagina_atual == 12)
    {

    }
}



/*! @brief PARTE LÓGICA DE CONFIGURAÇÃO DO ÂNGULO DA BASE DO SUPORTE CIRCULATÓRIO 
*/
void AnguloConfig(void)
{
    int verifica_bt_cima ;
    int verifica_bt_baixo ;
    while(verifica_botao_pressionado(bt_enter) != ligado)
    {
        verifica_bt_cima =  verifica_botao_pressionado(bt_cima);
        verifica_bt_baixo = verifica_botao_pressionado(bt_baixo);
        if (verifica_bt_cima == ligado) // se botao cima
        {
            if (angulo_atual == angulo_max)
                angulo_atual = 5;
            else
                angulo_atual++;
        }
        else if (verifica_bt_baixo == ligado) // se botao baixo
        {
            if (angulo_atual == 5)
                angulo_atual = angulo_max;
            else
                angulo_atual--;
        }
    }
    // envia_dados_sc(COD_ALTERACAO_SC);
    // envia_dados_sc(angulo_atual);
    // envia_dados_sc(ciclo_atual);
    // envia_dados_sc(tempo_envio[tempo_atual]);

  
}

/*! @brief PARTE LÓGICA DE CONFIGURAÇÃO DO CICLO DA BASE DO SUPORTE CIRCULATÓRIO 
*/
void CicloConfig(void)
{
    int verifica_bt_cima ;
    int verifica_bt_baixo ;
    while(verifica_botao_pressionado(bt_enter) != ligado)
    {
        verifica_bt_cima =  verifica_botao_pressionado(bt_cima);
        verifica_bt_baixo = verifica_botao_pressionado(bt_baixo);
        if (verifica_bt_cima == ligado) // se botao cima
        {
            if (ciclo_atual == ciclo_max)
                ciclo_atual = 5;
            else
                ciclo_atual++;
        }
        else if (verifica_bt_baixo == ligado) // se botao baixo
        {
            if (ciclo_atual == 5)
                ciclo_atual = ciclo_max;
            else
                ciclo_atual--;
        }
    }
    // envia_dados_sc(COD_ALTERACAO_SC);
    // envia_dados_sc(angulo_atual);
    // envia_dados_sc(ciclo_atual);
    // envia_dados_sc(tempo_envio[tempo_atual]);
}
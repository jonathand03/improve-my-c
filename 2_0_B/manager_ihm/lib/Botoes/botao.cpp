#include "botao.h"
#include <driver/adc.h>
#include "steve_debug.h"
#include <Arduino.h>

/*! @brief Maquina de estados dos botoes do IHM
*/
int estado_botoes_ihm[e_qtd_botoes];

/*!
*   Constantes do Código dos botões
*/
const uint8_t codigo_bt_baixo = COD_BT_BAIXO;
const uint8_t codigo_bt_cima = COD_BT_CIMA;
const uint8_t codigo_bt_enter = COD_BT_ENTER;
const uint8_t codigo_bt_standup = COD_BT_STADUP;
const uint8_t codigo_bt_panico = COD_BT_PANICO;

int estado_bt_anterior[5] = {desligado, desligado, desligado, desligado, desligado};

const int pinos_botoes_ihm[e_qtd_botoes] =
{
        codigo_bt_baixo,
        codigo_bt_cima,
        codigo_bt_enter,
        codigo_bt_standup,
        codigo_bt_panico
}; //!< Pinos dos botões

/*! @brief Função que inicializa os botões
*   @note  Essa função talvez não seja necessária caso os botões usarem interrupção via hardware para ativação
*/
void inicializa_botoes_ihm(void)
{
    for (int i = 0; i < e_qtd_botoes; i++)
    {
        pinMode(pinos_botoes_ihm[i], INPUT);
    }
}

/*! @brief Inicializa o vetor de estado dos botões
*
*/
void inicializa_estado_botoes_ihm(void)
{
    for (int i = 0; i < e_qtd_botoes; i++)
    {
        estado_botoes_ihm[i] = desligado;
    }
}

/*! @brief Retorna o pino do botao referente à enumeração repassada como parametro
*   @param[in] botao É o enumerador do botão do IHM
*/
int retorna_pino_botao(e_botao botao)
{
    return pinos_botoes_ihm[botao];
}


void IRAM_ATTR interrupcao_bt_baixo()
{
    estado_botoes_ihm[e_botao_baixo] = ligado;
}

void IRAM_ATTR interrupcao_bt_cima()
{
    estado_botoes_ihm[e_botao_cima] = ligado;
}

void IRAM_ATTR interrupcao_bt_enter()
{
    estado_botoes_ihm[e_botao_enter] = ligado;
}

void IRAM_ATTR interrupcao_bt_standup()
{
    estado_botoes_ihm[e_botao_standup] = ligado;
}

void IRAM_ATTR interrupcao_bt_panico()
{
    estado_botoes_ihm[e_botao_panico] = ligado;
}

void registra_interrupcao(void)
{
    attachInterrupt(codigo_bt_cima, interrupcao_bt_cima, HIGH);
    attachInterrupt(codigo_bt_baixo, interrupcao_bt_baixo, HIGH);
    attachInterrupt(codigo_bt_enter, interrupcao_bt_enter, HIGH);
    attachInterrupt(codigo_bt_standup, interrupcao_bt_standup, HIGH);
    attachInterrupt(codigo_bt_panico, interrupcao_bt_panico, HIGH);
}

void ativa_interrupcao_pino(e_botao botao_intr)
{
    switch (botao_intr)
    {
        case e_botao_baixo:
            attachInterrupt(retorna_pino_botao(e_botao_baixo), interrupcao_bt_baixo, HIGH);
            break;
        case e_botao_cima:
            attachInterrupt(retorna_pino_botao(e_botao_cima), interrupcao_bt_cima, HIGH);
            break;
        case e_botao_enter:
            attachInterrupt(retorna_pino_botao(e_botao_enter), interrupcao_bt_enter, HIGH);
            break;
        case e_botao_standup:
            attachInterrupt(retorna_pino_botao(e_botao_standup), interrupcao_bt_standup, HIGH);
            break;
        case e_botao_panico:
            attachInterrupt(retorna_pino_botao(e_botao_panico), interrupcao_bt_panico, HIGH);
            break;
    }
}

void desativa_interrupcao_pino(e_botao botao_intr)
{
    switch (botao_intr)
    {
        case e_botao_baixo:
            detachInterrupt(retorna_pino_botao(e_botao_baixo));
            break;
        case e_botao_cima:
            detachInterrupt(retorna_pino_botao(e_botao_cima));
            break;
        case e_botao_enter:
            detachInterrupt(retorna_pino_botao(e_botao_enter));
            break;
        case e_botao_standup:
            detachInterrupt(retorna_pino_botao(e_botao_standup));
            break;
        case e_botao_panico:
            detachInterrupt(retorna_pino_botao(e_botao_panico));
            break;
    }
}
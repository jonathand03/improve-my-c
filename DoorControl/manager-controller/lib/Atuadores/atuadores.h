/*!
    @brief LIB dos pinos dos atuadores e suas funções
*/

#ifndef ATUADORES_H
#define ATUADORES_H

#include <Arduino.h>
#include "steve_debug.h"
#define DEBUG_ATUADOR

#define ATUADORES_PINOUT
#ifdef ATUADORES_PINOUT

#define AT_AV_STANDUP (32)                        //!< [ATUADOR] Standup: pino de [avanço]
#define AT_AV_ELEVADOR_BASE (33)                  //!< [ATUADOR] Elevador da base: pino de [avanço]
#define AT_AV_ELEVADOR_SUPORTE_CIRC_ESQUERDO (25) //!< [ATUADOR] Elevador do suporte circulatório: pino de [avanço]
#define AT_AV_ELEVADOR_SUPORTE_CIRC_DIREITO (26)  //!< [ATUADOR] Elevador do suporte circulatório: pino de [avanço]
#define AT_AV_SUPORTE_CIRCU (16)                  //!< [ATUADOR] Suporte circulatório: pino de [avanço]
#define AT_AV_ALTURA_ENCOSTO (27)                 //!< [ATUADOR] Altura do enconsto: pino de [avanço]
#define AT_AV_INCLINACAO_ENCOSTO (14)             //!< [ATUADOR] Inclinação do encosto: pino de [avanço]
#define AT_AV_DISTANCIA_ASSENTO_ENCOSTO (13)      //!< [ATUADOR] Distancia do assento e encosto: pino de [avanço]

#define AT_RC_STANDUP (23)                        //!< [ATUADOR] Standup: pino de [recuo]
#define AT_RC_ELEVADOR_BASE (19)                  //!< [ATUADOR] Elevador da base: pino de [recuo]
#define AT_RC_ELEVADOR_SUPORTE_CIRC_ESQUERDO (18) //!< [ATUADOR] Elevador do suporte circulatório: pino de [recuo]
#define AT_RC_ELEVADOR_SUPORTE_CIRC_DIREITO (17)  //!< [ATUADOR] Elevador do suporte circulatório: pino de [recuo]
#define AT_RC_SUPORTE_CIRCU (5)                   //!< [ATUADOR] Suporte circulatório: pino de [recuo]
#define AT_RC_ALTURA_ENCOSTO (4)                  //!< [ATUADOR] Altura do enconsto: pino de [recuo]
#define AT_RC_INCLINACAO_ENCOSTO (2)              //!< [ATUADOR] Inclinação do encosto: pino de [recuo]
#define AT_RC_DISTANCIA_ASSENTO_ENCOSTO (15)      //!< [ATUADOR] Distancia do assento e encosto: pino de [recuo]

#endif

/*! @enum e_atuadores
* @brief Enumeração dos pinos de atuação.
*
* São dividos em 7 valores, onde cada valor tem avanço e recuo.
*/
enum e_atuadores
{
    e_atuador_standup,
    e_atuador_elevador_base,
    e_atuador_elevador_suporte_circ_direito,
    e_atuador_elevador_suporte_circ_esquerdo,
    //!< TODO [PADRONIZAR PARA ENUM (CIRCU - > CIRC)]
    e_atuador_suporte_circu, // provavelmente terá dois do suporte circulatório (verificar)
    e_atuador_altura_encosto,
    e_atuador_inclinacao_encosto,
    e_atuador_distancia_assento_encosto,
    //!< TODO [PADRONIZAR PARA ENUM ( QTD -> NUM)]
    e_atuador_qtd 
};

/*! @enum e_atuacao
* @brief Tipos de atuação [AVANÇO] ou [RECUO].
*
* *****
*/
enum e_atuacao
{
    avanco,
    recuo,
    e_atuacao_num
};

/*! @enum e_atuador_estado
* @brief *****.
*
* *****.
*/
enum e_atuador_estado
{
    ligado,
    desligado,
    e_atuador_estado_num
};

/*! @var const int qtd_atuadores = e_atuador_qtd, const int qtd_atuacao = e_atuacao_num
* @brief Tamanho da linha e coluna
* *****
*/
//!< TODO [PADRONIZAR QTD - > NUM]
const int qtd_atuadores = e_atuador_qtd;
const int qtd_atuacao = e_atuacao_num;

/*! @var int estados_pinos_atuador[qtd_atuadores][qtd_atuacao]
* @brief Matriz de estados dos atuadores 
*    
* ******
*/
extern int estados_pinos_atuador[qtd_atuadores][qtd_atuacao];

/*
        PROTOTIPAGEM
*/

void inicializa_atuadores(void);
void inicializacao_estados_atuadores(int estados_pinos_atuador[qtd_atuadores][qtd_atuacao]);
int escrita_atuador(e_atuadores atuador, int estado_pino);
int atuador_avancar(e_atuadores atuador);
int atuador_recuar(e_atuadores atuador);
void atuador_parar(e_atuadores atuador);
void reseta_atuadores(void);
void tratamento_atuador(void);
void acionamento_atuador(e_atuadores atuador);
void limpa_buffer(void);
#endif
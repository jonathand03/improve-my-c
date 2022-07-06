/*! @file com_ihm.h
*   @brief Lib de comunicação de dados do ESP-CONTROLE
*   @note Contem apenas funções referentes ao ESP-CONTROLE (SERVIDOR)
*   -----------------------------------
*   @fn verifica_barramento_serial(void)
*/

#ifndef COM_IHM_H
#define COM_IHM_H
#include <stdint.h>

/*! COMUNICAÇÃO DO SERVIDOR
*       O protocolo de comunicação serial do ESP-CONTROLE é composto por um vetor,
*       onde a transmissão é feita da esquerda para direita no barramento serial.
*        
*       Formato do protocolo para tratamento de dados:
*       
*       SUCESSO:
*
*       0               1                 2                 
*       0 1 2 3 4 5 6 7 8 0 1 2 3 4 5 6 7 8 
*       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
*       |  SERVIDOR_OK  | FIM_TRANSMISSAO |   
*       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
*
*       FALHA:
*       0               1                 2
*       0 1 2 3 4 5 6 7 8 0 1 2 3 4 5 6 7 8
*       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
*       |   COD_ERRO    | FIM_TRANSMISSAO |
*       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
*/

extern int vetor_atuador[5];
extern uint8_t buffer_de_dados[6];

enum estrutura_pacote_atuadores
{
    requisicao_pacote,
    pino_atuador_pacote,
    estado_pacote,
    checksum_pacote,
    fim_transmissao
};

enum estrutura_pacote_sc
{
    requisicao_pacote_sc,
    angulo,
    qtd_ciclos,
    tempo,
   // estado_sc,
    checksum_sc,
    fim_transmissao_sc
};

//ESTADOS
#define COD_ATUADOR_AVANCO (33)    //!
#define COD_ATUADOR_RECUO (34)     //"
#define COD_ATUADOR_DESLIGADO (35) //#

// REQUISICOES
#define COD_REQUISICAO_CONFIG_SC (50)
#define COD_REQUISICAO_PANICO (51)
#define COD_REQUISICAO_ATUADOR (52)
#define FIM_TRANSMISSAO (53)
#define COD_SERVIDOR_OK (54)

//CODIGO NEUTRO
#define COD_CRC_INVALIDO (60)
#define SEM_NOVO_DADO (61)
#define COD_ESTOURO_PACOTE (62)
#define COD_REQ_INVALIDO (63)

// CODIGOS DE ERRO
#define TAM_CONFIG_SC (6)
#define TAM_REQUISICAO_ATUADOR (5)

#define COD_PANICO_ATIVAR (113)
enum estrutura_pacote_servidor
{
    e_resposta_servidor,
    e_resposta_fim_transmissao,
    e_tam_resposta
};

// Define de configuração de interface
#define BAUDRATE (115200)
#define RX_PIN (3)
#define TX_PIN (1)

#define COD_ATUADOR_PARAR (75)

/*
*   Codigo dos atuadores
*/

#define COD_ATUADOR_STANDUP (32)
#define COD_ATUADOR_ELEVADOR_BASE (33)
#define COD_ATUADOR_ELEVADOR_SUPORTE_CIR (25)
#define COD_ATUADOR_SUPORTE_CIR (26)
#define COD_ATUADOR_ALTURA_ENCOSTO (27)
#define COD_ATUADOR_INCLINACAO_ENCOSTO (14)
#define COD_ATUADOR_DISTANCIA_ASSENTO_ENCOSTO (12)
#define COD_ATUADOR_INCLINACAO_ENCOSTO_RECUO (2)

/*!
*    SERVIDOR
*/

void inicializa_interface_com_ihm_servidor(void);
void servidor_pronto(void);

int8_t verifica_barramento_serial(void);
int8_t tratamento_de_dados(uint8_t *buffer_dados, uint8_t tam_buffer);
int8_t verifica_checksum(uint8_t *buffer_de_dados, uint8_t tam_buffer);
void retorna_codigo_req_invalida(void);
void retorna_codigo_estouro_pacote(void);

#endif //COMMUNICATION_IHM_H
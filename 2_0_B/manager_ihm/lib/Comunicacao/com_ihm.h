/*! @file com_ihm.h
*   Exportação de funções da comunicaçã do IHM
*   Mostragem do protocolo de comunicação
*    
*/


#ifndef COM_IHM_H
#define COM_IHM_H

#include <stdint.h>



/*
*    - COMUNICAÇÃO DO IHM -
*    O protocolo de comunicação serial do ESP-IHM é composto por um vetor ,
*    onde a transmissão é feita da esquerda para direita no barramento serial.
*
*    Formato do pacote para configuração do suporte circulatório:
*
*    0               1                 2                 3                 4                 5                 6
*    0 1 2 3 4 5 6 7 8 0 1 2 3 4 5 6 7 8 0 1 2 3 4 5 6 7 8 0 1 2 3 4 5 6 7 8 0 1 2 3 4 5 6 7 8 0 1 2 3 4 5 6 7 8
*    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
*    |   REQUISIÇÃO  |      ÂNGULO     | QTD DE CICLOS   | TEMPO PROX EXEC |    CHECKSUM     | COD FIM TRANSMI |
*    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
*
*    Formato do pacote para acionamento dos atuadores:
*
*    0               1                 2                 3                 4
*    0 1 2 3 4 5 6 7 8 0 1 2 3 4 5 6 7 8 0 1 2 3 4 5 6 7 8 0 1 2 3 4 5 6 7 8
*    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
*    |   REQUISIÇÃO  | CODIGO ATUADOR  |    CHECKSUM     | COD FIM TRANSMI |
*    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
*
*    Formato do pacote para o botão de pânico:
*
*    0               1                 2                 3                 4
*    0 1 2 3 4 5 6 7 8 0 1 2 3 4 5 6 7 8 0 1 2 3 4 5 6 7 8 0 1 2 3 4 5 6 7 8
*    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
*    |   REQUISIÇÃO    | CODIGO DO PANICO|     CHECKSUM    |COD FIM TRANSMI|
*    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
*
*    Formato do pacote para o botão de acionamento:
*
*    0               1                 2                 3  
*    0 1 2 3 4 5 6 7 8 0 1 2 3 4 5 6 7 8 0 1 2 3 4 5 6 7 8 
*    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
*    | COD ACIONAMENTO |    CHECKSUM     |COD FIM TRANSMI|
*    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
*/

/*! @note  Esses são os códigos do estado dos atuadores
*          temos 3 estados possíveis para os atuadores
*          [AVANCO] [RECUO] [DESLIGADO]
*/
#define COD_ATUADOR_AVANCO (33)                 //!
#define COD_ATUADOR_RECUO (34)                  //"
#define COD_ATUADOR_DESLIGADO (35)              //#


/*! @note  Essas são as requisições       
*          que podem ser enviadas via SERIAL
*          do ihm para o controlador
*/
#define COD_REQUISICAO_CONFIG_SC (50)   //2
#define COD_REQUISICAO_PANICO (51)      //3
#define COD_REQUISICAO_ATUADOR (52)     //4
#define COD_FIM_TRANSMISSAO (53)        //5
#define COD_SERVIDOR_OK (54)            //6

/*! @note Esses são as configurações 
*         da comunicação SERIAL
*/
#define BAUDRATE (115200) 
#define RX_PIN (3)
#define TX_PIN (1)

/*! @note Esses são os códigos de erro 
*         ou alerta do protocolo
*/
#define COD_CRC_INVALIDO (60)
#define SEM_NOVO_DADO (61)
#define COD_ESTOURO_PACOTE (62)
#define COD_REQ_INVALIDO (63)

/*! @note Esses são os códigos dos atuadores
*   @note Atribuímos os mesmos valores dos pinos
*         dos atuadores
*/
#define COD_ATUADOR_STANDUP (32)
#define COD_ATUADOR_ELEVADOR_BASE (33)
#define COD_ATUADOR_ELEVADOR_SUPORTE_CIR (25)
#define COD_ATUADOR_SUPORTE_CIR (26)
#define COD_ATUADOR_ALTURA_ENCOSTO (27)
#define COD_ATUADOR_INCLINACAO_ENCOSTO (14)
#define COD_ATUADOR_DISTANCIA_ASSENTO_ENCOSTO (12)
#define COD_ATUADOR_INCLINACAO_ENCOSTO_RECUO (2)

enum estrutura_pacote_config_sc
{
    e_requisicao,
    e_angulo,
    e_qtd_ciclos,
    e_temp_prox_atv,
    e_checksum,
    e_fim_transmissao,
    e_tam_pacote_sc
};//!< Enumerador com a estrutura do vetor do pacote da configuração do suporte circulatório

enum estrutura_pacote_atuador
{
    e_requisicao_atuador,
    e_codigo_atuador,
    e_codigo_estado_atuador,
    e_checksum_atuador,
    e_fim_transmissao_atuador,
    e_tam_pacote_atuador
}; //!< Enumeração com a estrutura do vetor do pacote do comando de atuador

enum estrutura_pacote_panico
{
    e_requisicao_panico,
    e_codigo_panico,
    e_checksum_panico,
    e_fim_transmissao_panico,
    e_tam_pacote_panico
};

enum estrutura_pacote_servidor
{
    e_codigo_resposta,
    e_fim_trans_pacote_servidor,
    e_tam_pacote_servidor
};

enum estrutura_pacote_acionamento
{
    e_codigo_acionamento,
    e_checksum_acionamento,
    e_fim_transmissao_acionamento,
    e_tam_pacote_acionamento
};

void inicializa_interface_com_ihm_cliente(void);
int8_t ihm_requisicao_atuador(uint8_t bt_pressionado, uint8_t estado_atuador);
// int8_t ihm_requisicao_atuador(uint8_t bt_pressionado);
int8_t ihm_aciona_atuador(uint8_t bt_tipo_de_atuacao);
int8_t ihm_configura_sup_circ(int angulo, int qtd_ciclos, int tempo_prox_ativacao);
int8_t verifica_resposta_servidor(void);
int8_t ihm_aciona_bt_panico(void);
int8_t new_ihm_req_atuador(uint8_t bt, int estado_botao);

#endif //COMMUNICATION_IHM_H
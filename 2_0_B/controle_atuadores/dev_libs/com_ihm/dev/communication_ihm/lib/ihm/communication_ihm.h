/*!

*/


#ifndef COMMUNICATION_IHM_H
#define COMMUNICATION_IHM_H
#include <stdint.h>

/*! @brief Esses são os defines com os códigos de avanço dos atuadores
           Para serem enviados pela serial
*/
#define COD_ATUADOR_AVANCO_STANDUP (0b100000)
#define COD_ATUADOR_AVANCO_ELEVADOR_BASE (0b100001)
#define COD_ATUADOR_AVANCO_ELEVADOR_SUPORTE_CIR (0b11001)
#define COD_ATUADOR_AVANCO_SUPORTE_CIR (0b11010)
#define COD_ATUADOR_AVANCO_ALTURA_ENCOSTO (0b11011)
#define COD_ATUADOR_AVANCO_INCLINACAO_ENCOSTO (0b1110)
#define COD_ATUADOR_AVANCO_DISTANCIA_ASSENTO_ENCOSTO (0b1100)

/*! @brief Esses são os defines com os códigos de recuo dos atuadores
           Para serem enviados pela serial
*/
#define COD_ATUADOR_RECUO_STANDUP (0b10111)
#define COD_ATUADOR_RECUO_ELEVADOR_BASE (0b10011)
#define COD_ATUADOR_RECUO_ELEVADOR_SUPORTE_CIR (0b10010)
#define COD_ATUADOR_RECUO_SUPORTE_CIR (0b00101)
#define COD_ATUADOR_RECUO_ALTURA_ENCOSTO (0b00100)
#define COD_ATUADOR_RECUO_INCLINACAO_ENCOSTO (0b00010)
#define COD_ATUADOR_RECUO_DISTANCIA_ASSENTO_ENCOSTO (0b1111)

/*! @brief Esses são os defines de quantidade de atuadores
           e de sensores que contem alguma necessidade de comunicação serial
*/
#define QTD_ATUADORES (14) //!< Define de Atuadores
#define QTD_FIM_CURSO (4)  //!< Defiene de quantidade de fins de curso
#define QTD_GIROSCOPIO (2) //!< define de quantidade de giroscopio
#define QTD_TIPOS_COMUNICACAO (3) //!<Define de quantidade de tipos de comunicação

#define REQUISICA_DE_ESCRITA (0X30)
#define AVANCO_ATUADOR (0b01)                //!< Valor do comando de avanço do atuador
#define RECUO_ATUADOR (0b10)                 //!< Valor do comando de recuo do atuador
#define PARAR_ATUADOR (0b11)                 //!< Valor do comando de parada do atuador
#define CONSULTA_ESTADO_FIM_CURSO (0b100)    //!< Valor do comando de consulta do estado do fim de curso
#define CONSULTA_ESTADO_GIROSCOPIO_X (0b101) //!< Valor do comando de consulta do eixo x do giroscopio

/*! @brief Esses são os defines de configurações da comunicação serial
*/
#define VELOCIDADE_TRANSMISSAO_SERIAL (115200)
#define RX_PIN (16)
#define TX_PIN (17)
#define VALOR_MAXIMO (30)
#define COD_AGUARDANDO_COMUNICACAO (1)

/*! @brief Esses são os defines de flags de comunicação
*/
#define SEM_COMUNICACAO (0)
#define DADO_DE_ENVIO (0b110110)
#define DADO_DE_EXECUCAO (0b110101)


const uint8_t qtd_codigo_pino_atuadores = QTD_ATUADORES;
const uint8_t qtd_tipos_de_comunicacao = QTD_TIPOS_COMUNICACAO;

enum Tipo_envio
{
        e_aciona_atuador,
        e_leitura_giroscopio,
        e_fim_curso
};

enum Status_comunicacao
{
        e_servidor,
        e_cliente
};

// Enumeração dos codigos
enum Codigo_atuacao
{
        e_codigo_atuador_avanco_standup,
        e_codigo_atuador_recuo_standup,
        e_codigo_atuador_avanco_elevador_base,
        e_codigo_atuador_recuo_elevador_base,
        e_codigo_atuador_avanco_elevador_suporte_circ,
        e_codigo_atuador_recuo_elevador_suporte_circ,
        e_codigo_atuador_avanco_suporte_circ,
        e_codigo_atuador_recuo_suporte_circ,
        e_codigo_atuador_avanco_altura_encosto,
        e_codigo_atuador_recuo_altura_encosto,
        e_codigo_atuador_avanco_inclinacao_encosto,
        e_codigo_atuador_recuo_inclinacao_encosto,
        e_codigo_atuador_avanco_distancia_assento_encosto,
        e_codigo_atuador_recuo_distancia_assento_encosto
};

enum Tipo_do_sensor
{
        e_sensor_giroscopio,
        e_sensor_fim_curos

};

void inicializa_comunicao_serial(void);
int8_t envia_requisicao_de_escrita(Tipo_envio tipo_de_requisicao);
int8_t envia_estado_botao(Codigo_atuacao botao_pressionado);
uint8_t verifica_comunicacao_serial(void);
int8_t requisita_dado_sensor(Tipo_do_sensor sensor_requisitado);
int8_t recebe_dado(void);
int8_t tipo_de_requisicao(Tipo_envio tipo_de_requisicao_envio);

#endif //COMMUNICATION_IHM_H

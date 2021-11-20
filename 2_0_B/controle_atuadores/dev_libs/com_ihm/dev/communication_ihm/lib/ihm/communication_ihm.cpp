/*! 
* @file communication_ihm.cpp
* @brief Arquivo com as funções e variaveis necessárias para o funcionamento da 
*        comunicação serial entre os módulos IHM e CONTROLE
*
*/

#include <communication_ihm.h>
#include "steve_debug.h"
#include <Arduino.h>

/*! @brief Comandos do protocolo de comunicacao dos modulos IHM e CONTROLE
*/

//!< Configurações da comunicação Serial
const uint32_t baud_esp32 = VELOCIDADE_TRANSMISSAO_SERIAL;
const uint8_t esp_rx = RX_PIN;
const uint8_t esp_tx = TX_PIN;
const uint8_t AGUARDANDO_COMUNICACAO = COD_AGUARDANDO_COMUNICACAO;

/* ======================================== NOVA VERSAO ======================================*/

const uint8_t envio_consulta_estado_fim_curso = CONSULTA_ESTADO_FIM_CURSO;
const uint8_t envio_consulta_estado_giro_x = CONSULTA_ESTADO_GIROSCOPIO_X;

const uint8_t sem_comunicacao_serial = SEM_COMUNICACAO;
const uint8_t qtd_sensores = 2;



const uint8_t codigo_sensor_requisitado[qtd_sensores]{
    envio_consulta_estado_giro_x,
    envio_consulta_estado_fim_curso,

};


// Codigos avanço
const uint8_t codigo_atuador_avanco_standup = COD_ATUADOR_AVANCO_STANDUP;
const uint8_t codigo_atuador_avanco_elevador_base = COD_ATUADOR_AVANCO_ELEVADOR_BASE;
const uint8_t codigo_atuador_avanco_elevador_suporte_circ = COD_ATUADOR_AVANCO_ELEVADOR_SUPORTE_CIR;
const uint8_t codigo_atuador_avanco_suporte_circu = COD_ATUADOR_AVANCO_SUPORTE_CIR;
const uint8_t codigo_atuador_avanco_altura_encosto = COD_ATUADOR_AVANCO_ALTURA_ENCOSTO;
const uint8_t codigo_atuador_avanco_inclinacao_encosto = COD_ATUADOR_AVANCO_INCLINACAO_ENCOSTO;
const uint8_t codigo_atuador_avanco_distancia_assento_encosto = COD_ATUADOR_AVANCO_DISTANCIA_ASSENTO_ENCOSTO;
// Codigos recuo
const uint8_t codigo_atuador_recuo_standup = COD_ATUADOR_RECUO_STANDUP;
const uint8_t codigo_atuador_recuo_elevador_base = COD_ATUADOR_RECUO_ELEVADOR_BASE;
const uint8_t codigo_atuador_recuo_elevador_suporte_circ = COD_ATUADOR_RECUO_ELEVADOR_SUPORTE_CIR;
const uint8_t codigo_atuador_recuo_suporte_circu = COD_ATUADOR_RECUO_SUPORTE_CIR;
const uint8_t codigo_atuador_recuo_altura_encosto = COD_ATUADOR_RECUO_ALTURA_ENCOSTO;
const uint8_t codigo_atuador_recuo_inclinacao_encosto = COD_ATUADOR_RECUO_INCLINACAO_ENCOSTO;
const uint8_t codigo_atuador_recuo_distancia_assento_encosto = COD_ATUADOR_RECUO_DISTANCIA_ASSENTO_ENCOSTO;

// Codigos do tipo de acionamento
const uint8_t tipo_aciona_atuador = DADO_DE_EXECUCAO;
const uint8_t tipo_leitura_giroscopio = DADO_DE_ENVIO;
const uint8_t tipo_leitura_fim_curso = 55;

const uint8_t tipos_de_comunicacao[qtd_tipos_de_comunicacao]
{
    tipo_aciona_atuador,
    tipo_leitura_giroscopio,
    tipo_leitura_fim_curso
};
const uint8_t codigo_pinos_atuadores[qtd_codigo_pino_atuadores]{
    codigo_atuador_avanco_standup,
    codigo_atuador_recuo_standup,
    codigo_atuador_avanco_elevador_base,
    codigo_atuador_recuo_elevador_base,
    codigo_atuador_avanco_elevador_suporte_circ,
    codigo_atuador_recuo_elevador_suporte_circ,
    codigo_atuador_avanco_suporte_circu,
    codigo_atuador_recuo_suporte_circu,
    codigo_atuador_avanco_altura_encosto,
    codigo_atuador_recuo_altura_encosto,
    codigo_atuador_avanco_inclinacao_encosto,
    codigo_atuador_recuo_inclinacao_encosto,
    codigo_atuador_avanco_distancia_assento_encosto,
    codigo_atuador_recuo_distancia_assento_encosto};

/*============================================================================================*/

/*! @brief Função responsável por inicializar a interface serial do IHM e CONTROLE
*/
void inicializa_comunicao_serial(void)
{
        Serial1.begin(baud_esp32, SERIAL_8N1, esp_rx, esp_tx);
}

/*! @brief Envia uma requisição de escrita via Serial1
*   @param[in] tipo_de_requisicao É o tipo de requisição que será feita pelo dispositivo. 
*        As requições foram dividas entre Requisiçao de Acionamento de atuador [e_aciona_atuador] e 
*        Requisição de Leitura de giroscopio [e_leitura_giroscopio]
*    @return Retorna a escrita da requisição na Serial1
*/
int8_t envia_requisicao_de_escrita(Tipo_envio tipo_de_requisicao)
{
        return Serial1.write(tipos_de_comunicacao[tipo_de_requisicao]);
}

/*! @brief envia o estado atual do botão pressionado para Serial1
*   @param[in] botao_pressionado É o botão pressionado
*   @return Retorna Sucesso caso o botão tenha sido pressionado e enviado.
*           Retorna Erro, caso o botão não tenha sido pressionado.
*/
int8_t envia_estado_botao(Codigo_atuacao botao_pressionado)
{
        if (digitalRead(codigo_pinos_atuadores[botao_pressionado]) == LOW)
        {
                delay(10);
                Serial1.write(codigo_pinos_atuadores[botao_pressionado]);
                return SUCESSO;
        }
        else
        {
                return SINALIZADOR_ERRO;
        }
}

/*! @brief Verifica o barramento Serial1
*   @return Retorna dados trafegados na serial, caso exista. Caso contrário, retorna a flag AGUARDANDO_COMUNICACAO
*/
uint8_t verifica_comunicacao_serial(void)
{
        if (Serial1.available() > sem_comunicacao_serial)
        {
                return recebe_dado();
        }
        else
        {
                return AGUARDANDO_COMUNICACAO;
        }
}

/*!  @brief Requisita dados do sensor repassado como paramentro
*    @param[in] sensor_requisitado É o sensor que será requisitado pela Serial1
*    @return Retorna a escrita na Serial1 com os dados a serem requisitados.
*/
int8_t requisita_dado_sensor(Tipo_do_sensor sensor_requisitado)
{
        return Serial1.write(codigo_sensor_requisitado[sensor_requisitado]);
}

/*!  @brief Recebe dados do sensor lidos na Serial1
*    @return Retorna a leitura do barramento Serial1 com os dados a serem lidos
*/
int8_t recebe_dado(void)
{
        return Serial1.read();
}

int8_t tipo_de_requisicao(Tipo_envio tipo_de_requisicao_envio)
{
        return tipos_de_comunicacao[tipo_de_requisicao_envio];
}
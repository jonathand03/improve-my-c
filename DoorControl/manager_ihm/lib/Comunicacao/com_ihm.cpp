/*! 
* @file communication_ihm.cpp
* @brief Arquivo com as funções e variaveis necessárias para o funcionamento da 
*        comunicação serial entre os módulos IHM e CONTROLE
*
*/

#include <com_ihm.h>
#include "steve_debug.h"
#include <Arduino.h>

/*
*       Constantes de configuração de interface
*/
const uint32_t baudrate_serial = BAUDRATE;
const uint8_t pino_rx = RX_PIN;
const uint8_t pino_tx = TX_PIN;

/*! @brief Inicializa a interface de comunicação do cliente
*/
void inicializa_interface_com_ihm_cliente(void)
{
        Serial.begin(baudrate_serial, SERIAL_8N1, pino_rx, pino_tx);
}

/*! @brief Envia um pacote de dados para o barramento serial referente ao botão apertado
*   @param[in] botao_pressionado É o botão que foi apertado na interface IHM
*   @return Retorna o código gerado pela função de verificação de resposta do servidor
*/
int8_t ihm_requisicao_atuador(uint8_t bt_pressionado, uint8_t estado_atuador)
{
        uint8_t buffer_de_dados[e_tam_pacote_atuador]; //!< buffer que armazena os dados para envio
        /* Constroe o pacote de dados a ser enviado no buffer de dados do atuador
        */
        buffer_de_dados[e_requisicao_atuador] = COD_REQUISICAO_ATUADOR;
        buffer_de_dados[e_codigo_atuador] = bt_pressionado;
        buffer_de_dados[e_codigo_estado_atuador] = estado_atuador;
        buffer_de_dados[e_checksum_atuador] = buffer_de_dados[e_requisicao_atuador] + buffer_de_dados[e_codigo_atuador] + buffer_de_dados[e_codigo_estado_atuador] + 1;
        buffer_de_dados[e_fim_transmissao_atuador] = COD_FIM_TRANSMISSAO;

        Serial.write(buffer_de_dados, e_tam_pacote_atuador); //!< Envia o buffer de dados para o barramento serial
        return verifica_resposta_servidor();
}

/*! @brief Envia o tipo de atuação que o controlador deve fazer
*   @param[in] bt_tipo_de_atuacao É o botão da atuação pressionada
*   @return Retorna o código gerado pela função de verificação de resposta do servidor
*/
int8_t ihm_aciona_atuador(uint8_t bt_tipo_de_atuacao)
{
        uint8_t buffer_de_dados[e_tam_pacote_acionamento];

        buffer_de_dados[e_codigo_acionamento] = bt_tipo_de_atuacao;
        buffer_de_dados[e_checksum_acionamento] = bt_tipo_de_atuacao+1;
        buffer_de_dados[e_fim_transmissao_acionamento] = COD_FIM_TRANSMISSAO;

        Serial.write(buffer_de_dados,e_tam_pacote_acionamento);
        return verifica_resposta_servidor();
}


/*! @brief Envia a configuração do suporte circulatório para o esp-controle
*   @param[in] angulo É o ângulo configurado na interface IHM
*   @param[in] qtd_ciclos É a quantidade de vezes que o suporte circulatório irá subir e descer
*   @param[in] tempo_prox_ativacao É o tempo para a próxima ativação do suporte circulatório
*   @return Retorna o código gerado pela função de verificação de resposta do servidor
*/
int8_t ihm_configura_sup_circ(int angulo, int qtd_ciclos, int tempo_prox_ativacao)
{

        uint8_t buffer_de_dados[e_tam_pacote_sc];

        buffer_de_dados[e_requisicao] = COD_REQUISICAO_CONFIG_SC;
        buffer_de_dados[e_angulo] = angulo;
        buffer_de_dados[e_qtd_ciclos] = qtd_ciclos;
        buffer_de_dados[e_temp_prox_atv] = tempo_prox_ativacao;
        buffer_de_dados[e_checksum] = (COD_REQUISICAO_CONFIG_SC + angulo + qtd_ciclos + tempo_prox_ativacao + 1) - 100;
        buffer_de_dados[e_fim_transmissao] = COD_FIM_TRANSMISSAO;

        Serial.write(buffer_de_dados, e_tam_pacote_sc);
        return verifica_resposta_servidor();
}

int8_t ihm_aciona_bt_panico(void)
{
        uint8_t buffer_de_dados[e_tam_pacote_panico];

        buffer_de_dados[e_requisicao_panico] = COD_REQUISICAO_PANICO;
        buffer_de_dados[e_codigo_panico] = COD_ATUADOR_AVANCO;
        buffer_de_dados[e_checksum_panico] = COD_REQUISICAO_PANICO + COD_ATUADOR_AVANCO + 1;
        buffer_de_dados[e_fim_transmissao_panico] = COD_FIM_TRANSMISSAO;

        Serial.write(buffer_de_dados, e_tam_pacote_panico);
        return verifica_resposta_servidor();
}

/*! @brief Verifica se o controlador enviou o codigo de OK para o ihm 
*   @return Retorna @b SUCESSO, caso o controlador envie OK, caso contrário, gera um código de erro
*           @p SINALIZADOR_ERRO -> Controlador não enviou OK e sim algum código de erro.
*           @p SEM_RESPOSTA -> Controlador não emitiu nenhuma resposta.
*/
int8_t verifica_resposta_servidor(void)
{
        if (Serial.available() > 0)
        {
                uint8_t buffer_de_dados[e_tam_pacote_servidor];
                Serial.readBytes(buffer_de_dados,e_tam_pacote_servidor);
                if(buffer_de_dados[e_codigo_resposta] == COD_SERVIDOR_OK)
                        return SUCESSO;
                else
                        return buffer_de_dados[e_codigo_resposta];
        }
        else
                return SEM_RESPOSTA; //!< Se o timout for acionado, retorna sem respsota
}







/*
int8_t verifica_resposta_servidor(void)
{
        if (Serial.available() > 0)
        {
                if (Serial.read() == COD_SERVIDOR_OK)
                        return SUCESSO; //!< Sucesso
                else
                        return SINALIZADOR_ERRO; // Sinalizador_erro
        }
        else
                return SEM_RESPOSTA; //!< Sem resposta
}*/

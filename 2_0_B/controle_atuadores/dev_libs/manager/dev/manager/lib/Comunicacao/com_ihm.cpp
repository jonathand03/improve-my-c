/*! 
* @file communication_ihm.cpp
* @brief Arquivo com as funções e variaveis necessárias para o funcionamento da 
*        comunicação serial entre os módulos IHM e CONTROLE
*
*/
#include <com_ihm.h>
#include "steve_debug.h"
#include <Arduino.h>

const int cod_requisicao = 0;
const uint32_t baudrate_serial = BAUDRATE;
const uint8_t pino_rx = RX_PIN;
const uint8_t pino_tx = TX_PIN;
int vetor_atuador[5];
uint8_t buffer_de_dados[6];
/*! @brief Inicializa a interface de comunicação do Servidor 
*
*/
void inicializa_interface_com_ihm_servidor(void)
{
    Serial.begin(baudrate_serial, SERIAL_8N1, pino_rx, pino_tx);
}

/*! @brief Verifica dados recebido pelo barramento serial
*   @return Retorna SUCESSO, caso o dado tenha sido tratado com sucesso, 
*   retorna erro caso contrário
*/
int8_t verifica_barramento_serial(void)
{
    if (Serial.available() > 0)
    {
        Serial.readBytes(buffer_de_dados, 6);           //!< Faz a leitura dos dados no barramento e salva no buffer temporario
        return tratamento_de_dados(buffer_de_dados, 6); //!< retorna o resultado do tratamento dos dados salvos
    }
    else
        return SEM_NOVO_DADO;
}

/*! @brief Faz o tratamento do dado recebido pelo barramento serial
*   @param[in] buffer_de_dados É o buffer de dados recebido pelo barramento serial
*   @param[in] tam_buffer É o tamanho do pacote contido no buffer
*   @return Retorna SUCESSO, caso o dado tenha sido tratado e executado com sucesso, 
*           caso contrário retorna erro
*/
int8_t tratamento_de_dados(uint8_t *buffer_dados, uint8_t tam_buffer)
{
    if (verifica_checksum(buffer_dados, tam_buffer) == SINALIZADOR_ERRO) // verifica o checksum
        return SINALIZADOR_ERRO;                                         // retorna erro caso o checksum retorne erro
    else
        return SUCESSO;
   
}

/*! @brief Faz o calculo do checksum do pacote recebido pelo barramento serial
*   @param[in] buffer_de_dados É o buffer de dados recebido pelo barramento serial
*   @param[in] tam_buffer É o tamanho do pacote contido no buffer
*   @return Retorna SUCESSO, caso o checksum seja válido, retorna SINALIZADOR_ERRO caso contrário
*   @note Caso o CRC seja inválido é enviado de volta um pacote contendo as informações de erro
*/
int8_t verifica_checksum(uint8_t *buffer_de_dados, uint8_t tam_buffer)
{
    if (buffer_de_dados[requisicao_pacote] == COD_REQUISICAO_ATUADOR) // verifica se o buffer é do botao de pânico ou requisicao atuador
    {
        uint8_t checksum = buffer_de_dados[requisicao_pacote] + buffer_de_dados[pino_atuador_pacote] + buffer_de_dados[estado_pacote] + 1; // faz o calculo do crc
        if (checksum == buffer_de_dados[checksum_pacote])                                                                                  // verifica se é igual o crc recebido
            return SUCESSO;                                                                                                                // se sim, retorna sucesso
        else                                                                                                                               // se não retorna um buffer com o codigo de crc invalido + fim transmisssao
        {
            uint8_t buffer_erro[e_tam_resposta];
            buffer_erro[e_resposta_servidor] = COD_CRC_INVALIDO;
            buffer_erro[e_resposta_fim_transmissao] = FIM_TRANSMISSAO;
            Serial.write(buffer_erro, e_tam_resposta);
            return SINALIZADOR_ERRO;
        }
    }
    else if (buffer_de_dados[requisicao_pacote_sc] == COD_REQUISICAO_CONFIG_SC) //!< verifica se é o buffer de config sup circ
    {
        uint8_t checksum;
        checksum = (buffer_de_dados[requisicao_pacote_sc] + buffer_de_dados[angulo] 
                    + buffer_de_dados[qtd_ciclos] + buffer_de_dados[tempo] + 1) - 100;
        if (checksum == buffer_de_dados[checksum_sc]) //!< se o cálculo do checkum for igual o checksum recebido
            return SUCESSO;
        else //!< se não, retorna para o ihm que o foi recebido um pacote de dados inválido
        {
            uint8_t buffer_erro[e_tam_resposta];
            buffer_erro[e_resposta_servidor] = COD_CRC_INVALIDO;
            buffer_erro[e_resposta_fim_transmissao] = FIM_TRANSMISSAO;
            Serial.write(buffer_erro, e_tam_resposta);
            return SINALIZADOR_ERRO;
        }
    }
    else
    {
        retorna_codigo_estouro_pacote();
        return SINALIZADOR_ERRO;
    }
}

// retorna para o ihm o código de requisição inválido
void retorna_codigo_req_invalida(void)
{
    uint8_t buffer_de_dados[e_tam_resposta];

    buffer_de_dados[e_resposta_servidor] = COD_REQ_INVALIDO;
    buffer_de_dados[e_resposta_fim_transmissao] = FIM_TRANSMISSAO;

    Serial.write(buffer_de_dados, e_tam_resposta);
    //Serial.flush();
}

// retorna para o ihm o código de estouro de pacote de dados
void retorna_codigo_estouro_pacote(void)
{
    uint8_t buffer_de_dados[e_tam_resposta];

    buffer_de_dados[e_resposta_servidor] = COD_ESTOURO_PACOTE;
    buffer_de_dados[e_resposta_fim_transmissao] = FIM_TRANSMISSAO;

    Serial.write(buffer_de_dados, e_tam_resposta);
    //Serial.flush();
}
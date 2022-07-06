#include "atuadores.h"
#include "steve_debug.h"
#include "com_ihm.h"

/*! \var const int qtd_pinos_atuadores
    \brief Armazena a quantidade de pinos de atuadores estão disponíveis
    
    *******
*/
const int qtd_pinos_atuadores = qtd_atuadores * qtd_atuacao;

/*! 
*        MAPEAMENTO DE PORTAS - AÇÕES DE AVANÇO 
*/
const int atuador_avanco_standup = AT_AV_STANDUP;                                               //!< [ATUADOR] Standup: pino de [avanço]
const int atuador_avanco_elevador_base = AT_AV_ELEVADOR_BASE;                                   //!< [ATUADOR] Elevador da base: pino de [avanço]
const int atuador_avanco_elevador_suporte_circ_esquerdo = AT_AV_ELEVADOR_SUPORTE_CIRC_ESQUERDO; //!< [ATUADOR] Elevador do suporte circulatório esquerdo: pino de [avanço]
const int atuador_avanco_elevador_suporte_circ_direito = AT_AV_ELEVADOR_SUPORTE_CIRC_DIREITO;   //<  [ATUADOR] Elevador do suporte circulatório direito: pino de [avanço]
//TODO PADRONIZAR VARIAVEL [circu -> circ]
const int atuador_avanco_suporte_circu = AT_AV_SUPORTE_CIRCU;                         //!< [ATUADOR] Suporte circulatório: pino de [avanço] //!< PADRONIZAR
const int atuador_avanco_altura_encosto = AT_AV_ALTURA_ENCOSTO;                       //!< [ATUADOR] Altura do enconsto: pino de [avanço]
const int atuador_avanco_inclinacao_encosto = AT_AV_INCLINACAO_ENCOSTO;               //!< [ATUADOR] Inclinação do encosto: pino de [avanço]
const int atuador_avanco_distancia_assento_encosto = AT_AV_DISTANCIA_ASSENTO_ENCOSTO; //!< [ATUADOR] Distancia do assento e encosto: pino de [avanço]

/*!
*        MAPEAMENTO DE PORTAS - AÇÕES DE RECUO
*/
const int atuador_recuo_standup = AT_RC_STANDUP;                                               //!< [ATUADOR] Standup: pino de [recuo]
const int atuador_recuo_elevador_base = AT_RC_ELEVADOR_BASE;                                   //!< [ATUADOR] Elevador da base: pino de [recuo]
const int atuador_recuo_elevador_suporte_circ_esquerdo = AT_RC_ELEVADOR_SUPORTE_CIRC_ESQUERDO; //!< [ATUADOR] Elevador do suporte circulatório: pino de [recuo]
const int atuador_recuo_elevador_suporte_circ_direito = AT_RC_ELEVADOR_SUPORTE_CIRC_DIREITO;   //<  [ATUADOR] Elevador do suporte circulatório direito: pino de [avanço]
const int atuador_recuo_suporte_circu = AT_RC_SUPORTE_CIRCU;                                   //!< [ATUADOR] Suporte circulatório: pino de [recuo]
const int atuador_recuo_altura_encosto = AT_RC_ALTURA_ENCOSTO;                                 //!< [ATUADOR] Altura do enconsto: pino de [recuo]
const int atuador_recuo_inclinacao_encosto = AT_RC_INCLINACAO_ENCOSTO;                         //!< [ATUADOR] Inclinação do encosto: pino de [recuo]
const int atuador_recuo_distancia_assento_encosto = AT_RC_DISTANCIA_ASSENTO_ENCOSTO;           //!< [ATUADOR] Distancia do assento e encosto: pino de [recuo]

/*! \var const int pinos_atuadores
    \brief Vetor com todas as portas dos ATUADORES
    
    *******
*/
const int pinos_atuadores[qtd_pinos_atuadores][qtd_atuacao] =
    {
        {atuador_avanco_standup, atuador_recuo_standup},
        {atuador_avanco_elevador_base, atuador_recuo_elevador_base},
        {atuador_avanco_elevador_suporte_circ_esquerdo, atuador_recuo_elevador_suporte_circ_esquerdo},
        {atuador_avanco_elevador_suporte_circ_direito, atuador_recuo_elevador_suporte_circ_direito},
        {atuador_avanco_suporte_circu, atuador_recuo_suporte_circu},
        {atuador_avanco_altura_encosto, atuador_recuo_altura_encosto},
        {atuador_avanco_inclinacao_encosto, atuador_recuo_inclinacao_encosto},
        {atuador_avanco_distancia_assento_encosto, atuador_recuo_distancia_assento_encosto}};

/*! \var int estados_pinos_atuador
    \brief Vetor com o estado de todos os atuadores ATUADORES

    *******
*/
int estados_pinos_atuador[qtd_atuadores][qtd_atuacao];

/*! \fn void inicializa_atuadores(void)
 * @brief Inicializa os pinos dos atuadores como OUTPUT
 * @param[in] estados_pinos_atuador É a matriz de estados dos atuadores
 */
void inicializa_atuadores(void)
{
        for (int i = 0; i < qtd_pinos_atuadores; i++)
        {
                for (int j = 0; j < qtd_atuacao; j++)
                {
                        pinMode(pinos_atuadores[i][j], OUTPUT);
                }
        }
        //debug("Atuadores inicializados com sucesso");
}

void reseta_atuadores(void)
{
        for (int i = 0; i < qtd_pinos_atuadores; i++)
        {
                for (int j = 0; j < qtd_atuacao; j++)
                {
                        digitalWrite(pinos_atuadores[i][j], HIGH);
                }
        }
}

/*! \fn void inicializacao_estados_atuadores(int estados_pinos_atuador[qtd_atuadores][qtd_atuacao])
 * @brief Inicializa os estados dos pinos dos atuadores em 0 (desligar)
 * @param[in] estados_pinos_atuador É a matriz de estados dos atuadores
 */
void inicializacao_estados_atuadores(int estados_pinos_atuador[qtd_atuadores][qtd_atuacao])
{
        for (int i = 0; i < qtd_atuadores; i++)
        {
                for (int j = 0; j < qtd_atuacao; j++)
                {
                        estados_pinos_atuador[i][j] = desligado;
                }
        }
}
void tratamento_atuador(void)
{
        int pino_atuador = buffer_de_dados[pino_atuador_pacote];
        switch (pino_atuador)
        {
        case e_atuador_standup:
                acionamento_atuador(e_atuador_standup);
                break;
        case e_atuador_elevador_base:
                acionamento_atuador(e_atuador_elevador_base);
                break;
        case e_atuador_elevador_suporte_circ_direito:
                acionamento_atuador(e_atuador_elevador_suporte_circ_direito);
                break;
        case e_atuador_elevador_suporte_circ_esquerdo:
                acionamento_atuador(e_atuador_elevador_suporte_circ_esquerdo);
                break;
        case e_atuador_suporte_circu:
                acionamento_atuador(e_atuador_suporte_circu);
                break;
        case e_atuador_altura_encosto:
                acionamento_atuador(e_atuador_altura_encosto);
                break;
        case e_atuador_inclinacao_encosto:
                acionamento_atuador(e_atuador_inclinacao_encosto);
                break;
        case e_atuador_distancia_assento_encosto:
                acionamento_atuador(e_atuador_distancia_assento_encosto);
                break;
        }
}

void acionamento_atuador(e_atuadores atuador)
{
        if (buffer_de_dados[estado_pacote] == COD_ATUADOR_AVANCO)
        {
                atuador_avancar(atuador);
        }
        else if (buffer_de_dados[estado_pacote] == COD_ATUADOR_RECUO)
        {
                atuador_recuar(atuador);
        }
        else if (buffer_de_dados[estado_pacote] == COD_ATUADOR_DESLIGADO)
        {
                atuador_parar(atuador);
        }
}

void limpa_buffer(void)
{
        int indice = 0;
        while (indice <= 5)
        {
                buffer_de_dados[indice] = 0;
                indice++;
        }
}

/*! \fn int escrita_atuador(e_atuadores atuador, int estado_pino)
 * @brief  Atualiza os estados dos pinos e escreve HIGH ou LOW no pino referido nos parametros
 * @param[in] atuador É uma enumeração referente ao atuador desejado
 * @param[in] estado_pino É o estado requerido para escrita
 * @return Retorna 0 em caso de sucesso, ou -1 em caso de falha
 */
int escrita_atuador(e_atuadores atuador, int estado_pino)
{
        if (estado_pino == avanco)
        {
                estados_pinos_atuador[atuador][avanco] = ligado;
                estados_pinos_atuador[atuador][recuo] = desligado;
                digitalWrite(pinos_atuadores[atuador][avanco], LOW);
                digitalWrite(pinos_atuadores[atuador][recuo], HIGH);
                #ifdef DEBUG_ATUADOR
                        debug("Foi feita a escrita nos pinos dos atuadores");
                #endif
                return SUCESSO;
        }
        else if (estado_pino == recuo)
        {
                estados_pinos_atuador[atuador][avanco] = desligado;
                estados_pinos_atuador[atuador][recuo] = ligado;
                digitalWrite(pinos_atuadores[atuador][avanco], HIGH);
                digitalWrite(pinos_atuadores[atuador][recuo], LOW);
                return SUCESSO;
        }
        else
        {
                #ifdef DEBUG_ATUADOR
                        debug("O estado da função só pode assumir 0 ou 1 ( avanço ou recuo)");
                #endif
                return SINALIZADOR_ERRO;
        }
}

/*! \fn int atuador_avancar(e_atuadores atuador)
 * @brief  Faz o tratamento de qual atuador deve ser acionado para AVANÇO
 * @param[in] atuador É uma enumeração referente ao atuador desejado
 * @return Retorna 0 em caso de sucesso, ou -1 em caso de falha
 */
int atuador_avancar(e_atuadores atuador)
{
        if (estados_pinos_atuador[atuador][avanco] == desligado)
        {
                atuador_parar(atuador);
                escrita_atuador(atuador, avanco);
                #ifdef DEBUG_ATUADOR
                        debug("Função de avanço acionada com sucesso");
                #endif
                return SUCESSO;
        }
        else if (estados_pinos_atuador[atuador][avanco] == ligado)
        {
                escrita_atuador(atuador, avanco);
                #ifdef DEBUG_ATUADOR
                        debug("Função de avanço acionada com sucesso");
                #endif
                return SUCESSO;
        }
        else
        {
                #ifdef DEBUG_ATUADOR
                        debug("Erro no vetor de estados. Verificar os valores no vetor");
                #endif
                return SINALIZADOR_ERRO;
        }
}

/*! \fn int atuador_recuar(e_atuadores atuador)
 * @brief  Faz o tratamento de qual atuador deve ser acionado para RECUO
 * @param[in] atuador É uma enumeração referente ao atuador desejado
 * @return Retorna 0 em caso de sucesso, ou -1 em caso de falha
 */
int atuador_recuar(e_atuadores atuador)
{
        if (estados_pinos_atuador[atuador][recuo] == desligado)
        {
                atuador_parar(atuador);
                escrita_atuador(atuador, recuo);
                #ifdef DEBUG_ATUADOR
                        debug("Função de recuo acionada com sucesso");
                #endif
                return SUCESSO;
        }
        else if (estados_pinos_atuador[atuador][recuo] == ligado)
        {
                escrita_atuador(atuador, recuo);
                #ifdef DEBUG_ATUADOR
                        debug("Função de recuo acionada com sucesso");
                #endif
                return SUCESSO;
        }
        else
        {
                #ifdef DEBUG_ATUADOR
                        debug("Erro no vetor de estados. Verificar os valores no vetor");
                #endif
                return SINALIZADOR_ERRO;
        }
}

/*! \fn void atuador_parar(e_atuadores atuador)
 * @brief  Determina que o atuador passado como parâmetro deve parar
 * @param[in] atuador É uma enumeração referente ao atuador desejado
 */
void atuador_parar(e_atuadores atuador)
{
        #ifdef DEBUG_ATUADOR
                debug("Função de parada acionada com sucesso");
        #endif
        estados_pinos_atuador[atuador][avanco] = desligado;
        estados_pinos_atuador[atuador][recuo] = desligado;
        digitalWrite(pinos_atuadores[atuador][avanco], HIGH);
        digitalWrite(pinos_atuadores[atuador][recuo], HIGH);
}
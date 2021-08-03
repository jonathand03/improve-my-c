#include "atuadores.h"

/*! \var const int qtd_pinos_atuadores
    \brief Armazena a quantidade de pinos de atuadores estão disponíveis
    
    *******
*/
const int qtd_pinos_atuadores = qtd_atuadores * qtd_atuacao;

/*! 
*        MAPEAMENTO DE PORTAS - AÇÕES DE AVANÇO 
*/
const int atuador_avanco_standup = AT_AV_STANDUP;                                     //!< [ATUADOR] Standup: pino de [avanço]
const int atuador_avanco_elevador_base = AT_AV_ELEVADOR_BASE;                         //!< [ATUADOR] Elevador da base: pino de [avanço]
const int atuador_avanco_elevador_suporte_circ = AT_AV_ELEVADOR_SUPORTE_CIRC;         //!< [ATUADOR] Elevador do suporte circulatório: pino de [avanço]
const int atuador_avanco_suporte_circu = AT_AV_SUPORTE_CIRCU;                         //!< [ATUADOR] Suporte circulatório: pino de [avanço]
const int atuador_avanco_altura_encosto = AT_AV_ALTURA_ENCOSTO;                       //!< [ATUADOR] Altura do enconsto: pino de [avanço]
const int atuador_avanco_inclinacao_encosto = AT_AV_INCLINACAO_ENCOSTO;               //!< [ATUADOR] Inclinação do encosto: pino de [avanço]
const int atuador_avanco_distancia_assento_encosto = AT_AV_DISTANCIA_ASSENTO_ENCOSTO; //!< [ATUADOR] Distancia do assento e encosto: pino de [avanço]

/*!
*        MAPEAMENTO DE PORTAS - AÇÕES DE RECUO
*/
const int atuador_recuo_standup = AT_RC_STANDUP;                                     //!< [ATUADOR] Standup: pino de [recuo]
const int atuador_recuo_elevador_base = AT_RC_ELEVADOR_BASE;                         //!< [ATUADOR] Elevador da base: pino de [recuo]
const int atuador_recuo_elevador_suporte_circ = AT_RC_ELEVADOR_SUPORTE_CIRC;         //!< [ATUADOR] Elevador do suporte circulatório: pino de [recuo]
const int atuador_recuo_suporte_circu = AT_RC_SUPORTE_CIRCU;                         //!< [ATUADOR] Suporte circulatório: pino de [recuo]
const int atuador_recuo_altura_encosto = AT_RC_ALTURA_ENCOSTO;                       //!< [ATUADOR] Altura do enconsto: pino de [recuo]
const int atuador_recuo_inclinacao_encosto = AT_RC_INCLINACAO_ENCOSTO;               //!< [ATUADOR] Inclinação do encosto: pino de [recuo]
const int atuador_recuo_distancia_assento_encosto = AT_RC_DISTANCIA_ASSENTO_ENCOSTO; //!< [ATUADOR] Distancia do assento e encosto: pino de [recuo]

/*! \var const int pinos_atuadores
    \brief Vetor com todas as portas dos ATUADORES
    
    *******
*/
const int pinos_atuadores[qtd_pinos_atuadores][qtd_atuacao] =
    {
        {atuador_avanco_standup, atuador_recuo_standup},
        {atuador_avanco_elevador_base, atuador_recuo_elevador_base},
        {atuador_avanco_elevador_suporte_circ, atuador_recuo_elevador_suporte_circ},
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
        debug("Atuadores inicializados com sucesso");
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
                delay(10);
                estados_pinos_atuador[atuador][avanco] = ligado;
                estados_pinos_atuador[atuador][recuo] = desligado;
                digitalWrite(pinos_atuadores[atuador][avanco], HIGH);
                digitalWrite(pinos_atuadores[atuador][recuo], LOW);
#ifdef DEBUG_ATUADOR
                debug("Foi feita a escrita nos pinos dos atuadores");
#endif
                return SUCESSO;
        }
        else if (estado_pino == recuo)
        {
                delay(10);
                estados_pinos_atuador[atuador][avanco] = desligado;
                estados_pinos_atuador[atuador][recuo] = ligado;
                digitalWrite(pinos_atuadores[atuador][avanco], LOW);
                digitalWrite(pinos_atuadores[atuador][recuo], HIGH);
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
        digitalWrite(pinos_atuadores[atuador][avanco], LOW);
        digitalWrite(pinos_atuadores[atuador][recuo], LOW);
}
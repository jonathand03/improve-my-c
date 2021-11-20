#include "manager.h"
#define QTD_INICIALIZACAO 5

enum DispositivoInicializado
{
    e_inicializa_atuador,
    e_inicializa_com_ihm,
    e_inicializa_fim_curso_standup_high,
    e_inicializa_fim_curso_standup_low,
    e_inicializa_fim_curso_suporte_circ_low,
    e_inicializa_giroscopio
    
};

/*! @brief Função de inicialização dos componentes do mananger do ESP CONTROLE (SERVIDOR).
*   MODULOS: GIROSCOPIO, FIM DE CURSO, ATUADORES, COMUNICAÇÃO SERIAL
*/
void inicializa_modulos_controle(void)
{
    inicializa_atuadores();
    reseta_atuadores();
    inicializa_fim_de_curso();
    inicializa_interface_com_ihm_servidor();
}

/* SERVIDOR */

void verifica_codigo_recebido(void)
{
        int verifica_retorno =  verifica_barramento_serial();
        if(verifica_retorno == SUCESSO)
        {
                int op = buffer_de_dados[0];   
                switch (op)
                {
                        case COD_REQUISICAO_ATUADOR:
                                tratamento_atuador();
                                limpa_buffer();
                                break;
                        case COD_REQUISICAO_PANICO:
                                break;
                        case COD_REQUISICAO_CONFIG_SC:
                                break;
                        default:// erro
                                break;  
              }  
        }
}


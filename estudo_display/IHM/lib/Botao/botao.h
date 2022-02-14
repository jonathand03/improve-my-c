#ifndef BOTAO_H
#define BOTAO_H

#include <stdint.h>
#include <Arduino.h>



enum estado_botao
{
  desligado,
  ligado,
  continua_desligado,
  continua_ligado
};

enum e_botao
{
    bt_baixo,
    bt_cima,
    bt_enter,
    bt_standup,
    bt_panico
};


const int qtd_bt_ihm = 5;
extern int QTD_BT;
extern volatile int estado_botoes_ihm[qtd_bt_ihm] ;
extern volatile int estado_bt_anterior[qtd_bt_ihm];


/* Flags de logica do ihm */
extern int opcao_atual;
extern int opcao_anterior;
extern int pagina_atual;
extern int limite_inf;




class Button
{
    private:
        typedef struct 
        {
            /* Estado do Botão */
            bool BtOn ;
            bool BtOff ;
            bool BtStayOn;
            bool BtStayOff ;
            /* Modos operacionais */
            bool BtWorking ;
            bool BtStopped ;
            /* Configurações do botão */
            int ButtonPin;
            int8_t ButtonID ;
            int ButtonEdge;


        }BtInfo;

    public:
        /* Construtor de Inicialização da Classe Button */
        Button(int pin, int edge);
        /* Pausa ou encerra o botão */
        uint8_t StopButton(void);
        uint8_t ResumeButton(void);
        /* Faz a Leitura do botão   */
        int ReadButton(void);
        /* Status de configuração do botão  (para fins de debug)*/
        void StatusButton(void);
        BtInfo ButtonStatus;
};


        int encapsula_intr(int pin, int bt_id);
        estado_botao verifica_botao_pressionado(e_botao botao_acionado);
        void evento_enter(void);

#endif
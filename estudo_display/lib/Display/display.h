#ifndef DISPLAY_H
#define DISPLAY_H

#include <TFT_eSPI.h>

/*! @brief Essa é classe de mostragem de itens no display do dispositivo.
*          Todas as funções aqui presentes, são exclusivamente de mostragem
*/
class IHM : public TFT_eSPI
{
    public:
        /* Inicializacao*/
        void InicializaDisplay(void);
        /*  Tela de Inicialização   */
        void TelaInicializacao(void);
        /*  Tela de Status inicial  */
        void StatusInicial(void);
        /*  Tela do menu inicial    */
        void TelaMenuInicial(void);
        /*  Tela de Navegação       */
        void NavegacaoMenu(void);
        /*  Tela de menu do suporte circulatorio*/
        void TelaMenuSC(void);
        /*Tela do menu dos microajustes*/
        void TelaMenuAjustes(void);

        /***************************** Suporte Circulatorio *****************************/
            /* Tela de status do suporte ciculatorio */
            void TelaStatusSC(void);
            /* Tela de configurações do angulo */
            void TelaAngulo(void);
            /* Tela de configurações de ciclo */
            void TelaCiclo(void);
            /* Tela de configurações de tempo */
            void TelaTempo(void);
        /************************************ Ajustes ***********************************/
            /*  Ajustes Assento */
            void AjusteVerticalAssento(void);
            void AjusteHorizontalAssento(void);
            /* Ajustes Encosto */
            void AjusteInclinacaoEncosto(void);
            void AjusteVerticalEncosto(void);
        /**************************** FIM DA INSTÂNCIA PUBLICA **************************/
    private:
        /***************************** Proporções da Tela *******************************/
            /* Proporções de tudo que vai aparacer na tela */
            const uint16_t LarguraDisplay = 200;
            const uint16_t AlturaDisplay = 190;
            /* Proporção do menu lateral */
            const uint16_t AlturaMenuIcones = 190;
            const uint16_t LarguraMenuIcones = 65;
        /************** Proporções dos objetos no display em porcetagem  ****************/
            /* O eixo x da primeira opção do menu terá 40% da proporção do display  */
            const uint8_t xOpcoesMenu = 40;
            /* O eixo y da primeira opção no menu terá 10% da proporção do display  */
            const uint8_t yOpcoesMenu = 10;
            /* Espaçamento entre as opções será de 20% da proporção do display      */
            const uint8_t yEntreOp = 20;

        /******************************** PALETA DE CORES ********************************/
            /* Cor de fundo do menu quando é selecionado */
            const int AZUL = TFT_BLUE;
            /* Cor do menu lateral quando não selecionado */
            const int PRETO = TFT_BLACK;
            /* Cor de destaque da opção atual de navegação, das letras do menu e da barra de progresso*/
            const int BRANCO = TFT_WHITE;
            /* Cor da barra de progresso quando está sendo preenchida */
            const int VERDE = TFT_GREEN;
        /******************************* BITMAP DOS ICONES *******************************/
            /* Icone do menu do suporte circulatorio */
            /* Icone do menu de ajustes */
            /* Icone do menu de Status do Steve */
        /************************** FIM  DA INSTÂNCIA PRIVADA ****************************/
};

#endif
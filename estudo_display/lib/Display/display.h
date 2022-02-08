#ifndef DISPLAY_H
#define DISPLAY_H

#include <TFT_eSPI.h>

class IHM : public TFT_eSPI
{
    public:
        /* Construtor com inicalização*/
        IHM();
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
        

       
        /**** Suporte Circulatorio ****/
        /* Tela de status do suporte ciculatorio */
        void TelaStatusSC(void);
        /* Tela de configurações do angulo */
        void TelaAngulo(void);
        /* Tela de configurações de ciclo */
        void TelaCiclo(void);
        /* Tela de configurações de tempo */
        void TelaTempo(void);

        /**** Ajustes ****/
        /* Ajustes Assento */
        void AjusteVerticalAssento(void);
        void AjusteHorizontalAssento(void);
        /* Ajustes Encosto */
        void AjusteInclinacaoEncosto(void);
        void AjusteVerticalEncosto(void);

        
        

    private:
};


#endif
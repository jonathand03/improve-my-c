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

    private:
};


#endif
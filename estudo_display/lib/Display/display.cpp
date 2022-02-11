/*******************************************************************
 * Lib do display do steve 2.1
 *  @author Francisco Jonathan Lima Drumond
 *   
 * 
 */

#include "display.h"


const char *op_menu_sc[4] = 
{
    MENU_SC_OP_0,
    MENU_SC_OP_1,
    MENU_SC_OP_2,
    MENU_SC_OP_3
};

void IHM::InicializaDisplay(void)
{
    this->init();
    this->setRotation(1);
    this->fillScreen(BRANCO);
}

void IHM::TelaMenuInicial(int opcao)
{
    
    this->fillRect(80,0,LarguraDisplay,AlturaDisplay,AZUL); // FUNÇÃO DA TELA DISPONIVEL
    this->fillRect(0,0,ProporcaoMenuLateral(largura,LarguraMenuIcones),ProporcaoMenuLateral(altura,AlturaMenuIcones),PRETO); // FUNÇÃO DO MENU LATERAL
    this->setTextSize(2);
    this->setTextFont(4);
    this->setTextColor(BRANCO);
    
    this->drawString(op_menu_sc[0],132,20);
    this->drawString(op_menu_sc[1],132,96,4);
    this->drawString(op_menu_sc[2],132,172,4);

    if(opcao == 0)
    {
        this->fillTriangle(80,10,120,40,80,70,BRANCO);
        this->fillTriangle(80,162,120,192,80,222,AZUL); 
    }
    if(opcao == 1)
    {
        this->fillTriangle(80,10,120,40,80,70,AZUL);
        this->fillTriangle(80,162,120,192,80,222,AZUL); 
        this->fillTriangle(80,86,120,116,80,146,BRANCO);


    }
    if(opcao == 2)
    {
        this->fillTriangle(80,86,120,116,80,146,AZUL);
        this->fillTriangle(80,162,120,192,80,222,BRANCO); 
    }
    // if(opcao == 3)
    // {
        // this->fillTriangle(80,162,120,192,80,222,AZUL); 
        // this->fillTriangle(80,10,120,40,80,70,BRANCO); 
    // }
   

}

void IHM::TelaAngulo(void)
{
    int32_t largura_atual =80;
    int32_t altura_atual = 240;
    
    this->fillRect(80,0,LarguraDisplay,AlturaDisplay,AZUL); // FUNÇÃO DA TELA DISPONIVEL
    this->fillRect(0,0,largura_atual,altura_atual,PRETO); // FUNÇÃO DO MENU LATERAL
    this->fillRect(80,250,200,30, BRANCO);
}

void IHM::TelaElevacao(void)
{
    int32_t largura_atual =80;
    int32_t altura_atual = 240;
    
    this->fillRect(80,0,LarguraDisplay,AlturaDisplay,AZUL); // FUNÇÃO DA TELA DISPONIVEL
    this->fillRect(0,0,largura_atual,altura_atual,PRETO); // FUNÇÃO DO MENU LATERAL

}
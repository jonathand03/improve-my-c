/*******************************************************************
 * Lib do display do steve 2.1
 *  @author Francisco Jonathan Lima Drumond
 *   
 * 
 */

#include "display.h"

void IHM::InicializaDisplay(void)
{
    this->init();
    this->setRotation(1);
    this->fillScreen(BRANCO);
    this->TelaMenuInicial();

}

void IHM::TelaMenuInicial(void)
{
    this->fillRect(80,0,LarguraDisplay,AlturaDisplay,AZUL); // FUNÇÃO DA TELA DISPONIVEL
    this->fillRect(0,0,80,240,PRETO); // FUNÇÃO DO MENU LATERAL
    this->setTextSize(2);
    this->setTextFont(4);
    this->setTextColor(BRANCO);
    //this->fillRoundRect(100,15,200,60,10,BRANCO);
   // this->setTextColor(PRETO);
    this->drawString("Status",132,20);
    this->drawString("Angulo",132,96,4);
    this->drawString("Ciclo",132,172,4);
}



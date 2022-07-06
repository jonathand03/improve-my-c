/*******************************************************************
 * Lib do display do steve 2.1
 *  @author Francisco Jonathan Lima Drumond
 *   
 * 
 */

#include "display.h"
/*

  
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
*/

const char *op_menu_sc[4] =
    {
        MENU_SC_OP_0,
        MENU_SC_OP_1,
        MENU_SC_OP_2,
        MENU_SC_OP_3};

void IHM::InicializaDisplay(void)
{
    this->init();
    this->setRotation(1);
    this->fillScreen(BRANCO);

    int32_t largura_atual = 80;
    int32_t altura_atual = 240;

    this->fillRect(80, 0, LarguraDisplay, AlturaDisplay, AZUL); // FUNÇÃO DA TELA DISPONIVEL
    this->fillRect(0, 0, largura_atual, altura_atual, PRETO);   // FUNÇÃO DO MENU LATERAL

    this->fillRect(0,0,80,80,BRANCO);
    this->fillRect(0,81,80,80,BRANCO);
    this->fillRect(0,162,80,80,BRANCO);

    this->PassaPorcimaAjuste();
}

void IHM::TelaMenuInicial(void)
{

int opcao_atual = 0;
    if (opcao_atual == 0)
    {
        this->fillRect(0,161,80,80,BRANCO);
        this->fillRect(0,0,80,80,TFT_GREEN);
    }
    if (opcao_atual == 1)
    {
        this->fillRect(0,0,80,79,BRANCO);
        this->fillRect(0,81,80,79,TFT_GREEN);
    }
    if (opcao_atual == 2)
    {
        this->fillRect(0,81,80,79,BRANCO);
        this->fillRect(0,162,80,80,TFT_GREEN);
    }
    else
    {
        //eror
    }
}

void IHM::NavegacaoMenu(void)
{
    int opcao_atual = 0;
    int opcao_anterior = 0;
    int pagina_atual = 0;

    if(opcao_atual != opcao_anterior)
    {
        if(pagina_atual == 0)
        {
            this->StatusInicial();
        }
        if(pagina_atual == 1)
        {
            this->TelaMenuInicial();
        }
        if(pagina_atual == 2)
        {
            this->TelaMenuSC();
        }
        if(pagina_atual == 3)
        {
            this->TelaMenuAjustes();
        }
    }
}

void IHM::TelaAngulo(void)
{
    int32_t largura_atual = 80;
    int32_t altura_atual = 240;

    this->fillRect(80, 0, LarguraDisplay, AlturaDisplay, AZUL); // FUNÇÃO DA TELA DISPONIVEL
    this->fillRect(0, 0, largura_atual, altura_atual, PRETO);   // FUNÇÃO DO MENU LATERAL
    this->fillRect(80, 250, 200, 30, BRANCO);
}

void IHM::TelaElevacao(int curso)
{
    
    this->setTextSize(2);
    this->setTextFont(4);
    this->setTextColor(BRANCO);
    this->drawString("Elevacao", 100, 20);

    if (curso == 200)
    {
        this->setTextSize(1);
        this->drawString("Concluido", 100, 150);
    }
    ProgressoBarra(curso);
}

void IHM::ProgressoBarra(int value)
{
    this->fillRect(100, 180, 200, 40, BRANCO);
    this->fillRect(100, 180, value, 40, TFT_GREEN);

    /* Sinalizadores de inicio e fim de percurso
    if (value == 200)
    {
    }
    if (value == 20)
    {
    }*/
}

void IHM::PassaPorcimaSC(void)
{
    this->setTextSize(2);
    this->setTextFont(4);
    this->setTextColor(BRANCO);
    
    this->drawString(op_menu_sc[0],132,20);
    this->drawString(op_menu_sc[1],132,96,4);
    this->drawString(op_menu_sc[2],132,172,4);
}

void IHM::PassaPorcimaAjuste(void)
{
    this->setTextSize(2);
    this->setTextFont(4);
    this->setTextColor(BRANCO);
    this->fillTriangle(90,20,120,40,90,60,BRANCO);
    this->drawString(MENU_AJUSTE_OP_0,132,20);
    this->drawString(MENU_AJUSTE_OP_1,132,96,4);
    this->drawString(MENU_AJUSTE_OP_2,132,172,4);
}
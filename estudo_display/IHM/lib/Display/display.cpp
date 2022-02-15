/*******************************************************************
 * Lib do display do steve 2.1
 *  @author Francisco Jonathan Lima Drumond
 *   
 * 
 */

#include "display.h"
#include "botao.h"
#include "display_logica.h"

const char *op_menu_sc[5] =
{
    MENU_SC_OP_0,
    MENU_SC_OP_1,
    MENU_SC_OP_2,
    MENU_SC_OP_3,
    MENU_OP_SAIR

};

void IHM::InicializaDisplay(void)
{
    this->init();
    this->setRotation(1);
    this->fillScreen(BRANCO);

    int32_t largura_atual = 80;
    int32_t altura_atual = 240;

    this->fillRect(80, 0, LarguraDisplay, AlturaDisplay, AZUL); // FUNÇÃO DA TELA DISPONIVEL
    this->fillRect(0, 0, largura_atual, altura_atual, BRANCO);   // FUNÇÃO DO MENU LATERAL

    this->fillRect(0,0,80,80,PRETO);
    this->fillRect(0,81,80,80,PRETO);
    this->fillRect(0,162,80,80,PRETO);

    this->TelaMenuInicial();
}

void IHM::TelaMenuInicial(void)
{

    if (opcao_atual == 0)
    {
        this->fillRect(0,161,80,80,PRETO);
        this->fillRect(0,0,80,80,BRANCO);
    }
    if (opcao_atual == 1)
    {
        this->fillRect(0,0,80,79,PRETO);
        this->fillRect(0,81,80,79,BRANCO);
    }
    if (opcao_atual == 2)
    {
        this->fillRect(0,81,80,79,PRETO);
        this->fillRect(0,162,80,80,BRANCO);
    }
    else
    {
        //eror
    }
}

void IHM::NavegacaoMenu(void)
{
    if(opcao_atual != opcao_anterior)
    {
        if(pagina_atual == 0)
        {
            this->TelaMenuInicial();
        }

        if(pagina_atual == 1)
        {
            this->TelaMenuSC(opcao_atual);
        }
        if(pagina_atual == 2)
        {
            //this->TelaMenuAjustes();
        }
        if(pagina_atual == 11)
        {
            this->TelaAngulo();
        }
    }
}

void IHM::TelaMenuSC(int op)
{

    this->fillRect(80,0,LarguraDisplay,AlturaDisplay,AZUL); // FUNÇÃO DA TELA DISPONIVEL

    this->setTextSize(2);
    this->setTextFont(4);
    this->setTextColor(BRANCO);

    if(op < 3)
    {
        this->drawString(op_menu_sc[0],132,20);
        this->drawString(op_menu_sc[1],132,96,4);
        this->drawString(op_menu_sc[2],132,172,4);
    }
    else
    {
        this->fillRect(80,0,LarguraDisplay,AlturaDisplay,AZUL);
        this->drawString(op_menu_sc[3],132,20);
        this->drawString(op_menu_sc[4],132,96,4);
    }


    if(op == 0)
    {
        this->fillTriangle(80,10,120,40,80,70,BRANCO);
        this->fillTriangle(80,162,120,192,80,222,AZUL); 
    }
    if(op == 1)
    {
        this->fillTriangle(80,10,120,40,80,70,AZUL);
        this->fillTriangle(80,162,120,192,80,222,AZUL); 
        this->fillTriangle(80,86,120,116,80,146,BRANCO);
    }
    if(op == 2)
    {
        this->fillTriangle(80,86,120,116,80,146,AZUL);
        this->fillTriangle(80,162,120,192,80,222,BRANCO); 
    }
    if(op == 3)
    {
        this->fillTriangle(80,10,120,40,80,70,BRANCO);
        this->fillTriangle(80,162,120,192,80,222,AZUL); 
    }
    if(op == 4)
    {
        this->fillTriangle(80,10,120,40,80,70,AZUL);
        this->fillTriangle(80,86,120,116,80,146,BRANCO);
    }
}

void IHM::TelaAngulo(void)
{
    int32_t largura_atual = 80;
    int32_t altura_atual = 240;

    this->fillRect(80, 0, LarguraDisplay, AlturaDisplay, AZUL); // FUNÇÃO DA TELA DISPONIVEL
    this->setTextSize(2);
    this->setTextColor(BRANCO);
    this->drawString("ANGULO",100,20,4);
    this->setTextSize(4);
    this->drawNumber(angulo_atual,170,80,4); // Alteravel
    ProgressoBarra(angulo_atual*13); // alteravel
}

void IHM::TelaCiclo(void)
{
    int32_t largura_atual = 80;
    int32_t altura_atual = 240;

    this->fillRect(80, 0, LarguraDisplay, AlturaDisplay, AZUL); // FUNÇÃO DA TELA DISPONIVEL
    this->setTextSize(2);
    this->setTextColor(BRANCO);
    this->drawString("CICLO",130,20,4);
    this->setTextSize(4);
    this->drawNumber(10,140,80,4); // Alteravel
    ProgressoBarra(100); // alteravel
}

void IHM::TelaTempo(void)
{
    int32_t largura_atual = 80;
    int32_t altura_atual = 240;

    this->fillRect(80, 0, LarguraDisplay, AlturaDisplay, AZUL); // FUNÇÃO DA TELA DISPONIVEL
    this->setTextSize(2);
    this->setTextColor(BRANCO);
    this->drawString("TEMPO",115,20,4);
    this->setTextSize(3);
    this->drawString("00:30",105,85,4);// Alteravel
    ProgressoBarra(100); // alteravel
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
    this->fillRoundRect(100, 180, 200, 40, 8,BRANCO);
    this->fillRoundRect(100, 180, value, 40,8, TFT_GREEN);

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
    
    this->drawString(op_menu_sc[0],120,20);
    this->drawString(op_menu_sc[1],120,96,4);
    this->drawString(op_menu_sc[2],120,172,4);
}

void IHM::PassaPorcimaAjuste(void)
{
    this->setTextSize(2);
    this->setTextFont(4);
    this->setTextColor(BRANCO);
    this->fillTriangle(90,20,120,40,90,60,BRANCO);
    this->drawString(MENU_AJUSTE_OP_0,120,20);
    this->drawString(MENU_AJUSTE_OP_1,120,96,4);
    this->drawString(MENU_AJUSTE_OP_2,120,172,4);
}
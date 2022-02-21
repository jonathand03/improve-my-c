/*******************************************************************
 * Lib do display do steve 2.1
 *  @author Francisco Jonathan Lima Drumond
 *   
 * 
 */

#include "display.h"
#include "botao.h"
#include "display_logica.h"

/*************** VETORES DE STRING DAS MENSANGES DOS MENUS*************/
/* MENSAGENS DO MENU DO SUPORTE CIRCULATORIO */
const char *op_menu_sc[5] =
{
    MENU_SC_OP_0,
    MENU_SC_OP_1,
    MENU_SC_OP_2,
    MENU_SC_OP_3,
    MENU_OP_SAIR

};
/* NUMERAÇÃO DO TEMPO ATUAL DE 00:30 SEGUNDOS A 03:00 MINUTOS */
const char *tempo_config[6] =
{
    OP_TEMPO_0,
    OP_TEMPO_1,
    OP_TEMPO_2,
    OP_TEMPO_3,
    OP_TEMPO_4,
    OP_TEMPO_5
};

const char *op_menu_ajuste[3] =
{
    MENU_AJUSTE_OP_0,
    MENU_AJUSTE_OP_1,
    MENU_AJUSTE_OP_2
};

bool mostra_op_1 = false;
bool mostra_op_2 = false;
void IHM::InicializaDisplay(void)
{
    this->init();
    this->setRotation(1);
    this->fillScreen(BRANCO);

    this->setTextSize(2);
    this->setTextFont(4);
    this->setTextColor(BRANCO);

    int32_t largura_atual = 80;
    int32_t altura_atual = 240;

    this->fillRect(80, 0, LarguraDisplay, AlturaDisplay, AZUL); // FUNÇÃO DA TELA DISPONIVEL
    this->fillRect(0, 0, largura_atual, altura_atual, BRANCO);   // FUNÇÃO DO MENU LATERAL

    this->fillRect(0,0,80,80,PRETO);
    this->fillRect(0,81,80,80,PRETO);
    this->fillRect(0,162,80,80,PRETO);

    this->TelaMenuInicial();
}


void IHM::NavegacaoMenu(void)
{
    if(opcao_atual != opcao_anterior)
    {
        if(pagina_atual == 0)
        {
            this->TelaMenuInicial();
        }

        else if(pagina_atual == 1)
        {
            this->TelaMenuSC(opcao_atual);
        }
        else if(pagina_atual == 2)
        {
            //this->TelaMenuAjustes();
        }
        else if(pagina_atual == 10)
        {
            this->TelaStatusSC();
        }
        else if(pagina_atual == 11)
        {
            this->TelaAngulo();
        }
        else if(pagina_atual == 12)
        {
            this->TelaCiclo();
        }
        else if(pagina_atual == 13)
        {
            this->TelaTempo();
        }
        else if(pagina_atual == 30)
        {
            this->TelaElevacao(200);
        }
        opcao_anterior = opcao_atual;
    }
}

void IHM::TelaMenuInicial(void)
{

    if (opcao_atual == 0)
    {
        this->fillRect(0,161,80,80,PRETO);
        this->fillRect(0,81,80,79,PRETO);
        this->fillRect(0,0,80,80,BRANCO);
        if(mostra_op_1 == false)
        {
            this->fillRect(80,0,LarguraDisplay,AlturaDisplay,AZUL);
            this->drawString(op_menu_sc[0],132,20);
            this->drawString(op_menu_sc[1],132,96,4);
            this->drawString(op_menu_sc[2],132,172,4);
        }
        mostra_op_1 = true;
        mostra_op_2 = false;

    }
    else if (opcao_atual == 1)
    {
        this->fillRect(0,0,80,80,PRETO);
        this->fillRect(0,81,80,79,BRANCO);
        this->fillRect(0,161,80,80,PRETO);

        if(mostra_op_2 == false)
        {
            this->fillRect(80,0,LarguraDisplay,AlturaDisplay,AZUL);
            this->drawString(op_menu_ajuste[0],120,20);
            this->drawString(op_menu_ajuste[1],120,96,4);
            this->drawString(op_menu_ajuste[2],120,172,4);
        }
        mostra_op_2 = true;
        mostra_op_1 = false;
       
    }
    else if (opcao_atual == 2)
    {
        this->fillRect(0,0,80,80,PRETO);
        this->fillRect(0,81,80,79,PRETO);
        this->fillRect(0,161,80,80,BRANCO);
    }
    else
    {
        //eror
    }
}


void IHM::TelaMenuSC(int op)
{

    this->fillRect(80,0,LarguraDisplay,AlturaDisplay,AZUL); // FUNÇÃO DA TELA DISPONIVEL
    this->fillRect(0,0,80,80,AZUL);
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
    else if(op == 1)
    {
        this->fillTriangle(80,10,120,40,80,70,AZUL);
        this->fillTriangle(80,162,120,192,80,222,AZUL); 
        this->fillTriangle(80,86,120,116,80,146,BRANCO);
    }
    else if(op == 2)
    {
        this->fillTriangle(80,86,120,116,80,146,AZUL);
        this->fillTriangle(80,162,120,192,80,222,BRANCO); 
    }
    else if(op == 3)
    {
        this->fillTriangle(80,10,120,40,80,70,BRANCO);
        this->fillTriangle(80,162,120,192,80,222,AZUL); 
    }
    else if(op == 4)
    {
        this->fillTriangle(80,10,120,40,80,70,AZUL);
        this->fillTriangle(80,86,120,116,80,146,BRANCO);
    }
    else
    {

    }
}

void IHM::TelaStatusSC(void)
{
    this->fillRect(0, 0, 240, 240, AZUL); // FUNÇÃO DA TELA DISPONIVEL
    this->setTextSize(2);
    this->setTextColor(BRANCO);

        this->fillRect(80,160,90,60,AZUL);
        this->fillRect(140,160,60,50,AZUL);
        this->setTextSize(1);
        this->setTextColor(BRANCO);
        this->drawString("SIM",81,160,4);
        this->drawString("NAO",81,160,4);
    if(statusSC == true)
    {
        this->drawString("Ativado",70,20,4);
        this->setTextSize(1);
        this->drawString("Desativar Suporte ?",70,80,4);
    }
    else
    {
        this->setTextSize(2);
        this->drawString("Desativado",35,20,4);
        this->setTextSize(1);
        this->drawString("Ativar Suporte ?",80,100,4);
    }

    if(opcao_atual == 0)
    {   
        this->fillRect(80,160,90,60,BRANCO);
        this->setTextSize(1);
        this->setTextColor(PRETO);
        this->drawString("SIM",81,160,4);
    }
    else if(opcao_atual == 1)
    {
        this->fillRect(140,160,60,50,BRANCO);
        this->setTextSize(1);
        this->setTextColor(PRETO);
        this->drawString("NAO",141,160,4);
    }
    else
    {
        //erro
    }
   
}

int value = 5;
void IHM::TelaAngulo(void)
{
    this->fillRect(80, 0, LarguraDisplay, AlturaDisplay, AZUL); // FUNÇÃO DA TELA DISPONIVEL
    this->setTextSize(2);
    this->setTextColor(BRANCO);
    this->drawString("ANGULO",100,20,4);
    this->setTextSize(4);
    
    if(angulo_atual < 10)
    {
        this->drawNumber(angulo_atual,170,80,4); 
    }
    else
    {
        this->drawNumber(angulo_atual,140,80,4); 
    }
    int progresso = (angulo_atual-value)*20;
    ProgressoBarra(progresso); 
}

void IHM::TelaCiclo(void)
{
    this->fillRect(80, 0, LarguraDisplay, AlturaDisplay, AZUL); // FUNÇÃO DA TELA DISPONIVEL
    this->setTextSize(2);
    this->setTextColor(BRANCO);
    this->drawString("CICLO",130,20,4);
    this->setTextSize(4);
    if(ciclo_atual < 10)
        this->drawNumber(ciclo_atual,170,80,4); 
    else
        this->drawNumber(ciclo_atual,140,80,4); 
   
    ProgressoBarra((ciclo_atual-value)*40); 
}

void IHM::TelaTempo(void)
{
    this->fillRect(80, 0, LarguraDisplay, AlturaDisplay, AZUL); // FUNÇÃO DA TELA DISPONIVEL
    this->setTextSize(2);
    this->setTextColor(BRANCO);
    this->drawString("TEMPO",115,20,4);
    this->setTextSize(3);
    this->drawString(tempo_config[tempo_atual],105,85,4); 
    ProgressoBarra((tempo_atual*40)); 
}

void IHM::TelaElevacao(int curso)
{
    this->fillRect(80, 0, LarguraDisplay, AlturaDisplay, AZUL); // FUNÇÃO DA TELA DISPONIVEL
    this->setTextSize(2);
    this->setTextFont(4);
    this->setTextColor(BRANCO);
    if(elevacao == true)
    {
        this->drawString("Elevacao", 100, 20);
    }
    else
    {
        this->drawString("Recuo", 130, 20);
    }

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
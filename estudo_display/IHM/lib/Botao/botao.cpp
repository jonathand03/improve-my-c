#include "botao.h"
#include "display_logica.h"

//!< Variaveis e flag dos botões 
int QTD_BT = 0;
volatile int estado_botoes_ihm[QTD_BT_IHM] = {desligado, desligado, desligado, desligado,desligado};
volatile int estado_bt_anterior[QTD_BT_IHM] = {desligado, desligado, desligado, desligado,desligado};

volatile int opcao_atual = 0;
volatile int opcao_anterior = -1;
volatile int pagina_atual = 0;
int limite_inf = 2;

bool elevacao = false;
bool statusSC = false;

void IRAM_ATTR InterrruptFlagBtBaixo()
{
    estado_botoes_ihm[bt_baixo] = ligado;
}

void IRAM_ATTR InterrruptFlagBtCima()
{
    estado_botoes_ihm[bt_cima] = ligado;
}

void IRAM_ATTR InterrruptFlagBtEnter()
{ 
    estado_botoes_ihm[bt_enter] = ligado;
}

void IRAM_ATTR InterrruptFlagBtStandup()
{
    estado_botoes_ihm[bt_standup] = ligado;
}

void IRAM_ATTR InterrruptFlagBtPanico()
{
    estado_botoes_ihm[bt_panico] = ligado;
}

void evento_enter(void)
{
    if(pagina_atual == 0)
    {
        switch (opcao_atual)
        {
            case 0: // caso esteja na opcao SC
                pagina_atual = 1; // pagina do SC
                limite_inf = 4;
                opcao_atual = 0;
                opcao_anterior = -1;
                break;
            case 1: // caso esteja na opcao ajustes
                limite_inf= 3;
                pagina_atual = 2; // pagina ajustes
                break;
            case 2: // caso esteja na opção status
                pagina_atual = 3; // pagina status
                break;
        }
      
    }
    else if(pagina_atual == 1) // se a pagina for do Suporte circulatorio
    {
        switch (opcao_atual)
        {
            case 0:
                pagina_atual = 10;
                opcao_atual = 0;
                opcao_anterior = -1;
                limite_inf = 1; // da o limite inferior de 1 para opção de sim ou nao
                break;
            case 1:
                pagina_atual = 11;
                opcao_atual = 0;
                opcao_anterior = -1;
                break;
            case 2:
                pagina_atual = 12;
                opcao_atual = 0;
                opcao_anterior = -1;
                break;
            case 3:
                pagina_atual = 13;
                opcao_atual = 0;
                opcao_anterior = -1;
                break;
            case 4:
                pagina_atual = 0;
                opcao_anterior = -1;
                opcao_atual = 0;
                break;
        }
    }
    else if(pagina_atual == 2) // Se pagina de ajustes
    {
        switch (opcao_atual)
        {
             case 0: // Se assento
                pagina_atual = 20;
                limite_inf = 1;
                break;
            case 1: // se Encosto
                pagina_atual = 21;
                break;
            case 2: // se suporte
                pagina_atual = 22;
                break;
            case 3: // se sair
                pagina_atual = 23;
                break;
        }
       
    }
    else if(pagina_atual == 10) // status
    {
       switch (opcao_atual)
       {
            case 0:
                statusSC = !statusSC;
                pagina_atual = 1;
                opcao_atual = 0;
                opcao_anterior = -1;
                break;
            case 1:
                pagina_atual = 1;
                opcao_atual = 0;
                opcao_anterior = -1;
                break;
       }
    }
    else if(pagina_atual == 11) // angulo
    {
        pagina_atual = 1;
        opcao_atual = 1;
        opcao_anterior = -1;
    }
    else if(pagina_atual == 12) // ciclo
    {
        pagina_atual = 1;
        opcao_atual = 2;
        opcao_anterior = -1;
    }
    else if(pagina_atual == 13) // tempo
    {
        pagina_atual = 1;
        opcao_atual = 3;
        opcao_anterior = -1;
    }
    else
    {
        //nothing
    }
}

//!< Criando uma estrutura para suportar todas as funções de interrupção e anular os IFS no Construtor */
typedef void (*FunctionVector)(void);    
//!< Criando um vetor de funções baseados na estrutura criada anteriormente */
FunctionVector StateFunction[QTD_BT_IHM] = {&InterrruptFlagBtBaixo, &InterrruptFlagBtCima,
                                  &InterrruptFlagBtEnter,&InterrruptFlagBtStandup,
                                  &InterrruptFlagBtPanico};

//!< Inicializando botão utilizando interrupção de hardware 
Button::Button(int pin, int edge)
{
    pinMode(pin,INPUT);
    attachInterrupt(pin,StateFunction[QTD_BT],edge);
    this->ButtonStatus.ButtonID = QTD_BT;
    this->ButtonStatus.ButtonEdge = edge;
    this->ButtonStatus.ButtonPin = pin;
    QTD_BT++;
}

//!< Ativando Botão caso ele tenha sido parado anteriormente 
uint8_t Button::ResumeButton(void)
{
    //!< Verifica se o botão foi parado anteriormente. Caso sim, realoca a interrupção no pino 
    if(this->ButtonStatus.BtStopped == true)
    {
        attachInterrupt(this->ButtonStatus.ButtonPin,
                        StateFunction[this->ButtonStatus.ButtonID],
                        this->ButtonStatus.ButtonEdge);
        this->ButtonStatus.BtWorking = true;
        this->ButtonStatus.BtStopped = false;
        return 0;
    }
    else
    {
        return 1;
    }
   
}

void  Button::isPressed(int botao_acionado)
{
    if (estado_botoes_ihm[botao_acionado] == ligado)
    {
        estado_bt_anterior[botao_acionado] == desligado ? 
                                              this->ButtonStatus.BtOn = true : 
                                              this->ButtonStatus.BtStayOn = true;
    }
    else
    {
       estado_bt_anterior[botao_acionado] == desligado ?
                                             this->ButtonStatus.BtStayOff = true :
                                             this->ButtonStatus.BtOff = true; 
    }
    estado_bt_anterior[botao_acionado] = estado_botoes_ihm[botao_acionado];
    estado_botoes_ihm[botao_acionado] = desligado;
}

//!<Pausa a interrupção do botão 
uint8_t Button::StopButton(void)
{
    if (QTD_BT <= 0)
    {
        return 1;
    }
    else
    {
        detachInterrupt(this->ButtonStatus.ButtonPin);
        this->ButtonStatus.BtStopped = true;
        this->ButtonStatus.BtWorking = false;
        return 0;
    }
}

int Button::ReadButton(void)
{
    this->isPressed(this->ButtonStatus.ButtonID);
    if(this->ButtonStatus.BtOn == true)
    {
        if(this->ButtonStatus.ButtonID == bt_baixo)
        {
            
            switch (pagina_atual)
            {
                case 0: // se  for a pagina inicial
                    NavegacaoPagina(2,bt_baixo);
                    break;
                case 1: // se for a pagina do suporte circulatorio
                    NavegacaoPagina(4,bt_baixo);
                    break;
                case 2: // se for a pagina de ajustes
                    NavegacaoPagina(2,bt_baixo);
                    break;
                case 10: // se for a pagina de status do SC
                    NavegacaoPagina(1,bt_baixo);
                    break;
                case 11: // se for a pagina do angulo
                    AlteraAnguloBaixo();
                    break;
                case 12: // se for a pagina do ciclo
                    AlteraCicloBaixo();
                    break;
                case 13: // se for a pagina do tempo
                    AlteraTempoBaixo();
                    break;
                case 21: // se for a pagina de ajuste do assento
                    AjusteAssentoHorizontal(bt_baixo,this);
                    break;
            }
        }
        else if(this->ButtonStatus.ButtonID == bt_cima)
        {
            switch (pagina_atual)
            {
                case 0: // se  for a pagina inicial
                    NavegacaoPagina(2,bt_cima);
                    break;
                case 1: // se for a pagina do suporte circulatorio
                    NavegacaoPagina(4,bt_cima);
                    break;
                case 2: // se for a pagina de ajustes
                    NavegacaoPagina(2,bt_cima);
                    break;
                case 10:
                    NavegacaoPagina(1,bt_cima);
                    break;
                case 11:
                    AlteraAnguloCima();
                    break;
                case 12:
                    AlteraCicloCima();
                    break;
                case 13:
                    AlteraTempoCima();
                    break;
                case 21:
                    AjusteAssentoHorizontal(bt_cima,this);
                    break;
            }
        }
        else if(this->ButtonStatus.ButtonID ==  bt_enter)
        {
            evento_enter();
        }
        else if(this->ButtonStatus.ButtonID == bt_standup)
        {
            pagina_atual = 30;
            opcao_atual = 0;
            opcao_anterior = -1;
            elevacao = !elevacao;
        }
    }
    this->ButtonStatus.BtOn = false;
    this->ButtonStatus.BtStayOff = false;
    this->ButtonStatus.BtStayOn = false;
    this->ButtonStatus.BtOff = false;
    return 0;
}
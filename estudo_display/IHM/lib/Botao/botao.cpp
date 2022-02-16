#include "botao.h"

//!< Variaveis e flag dos botões 
int QTD_BT = 0;
volatile int estado_botoes_ihm[QTD_BT_IHM] = {desligado, desligado, desligado, desligado,desligado};
volatile int estado_bt_anterior[QTD_BT_IHM] = {desligado, desligado, desligado, desligado,desligado};

int opcao_atual = 0;
int opcao_anterior = -1;
int pagina_atual = 0;
int limite_inf = 2;

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
                limite_inf = 4;
                pagina_atual = 1; // pagina do SC
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
    if(pagina_atual == 1) // se a pagina for do Suporte circulatorio
    {
       switch (opcao_atual)
       {
            case 0: // se Status SC
                pagina_atual = 10;
                limite_inf = 1;
                break;
            case 1: // se Angulo
                pagina_atual = 11;
                break;
            case 2: // se ciclo
                pagina_atual = 12;
                break;
            case 3: // se Tempo
                pagina_atual = 13;
                break;
            case 4: // se Sair
                pagina_atual = 0;
                opcao_anterior = -1;
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
        QTD_BT++;
        return 0;
    }
    else
    {
        return 1;
    }
   
}

bool  Button::verifica_botao_pressionado(e_botao botao_acionado)
{
    delay(150);

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
    return true;
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
        QTD_BT--;
        return 0;
    }
}

int Button::ReadButton(void)
{
        bool verifica_bt = this->ButtonStatus.BtOn;
        if(verifica_bt == true)
        {
            opcao_atual == limite_inf ? opcao_atual = 0 : opcao_atual++;
            this->ButtonStatus.BtOn = false;
        }
        else
        {
            return 1;
        }   
}
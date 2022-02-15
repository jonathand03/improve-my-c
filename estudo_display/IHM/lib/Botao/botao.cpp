#include "botao.h"


int QTD_BT = -1;
volatile int estado_botoes_ihm[qtd_bt_ihm] = {desligado, desligado, desligado, desligado,desligado};
volatile int estado_bt_anterior[qtd_bt_ihm] = {desligado, desligado, desligado, desligado,desligado};

int opcao_atual = 0;
int opcao_anterior = -1;
int pagina_atual = 0;
int limite_inf = 2;
estado_botao verifica_botao_pressionado(e_botao botao_acionado)
{
    delay(150);
    estado_botao status_atual_verificao = desligado;

    if (estado_botoes_ihm[botao_acionado] == ligado)
    {
        if (estado_bt_anterior[botao_acionado] == desligado)

            status_atual_verificao = ligado; // retorna ligado
        else
            status_atual_verificao = continua_ligado; // retorna mantendo ligado
    }
    else
    {
        if (estado_bt_anterior[botao_acionado] == desligado)
            status_atual_verificao = continua_desligado; // retorna mantendo desligado
        else
            status_atual_verificao = desligado; // retorna desligando
    }
    estado_bt_anterior[botao_acionado] = estado_botoes_ihm[botao_acionado];
    estado_botoes_ihm[botao_acionado] = desligado;
    return status_atual_verificao;
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

/* Inicializando botão utilizando interrupção de hardware */
Button::Button(int pin, int edge)
{
    if (QTD_BT == -1) // entra aqui primeira vez
    {
        pinMode(pin,INPUT);
        attachInterrupt(pin, InterrruptFlagBtBaixo, FALLING);
       
    }
    
    if(QTD_BT == 0)
    {
        pinMode(pin,INPUT);
        attachInterrupt(pin, InterrruptFlagBtCima, edge);
       // ButtonStatus.ButtonID = QTD_BT+1;
    }
    if(QTD_BT == 1)
    {
        pinMode(pin,INPUT);
        attachInterrupt(pin, InterrruptFlagBtEnter, edge);
        //ButtonStatus.ButtonID = QTD_BT+1;
    }
    if(QTD_BT == 2)
    {
        pinMode(pin,INPUT);
        attachInterrupt(pin, InterrruptFlagBtStandup, edge);
       // ButtonStatus.ButtonID = QTD_BT+1;
    }
    if(QTD_BT == 3)
    {
        pinMode(pin,INPUT);
        attachInterrupt(pin, InterrruptFlagBtPanico, edge);
       // ButtonStatus.ButtonID = QTD_BT+1;
    }
    QTD_BT++;
    ButtonStatus.ButtonID  = QTD_BT;
    ButtonStatus.ButtonEdge = edge;
    ButtonStatus.ButtonPin = pin;
}

uint8_t Button::ResumeButton(void)
{
   if(ButtonStatus.BtStopped == true)
   {
       // attachInterruptArg(ButtonStatus.ButtonPin, InterrruptFlag, (void *)ButtonStatus.ButtonID,  ButtonStatus.ButtonEdge);
        return 0;
   }
   else
   {
       return 1;
   }
   
}extern long tempo_ant ;
extern long tempo_atual;


/* Pausa a interrupção do botão */
uint8_t Button::StopButton(void)
{
    if (QTD_BT <= 0)
    {
        //Serial.print("Impossivel parar o botão pois não existe nenhum botão cadastrado");
        return 1;
    }
    else
    {
        esp_err_t STATUS;
        STATUS = gpio_isr_handler_remove((gpio_num_t)ButtonStatus.ButtonPin);
        if (STATUS == ESP_OK)
        {
            ButtonStatus.BtStopped = true;
            return 0;
        }
        else
        {
           // Serial.print("Erro ao pausar o botão");
            return 1;
        }
    }
}

int Button::ReadButton(void)
{
    if(ButtonStatus.ButtonID == bt_baixo )
    {
        int verifica_bt = verifica_botao_pressionado(bt_baixo);
        if(verifica_bt == ligado)
        {
            if(opcao_atual == limite_inf)
                opcao_atual = 0;
            else
                opcao_atual++;
        }
    }
    if(ButtonStatus.ButtonID == bt_cima)
    {
        int verifica_bt = verifica_botao_pressionado(bt_cima);
        if(verifica_bt == ligado)
        {
            if(opcao_atual == 0)
                opcao_atual = limite_inf;
            else
                opcao_atual--;
           
        }
    }
    if(ButtonStatus.ButtonID == bt_enter)
    {
        int verifica_bt = verifica_botao_pressionado(bt_enter);
        if(verifica_bt == ligado)
        {
            evento_enter();
        }
    }
    return 0;
    
}
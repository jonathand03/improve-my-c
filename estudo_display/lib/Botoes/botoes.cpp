#include "botoes.h"


int QTD_BT = -1;
int estado_botoes_ihm[qtd_bt_ihm] = {desligado, desligado, desligado, desligado,desligado};
int estado_bt_anterior[qtd_bt_ihm] = {desligado, desligado, desligado, desligado,desligado};

int opcao_atual = 0;
int opcao_anterior = 0;
int pagina_atual = 0;

estado_botao verifica_botao_pressionado(int botao_acionado)
{
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

void IRAM_ATTR InterrruptFlagBtBaixo(void)
{
    estado_botoes_ihm[0] = ligado;
}

void IRAM_ATTR InterrruptFlagBtCima(void)
{
    estado_botoes_ihm[1] = ligado;
}

void IRAM_ATTR InterrruptFlagBtEnter(void)
{ 
    estado_botoes_ihm[2] = ligado;
}

void IRAM_ATTR InterrruptFlagBtStandup(void)
{
    estado_botoes_ihm[3] = ligado;
}

void IRAM_ATTR InterrruptFlagBtPanico(void)
{
    estado_botoes_ihm[4] = ligado;
}

/* Inicializando botão utilizando interrupção de hardware */
Button::Button(int pin, int edge)
{
    if (QTD_BT == -1) // entra aqui primeira vez
    {
        pinMode(pin,INPUT);
        attachInterrupt(pin, InterrruptFlagBtBaixo, HIGH);
       
    }
    if(QTD_BT == 0)
    {
        pinMode(pin,INPUT);
        attachInterrupt(pin, InterrruptFlagBtCima, HIGH);
       // ButtonStatus.ButtonID = QTD_BT+1;
    }
    if(QTD_BT == 1)
    {
        pinMode(pin,INPUT);
        attachInterrupt(pin, InterrruptFlagBtEnter, HIGH);
        //ButtonStatus.ButtonID = QTD_BT+1;
    }
    if(QTD_BT == 2)
    {
        pinMode(pin,INPUT);
        attachInterrupt(pin, InterrruptFlagBtStandup, HIGH);
       // ButtonStatus.ButtonID = QTD_BT+1;
    }
    if(QTD_BT == 3)
    {
        pinMode(pin,INPUT);
        attachInterrupt(pin, InterrruptFlagBtPanico, HIGH);
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
   
}


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
    int verifica_bt = verifica_botao_pressionado(ButtonStatus.ButtonID);
    if(verifica_bt == ligado || verifica_bt == continua_ligado)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}
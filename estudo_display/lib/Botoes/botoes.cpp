#include "botoes.h"


int QTD_BT = 0;
extern int estado_botoes_ihm[qtd_bt_ihm] = {desligado, desligado, desligado, desligado};
extern int estado_bt_anterior[qtd_bt_ihm] = {desligado, desligado, desligado, desligado};


void InterrruptFlag(void *args)
{
    int bt = (int )args;
    estado_botoes_ihm[bt] = ligado;
}

/* Inicializando botão utilizando interrupção de hardware */
Button::Button(int pin, int edge)
{
    if (QTD_BT == 0) // entra aqui primeira vez
    {
        attachInterruptArg(pin, InterrruptFlag, (void *)QTD_BT, edge);
        ButtonStatus.ButtonID  = QTD_BT;
        Serial.print(QTD_BT);
    }
    else
    {
        attachInterruptArg(pin, InterrruptFlag, (void *)QTD_BT+1, edge);
        ButtonStatus.ButtonID = QTD_BT+1;
    }
    QTD_BT++;
    ButtonStatus.ButtonEdge = edge;
    ButtonStatus.ButtonPin = pin;
    Serial.print( ButtonStatus.ButtonPin);
    Serial.print(ButtonStatus.ButtonEdge);
    
}

uint8_t Button::ResumeButton(void)
{
   if(ButtonStatus.BtStopped == true)
   {
        attachInterruptArg(ButtonStatus.ButtonPin, InterrruptFlag, (void *)ButtonStatus.ButtonID,  ButtonStatus.ButtonEdge);
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
        Serial.print("Impossivel parar o botão pois não existe nenhum botão cadastrado");
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
            Serial.print("Erro ao pausar o botão");
            return 1;
        }
    }
}

estado_botao Button::ReadButton(void)
{
    estado_botao status_atual_verificao = desligado;

    if (estado_botoes_ihm[ButtonStatus.ButtonID] == ligado)
    {
        if (estado_bt_anterior[ButtonStatus.ButtonID] == desligado)

            status_atual_verificao = ligado; // retorna ligado
        else
            status_atual_verificao = continua_ligado; // retorna mantendo ligado
    }
    else
    {
        if (estado_bt_anterior[ButtonStatus.ButtonID] == desligado)
            status_atual_verificao = continua_desligado; // retorna mantendo desligado
        else
            status_atual_verificao = desligado; // retorna desligando
    }
    estado_bt_anterior[ButtonStatus.ButtonID] = estado_botoes_ihm[ButtonStatus.ButtonID];
    estado_botoes_ihm[ButtonStatus.ButtonID] = desligado;
    return status_atual_verificao;
}

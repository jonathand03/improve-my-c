#include "botoes.hpp"

enum estado_botao
{
  desligado,
  ligado,
  continua_desligado,
  continua_ligado
};
enum teclas_menu
{
    bt_baixo,
    bt_cima,
    bt_enter,
    bt_standup,
    bt_panico
};
int tecla = 0;
int estado_botoes_ihm[4] = {desligado,desligado,desligado,desligado};
int estado_bt_anterior[4] = {desligado,desligado,desligado,desligado};

void InterrruptFlag(void *args)
{
  int bt = (int) args;
  estado_botoes_ihm[bt] = ligado;
}


estado_botao leitura_botao(teclas_menu tecla)
{

}


/* Inicializando botão sem utilizar interrupção de hardware */
Button::Button(int pin)
{
   pinMode(pin,INPUT);
}

/* Inicializando botão utilizando interrupção de hardware */
Button::Button(int pin, gpio_int_type_t edge, void (*fn)())
{
        ButtonPin = pin;
        esp_err_t DRIVER_INSTALL_RETURN;
        esp_err_t INTR_TYPE_RETURN;
        esp_err_t ENABLE_INTR_RETURN;
        esp_err_t INTR_ADD_RETURN;
        esp_err_t SIGNAL_PIN_RETURN;

        DRIVER_INSTALL_RETURN = gpio_install_isr_service(0);
        INTR_TYPE_RETURN      = gpio_set_intr_type((gpio_num_t)pin, edge);
        ENABLE_INTR_RETURN    = gpio_intr_enable((gpio_num_t)pin);
        INTR_ADD_RETURN       = gpio_isr_handler_add((gpio_num_t)pin, (gpio_isr_t)InterrruptFlag, (void *) 1); // TODO
        SIGNAL_PIN_RETURN     = gpio_set_direction((gpio_num_t)pin, GPIO_MODE_INPUT);

        if(DRIVER_INSTALL_RETURN != ESP_OK) {Serial.println("Erro ao instalar o Driver de interrupcao");}
        if(INTR_TYPE_RETURN != ESP_OK)      {Serial.println("Erro ao inicializar o tipo de interrupcao no pino");}
        if(ENABLE_INTR_RETURN != ESP_OK)    {Serial.println("Erro ao ativar a interrupção no pino");}
        if(INTR_ADD_RETURN != ESP_OK)       {Serial.println("Erro ao adicionar a interrupção no pino");}
        if(SIGNAL_PIN_RETURN != ESP_OK)     {Serial.println("Erro ao adicionar o modo de operação do pino");}
}



uint8_t Button::ResumeButton(void)
{

    /* TODO
        VERIFICAR O BOTÃO DA CLASSE E ATUALIZAR O ARGUMENTO DO ADD INTR HANDLER
    */
        esp_err_t DRIVER_INSTALL_RETURN;
        esp_err_t INTR_TYPE_RETURN;
        esp_err_t ENABLE_INTR_RETURN;
        esp_err_t INTR_ADD_RETURN;
        esp_err_t SIGNAL_PIN_RETURN;

        DRIVER_INSTALL_RETURN = gpio_install_isr_service(0);
        INTR_TYPE_RETURN      = gpio_set_intr_type((gpio_num_t)ButtonPin, GPIO_INTR_HIGH_LEVEL);
        ENABLE_INTR_RETURN    = gpio_intr_enable((gpio_num_t)ButtonPin);
        INTR_ADD_RETURN       = gpio_isr_handler_add((gpio_num_t)ButtonPin, (gpio_isr_t)InterrruptFlag, (void *) 1);
        SIGNAL_PIN_RETURN     = gpio_set_direction((gpio_num_t)ButtonPin, GPIO_MODE_INPUT);

        if(DRIVER_INSTALL_RETURN != ESP_OK) {Serial.println("Erro ao instalar o Driver de interrupcao");}
        if(INTR_TYPE_RETURN != ESP_OK)      {Serial.println("Erro ao inicializar o tipo de interrupcao no pino");}
        if(ENABLE_INTR_RETURN != ESP_OK)    {Serial.println("Erro ao ativar a interrupção no pino");}
        if(INTR_ADD_RETURN != ESP_OK)       {Serial.println("Erro ao adicionar a interrupção no pino");}
        if(SIGNAL_PIN_RETURN != ESP_OK)     {Serial.println("Erro ao adicionar o modo de operação do pino");}
}

uint8_t Button::StopButton(void)
{
    gpio_isr_handler_remove((gpio_num_t)ButtonPin);
}



/*
    TODO: FAZER UMA VARIAVEL QUE SALVA O ESTADO DO BOTÃO NA INTERRUPÇÃO PARA CADA PINO ADICIONADO [TECLAS]
*/
estado_botao Button::ReadButton(void)
{
    estado_botao status_atual_verificao = desligado;

    if (estado_botoes_ihm[tecla] == ligado)
    {
        if (estado_bt_anterior[tecla] == desligado)

            status_atual_verificao = ligado; // retorna ligado
        else
            status_atual_verificao = continua_ligado; // retorna mantendo ligado
    }
    else
    {
        if (estado_bt_anterior[tecla] == desligado)
            status_atual_verificao = continua_desligado; // retorna mantendo desligado
        else
            status_atual_verificao = desligado; // retorna desligando
    }
    estado_bt_anterior[tecla] = estado_botoes_ihm[tecla];
    estado_botoes_ihm[tecla] = desligado;
    return status_atual_verificao;
}


#include <Arduino.h>
#include "TFT_eSPI.h"
#include <driver/gpio.h>

TFT_eSPI Display = TFT_eSPI();


uint8_t BUTTON_SIZE = 0;

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

int estado_botoes_ihm[4] = {desligado,desligado,desligado,desligado};
int estado_bt_anterior[4] = {desligado,desligado,desligado,desligado};

void InterrruptFlag(void *args)
{
  int bt = (int) args;
  estado_botoes_ihm[bt] = ligado;
}


estado_botao leitura_botao(teclas_menu tecla)
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



int inicializa(int pin ,gpio_int_type_t edge)
{
        esp_err_t DRIVER_INSTALL_RETURN;
        esp_err_t INTR_TYPE_RETURN;
        esp_err_t ENABLE_INTR_RETURN;
        esp_err_t INTR_ADD_RETURN;
        esp_err_t SIGNAL_PIN_RETURN;

        DRIVER_INSTALL_RETURN = gpio_install_isr_service(0);
        INTR_TYPE_RETURN      = gpio_set_intr_type((gpio_num_t)pin, edge);
        ENABLE_INTR_RETURN    = gpio_intr_enable((gpio_num_t)pin);
        INTR_ADD_RETURN       = gpio_isr_handler_add((gpio_num_t)pin, (gpio_isr_t)InterrruptFlag, (void *) 1);
        SIGNAL_PIN_RETURN     = gpio_set_direction((gpio_num_t)pin, GPIO_MODE_INPUT);

        if(DRIVER_INSTALL_RETURN != ESP_OK) {return -1;}
        if(INTR_TYPE_RETURN != ESP_OK)      {return -1;}
        if(ENABLE_INTR_RETURN != ESP_OK)    {return -1;}
        if(INTR_ADD_RETURN != ESP_OK)       {return -1;}
        if(SIGNAL_PIN_RETURN != ESP_OK)     {return -1;}
        return 0;
}

void remove_interrupcao(int pin)
{
  gpio_isr_handler_remove((gpio_num_t)pin);
}


void setup()
{
  Serial.begin(115200);
  inicializa(23,GPIO_INTR_HIGH_LEVEL);
  inicializa(23,GPIO_INTR_HIGH_LEVEL);
}

void loop()
{
  Serial.print(leitura_botao(bt_baixo));
  Serial.print(leitura_botao(bt_cima));
  Serial.print(leitura_botao(bt_enter));
  Serial.println(leitura_botao(bt_standup));
  delay(500);
}
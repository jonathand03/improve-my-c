#include "botoes.hpp"

#define RETURN_PIN_MASK(pin) ((uint32_t)1 << pin)
#define PIN_ISR(pin) ((gpio_num_t)pin)
#define SET_FLAG(pin,vetor) (vetor[pin] = 1)

uint8_t BUTTON_SIZE = 0;

typedef struct
{
    bool IsStopped;
    bool IsTrashed;
}STATUS_BUTTON;


void IRAM_ATTR InterrruptFlag(register void *args)
{
   register uint8_t atualizador_flag = 1;
}

/* Inicializando botão sem utilizar interrupção de hardware */
Button::Button(int pin, int edge)
{
     /* FLAGS DE DEBUG */
    esp_err_t CONFIG_RETURN;
    /*Configurando a porta com ESP-IDF */
    gpio_config_t ButtonCofing; //!< Cria uma estrutura para configuração do botão
    ButtonCofing.pin_bit_mask = RETURN_PIN_MASK(pin); //!< Mascara de bit do pino
    ButtonCofing.mode = GPIO_MODE_INPUT; //!< Configurando o modo do pino como INPUT
    CONFIG_RETURN = gpio_config(&ButtonCofing); //!< Configura o Button com seus parametros definidos
    CONFIG_RETURN == ESP_OK ? Serial.print("CONFIG SUCESS") : Serial.print("FAIL TO CONFIG"); //!< Retorno na serial para debug
    BUTTON_SIZE ++;
}

/* Inicializando botão utilizando interrupção de hardware */
Button::Button(int pin, int edge, void (*fn)())
{
    /* FLAGS DE DEBUG */
    esp_err_t CONFIG_RETURN, ISR_HANDLER_RETURN , ISR_SERVICE_RETURN;
    /* Configurando a porta com ESP-IDF */
    gpio_config_t ButtonCofing; //!< Cria uma estrutura para configuração do botão
    ButtonCofing.pin_bit_mask = RETURN_PIN_MASK(pin);
    ButtonCofing.intr_type = GPIO_INTR_HIGH_LEVEL; //!< Configurando a borda de interrupção como HIGH
    ButtonCofing.mode = GPIO_MODE_INPUT; //!< Configurando o modo do pino como INPUT
    /* Pin Configuration and Results */
    CONFIG_RETURN =  gpio_config(&ButtonCofing); //!< Configura o Button com seus parametros definidos 
    CONFIG_RETURN == ESP_OK ? Serial.print("CONFIG SUCESS") : Serial.print("FAIL TO CONFIG");
    /* ISR Handler Function Pin and Results */
    ISR_SERVICE_RETURN = gpio_install_isr_service(0); //!< Prepara o esp para gerenciar interrupções por pino
    ISR_SERVICE_RETURN == ESP_OK ? Serial.print("ISR ADDED") : Serial.print("ISR ADDED ERROR");
    ISR_HANDLER_RETURN = gpio_isr_handler_add(PIN_ISR(pin),(gpio_isr_t)fn,NULL); //!< Adiciona a função ao pino
    ISR_HANDLER_RETURN == ESP_OK ? Serial.print("ISR ADDED") : Serial.print("ISR ADDED ERROR");
    BUTTON_SIZE++;
}

uint8_t Button::ReadButton(void)
{

}







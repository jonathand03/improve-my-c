#include "botao.h"
#ifdef BUTTON_ON
#include "esp_intr_alloc.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"
#include "steve_debug.h"



#define ESP_INTR_FLAG_DEFAULT 0
#define DEBUG
bool first_defined_button = false;
// Flags de ativação de cada botão


volatile bool flag_down_button = false;
volatile bool flag_up_button = false;
volatile bool flag_enter_button = false;
volatile bool flag_standup_button = false;

volatile bool previous_flag_down_button = false;
volatile bool previous_flag_up_button = false;
volatile bool previous_flag_enter_button = false;
volatile bool previous_flag_standup_button = false;

volatile bool button_flags[4] =
{
    flag_down_button,
    flag_up_button,
    flag_enter_button,
    flag_standup_button,
};

volatile bool previous_button_flags[4] =
{
    previous_flag_down_button,
    previous_flag_up_button,
    previous_flag_enter_button,
    previous_flag_standup_button,
};

double reading = 0;

gpio_num_t gpio_handle[ButtonSpace::button_type_max] =
{
    GPIO_NUM_25, // baixo
    GPIO_NUM_39, // cima
    GPIO_NUM_34, // enter
    GPIO_NUM_36 // standup
};

double voltage_verify(int button)
{
    int captura_voltage = 0;
    double result;
    switch (button)
    {
        case 25:
            reading = adc2_get_raw(ADC2_CHANNEL_8,ADC_WIDTH_BIT_12,&captura_voltage);
            result = 3.3*(captura_voltage)/4096;
            break;
        case 34:
            reading = adc1_get_raw(ADC1_CHANNEL_6);
            result = 3.3*(reading)/4096;
            break;
        case 36:
            reading = adc1_get_raw(ADC1_CHANNEL_0);
            result = 3.3*(reading)/4096;
            break;
        case 39:
            reading = adc1_get_raw(ADC1_CHANNEL_3);
            result = 3.3*(reading)/4096;
            Serial.print(result);
            break;
    }

    return result;
}




void BT_ACTVATE(void *args)
{
    int button_position = (int) args;
    button_flags[button_position] = true;
}

void DOWN_BT_ACTIVATE(void)
{
    flag_down_button = true;
}
void UP_BT_ACTIVATE(void)
{
    flag_up_button = true;
}
void ENTER_BT_ACTIVATE(void)
{
    flag_enter_button = true;
}
void STANDUP_BT_ACTIVATE(void)
{
    flag_standup_button = true;
}

/**
 * @brief Essa função tem como objetivo verificar qual modo de interrupção definida,
 * no padrão arduino e converter para o padrão da espressif
 * @param[in] type_to_convert é o tipo de interrupção no padrão arduino
 * @return Retorna o tipo de interrupção no padrão espressif.
 * */
gpio_int_type_t ButtonSpace::conversion_int_type(uint8_t type_to_convert)
{
    gpio_int_type_t my_type;
    switch (type_to_convert)
    {
        case ONLOW:
            my_type = GPIO_INTR_LOW_LEVEL;
            #ifdef DEBUG
                Serial.println("Definido o pino em [ON LOW]");
            #endif
            break;
        case ONHIGH:
            my_type = GPIO_INTR_HIGH_LEVEL;
            #ifdef DEBUG
                Serial.println("Definido o pino em [ON HIGH]");
            #endif
            break;
        case CHANGE:
            my_type = GPIO_INTR_ANYEDGE;
            #ifdef DEBUG
                Serial.println("Definido o pino em [CHANGE]");
            #endif
            break;
        case FALLING:
            my_type = GPIO_INTR_NEGEDGE;
            #ifdef DEBUG
                Serial.println("Definido o pino em [FALLING]");
            #endif
            break;
        case RISING:
            my_type = GPIO_INTR_POSEDGE;
             #ifdef DEBUG
                Serial.println("Definido o pino em [RISING]");
            #endif
            break;
        default:
            my_type = GPIO_INTR_DISABLE;
            #ifdef DEBUG
                Serial.println("Borda de interrupção não definida ou não encontrada...");
                Serial.println("Setando o padrão: [SEM INTERRUPÇÃO] ");
            #endif
            break;
    }
    return my_type;
}

gpio_num_t ButtonSpace::gpio(button_type_t button)
{
    gpio_num_t value = gpio_handle[button];
    return value;
}

/** TODO: FAZER TRADUÇÃO
 * @brief initialize the button with your activation border and type function in Steve
 * @param[in] border_activate Wich border the interrupt was activate
 * @param[in] type Functionally in the Steve
 * @return Return Sucess, if the initialization was sucefull, Return a error flag if was not ok.
 */
uint8_t ButtonSpace::Button::init(uint8_t border_activate, button_type_t type)
{
    esp_err_t GET_RETURN_GPIO_INSTALL;
    esp_err_t GET_RETURN_INTR_TYPE;
    esp_err_t GET_RETURN_INTR_ENABLE;
    esp_err_t GET_RETURN_GPIO_DIRECTION;
    esp_err_t GET_RETURN_ISR_HANDLER;

    if(first_defined_button == false)
    {
       GET_RETURN_GPIO_INSTALL = gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);
       if(GET_RETURN_GPIO_INSTALL != ESP_OK){return INSTALL_ERROR;}
    }

    GET_RETURN_INTR_TYPE = gpio_set_intr_type(gpio(type),conversion_int_type(border_activate));
    if(GET_RETURN_INTR_TYPE != ESP_OK){return INTR_TYPE_ERROR;}
    GET_RETURN_INTR_ENABLE = gpio_intr_enable(gpio(type));
    if(GET_RETURN_INTR_ENABLE != ESP_OK){return INTR_ENABLE_ERROR;}
    GET_RETURN_GPIO_DIRECTION = gpio_set_direction(gpio(type),GPIO_MODE_INPUT);
    if(GET_RETURN_GPIO_DIRECTION != ESP_OK){return GPIO_DIRECTION_ERROR;}
    GET_RETURN_ISR_HANDLER = gpio_isr_handler_add(gpio(type), (gpio_isr_t) BT_ACTVATE, (void *) type);   
    if(GET_RETURN_ISR_HANDLER != ESP_OK){return ISR_ADD_ERROR;}   

    first_defined_button = true;
    this->button_info.button_type = type;
    this->button_info.is_paused = false;
    return SUCESS;
}

uint8_t ButtonSpace::Button::read(void)
{
    delay(50);
    uint8_t button =  this->button_info.button_type;
    if(button_flags[button] == true)
    {
        if(previous_button_flags[button] == false) // botão foi ligado
        {
            previous_button_flags[button] = button_flags[button];
            button_flags[button] = false;
            return on;
        }
        else // botão permanece ligado
        {
            previous_button_flags[button] = button_flags[button];
            button_flags[button] = false;
            return stay_on; 
        }
    }
    else
    {
        if(previous_button_flags[button] == false) // botão continua desligado
        {
            previous_button_flags[button] = button_flags[button];
            button_flags[button] = false;
            return stay_off;
        }
        else // botão foi desligado
        {
            previous_button_flags[button] = button_flags[button];
            button_flags[button] = false;
            return off; 
        }
    }
}


uint8_t ButtonSpace::Button::pause(void)
{
    if(this->button_info.is_paused == true)
    {
        #ifdef DEBUG
            Serial.println("Botão já está em pausa");
        #endif
        return 1;
    }
    else
    {
        this->button_info.is_paused = true;
        esp_err_t GET_RETURN_INTR_DIS = gpio_intr_disable(gpio(this->button_info.button_type));
        return GET_RETURN_INTR_DIS == ESP_OK ? 0 : 1;
    }
}

uint8_t ButtonSpace::Button::start(void)
{
    if(this->button_info.is_paused == false)
    {
        #ifdef DEBUG
            Serial.println("Botão já está em execução normal");
        #endif
        return 1;
    }
    else
    {
        this->button_info.is_paused = false;
        esp_err_t GET_RETURN_INTR_EN = gpio_intr_enable(gpio(this->button_info.button_type));
        return GET_RETURN_INTR_EN == ESP_OK ? 0 : 1;
    }
}
#endif

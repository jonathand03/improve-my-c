#ifndef BOTAO_H
#define BOTAO_H

#include <stdint.h>
#include <Arduino.h>
#include "file.h"
#include "driver/gpio.h"
#include "display_logica.h"
#include "com.h"
#define BUTTON_ON

//------------ TODO: Convert to English ----//
namespace ButtonSpace
{
    enum button_type_t{down,up,enter,standup,button_type_max};
    enum button_state{on,off,stay_on,stay_off};

    // Flags de tratamento de retorno
    enum return_button_flags{INSTALL_ERROR = 5,INTR_TYPE_ERROR,INTR_ENABLE_ERROR,GPIO_DIRECTION_ERROR,ISR_ADD_ERROR};
    typedef struct
    {
        unsigned long int last_time_read;
        button_type_t button_type;
        bool is_paused;
    }button_info_t;
    
    //converte valores de Arduino Framework pra Espressif Framework
    gpio_int_type_t conversion_int_type(uint8_t type_to_convert);
    gpio_num_t gpio(button_type_t button);

    class Button
    {
        public:
            uint8_t init(uint8_t border_activate, button_type_t type);
            uint8_t read(void);
            uint8_t start(void);
            uint8_t pause(void);
            button_info_t button_info;
    };
}

extern gpio_num_t gpio_handle[ButtonSpace::button_type_max];
double verifica_tensao(int button);
#endif 

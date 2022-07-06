#ifndef BOTAO_H
#define BOTAO_H

#include <stdint.h>
#include <Arduino.h>
#include "file.h"
#include "driver/gpio.h"
#include "display_logica.h"
#include "com.h"
#define BUTTON_ON
#define ESP_INTR_FLAG_DEFAULT 0
// ---- TODO: convert to english -------//
namespace ButtonSpace
{
    enum button_type_t{down,up,enter,standup,panic,button_type_max};
    enum button_state{off,on,stay_on,stay_off, pressed_out};

    

    // Flags de tratamento de retorno
    enum bt_init_return{INSTALL_ERROR,INTR_TYPE_ERROR,INTR_ENABLE_ERROR,
                        GPIO_DIRECTION_ERROR,ISR_ADD_ERROR, INIT_SUCESS};
    enum button_start_return{START_SUCESS, START_ERROR};
    enum button_pause_return{PAUSE_SUCESS, PAUSE_ERROR};
    enum button_read_return{READ_SUCESS,READ_ERROR};
    typedef struct
    {
        unsigned long int last_time_read;
        button_type_t button_type;
        int border_type;
        bool is_paused;
        int current_state;
        int last_state;
    }button_info_t;


    
    //converte valores de Arduino Framework pra Espressif Framework
    gpio_int_type_t conversion_int_type(uint8_t type_to_convert);
    gpio_num_t gpio(button_type_t button);

    class Button
    {
        public:
            Button(uint8_t border_activate, button_type_t type);
            uint8_t init(uint8_t border_activate, button_type_t type);
            uint8_t read(void);
            uint8_t start(void);
            uint8_t pause(void);
            uint8_t process(void (*onPressCallBack)(void),void (*onReleaseCallBack)(void));
            button_info_t button_info;

    };
}

extern gpio_num_t gpio_handle[ButtonSpace::button_type_max];
double verifica_tensao(int button);
void teste_press(void);
void test_out(void);

extern ButtonSpace::Button Up;
extern ButtonSpace::Button Down;
extern ButtonSpace::Button Enter;
extern ButtonSpace::Button Standup;
extern ButtonSpace::Button Panic;

#endif 

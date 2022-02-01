#ifndef BOTOES_HPP
#define BOTOES_HPP

#include <stdint.h>
#include <Arduino.h>

class Button
{
    public:
        /* Inicializa o botão com ou sem interrupção de hardware */
        Button(int pin);
        Button(int pin, gpio_int_type_t edge, void (*fn)());
        /* Pausa ou encerra o botão */
        uint8_t StopButton(void);
        uint8_t ResumeButton(void);
        /* Faz a Leitura do botão   */
        estado_botao ReadButton(void);
        /* Status de configuração do botão  (para fins de debug)*/
        void StatusButton(void);
    protected:
        int ButtonPin = 0;
    private:
        /* Estado do Botão */
        bool BtOn = false;
        bool BtOff = false;
        bool BtStayOn = false;
        bool BtStayOff = false;
        /* Modos operacionais */
        bool BtWorking = false;
        bool BtStopped = false;
};




#endif
#ifndef BOTOES_HPP
#define BOTOES_HPP

#include <stdint.h>
#include <Arduino.h>
class Button
{
    public:
        /* Inicializa o botão com ou sem interrupção de hardware */
        Button(int pin, int edge);
        Button(int pin, int edge, void (*fn)());
        /* Pausa ou encerra o botão */
        uint8_t StopButton(void);
       // uint8_t TrashButton(void);
        /* Faz a Leitura do botão   */
        uint8_t ReadButton(void);
        /* Status de configuração do botão  (para fins de debug)*/
        void StatusButton(void);
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
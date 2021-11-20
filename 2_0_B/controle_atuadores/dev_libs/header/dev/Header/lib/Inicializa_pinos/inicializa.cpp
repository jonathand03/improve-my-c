#include "inicializa.h"
#include <Arduino.h>
#include "debug.h"

void inicializa_atuadores(void )
{
    for(int i = 0; i < qtd_pinos_atuadores; i++)
    {
        for(int j = 0; j < qtd_tipo_atuacao; j++)
        {
                pinMode(pinos_atuadores[i][j],OUTPUT);
        }
    }
    debug("Atuadores inicializados com sucesso");
}

void inicializa_fim_de_curso(void)
{
    for(int i = 0; i < qtd_pinos_fim_curso; i++)
    {
        pinMode(pinos_fim_curso[i], INPUT);
    }
     debug("Fins de curso inicializados com sucesso");
}
    
void inicializa_led(void)
{
    pinMode(led, OUTPUT);
}
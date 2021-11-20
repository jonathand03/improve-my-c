#include <Arduino.h>
#include <stdlib.h>
#include "steve_debug.h"
#include "communication_ihm.h"
const int botao_1 = 18;
const int fim_curso_1 = 19;

void setup()
{
    Serial.begin(115200);
    inicializa_comunicao_serial();
    pinMode(botao_1, INPUT);
    pinMode(fim_curso_1, INPUT);
}


//SERVIDOR
/*
void loop()
{
    int8_t valor;
    valor = verifica_comunicacao_serial();
    if(valor == tipo_de_requisicao(e_aciona_atuador))
    {
        Serial.print(" Requisição de botao");
    }
    if(valor == tipo_de_requisicao(e_fim_curso))
    {
       Serial.print(" Requisicao fim de curso");
    }
}
*/


// CLIENTE

void loop()
{
    if(digitalRead(botao_1) == LOW)
    {
        envia_requisicao_de_escrita(e_aciona_atuador);
    }
    else if(digitalRead(fim_curso_1) == LOW)
    {
        envia_requisicao_de_escrita(e_fim_curso);
    }
   
}

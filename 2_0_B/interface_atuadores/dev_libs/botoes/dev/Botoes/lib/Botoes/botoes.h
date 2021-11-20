/*!  @file botoes.h
*    @brief Lib dos botões da interface ihm do projeto STEVE
*    @note Será utilizado interrupções via hardware para ativação dos botoes
*/

#ifndef BOTOES_H
#define BOTOES_H

#include <driver/adc.h>

int instala_isr_botoes(void);
int anexa_interrupcao_botao(int botao);


#endif
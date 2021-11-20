#ifndef MANAGER_H
#define MANAGER_H


#include "atuadores.h"
#include "giroscopio.h"
#include "fim_curso.h"
#include "com_ihm.h"


/*!
*    Funções
*/
void inicializa_modulos_controle(void);
void tratamento_atuador_com_serial();
void aciona_atuador_com_serial(uint8_t codigo_comando_serial);
void executa_atuador(int codigo_comando_serial,int estado);

void verifica_codigo_recebido(void);



//void reconfigura_suporte_circulatorio(void);
#endif
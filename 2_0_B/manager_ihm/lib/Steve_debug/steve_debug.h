#ifndef STEVE_DEBUG_H
#define STEVE_DEBUG_H
extern const int SUCESSO;
extern const int SINALIZADOR_ERRO;
extern const int SEM_RESPOSTA ;
//!< Tornando o Serial print como DEBUG()
#define debug(x) Serial.println(x)
void manager_interrupcao_fim_de_curso(void);
#endif
#ifndef DISPLAY_LOGICA_H
#define DISPLAY_LOGICA_H

/* Logica SC */
void StatusConfigSC(void);
void AnguloConfig(void);
void CicloConfig(void);
void TempoConfig(void);

/* Logica Ajustes */
void AssentoAjusteVertical(void);
void AssentoAjusteHorizontal(void);
void EncostoAjusteInclinacao(void);
void EncostoAjusteVertical(void);
void SCAjusteVertical(void);

/* Navegacao da logica dos ajustes */
void NavegacaoLogica(void);

extern int angulo_atual;
extern int angulo_max;
extern int ciclo_atual;
extern int ciclo_max;
extern int tempo_atual;
extern int tempo_max;

#endif
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



void AlteraAnguloBaixo(void);
void AlteraAnguloCima(void);
void AlteraCicloBaixo(void);
void AlteraCicloCima(void);
void AlteraTempoBaixo(void);
void AlteraTempoCima(void);

void NavegacaoPagina(int LimiteNavegacao, int Bt);
void AjusteAssentoHorizontal(int bt, Button *button);

extern int angulo_atual;
extern int angulo_max;
extern int ciclo_atual;
extern int ciclo_max;
extern int tempo_atual;
extern int tempo_max;
#endif
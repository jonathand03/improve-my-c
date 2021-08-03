#ifndef FIM_DE_CURSO_H
#define FIM_DE_CURSO_H

#define FIM_DE_CURSO_PINOUT
#ifdef FIM_DE_CURSO_PINOUT

#define FC_STANDUP_LOW (36)
#define FC_STANDUP_HIG (39)
#define FC_SSC_LOW (34)
#define FC_RSV (35)

#endif

extern const int SINALIZADOR_INSTALACAO_DRIVER; //!< Sinalizador da instalação do driver de interrupção do fim de curso

/*! \enum e_fim_curso
    \brief Enumeração com todos os fim de cursos
    
    *******
*/
enum e_fim_curso
{
    e_fim_curso_standup_low,
    e_fim_curso_standup_high,
    e_fim_curso_suporte_circ,
    e_fim_curso_reserva,
};

int instalar_servico_isr(int flag_de_instalacao);
int configura_pinos_fim_curso_isr(e_fim_curso fim_curso);
int retorna_pino_fim_curso(e_fim_curso fim_curso);
void inicializa_fim_de_curso(void);

#endif
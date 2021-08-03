#ifndef INICIALIZADOR_PORTAS_H
#define INICIALIZADOR_PORTAS_H


/*============================================== MAPEAMENTO DE PORTAS ============================================================*/
  /* AÇÕES DE AVANÇO */
  const int atuador_avanco_standup = 32;                         // [ATUADOR] Standup: pino de [avanço]                          
  const int atuador_avanco_elevador_base = 33;                   // [ATUADOR] Elevador da base: pino de [avanço]                 
  const int atuador_avanco_elevador_suporte_circ = 25;           // [ATUADOR] Elevador do suporte circulatório: pino de [avanço] 
  const int atuador_avanco_suporte_circu = 26;                   // [ATUADOR] Suporte circulatório: pino de [avanço]             
  const int atuador_avanco_altura_encosto = 27;                  // [ATUADOR] Altura do enconsto: pino de [avanço]               
  const int atuador_avanco_inclinacao_encosto = 14;              // [ATUADOR] Inclinação do encosto: pino de [avanço]            
  const int atuador_avanco_distancia_assento_encosto = 12;       // [ATUADOR] Distancia do assento e encosto: pino de [avanço]   
  /* AÇÕES DE RECUO */
  const int atuador_recuo_standup = 23;                          // [ATUADOR] Standup: pino de [recuo]                           
  const int atuador_recuo_elevador_base = 19;                    // [ATUADOR] Elevador da base: pino de [recuo]                  
  const int atuador_recuo_elevador_suporte_circ = 18;            // [ATUADOR] Elevador do suporte circulatório: pino de [recuo]  
  const int atuador_recuo_suporte_circu = 5;                     // [ATUADOR] Suporte circulatório: pino de [recuo]              
  const int atuador_recuo_altura_encosto = 4;                    // [ATUADOR] Altura do enconsto: pino de [recuo]                
  const int atuador_recuo_inclinacao_encosto = 2;                // [ATUADOR] Inclinação do encosto: pino de [recuo]             
  const int atuador_recuo_distancia_assento_encosto = 15;        // [ATUADOR] Distancia do assento e encosto: pino de [recuo]    
  /* PORTAS I2C  */
  const int i2c_giroscopio_sda = 21;                             // [SENSOR] Giroscópio para o encosto: pino I2C [sda]           
  const int i2c_giroscopio_scl = 22;                             // [SENSOR] Giroscópio para o encosto: pino I2C [scl]           
  /* FIM DE CURSO */
  const int fim_curso_standup_low = 36;                          // [SENSOR] Fim de curso para o Standup Low                     
  const int fim_curso_standup_high = 39;                         // [SENSOR] Fim de curso para o Standup High                    
  const int fim_curso_suporte_circ_low = 34;                     // [SENSOR] Fim de curso do Suporte Circulatorio Low (reserva)  
  const int fim_curso_reserva = 35;                              // [SENSOR] Porta reserva para fim de curso                     
  /* DEBUG */
  const int debug_txd = 17;                                      // [DEBUG]  Porta para debug                                    
  const int debug_rxd = 16;                                      // [DEBUG]  Porta para debug                                    
  /* R232 - IHM */
  const int r232_txd = 1;                                        // [R232]   Porta para controle                               
  const int r232_rxd = 3;                                        // [R232]   Porta para controle                                 
  /* Reservada */
  const int porta_analogica = 13;                                // [ANALOGICO] Porta Analógica reservada                        


  /*================================================ Enumeradores, Variáveis e Constantes ======================================*/
  const int qtd_pinos_atuadores = 14;                   // Armazena a quantidade de pinos de atuadores estão disponíveis
  const int qtd_tipo_atuacao = 2;                       // Armazena a quantidade de estados possiveis dos atuadores stão disponíveis
  const int qtd_pinos_i2c = 2;                          // Armazena a quantidade de Pinos I2C
  const int qtd_pinos_fim_curso = 4;                    // Armazena a quantidade de pinos de Fim de curso estão disponíveis
  const int qtd_pino_giroscopio = 2;                    // Armazena a quantidade de pinos de dados do giroscopio
  const int qtd_pino_display = 2;                       // Armazena a quantidade de pinos de dados do display

  
  /* [VETOR] Vetor com todas as portas dos ATUADORES              */
  const int pinos_atuadores[qtd_pinos_atuadores][qtd_tipo_atuacao] =
  {
          {atuador_avanco_standup,atuador_recuo_standup},
          {atuador_avanco_elevador_base,atuador_recuo_elevador_base},
          {atuador_avanco_elevador_suporte_circ,atuador_recuo_elevador_suporte_circ},
          {atuador_avanco_suporte_circu,atuador_recuo_suporte_circu},
          {atuador_avanco_altura_encosto, atuador_recuo_altura_encosto},
          {atuador_avanco_inclinacao_encosto, atuador_recuo_inclinacao_encosto},
          {atuador_avanco_distancia_assento_encosto,atuador_recuo_distancia_assento_encosto}
  };
  /* [VETOR] Vetor com todas as portas do I2C                     */                                                             
  const int pinos_i2c[qtd_pinos_i2c] =
  {
          i2c_giroscopio_sda,
          i2c_giroscopio_scl
  };
  /* [VETOR] Vetor com todas as portas do FIM DE CURSO            */                                                             
  const int pinos_fim_curso[qtd_pinos_fim_curso] =
  {
          fim_curso_standup_low,
          fim_curso_standup_high,
          fim_curso_suporte_circ_low,
          fim_curso_reserva
  };                                                            

/*================================================ Area de exportação de funções =====================================================*/
void inicializa_atuadores(void);
void inicializa_fim_de_curso(void);
void inicializa_display(void);
void inicializa_giroscopio(void);
void inicializa_led(void);

#endif
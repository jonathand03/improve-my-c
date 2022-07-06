#include "fim_curso.h"
#include "rom/gpio.h"
#include <Arduino.h>
#include "steve_debug.h"
#define DEBUG_FIM_CURSO

const int qtd_pinos_fim_curso = 4; //!< Armazena a quantidade de pinos de Fim de curso estão disponíveis



/*! \var const int pinos_fim_curso[qtd_pinos_fim_curso]
    \brief [VETOR] Vetor com todas as portas do FIM DE CURSO
    
    *******
*/
const int pinos_fim_curso[qtd_pinos_fim_curso] =
{
        fim_curso_standup_low,
        fim_curso_standup_high,
        fim_curso_suporte_circ_low,
        fim_curso_reserva
};

extern const int SINALIZADOR_INSTALACAO_DRIVER = 0; //!< Sinalizador de instalação do driver de interrupção

/*! @fn int instalar_servico_isr(int flag_de_instalacao)
 * @brief  Instala o driver de interrupção nas portas do ESP32
 * @return Retorna 0 em caso de sucesso, ou -1 em caso de falha
 */
int instalar_servico_isr(int flag_de_instalacao)
{
        esp_err_t retorno; //<! Variável que guarda o retorno do serviço de instalação
        retorno = gpio_install_isr_service(flag_de_instalacao);
        if (retorno != ESP_OK)
                return SINALIZADOR_ERRO;
        else
                return SUCESSO;
}

/*! @fn int configura_pinos_fim_curso_isr(e_fim_curso fim_curso)
 * @brief  Configura a porta passada como parametro para a ISR do ESP32 
 * São utilizadas um conjunto de funções de interrupção da espressif para 
 * fazer o tratamento de interrupção do nosso projeto, são elas:
 * gpio_set_intr_type: Configura em que tipo de sinal será lida a interrupção;
 * gpio_intr_enable: Ativa o modo de interrupção no pino;
 * gpio_isr_handler_add: Configura qual função vai ser chamada quando a interrupção for gerada;
 * gpio_set_direction: Configura o modo do pino [ Se é INPUT ou OUTPUT];
 * @param[in] fim_curso É uma enumeração referente ao fim de curso desejado
 * @return Retorna 0 em caso de sucesso, ou -1 em caso de falha
 */
int configura_pinos_fim_curso_isr(e_fim_curso fim_curso)
{
        /*! @brief
        *        Variaveis que armazenam o retorno das funções de configurações dos pinos
        */
        esp_err_t retorno_gpio_set_intr_type;
        esp_err_t retorno_gpio_intr_enable;
        esp_err_t retorno_gpio_isr_handler_add;
        esp_err_t retorno_gpio_set_direction;

        retorno_gpio_set_intr_type = gpio_set_intr_type((gpio_num_t)retorna_pino_fim_curso(fim_curso), GPIO_INTR_NEGEDGE);
        if (retorno_gpio_set_intr_type != ESP_OK)
                return SINALIZADOR_ERRO;

        retorno_gpio_intr_enable = gpio_intr_enable((gpio_num_t)retorna_pino_fim_curso(fim_curso));
        if (retorno_gpio_intr_enable != ESP_OK)
                return SINALIZADOR_ERRO;

        retorno_gpio_isr_handler_add = gpio_isr_handler_add((gpio_num_t)retorna_pino_fim_curso(fim_curso), (gpio_isr_t)manager_interrupcao_fim_de_curso, NULL);
        if (retorno_gpio_isr_handler_add != ESP_OK)
                return SINALIZADOR_ERRO;

        retorno_gpio_set_direction = gpio_set_direction((gpio_num_t)retorna_pino_fim_curso(fim_curso), GPIO_MODE_INPUT);
        if (retorno_gpio_set_direction != ESP_OK)
                return SINALIZADOR_ERRO;
        return SUCESSO;
}

/*! @fn int retorna_pino_fim_curso(e_fim_curso fim_curso)
 * @brief  Retorna o pino referente a enumeração repassada. Retorna -1 caso seja repassado um pino invalido
 * @param[in] fim_curso É uma enumeração referente ao fim de curso desejado
 * @return retorna o pino referente à enumeração repassada, caso sucesso
 */
int retorna_pino_fim_curso(e_fim_curso fim_curso)
{
        if(fim_curso > 3)
        {
                return SINALIZADOR_ERRO;
        }
        else
        {
                return pinos_fim_curso[fim_curso];
        }
       
}

/*! @fn void inicializa_fim_de_curso(void)
* @brief Inicializa todos os pinos dos fins de curso como pinos de saída [OUTPUT]
*/
void inicializa_fim_de_curso(void)
{
        for (int i = 0; i < qtd_pinos_fim_curso; i++)
        {
                pinMode(pinos_fim_curso[i], INPUT);
        }
        #ifdef DEBUG_FIM_CURSO
                debug("Fins de curso inicializados com sucesso");
        #endif
}


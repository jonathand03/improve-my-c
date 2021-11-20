#include <botoes.h>

void interrupcao(void);


/*! @brief Instala o serviço de interrupção global via pinos
*   @return Retorna SUCESSO, caso a instalação do driver de interrupção seja feita com sucesso
*           Retorna SINALIZADOR_ERRO, caso contrário.
*/
int instala_isr_botoes(void)
{
        esp_err_t retorno; //<! Variável que guarda o retorno do serviço de instalação
        retorno = gpio_install_isr_service(0);
        if (retorno != ESP_OK)
                return -1;
        else
                return 0;
}

/*! @brief Instancia o botão repassado como parametro como uma interrupção de hardware
*   @param[in] botao é o botão que será preparado como interrupção
*   @return Retorna SUCESSO, caso a interrupção tenha sido anexada ao pino com sucesso,
*           caso contrário, retorna SINALIZADOR_ERRO
*/
int anexa_interrupcao_botao(int botao)
{
    gpio_set_intr_type((gpio_num_t)1, GPIO_INTR_HIGH_LEVEL);
    gpio_intr_enable((gpio_num_t)1);
    gpio_isr_handler_add((gpio_num_t)1, (gpio_isr_t)interrupcao, NULL);
    gpio_set_direction((gpio_num_t)1, GPIO_MODE_INPUT);
}

#include "giroscopio.h"
#include <Adafruit_MPU6050.h>
#include "steve_debug.h"

Adafruit_MPU6050 sensor_mpu;

/*! \fn int inicializa_mpu6050(void)
 * @brief Inicializa o módulo MPU6050, definindo a calibração do 
 * sensores acelerômetro e giroscópio
 * @return Retorna  SUCESSO , caso o sensor seja inicializado com sucesso. Retorna  SINALIZADOR_ERRO , caso falhe.
*/
int inicializa_mpu6050(void)
{
        /*!
        *      Verifica se o sensor foi inicializado com sucesso
        */
        if (!sensor_mpu.begin())
        {
                #ifdef DEBUG
                                debug("Falha na inicialização do módulo MPU6050");
                #endif
                return SINALIZADOR_ERRO;
        }
        else
        {

                /*!
                *      Calibração dos sensores do MPU6050
                */
                sensor_mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
                sensor_mpu.setGyroRange(MPU6050_RANGE_500_DEG);
                sensor_mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
                /*!
                *      Mostra o resultado
                */
                #ifdef DEBUG
                                debug("Giroscopio inicializado com sucesso");
                #endif
                return SUCESSO;
        }
}

/*! \fn sensors_event_t *leitura_sensor_mpu(sensors_event_t *vetor_dados_mpu)
 * @brief   Faz a leitura dos sensores [ Giroscópio] e [Acelerômetro] do MPU6050
 * @param[in] vetor_dados_mpu é o vetor do tipo 'sensors_event_t' onde é armazenado
 * os dados dos sensores
 * @return Retorna o vetor com os dados dos sensores
*/
sensors_event_t *leitura_sensor_mpu(sensors_event_t *vetor_dados_mpu)
{
        /*!
        *       Variaveis que irão guardar as leituras dos sensores do MPU-6050
        */
        sensors_event_t leitura_acelerometro; //!< Variável que irá guardar a leitura do acelerometro
        sensors_event_t leira_giroscopio;     //!< Variável que irá guardar a leitura do giroscopio
        sensors_event_t leitura_temperatura;  //!< Variável que irá guardar a leitura da temperatura

        /*! \fn sensor_mpu.getEvent(&leitura_acelerometro, &leira_giroscopio, &leitura_temperatura)
        *   \brief   Evento de captura dos dados (Temperatura, Aceleração e Rotação) 
        *
        *   ******
        */
        sensor_mpu.getEvent(&leitura_acelerometro, &leira_giroscopio, &leitura_temperatura);

        /*!
        *       \brief Armazenamento de dados dos sensores   
        */
        vetor_dados_mpu[aceleracao] = leitura_acelerometro; //!<  Armazenando os dados lidos do acelerometro no vetor de dados
        vetor_dados_mpu[giroscopio] = leira_giroscopio;     //!< Armazenando os dados lidos do giroscopio no vetor de dados

        /*!
        *       \brief Ativa a flag de status de leitura do mpu
        */
        ativa_status_mpu6050(vetor_dados_mpu);
        return vetor_dados_mpu; //<! Retornando o vetor com os dados lidos
}

/*! \fn int mostra_dados_giroscopio(sensors_event_t *leitura_sensor_mpu)
 * @brief Mostra na Serial os dados do MPU6050 referente ao [Giroscopio]
 * @param[in] leitura_sensor_mpu é a função de captura de dados do MPU6050 
 * @return Retorna  SUCESSO , caso os dados sejam mostrados. 
 * Retorna SINALIZADOR_ERRO , caso falhe na mostragem de dados.
*/
int mostra_dados_giroscopio(sensors_event_t *leitura_sensor_mpu)
{
        if (leitura_sensor_mpu[giroscopio].gyro.status == ativado)
        {
                const int qtd_eixos_giroscopio = 3;               //!< Quantidade de eixos do giroscopio
                float eixos_giroscopio[qtd_eixos_giroscopio];     //!< Vetor que armazena os valores dos eixos do giroscopio
                eixos_giroscopio[x] = leitura_sensor_mpu->gyro.x; //!< Alimentando a variavei [X] com a leitura atual do sensor de giroscopio
                eixos_giroscopio[y] = leitura_sensor_mpu->gyro.y; //!< Alimentando a variavei [Y] com a leitura atual do sensor de giroscopio
                eixos_giroscopio[z] = leitura_sensor_mpu->gyro.z; //!< Alimentando a variavei [Z] com a leitura atual do sensor de giroscopio

                /*! 
                *       Mostra os dados formatado na Serial
                */
                formatador_serial_print_giroscopio(eixos_giroscopio);

                /*! 
                *      Desativa o status de leitura do sensor mpu para a proxima leitura
                */
                desativa_status_mpu6050(leitura_sensor_mpu);

                return SUCESSO; //!< Retorna sucesso
        }
        else
        {
                return SINALIZADOR_ERRO; //!< Retorna Falha
        }
}

/*! \fn int mostra_dados_acelerometro(sensors_event_t *leitura_sensor_mpu)
 * @brief Mostra na Serial os dados do MPU6050 referente ao [Acelerometro]
 * @param[in] leitura_sensor_mpu é a função de captura de dados do MPU6050 
 * @return Retorna SUCESSO , caso os dados sejam mostrados. 
 * Retorna SINALIZADOR_ERRO , caso falhe na mostragem de dados.
*/
int mostra_dados_acelerometro(sensors_event_t *leitura_sensor_mpu)
{
        if (leitura_sensor_mpu[giroscopio].gyro.status == ativado)
        {
                const int qtd_eixos_acelerometro = 3;             //!< Quantidade de eixos do giroscopio
                float eixos_acelerometro[qtd_eixos_acelerometro]; //!< Vetor que armazena os valores dos eixos do giroscopio

                eixos_acelerometro[x] = leitura_sensor_mpu->acceleration.x; //!< Alimentando a variavel [X] com a leitura atual do sensor de aceleração
                eixos_acelerometro[y] = leitura_sensor_mpu->acceleration.y; //!<Alimentando a variavel [Y] com a leitura atual do sensor de aceleração
                eixos_acelerometro[z] = leitura_sensor_mpu->acceleration.z; //!<Alimentando a variavel [Z] com a leitura atual do sensor de aceleração

                /*!
                *       Mostra os dados formatado na Serial 
                */
                formatador_serial_print_acelerometro(eixos_acelerometro);

                /*!
                *       Desativa o status de leitura do sensor mpu para a proxima leitura
                */
                desativa_status_mpu6050(leitura_sensor_mpu);

                return SUCESSO; //!< Retorna Sucesso
        }
        else
        {
                return SINALIZADOR_ERRO; //!< Retorna Falha
        }
}

/*! \fn int formatador_serial_print_giroscopio(float *vetor_eixo_giroscopio)
 * @brief Formata o mostrador serial para melhor visualização dos dados
 * @param[in] vetor_eixo_giroscopio é o vetor do tipo float onde é armazenado
 * os dados dos eixos do sensor giroscopio
*/
int formatador_serial_print_giroscopio(float *vetor_eixo_giroscopio)
{
        if (vetor_eixo_giroscopio == NULL)
        {
                return SINALIZADOR_ERRO;
        }
        else
        {
                debug("---------------------------------------");
                debug(" Eixos do giroscopio: ");
                Serial.print("X : ");
                debug(vetor_eixo_giroscopio[x]);
                Serial.print("Y : ");
                debug(vetor_eixo_giroscopio[y]);
                Serial.print("Z : ");
                debug(vetor_eixo_giroscopio[z]);
                return SUCESSO;
        }
}

/*! \fn int formatador_serial_print_acelerometro(float *vetor_eixo_acelerometro)
 * @brief Formata o mostrador serial para melhor visualização dos dados
 * @param[in] vetor_eixo_acelerometro é o vetor do tipo float onde é armazenado
 * os dados dos eixos do sensor acelerometro
*/
int formatador_serial_print_acelerometro(float *vetor_eixo_acelerometro)
{
        if (vetor_eixo_acelerometro == NULL)
        {
                return SINALIZADOR_ERRO; //!< Caso não exista nenhum dado para leitura
        }
        else
        {
                debug("---------------------------------------");
                debug(" Eixos do acelerometro (m/s^2): ");
                Serial.print("X : ");
                debug(vetor_eixo_acelerometro[x]);
                Serial.print("Y : ");
                debug(vetor_eixo_acelerometro[y]);
                Serial.print("Z : ");
                debug(vetor_eixo_acelerometro[z]);

                return SUCESSO; //!< Retorna sucesso após mostrar os dados na serial
        }
}

/*! \fn sensors_event_t *desativa_status_mpu6050(sensors_event_t *vetor_dados_mpu)
 * @brief Seta a flag de status dos sensor mpu para desativado.
 * @param[in] vetor_dados_mpu é o vetor do tipo 'sensors_event_t' onde é armazenado
 * os dados dos sensores
 * @return Rertona o vetor com a flag atualizada
*/
sensors_event_t *desativa_status_mpu6050(sensors_event_t *vetor_dados_mpu)
{
        if (vetor_dados_mpu == NULL)
        {
                vetor_dados_mpu->version = 0;
                return vetor_dados_mpu;
        }
        else
        {
                vetor_dados_mpu[aceleracao].acceleration.status = desativado; //!< Desativa o status do acelerometro
                vetor_dados_mpu[giroscopio].gyro.status = desativado;         //!< Desativa o status do giroscopio

                return vetor_dados_mpu; //!< Retorna o vetor com os status desativados
        }
}

/*! \fn sensors_event_t *desativa_status_mpu6050(sensors_event_t *vetor_dados_mpu)
 * @brief Seta a flag de status dos sensor mpu para desativado.
 * @param[in] vetor_dados_mpu é o vetor do tipo 'sensors_event_t' onde é armazenado
 * os dados dos sensores
 * @return Rertona o vetor com a flag atualizada
*/
sensors_event_t *ativa_status_mpu6050(sensors_event_t *vetor_dados_mpu)
{
        if (vetor_dados_mpu == NULL)
        {
                vetor_dados_mpu->version = 0;
                return vetor_dados_mpu;
        }
        else
        {
                vetor_dados_mpu[aceleracao].acceleration.status = ativado; //!< Ativa o status do acelerometro
                vetor_dados_mpu[giroscopio].gyro.status = ativado;         //!< Ativa o status do giroscopio

                return vetor_dados_mpu; //!< Retorna o vetor com os status ativados
        }
}

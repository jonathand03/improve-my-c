
#include "giroscopio.h"
#include "steve_debug.h"

extern const uint8_t endereco_mpu_modulo_1 = ENDERECO_0X68;
extern const uint8_t endereco_mpu_modulo_2 = ENDERECO_0X69;

/*! @fn int inicializa_sensor_mpu(int endereco_sensor_mpu, Adafruit_MPU6050 &Sensor)
 * @brief Inicializa o módulo MPU6050, definindo a calibração do 
 * sensores acelerômetro e giroscópio.
 * @param[in] endereco_sensor_mpu É o endereço do sensor que será inicializado.
 * @param[in] Sensor É o objeto com a estrutura e as funções do Sensor MPU6050.
 * @return Retorna  SUCESSO , caso o sensor seja inicializado com sucesso. Retorna  SINALIZADOR_ERRO , caso falhe.
*/
int inicializa_sensor_mpu(int endereco_sensor_mpu, Adafruit_MPU6050 &Sensor)
{
        bool status;
        status = Sensor.begin(endereco_sensor_mpu); //<! Faz a inicialização do sensor no endereço repassado
        if (status == false)                        //!< Caso essa inicialização falhe, retorna SINALIZADOR_ERRO
        {
                return SINALIZADOR_ERRO;
        }

        /*! 
          *@brief Calibração dos sensores internos do MPU6050
        */
        Sensor.setAccelerometerRange(MPU6050_RANGE_8_G);
        Sensor.setGyroRange(MPU6050_RANGE_250_DEG);
        Sensor.setFilterBandwidth(MPU6050_BAND_5_HZ);
        return SUCESSO;
}

/*! @fn sensors_event_t leitura_sensor_mpu(Adafruit_MPU6050 &Sensor)
 * @brief   Faz a leitura dos sensores [ Giroscópio] do  MPU6050
 * @param[in] Sensor É o objeto com a estrutura e as funções do Sensor MPU6050.
 * @return Retorna a estrutura com os dados do giroscópio
*/
sensors_event_t leitura_sensor_mpu(Adafruit_MPU6050 &Sensor)
{
        bool status_leitura_sensor;
        sensors_event_t leitura_acelerometro; //!< Variável que irá guardar a leitura do acelerometro
        sensors_event_t leitura_giroscopio;   //!< Variável que irá guardar a leitura do giroscopio
        sensors_event_t leitura_temperatura;  //!< Variável que irá guardar a leitura da temperatura

        /*! \fn sensor_mpu.getEvent(&leitura_acelerometro, &leira_giroscopio, &leitura_temperatura)
        *   \brief   Evento de captura dos dados (Temperatura, Aceleração e Rotação) 
        *
        *   ******
        */
        status_leitura_sensor = Sensor.getEvent(&leitura_acelerometro, &leitura_giroscopio, &leitura_temperatura);
        if (status_leitura_sensor == false || verifica_endereco_sensor() == SINALIZADOR_ERRO) //<! Caso não seja possível fazer a leitura
        {
                debug("Não foi possível ler os dados do sensor");
                leitura_acelerometro.acceleration.status = SINALIZADOR_ERRO;
                return leitura_acelerometro;
        }
        else
        {
                leitura_acelerometro.acceleration.status = SUCESSO;
                return leitura_acelerometro; //<! Retorna a estrutura com os dados do giroscopio
        }
}

/*! @fn void mostra_dados_giroscopio(sensors_event_t leitura_sensor_mpu)
 * @brief Mostra na Serial os dados do MPU6050 referente ao [Giroscopio]
 * @param[in] leitura_sensor_mpu é a função de captura de dados do MPU6050 
 * @return Retorna  SUCESSO , caso os dados sejam mostrados. 
 * Retorna SINALIZADOR_ERRO , caso falhe na mostragem de dados.
*/
int mostra_dados_giroscopio(sensors_event_t leitura_sensor_mpu)
{
        const int offset = 10;
        if (leitura_sensor_mpu.acceleration.status == SINALIZADOR_ERRO)
                return SINALIZADOR_ERRO;

        Serial.println();
        Serial.print("Rotacao x: ");
        Serial.print(leitura_sensor_mpu.gyro.x);
        Serial.print(" Rotacao y: ");
        Serial.print(leitura_sensor_mpu.gyro.y*offset);
        Serial.print(" Rotacao z: ");
        Serial.print(leitura_sensor_mpu.gyro.z-offset);
        Serial.println();
        return SUCESSO;
}

/*! @fn modo_soneca_sensor_mpu(Adafruit_MPU6050 &Sensor, bool status)
 * @brief Altera o modo operacional do sensor repassado por parametro
 * @param[in] Sensor é sensor que terá seu modo operacional alterado
 * @param[in] status é o modo operacional que o sensor irá ficar
 * @return Retorna SUCESSO caso o sensor consega alterar o modo operacional, Retorna SINALIZADOR_ERRO, caso contrario.
 */
bool modo_soneca_sensor_mpu(Adafruit_MPU6050 &Sensor, bool status)
{
        return Sensor.enableSleep(status);
}

/*! @fn int verifica_endereco_sensor(void)
 * @brief Verifica os endereços dos sensores conectados na I2C do microcontrolador
 * @return Retorna  SUCESSO , caso pelo menos um dos sensores esteja conectado na I2C. 
 * Retorna SINALIZADOR_ERRO , caso não seja encontrado nenhum dispositivo conectado na I2C.
*/
int verifica_endereco_sensor(void)
{
        /*!
                @brief Variaveis locais
        */
        uint8_t verificador_erro;
        uint8_t endereco_atual;
        const uint8_t endereco_inicial = 1;
        const uint8_t endereco_final = 127;
        const int nenhum_dispositivo = 0;
        const int tamanho_maximo_hexadecimal = 16;
        int numero_dispositivos = 0;

        for (endereco_atual = endereco_inicial; endereco_atual < endereco_final; endereco_atual++) //!< Faz a busca por endereços de dispositivos no I2C
        {
                Wire.beginTransmission(endereco_atual);    //!< Inicializa a comunicação com o endereço atual
                verificador_erro = Wire.endTransmission(); //!< Conclui a comunicação com o endereço atual e verifica se houve erro na comunicação
                if (verificador_erro == SUCESSO)           //!< Caso não encontre nenhum erro, atualiza o numero de dispositivos conectados no I2C
                {
                        /* Serial.print("Dispositivo I2C encontrado no endereço 0x");
                        if (endereco<16) 
                        {
                                Serial.print("0");
                        }
                        Serial.println(endereco,HEX);*/
                        numero_dispositivos++;
                }
                else if (verificador_erro == 4) //!< Caso encontre um erro no endereço atual, mostra onde foi encontrado o erro
                {
                        Serial.print(" Erro desconhecido no endereço 0x");
                        if (endereco_atual < tamanho_maximo_hexadecimal)
                        {
                                Serial.print("0");
                        }
                        Serial.println(endereco_atual, HEX);
                }
        }
        if (numero_dispositivos == nenhum_dispositivo) //!< Caso nenhum dispositivo for encontrado, retorna SINALIZADOR_ERRO
        {
                return SINALIZADOR_ERRO;
        }
        else //!< Caso pelo menos UM dispositivo for encontrado, retorna SUCESSO
        {
                return SUCESSO;
        }
}

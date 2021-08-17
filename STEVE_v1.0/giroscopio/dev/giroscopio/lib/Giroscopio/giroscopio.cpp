
#include "giroscopio.h"
#include "steve_debug.h"




extern const int endereco_mpu_modulo_1 = ENDERECO_0X68;
extern const int endereco_mpu_modulo_2 = ENDERECO_0X69;

/*! @fn int inicializa_mpu6050(void)
 * @brief Inicializa o módulo MPU6050, definindo a calibração do 
 * sensores acelerômetro e giroscópio
 * @return Retorna  SUCESSO , caso o sensor seja inicializado com sucesso. Retorna  SINALIZADOR_ERRO , caso falhe.
*/
int inicializa_sensor_mpu(int endereco_sensor_mpu, Adafruit_MPU6050 &Sensor)
{
        bool status;
        status = Sensor.begin(endereco_sensor_mpu);
        if(status == false)
        {
                return SINALIZADOR_ERRO;
        }       
        Sensor.setAccelerometerRange(MPU6050_RANGE_8_G);
        Sensor.setGyroRange(MPU6050_RANGE_500_DEG);
        Sensor.setFilterBandwidth(MPU6050_BAND_5_HZ);
        return SUCESSO;
}

/*! @fn sensors_event_t *leitura_sensor_mpu(sensors_event_t *vetor_dados_mpu)
 * @brief   Faz a leitura dos sensores [ Giroscópio] e [Acelerômetro] do MPU6050
 * @param[in] Sensor é o objeto do tipo Adafruit_MPU6050 onde é armazenado
 * a estrutura do Sensor mpu_6050
 * @return Retorna a estrutura com os dados do giroscópio
*/
sensors_event_t leitura_sensor_mpu(Adafruit_MPU6050 &Sensor)
{
        bool status;
        sensors_event_t leitura_acelerometro; //!< Variável que irá guardar a leitura do acelerometro
        sensors_event_t leitura_giroscopio;     //!< Variável que irá guardar a leitura do giroscopio
        sensors_event_t leitura_temperatura;  //!< Variável que irá guardar a leitura da temperatura

        /*! \fn sensor_mpu.getEvent(&leitura_acelerometro, &leira_giroscopio, &leitura_temperatura)
        *   \brief   Evento de captura dos dados (Temperatura, Aceleração e Rotação) 
        *
        *   ******
        */
        status = Sensor.getEvent(&leitura_acelerometro, &leitura_giroscopio, &leitura_temperatura);
        if(status == false) //<! Caso não seja possível fazer a leitura
        {
                debug("Não foi possível ler os dados do sensor");
                leitura_giroscopio.gyro.status = -1;
                return  leitura_giroscopio;
        }
        else
        {
                leitura_giroscopio.gyro.status = 0;
                return leitura_giroscopio; //<! Retorna a estrutura com os dados do giroscopio
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
        if(leitura_sensor_mpu.gyro.status == SINALIZADOR_ERRO)
                return SINALIZADOR_ERRO;
        
        Serial.println();
        Serial.print("Rotacao x: ");Serial.print(leitura_sensor_mpu.gyro.x);
        Serial.print(" Rotacao y: ");Serial.print(leitura_sensor_mpu.gyro.y);
        Serial.print(" Rotacao z: ");Serial.print(leitura_sensor_mpu.gyro.z);
        Serial.println();
        return SUCESSO;
}

/*! @fn modo_operacional_sensor_mpu(Adafruit_MPU6050 &Sensor, bool status)
 * @brief Altera o modo operacional do sensor repassado por parametro
 * @param[in] Sensor é sensor que terá seu modo operacional alterado
 * @param[in] status é o modo operacional que o sensor irá ficar
 * @return Retorna SUCESSO caso o sensor consega alterar o modo operacional, Retorna SINALIZADOR_ERRO, caso contrario.
 */
bool modo_operacional_sensor_mpu(Adafruit_MPU6050 &Sensor, bool status)
{
        return Sensor.enableSleep(status);
}


int verifica_endereco_sensor(int endereco)
{
        uint8_t primeiro_endereco = 1, ultimo_endereco = 127;

        uint8_t sinalizador, endereco_atual = primeiro_endereco;
        int numero_dispositivos;
        //Serial.println("Verificando...");
        numero_dispositivos = 0;
        for (endereco_atual = primeiro_endereco; endereco_atual < ultimo_endereco; endereco_atual++)
        {
                while (endereco_atual != endereco)
                {
                        Wire.beginTransmission(endereco_atual);
                        sinalizador = Wire.endTransmission();
                        if (sinalizador == 0)
                        {
                               
                                numero_dispositivos++;
                        }
                        else if (sinalizador == 4)
                        {
                              
                        }
                        endereco_atual++;
                }
        }
}


#include "giroscopio.h"
#include "steve_debug.h"

extern const int endereco_mpu_modulo_1 = ENDERECO_0X68;
extern const int endereco_mpu_modulo_2 = ENDERECO_0X69;
extern bool ativado = true;
extern bool desativado= false;

/*! \fn int inicializa_mpu6050(void)
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

/*! \fn sensors_event_t *leitura_sensor_mpu(sensors_event_t *vetor_dados_mpu)
 * @brief   Faz a leitura dos sensores [ Giroscópio] e [Acelerômetro] do MPU6050
 * @param[in] Sensor é o objeto do tipo Adafruit_MPU6050 onde é armazenado
 * a estrutura do Sensor mpu_6050
 * @return Retorna a estrutura com os dados do giroscópio
*/
sensors_event_t leitura_sensor_mpu(Adafruit_MPU6050 &Sensor)
{

        sensors_event_t leitura_acelerometro; //!< Variável que irá guardar a leitura do acelerometro
        sensors_event_t leitura_giroscopio;     //!< Variável que irá guardar a leitura do giroscopio
        sensors_event_t leitura_temperatura;  //!< Variável que irá guardar a leitura da temperatura

        /*! \fn sensor_mpu.getEvent(&leitura_acelerometro, &leira_giroscopio, &leitura_temperatura)
        *   \brief   Evento de captura dos dados (Temperatura, Aceleração e Rotação) 
        *
        *   ******
        */
        Sensor.getEvent(&leitura_acelerometro, &leitura_giroscopio, &leitura_temperatura);

        return leitura_giroscopio; //<! Retornando o vetor com os dados lidos
}


/*! \fn void mostra_dados_giroscopio(sensors_event_t leitura_sensor_mpu)
 * @brief Mostra na Serial os dados do MPU6050 referente ao [Giroscopio]
 * @param[in] leitura_sensor_mpu é a função de captura de dados do MPU6050 
 * @return Retorna  SUCESSO , caso os dados sejam mostrados. 
 * Retorna SINALIZADOR_ERRO , caso falhe na mostragem de dados.
*/
void mostra_dados_giroscopio(sensors_event_t leitura_sensor_mpu)
{
        Serial.println();
        Serial.print("Rotacao x: ");Serial.print(leitura_sensor_mpu.gyro.x);
        Serial.print(" Rotacao y: ");Serial.print(leitura_sensor_mpu.gyro.y);
        Serial.print(" Rotacao z: ");Serial.print(leitura_sensor_mpu.gyro.z);
        Serial.println();
}

/*!
        Altera o modo operacional do sensor repassado por parametro
        @param[in] Sensor é sensor que terá seu modo operacional alterado
        @param[in] status é o modo operacional que o sensor irá ficar
        @return Retorna Sucesso se o sensor conseguir alterar o modo operacional, Retorna Sinalizador
        erro caso contrario
*/
bool modo_operacional_sensor_mpu(Adafruit_MPU6050 &Sensor, bool status)
{
        return Sensor.enableSleep(status);
}

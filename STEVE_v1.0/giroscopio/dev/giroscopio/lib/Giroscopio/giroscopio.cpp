
#include "giroscopio.h"
#include "steve_debug.h"

extern const int endereco_mpu_modulo_1 = ENDERECO_0X68;
extern const int endereco_mpu_modulo_2 = ENDERECO_0X69;

/*! @fn int inicializa_sensor_mpu(int endereco_sensor_mpu, Adafruit_MPU6050 &Sensor)
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

/*! @fn sensors_event_t leitura_sensor_mpu(Adafruit_MPU6050 &Sensor)
 * @brief   Faz a leitura dos sensores [ Giroscópio] e [Acelerômetro] do MPU6050
 * @param[in] Sensor é o objeto do tipo Adafruit_MPU6050 onde é armazenado
 * a estrutura do Sensor mpu_6050
 * @return Retorna a estrutura com os dados do giroscópio
*/
sensors_event_t leitura_sensor_mpu(Adafruit_MPU6050 &Sensor)
{
        bool status_leitura_sensor;
        sensors_event_t leitura_acelerometro; //!< Variável que irá guardar a leitura do acelerometro
        sensors_event_t leitura_giroscopio;     //!< Variável que irá guardar a leitura do giroscopio
        sensors_event_t leitura_temperatura;  //!< Variável que irá guardar a leitura da temperatura

        /*! \fn sensor_mpu.getEvent(&leitura_acelerometro, &leira_giroscopio, &leitura_temperatura)
        *   \brief   Evento de captura dos dados (Temperatura, Aceleração e Rotação) 
        *
        *   ******
        */
        status_leitura_sensor = Sensor.getEvent(&leitura_acelerometro, &leitura_giroscopio, &leitura_temperatura);
        if(status_leitura_sensor == false || verifica_endereco_sensor() == SINALIZADOR_ERRO) //<! Caso não seja possível fazer a leitura
        {
                debug("Não foi possível ler os dados do sensor");
                leitura_acelerometro.acceleration.status = SINALIZADOR_ERRO;
                return  leitura_acelerometro;
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
        if(leitura_sensor_mpu.acceleration.status == SINALIZADOR_ERRO)
                return SINALIZADOR_ERRO;
        
        Serial.println();
        Serial.print("Rotacao x: ");Serial.print(leitura_sensor_mpu.acceleration.x);
        Serial.print(" Rotacao y: ");Serial.print(leitura_sensor_mpu.acceleration.y);
        Serial.print(" Rotacao z: ");Serial.print(leitura_sensor_mpu.acceleration.z);
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

int verifica_endereco_sensor()
{
        byte verificador_erro, endereco;
        const uint8_t endereco_inicial = 1, endereco_final = 127;
        const int nenhum_dispositivo = 0;
        int numero_dispositivos;
        
        numero_dispositivos = 0;
        for(endereco = endereco_inicial; endereco < endereco_final; endereco++ ) {
                Wire.beginTransmission(endereco);
                verificador_erro = Wire.endTransmission();
                if (verificador_erro == SUCESSO)
                {
                       /* Serial.print("I2C device found at address 0x");
                        if (endereco<16) 
                        {
                                Serial.print("0");
                        }
                        Serial.println(endereco,HEX);*/
                        numero_dispositivos++;
                }
                else if (verificador_erro==4) 
                {
                       Serial.print(" Erro desconhecido no endereço 0x");
                        if (endereco<16) 
                        {
                                Serial.print("0");
                        }
                        Serial.println(endereco,HEX);
                }    
        }
        if (numero_dispositivos == nenhum_dispositivo) 
        {
               return SINALIZADOR_ERRO;
        }
        else 
        {
               return SUCESSO;
        }
             
}

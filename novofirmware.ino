#include <Arduino.h>
#include <stdlib.h>
#include <Wire.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

/********************************************* INDEX DE FUNÇÕES PARA UTILIZAR **************************************************/
void ativacao_atuador_standup(void);
/********************************************* MAPEAMENTO DE PORTAS ************************************************************/
/* BATERIA     */
const int bat_monitor                                = 34;     /* [MONITORAMENTO] Monitoramento da bateria                     */
/* ATUADORES sem multiplexador  */
/*const int atuador_standup_avanco                   = 32;     /* [ATUADOR] Standup: pino de [avanço]                          */
/*const int atuador_standup_recuo                    = 35;     /* [ATUADOR] Standup: pino de [recuo]                           */
/*const int atuador_elevador_base_avanco             = 25;     /* [ATUADOR] Elevador da base: pino de [avanço]                 */
/*const int atuador_elevador_base_recuo              = 26;     /* [ATUADOR] Elevador da base: pino de [recuo]                  */
/*const int atuador_elevador_suporte_circ_avanco     = 27;     /* [ATUADOR] Elevador do suporte circulatório: pino de [avanço] */
/*const int atuador_elevador_suporte_circ_recuo      = 14;     /* [ATUADOR] Elevador do suporte circulatório: pino de [recuo]  */
/*const int atuador_suporte_circu_avanco             = 12;     /* [ATUADOR] Suporte circulatório: pino de [avanço]             */
/*const int atuador_suporte_circu_recuo              = 13;     /* [ATUADOR] Suporte circulatório: pino de [recuo]              */
/*const int atuador_altura_encosto_avanco            = 15;     /* [ATUADOR] Altura do enconsto: pino de [avanço]               */
/*const int atuador_altura_encosto_recuo             = 23;     /* [ATUADOR] Altura do enconsto: pino de [recuo]                */
/*const int atuador_inclinacao_encosto_avanco        = 16;     /* [ATUADOR] Inclinação do encosto: pino de [avanço]            */
/*const int atuador_inclinacao_encosto_recuo         = 17;     /* [ATUADOR] Inclinação do encosto: pino de [recuo]             */
/*const int atuador_distancia_assento_encosto_avanco = 18;     /* [ATUADOR] Distancia do assento e encosto: pino de [avanço]   */
/*const int atuador_distancia_assento_encosto_recuo  = 19;     /* [ATUADOR] Distancia do assento e encosto: pino de [recuo]    */

/* Atuadores com multiplexador */
const int multiplex_port_s0                          = 25;     /* [Multiplexador] Endereço 0 do multiplexador                  */ 
const int multiplex_port_s1                          = 26;     /* [Multiplexador] Endereço 1 do multiplexador                  */ 
const int multiplex_port_s2                          = 27;     /* [Multiplexador] Endereço 2 do multiplexador                  */
const int multiplex_port_s3                          = 15;     /* [Multiplexador] Endereço 3 do multiplexador                  */ 
const int multiplex_module_enable_1                  = 14;     /* [Multiplexador] Enable para ativação do multiplexador 1      */ 
const int multiplex_module_enable_2                  = 13;     /* [Multiplexador] Enable para ativação do multiplexador 2      */


/* PORTAS I2C  */
const int giroscopio_encosto_sda                     = 21;     /* [SENSOR] Giroscópio para o encosto: pino I2C [sda]           */
const int giroscopio_encosto_scl                     = 22;     /* [SENSOR] Giroscópio para o encosto: pino I2C [scl]           */
const int giroscopio_suporte_circu_sda               = 23;     /* [SENSOR] Giroscópio suporte circulatorio: pino I2C [sda]     */
const int giroscopio_suporte_circu_scl               = 33;     /* [SENSOR] Giroscópio suporte circulatorio: pino I2C [scl]     */
/*******************************************  BLUETOOTH LOW ENERGY  **********************************************************/


/* BLOCO DO GATT */
#define SERVICE_UUID            "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"      /* Serviço do atuador                      */
#define CHARACTERISTIC_UUID_RX  "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"      /* Caracteristica do atuador               */

/* FUNÇÕES E CLASSES DO BLE */
BLECharacteristic *pCharacteristic;
bool deviceConnected = false;
void startBLE(void);
/* Pilha de execução do BLE Server */
class MyServerCallbacks: public BLEServerCallbacks 
{
    void onConnect(BLEServer* pServer)
    {
      deviceConnected = true;
    };
    void onDisconnect(BLEServer* pServer)
    {
      deviceConnected = false;
    }
};
/* Pilha de execução do BLE Client */
class MyCallbacks: public BLECharacteristicCallbacks
{
    void onWrite(BLECharacteristic *pCharacteristic)
    {
      
      std::string value = pCharacteristic->getValue();
      if(value == "1")
      {
       ledcWrite(0, 1024);
        delay(100);
      }
      else
      {
        ledcWrite(0, 0);
        delay(100);
      }
};

/****************************************  FUNÇÕES DO SISTEMA  ***********************************************************/
/* Função de Start do BLE */
void startBLE(void)
{
  /* Create the BLE Device */
  BLEDevice::init("Steve_TEST"); 
 
  /* Configura o dispositivo como Servidor BLE */
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());
  /* Cria o servico UART */
  BLEService *pService = pServer->createService(SERVICE_UUID);
 
  /* cria uma característica BLE para recebimento dos dados */
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID_RX,
                                         BLECharacteristic::PROPERTY_WRITE
                                       );
  pCharacteristic->setCallbacks(new MyCallbacks());
  /* Inicia o serviço */
  pService->start();
  /* Inicia a descoberta do ESP32 */
  pServer->getAdvertising()->start();
  #ifdef DEBUG 
    Serial.println("Esperando um cliente se conectar...");
  #endif
}


/*****************************************************  SETUP  ***********************************************************/
void setup() 
{
  Serial.begin(115200);
  pinMode(giroscopio_suporte_circu_scl, OUTPUT);
  ledcAttachPin(giroscopio_suporte_circu_scl, 0);
  ledcSetup(0, 1000, 10);
  startBLE();
 
}
/*****************************************************  MAIN  ************************************************************/
void loop() 
{

}
//void mapping_multiplex()

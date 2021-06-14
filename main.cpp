#include <Arduino.h>
#include <stdlib.h>
#include <Wire.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

const int led = 2;
/********************************************* INDEX DE FUNÇÕES PARA UTILIZAR **************************************************/
void ativacao_atuador_standup(void);
void map_multiplex(void);
void multiplex_write(int pin);
/********************************************* MAPEAMENTO DE PORTAS ************************************************************/
/* BATERIA     */
const int bat_monitor                                = 34;     /* [MONITORAMENTO] Monitoramento da bateria                     */
/* ENUMERAÇÃO DOS ATUADORES   */
enum atuadores
{
  atuador_standup_avanco,                                      /* [ATUADOR] Standup: pino de [avanço]                          */
  atuador_standup_recuo,                                       /* [ATUADOR] Standup: pino de [recuo]                           */
  atuador_elevador_base_avanco,                                /* [ATUADOR] Elevador da base: pino de [avanço]                 */
  atuador_elevador_base_recuo,                                 /* [ATUADOR] Elevador da base: pino de [recuo]                  */
  atuador_elevador_suporte_circ_avanco,                        /* [ATUADOR] Elevador do suporte circulatório: pino de [avanço] */
  atuador_elevador_suporte_circ_recuo,                         /* [ATUADOR] Elevador do suporte circulatório: pino de [recuo]  */
  atuador_suporte_circu_avanco,                                /* [ATUADOR] Suporte circulatório: pino de [avanço]             */
  atuador_suporte_circu_recuo,                                 /* [ATUADOR] Suporte circulatório: pino de [recuo]              */
  atuador_altura_encosto_avanco,                               /* [ATUADOR] Altura do enconsto: pino de [avanço]               */
  atuador_altura_encosto_recuo,                                /* [ATUADOR] Altura do enconsto: pino de [recuo]                */
  atuador_inclinacao_encosto_avanco,                           /* [ATUADOR] Inclinação do encosto: pino de [avanço]            */
  atuador_inclinacao_encosto_recuo,                            /* [ATUADOR] Inclinação do encosto: pino de [recuo]             */
  atuador_distancia_assento_encosto_avanco,                    /* [ATUADOR] Distancia do assento e encosto: pino de [avanço]   */
  atuador_distancia_assento_encosto_recuo,                     /* [ATUADOR] Distancia do assento e encosto: pino de [recuo]    */
};
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
      
      String value = (pCharacteristic->getValue().c_str());
      int pin = value.toInt();
      multiplex_write(pin);
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
  map_multiplex();
  pinMode(led, OUTPUT);
  startBLE();
 
}
/*****************************************************  MAIN  ************************************************************/
void loop() 
{

}

// * Mapeamento das portas do Multiplexador */
void map_multiplex(void)
{
  int i;
  /* Quantidade de pinos usados pelos dois multiplexadores */
  const int qtd_pin_multiplexador = 6;
  /* vetor com todos os pinos utilizados pelo multiplexador */
  int setup_pin_multiplex[qtd_pin_multiplexador] = 
  {
    multiplex_port_s0,
    multiplex_port_s1,
    multiplex_port_s2,
    multiplex_port_s3,
    multiplex_module_enable_1,
    multiplex_module_enable_2
  };

  /* Laço para inicializaçao das portas como [OUTPUT] e inicialização de todas como [LOW] */
  for(i=0;i< qtd_pin_multiplexador;i++)
  {
    pinMode(setup_pin_multiplex[i],OUTPUT);
    digitalWrite(setup_pin_multiplex[i],LOW);
  }
}

/* Função para escrita no multiplexador. Ativa a porta passada como parâmetro [ Entre 0 - 15] */
void multiplex_write(int pin)
{
  /* Ativa o multiplexador 1 */
  digitalWrite(multiplex_module_enable_1,LOW);
  switch (pin)
  {
  /* Escreve no pino 0*/
  case atuador_standup_avanco:
    digitalWrite(multiplex_port_s0,LOW);
    digitalWrite(multiplex_port_s1,LOW);
    digitalWrite(multiplex_port_s2,LOW);
    digitalWrite(multiplex_port_s3,LOW);
     Serial.println("Acionou o pino 0");
    break;
  /* Escreve no pino 1*/ 
  case atuador_standup_recuo:
    digitalWrite(multiplex_port_s0,HIGH);
    digitalWrite(multiplex_port_s1,LOW);
    digitalWrite(multiplex_port_s2,LOW);
    digitalWrite(multiplex_port_s3,LOW);
    Serial.println("Acionou o pino 1");
    break;
  /* Escreve no pino 2*/
  case atuador_elevador_base_avanco:
    digitalWrite(multiplex_port_s0,LOW);
    digitalWrite(multiplex_port_s1,HIGH);
    digitalWrite(multiplex_port_s2,LOW);
    digitalWrite(multiplex_port_s3,LOW);
    Serial.println("Acionou o pino 2");
    break;
  /* Escreve no pino 3*/
  case atuador_elevador_base_recuo:
    digitalWrite(multiplex_port_s0,HIGH);
    digitalWrite(multiplex_port_s1,HIGH);
    digitalWrite(multiplex_port_s2,LOW);
    digitalWrite(multiplex_port_s3,LOW);
    Serial.println("Acionou o pino 3");
    break;
  /* Escreve no pino 4*/
  case atuador_elevador_suporte_circ_avanco:
    digitalWrite(multiplex_port_s0,LOW);
    digitalWrite(multiplex_port_s1,LOW);
    digitalWrite(multiplex_port_s2,HIGH);
    digitalWrite(multiplex_port_s3,LOW);
    Serial.println("Acionou o pino 4");
    break;
  /* Escreve no pino 5*/
  case atuador_elevador_suporte_circ_recuo:
    digitalWrite(multiplex_port_s0,HIGH);
    digitalWrite(multiplex_port_s1,LOW);
    digitalWrite(multiplex_port_s2,HIGH);
    digitalWrite(multiplex_port_s3,LOW);
    Serial.println("Acionou o pino 5");
    break;
  /* Escreve no pino 6*/
  case atuador_suporte_circu_avanco:
    digitalWrite(multiplex_port_s0,LOW);
    digitalWrite(multiplex_port_s1,HIGH);
    digitalWrite(multiplex_port_s2,HIGH);
    digitalWrite(multiplex_port_s3,LOW);
    Serial.println("Acionou o pino 6");
    delay(5);
    digitalWrite(multiplex_module_enable_1,HIGH);
    break;
  /* Escreve no pino 7*/
  case atuador_suporte_circu_recuo:
    break;
  /* Escreve no pino 8*/
  case atuador_altura_encosto_avanco:
    break;
  /* Escreve no pino 9*/
  case atuador_altura_encosto_recuo:
    break;
  /* Escreve no pino 10*/
  case atuador_inclinacao_encosto_avanco:
    break;
  /* Escreve no pino 11*/
  case atuador_inclinacao_encosto_recuo:
    break;
  /* Escreve no pino 12*/
  case atuador_distancia_assento_encosto_avanco:
    break;
  /* Escreve no pino 13*/
  case atuador_distancia_assento_encosto_recuo:
    break;
  /* Escreve no pino 14*/
  case 14:
    break;
  /* Escreve no pino 15*/
  case 15:
    break;
  /* Desliga o Multiplexador*/  
  default:
    break;
  }
}

/* Verificar se o enquanto pressionar no bluetooth fica sempre ativando */
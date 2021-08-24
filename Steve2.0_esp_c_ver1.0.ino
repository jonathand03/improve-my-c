/*
    Lead - Centro de Pesquisa, Desenvolvimento e Inovação Dell

    Projeto: STEVE 
*/

#include <Arduino.h>
#include <stdlib.h>
#include <Wire.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include "defines.h"








uint8_t i2cData[14]; // Buffer for I2C data
uint8_t flagi2cbusy =0;
uint8_t sensores_portaA=0;
uint8_t sensores_portaB=0;
uint8_t leitura_portaA = 0;
uint8_t leitura_portaB =0;
int32_t timeNow = 0;
int32_t timer = 0;



/* BLE */
BLECharacteristic *pCharacteristic;
bool deviceConnected = false;
void startBLE(void);

/* Prototipo das funções MCP */
void setupMCPins(void);
void configurePort(uint8_t address, uint8_t port, uint8_t type);
void writeBlockData(uint8_t address, uint8_t port, uint8_t data);
void digitalWriteMCP(uint8_t address, int pin, int value);
uint8_t digitalReadMCP(uint8_t address, uint8_t pin);
uint8_t digitalReadPortMCP(uint8_t address, uint8_t port);



bool acionar_atuador(uint8_t atuador, uint8_t valor);



void tratar_protocolo_teste(uint8_t atuador, uint8_t valor);
void enviar_status_sensores(void);





class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };
 
    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};


class MyCallbacks: public BLECharacteristicCallbacks 
{
  void onRead(BLECharacteristic *pCharacteristic) 
  {
    char txString[20];                 
    
    pCharacteristic->setValue(txString);
  }
  void onWrite(BLECharacteristic *pCharacteristic) 
  {
    uint8_t* rxValue = pCharacteristic->getData();      //recebendo o array de bytes
    std::string rxValue1 = pCharacteristic->getValue(); //recebendo o mesmo array como string
    
    if (rxValue1.length() == 20)                        // verificar se o pacote é do tamanho esperado 
    {                      
      #ifdef DEBUG 
        Serial.println("*********"); 
        Serial.print("Received Value: ");
        for (int i = 0; i < rxValue1.length(); i++) {     //utilizar esse for para rodar o array e calcular o checksum
          Serial.print(rxValue[i],HEX);
          Serial.print("  ");
        }
        Serial.println();
        Serial.println("*********");
      #endif

      
      if ((rxValue[0] == 0x00) && (rxValue[1] == 0x01))
      {       
        
      }//if(ID confirmed)

     
    }else if(rxValue1.length() == 5){

      #ifdef DEBUG 
        Serial.println("*********"); 
        Serial.print("Received Value: ");
        for (int i = 0; i < rxValue1.length(); i++) {     //utilizar esse for para rodar o array e calcular o checksum
          Serial.print(rxValue[i],HEX);
          Serial.print("  ");
        }
        Serial.println();
        Serial.println("*********");
      #endif
      
      if ((rxValue[0] == 0x00) && (rxValue[1] == 0x02))
      {
        if(rxValue[3]==rxValue[4]){
          tratar_protocolo_teste(rxValue[2], rxValue[3]);
        }
      }
      
    }
  }//void onWrite(BLECharacteristic *pCharacteristic) 
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {

  Wire.begin();
  Wire.setClock(400000UL);
  Serial.begin(9600);
  #ifdef DEBUG 
    Serial.println("\n");
    Serial.println("STEVE Iniciando");
  #endif

      
      
  setupMCPins();
  
  startBLE();

  
  timer = (xTaskGetTickCount()/portTICK_PERIOD_MS);//tempo atual
   
}


void loop() 
{
  timeNow = (xTaskGetTickCount()/portTICK_PERIOD_MS);//tempo atual
  if((timeNow-timer)>10000){
    timer = timeNow;

    leitura_portaA = digitalReadPortMCP(MCPsenAddress, GPA);
    leitura_portaB = digitalReadPortMCP(MCPsenAddress, GPB);
    if((sensores_portaA != leitura_portaA)||(sensores_portaB != leitura_portaB)){
      sensores_portaA = leitura_portaA;
      sensores_portaB != leitura_portaB;
      enviar_status_sensores();    
    }
  }
  delay(10);
  
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void tratar_protocolo_teste(uint8_t atuador, uint8_t valor){


  #ifdef DEBUG 
        Serial.print("*** ");
        Serial.print(atuador);
        Serial.print("  ");
        Serial. print(valor);
        Serial.println(" ***");
  #endif
  switch (atuador){
    case 1: 
      
      if(valor==0){
        acionar_atuador(actElevacao0, 0);
        acionar_atuador(actElevacao1, 0);
      }else if(valor==1){
        acionar_atuador(actElevacao0, 1);
        acionar_atuador(actElevacao1, 0);
        
      }else if(valor==2){
        acionar_atuador(actElevacao0, 0);
        acionar_atuador(actElevacao1, 1);
      }
      break;
    case 2:
      if(valor==0){
        acionar_atuador(actAlturaEncosto0, 0);
        acionar_atuador(actAlturaEncosto1, 0);
      }else if(valor==1){
        acionar_atuador(actAlturaEncosto0, 1);
        acionar_atuador(actAlturaEncosto1, 0);
        
      }else if(valor==2){
        acionar_atuador(actAlturaEncosto0, 0);
        acionar_atuador(actAlturaEncosto1, 1);
      }
      break;
    case 3:
      if(valor==0){
        acionar_atuador(actAssento0, 0);
        acionar_atuador(actAssento1, 0);
      }else if(valor==1){
        acionar_atuador(actAssento0, 1);
        acionar_atuador(actAssento1, 0);
        
      }else if(valor==2){
        acionar_atuador(actAssento0, 0);
        acionar_atuador(actAssento1, 1);
      }
      break;
    case 4:
      if(valor==0){
        acionar_atuador(actEncosto0, 0);
        acionar_atuador(actEncosto1, 0);
      }else if(valor==1){
        acionar_atuador(actEncosto0, 1);
        acionar_atuador(actEncosto1, 0);
        
      }else if(valor==2){
        acionar_atuador(actEncosto0, 0);
        acionar_atuador(actEncosto1, 1);
      }
      break;
    case 5:
      if(valor==0){
        acionar_atuador(actAlturaGeral0, 0);
        acionar_atuador(actAlturaGeral1, 0);
      }else if(valor==1){
        acionar_atuador(actAlturaGeral0, 1);
        acionar_atuador(actAlturaGeral1, 0);
        
      }else if(valor==2){
        acionar_atuador(actAlturaGeral0, 0);
        acionar_atuador(actAlturaGeral1, 1);
      }
      break;
    case 6:
      if(valor==0){
        acionar_atuador(actAlturaBase0, 0);
        acionar_atuador(actAlturaBase1, 0);
      }else if(valor==1){
        acionar_atuador(actAlturaBase0, 1);
        acionar_atuador(actAlturaBase1, 0);
        
      }else if(valor==2){
        acionar_atuador(actAlturaBase0, 0);
        acionar_atuador(actAlturaBase1, 1);
      }
      break;
    case 7:
      if(valor==0){
        acionar_atuador(actSSC0, 0);
        acionar_atuador(actSSC1, 0);
      }else if(valor==1){
        acionar_atuador(actSSC0, 1);
        acionar_atuador(actSSC1, 0);
        
      }else if(valor==2){
        acionar_atuador(actSSC0, 0);
        acionar_atuador(actSSC1, 1);
      }
      break;

    
        
  }
  
}




bool acionar_atuador(int atuador, int valor){
  digitalWriteMCP(MCPactAddress, atuador, valor);

  return digitalReadMCP(MCPactAddress, atuador);
}

bool ler_sensor(int sensor){
  return digitalReadMCP(MCPsenAddress, sensor);
}



/* Função para Configurar pinos do MCP */
void setupMCPins()
{
    pinMode(ResetMCPAct, OUTPUT);
    pinMode(ResetMCPSen, OUTPUT);
    digitalWrite(ResetMCPAct,HIGH);
    digitalWrite(ResetMCPSen,HIGH);
    
    pinMode(02,OUTPUT); //pino onboard
    //Configura os pinos do MCP ligado aos sensores como Entrada
    configurePort(MCPsenAddress,IODIRA, INPUT);
    configurePort(MCPsenAddress,IODIRB, INPUT);

    //Configura os pinos do MCP ligado aos atuadores como Saída
    configurePort(MCPactAddress,IODIRA, OUTPUT);
    configurePort(MCPactAddress,IODIRB, OUTPUT);

    
    

    acionar_atuador(actElevacao0, LOW);
    delay(10);
    acionar_atuador(actElevacao1, LOW);
    delay(10);
    acionar_atuador(actSSC0, LOW);
    delay(10);
    acionar_atuador(actSSC1, LOW);
    delay(1);
    acionar_atuador(actAlturaEncosto0, LOW);
    delay(1);
    acionar_atuador(actAlturaEncosto1, LOW);
    delay(1);
    acionar_atuador(actEncosto1, LOW);
    delay(1);
    acionar_atuador(actEncosto0, LOW);
    delay(1);
    acionar_atuador(actAssento0, LOW);
    delay(1);
    acionar_atuador(actAssento1, LOW);
    delay(1);
    acionar_atuador(actAlturaGeral0, LOW);
    delay(1);
    acionar_atuador(actAlturaGeral1, LOW);
    delay(1);
    acionar_atuador(actAlturaBase0, LOW);
    delay(1);
    acionar_atuador(actAlturaBase1, LOW);
    delay(1);

}



//Configura o modo dos pinos das portas (GPA ou GPB)
//como parametro passamos:
//  port: GPA ou GPB
//  type:
//    INPUT para todos os pinos da porta trabalharem como entrada
//    OUTPUT para todos os pinos da porta trabalharem como saída
void configurePort(uint8_t address, uint8_t port, uint8_t type)
{
  if(type == INPUT)
  {
    writeBlockData(address, port, 0xFF);
  }
  else if(type == OUTPUT)
  {
    writeBlockData(address, port, 0x00);
  }
}

//muda o estado de um pino desejado
void digitalWriteMCP(uint8_t address, int pin, int value)
{
  uint8_t port;
  uint8_t v;

  

  //de 0 a 7 porta A, de 8 a 15 porta B
  if(pin < 8){
    port = GPA;
 
  }else{
    port = GPB;
 
    pin -= 8;
  }
  v = digitalReadPortMCP(address, port); 
      
  if (value == LOW){
    v &= ~(B00000001 << (pin)); // muda o pino para LOW
    //v = 0;
  }
  else if (value == HIGH){
    v |= (B00000001 << (pin)); // muda o pino para HIGH
    //v=0xFF;
  }
  writeBlockData(address, port, v);
}

uint8_t digitalReadMCP(uint8_t address, uint8_t pin)
{
  uint8_t port;
  uint8_t byteVal;

  if(pin < 8){
    port = GPA;
  }else{
    port = GPB;
    pin -= 8;
  }

  while(flagi2cbusy){delay(10);}
  flagi2cbusy = 1;
  Wire.beginTransmission(address);
  Wire.write(port);  // read the inputs off PORT B
  Wire.requestFrom(address, 1); // ask for 1 byte
  byteVal = Wire.read(); // read it 
  Wire.endTransmission(); 
  flagi2cbusy = 0;
  
  return(byteVal & (1<<pin)) != 0;
}

uint8_t digitalReadPortMCP(uint8_t address, uint8_t port)
{ 
  uint8_t byteVal;

  while(flagi2cbusy){delay(10);}
  flagi2cbusy = 1;
  Wire.beginTransmission(address);
  Wire.write(port);  // read the inputs off PORT B
  Wire.endTransmission();
  Wire.requestFrom(address, 1); // ask for 1 byte
  if(Wire.available()){
    byteVal = Wire.read(); // read it 
  }
  
  flagi2cbusy = 0;
    
  return byteVal;

}

void writeBlockData(uint8_t address, uint8_t port, uint8_t data)
{
  while(flagi2cbusy){delay(10);}
  flagi2cbusy = 1;
    Wire.beginTransmission(address);
    Wire.write(port);
    Wire.write(data);
    Wire.endTransmission();
    
  flagi2cbusy = 0;
 }




void enviar_status_sensores(void)
{
  byte protocolo[20];
  byte portaA=0;
  byte portaB=0;

  portaA = digitalReadPortMCP(MCPsenAddress, GPA);
  portaB = digitalReadPortMCP(MCPsenAddress, GPB);

  //portaA = random(255);
  //portaB = random(255);

  //flagSendProtocol |= (1<<0);
  if (deviceConnected)
  {
    protocolo[0] = 0x00;
    protocolo[1] = 0x01;

    protocolo[2] = ((portaA & (1<<7)) != 0);
    protocolo[3] = ((portaA & (1<<5)) != 0);
    protocolo[4] = ((portaA & (1<<4)) != 0);
    protocolo[5] = ((portaA & (1<<3)) != 0);
    protocolo[6] = ((portaA & (1<<2)) != 0);
    protocolo[7] = ((portaA & (1<<1)) != 0);
    protocolo[8] = ((portaA & (1<<0)) != 0);
    protocolo[9] = ((portaB & (1<<7)) != 0);
    protocolo[10] = ((portaB & (1<<0)) != 0);
    protocolo[11] = ((portaB & (1<<1)) != 0);
    protocolo[12] = ((portaB & (1<<2)) != 0);
    protocolo[13] = ((portaB & (1<<3)) != 0);
    protocolo[14] = ((portaB & (1<<4)) != 0);
    protocolo[15] = ((portaB & (1<<5)) != 0);
    protocolo[16] = ((portaB & (1<<6)) != 0);
    protocolo[17] = ((portaB & (1<<7)) != 0);
    

    protocolo[19] = 0xFF;//checksum

   
    #ifdef DEBUG 
      Serial.print("*** Sent Value: ");
      for(int i=0;i<20;i++){
        Serial.print(protocolo[i], HEX);
        Serial.print("  ");
      }
      Serial.println(" ***");
    #endif

    pCharacteristic->setValue(protocolo,20);

    pCharacteristic->notify();

  }//if(device is connected)
}//void enviar_status_sensores(void)

/* Função de Start do BLE */
void startBLE(void)
{
  // Create the BLE Device
  BLEDevice::init("STEVE Ver2.0"); // Give it a name
 
  // Configura o dispositivo como Servidor BLE
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());
 
  // Cria o servico UART
  BLEService *pService = pServer->createService(SERVICE_UUID);
 
  // Cria uma Característica BLE para envio dos dados
  pCharacteristic = pService->createCharacteristic(
                      DHTDATA_CHAR_UUID,
                      BLECharacteristic::PROPERTY_NOTIFY
                    );
                       
  pCharacteristic->addDescriptor(new BLE2902());
 
  // cria uma característica BLE para recebimento dos dados
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID_RX,
                                         BLECharacteristic::PROPERTY_WRITE
                                       );
 
  pCharacteristic->setCallbacks(new MyCallbacks());
 
  // Inicia o serviço
  pService->start();
 
  // Inicia a descoberta do ESP32
  pServer->getAdvertising()->start();
  #ifdef DEBUG 
    Serial.println("Esperando um cliente se conectar...");
  #endif
}

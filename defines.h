
/* LED Onboard*/
#define LED_BUILTIN 02

#define DEBUG true

/* SO PARAMETERS*/
#define mainCore 00
#define _2ndCore 01
#define I2C_TIMEOUT    1000
#define Serial_TIMEOUT 4000

/* I2C Adressed */
#define MCPsenAddress  0x24 // ->MCP IO Sensors   24 = A2 high, A1 low, A0 low
#define MCPactAddress  0x26 // ->MCP IO Actuators 26 = A2 high, A1 high, A0 low
#define MPUsscAddress  0x69 // ->MPU Accelerometers :: AD0 is logic high on the PCB
#define MPUbckAddress  0x68 // ->MPU back STEVE ang :: AD0 is logic low on PCB
#define intMPUssc      19
#define intMPUbck      18


/* MCP rest pin */
#define ResetMCPAct  12
#define ResetMCPSen  05

//ENDEREÇOS DE REGISTRADORES
#define GPA 0x12    // DATA PORT REGISTER A
#define GPB 0x13    // DATA PORT REGISTER B 
#define IODIRA 0x00 // I/O DIRECTION REGISTER A
#define IODIRB 0x01 // I/O DIRECTION REGISTER B


/* Actuator Mapping */

#define actElevacao0  2   //lowering actuator
#define actElevacao1  3   //lifting actuator 
#define actSSC0   4   //Down SSC
#define actSSC1   5   //rising SSC
#define actAlturaEncosto0    6   //Micro Adjustment of X1 // Altura do encosto
#define actAlturaEncosto1    7   //Micro Adjustment of X1 // Altura do encosto
#define actEncosto0    8   //micro adjustment X2 ang pos
#define actEncosto1    9   //micro adjustment X2 ang neg
#define actAssento0   10  //micro adjustment X2
#define actAssento1   11  //micro adjustment X2
#define actAlturaGeral0    12  //
#define actAlturaGeral1    13  //
#define actAlturaBase0    14  //
#define actAlturaBase1    15  //

/* Limit Switches Mapping */

#define senElevRvs  0   //initial stroke lss 6. Steve in a sitting position
#define senElevFwd  1   //limit switch full stroke. Steve in an elevated position
#define senSSCRvs   2   //Down SSC
#define senSSCFwd   3   //Up SSC
#define senX1Rvs    4   //Micro Adjustment of X1 // Altura do encosto
#define senX1Fwd    5   //Micro Adjustment of X1 // Altura do encosto
#define senX2Fwd    7   //
#define senX2Rvs    8   //
#define senX2Fwd2   9   //
#define senX2Rvs2   10  //
#define senX3Fwd    11  //
#define senX3Rvs    12  //
#define senX4Fwd    13  //
#define senX4Rvs    14  //


/* Blutooth LE */

#define SERVICE_UUID           "6E400001-B5A3-F393-E0A9-E50E24DCCA9E" // UART service UUID
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define DHTDATA_CHAR_UUID       "6E400003-B5A3-F393-E0A9-E50E24DCCA9E" 

/*

QueueHandle_t xQueue_steveConnected;
QueueHandle_t xQueue_steveElevated;
QueueHandle_t xQueue_sscAble;
QueueHandle_t xQueue_sscAngle;
QueueHandle_t xQueue_sscCycleInterval;
QueueHandle_t xQueue_sscCycleTime;
QueueHandle_t xQueue_x1Moving;
QueueHandle_t xQueue_x2Moving;
QueueHandle_t xQueue_x3Moving;
QueueHandle_t xQueue_x4Moving;
QueueHandle_t xQueue_ableJoystick;
QueueHandle_t xQueue_ableHeadSteve;
QueueHandle_t xQueue_steveMoving;
QueueHandle_t xQueue_sensorConnected;
QueueHandle_t xQueue_heartBeats;
QueueHandle_t xQueue_sensorBatt;
QueueHandle_t xQueue_steveBatt;


*/

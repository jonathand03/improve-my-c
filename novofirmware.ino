#include <Arduino.h>
#include <stdlib.h>
#include <Wire.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
/* #include "defines.h" */


/*************************************** I2C *************************************************/
    /* Mapeamento do MCP23017 */
    #define MCPsenAddress  0x24       /* [MCP] IO Sensors   24 = A2 high, A1 low, A0 low  */
    #define MCPactAddress  0x26       /* [MCP] IO Actuators 26 = A2 high, A1 high, A0 low */
    #define ResetMCPSen  05           /* [MCP] IO Sensors reset pin                       */
    #define ResetMCPAct  12           /* [MCP] IO Actuators reset pin                     */
    #define GPA 0x12                  /* [MCP] DATA PORT REGISTER A                       */
    #define GPB 0x13                  /* [MCP] DATA PORT REGISTER B                       */
    #define IODIRA 0x00               /* [MCP] I/O DIRECTION REGISTER A                   */
    #define IODIRB 0x01               /* [MCP] I/O DIRECTION REGISTER B                   */

    /* Mapeamento do Acelerometro */
    #define MPUsscAddress  0x69       /* [MPU] Accelerometers :: AD0 is logic high on the PCB    */
    #define MPUbckAddress  0x68       /* [MPU] back STEVE angulation :: AD0 is logic low on PCB  */
    #define intMPUssc      19
    #define intMPUbck      18

    /* Actuator Mapping */
    #define actElevacao0  2         /* lowering actuator                           */
    #define actElevacao1  3         /* lifting actuator                            */
    #define actSSC0   4             /* Down SSC                                    */
    #define actSSC1   5             /* rising SSC                                  */
    #define actAlturaEncosto0  6    /* Micro Adjustment of X1  [Altura do encosto] */
    #define actAlturaEncosto1  7    /* Micro Adjustment of X1  [Altura do encosto] */
    #define actEncosto0  8          /* Micro adjustment X2 ang pos                 */
    #define actEncosto1  9          /* Micro adjustment X2 ang neg                 */
    #define actAssento0  10         /* Micro adjustment X2                         */
    #define actAssento1  11         /* Micro adjustment X2                         */
    #define actAlturaGeral0  12     /* FREE PORT                                   */
    #define actAlturaGeral1  13     /* FREE PORT                                   */
    #define actAlturaBase0   14     /* FREE PORT                                   */
    #define actAlturaBase1   15     /* FREE PORT                                   */

    /* Limit Switches Mapping */
    #define senElevRvs  0   /* initial stroke lss 6. Steve in a sitting position       */
    #define senElevFwd  1   /* limit switch full stroke. Steve in an elevated position */
    #define senSSCRvs   2   /* Down SSC                                    */
    #define senSSCFwd   3   /* Up SSC                                      */
    #define senX1Rvs    4   /* Micro Adjustment of X1 [Altura do encosto]  */
    #define senX1Fwd    5   /* Micro Adjustment of X1 [Altura do encosto]  */
    #define senX2Fwd    7   /* FREE PORT                                   */
    #define senX2Rvs    8   /* FREE PORT                                   */
    #define senX2Fwd2   9   /* FREE PORT                                   */
    #define senX2Rvs2   10  /* FREE PORT                                   */
    #define senX3Fwd    11  /* FREE PORT                                   */
    #define senX3Rvs    12  /* FREE PORT                                   */
    #define senX4Fwd    13  /* FREE PORT                                   */
    #define senX4Rvs    14  /* FREE PORT                                   */

/************************************** SETUP ***********************************************/
#ifndef COM_H
#define COM_H

#include <stdint.h>
#include <Arduino.h>

/* Communcation Pin */
#define TX_PIN 2
#define RX_PIN 3
/* Baud Rate */
#define SERIAL_BAUD 115200
/* Communication Flags */
#define COM_SUCESS 0
#define COM_TIMEOUT 1
#define COM_ERROR 2

class SerialCom
{
    private:
        typedef struct
        {
            bool IsStopped; //!< Flag to show the stop state
            bool IsWorking; //!< Flag to show the work state
            uint8_t txPin; //!< Store TX pin 
            uint8_t rxPin;  //!< Store RX pin
            uint8_t *StreamPackage; // Store the transmission package
        }ComStatus; //!< Struct with some data types for the serial communication
    public:
        uint8_t SerialRead(void);
        uint8_t SerialWrite(void);
        uint8_t SerialInit(void);
};






#endif
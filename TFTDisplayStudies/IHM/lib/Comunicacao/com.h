#ifndef COM_H
#define COM_H

#include <stdint.h>
#include <Arduino.h>

/* Communcation Pin */
#define TX_PIN 1
#define RX_PIN 3
/* Baud Rate */
#define SERIAL_BAUD 115200
/* Communication Flags */
#define COM_SUCESS 0
#define COM_TIMEOUT 1
#define COM_ERROR 2
#define COM_NO_DATA 3


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
            size_t PackageSize;
        }ComStatus; //!< Struct with some data types for the serial communication
    public:
        uint8_t SerialRead(void); //!< Read the Serial bus and return the data read
        uint8_t SerialWrite(uint8_t *package); //!< Write in Serial bus
        void SerialInit(int baud, uint8_t rx, uint8_t tx); //!< Initialize the Serial Com
        void SerialInit(int baud, uint8_t rx, uint8_t tx, uint32_t timeout); //!< Initialize the Serial Com with timeout
        void SerialStop(void);  //!< Stop the serial com interface
        void SerialResume(void); //!< Resume the serial com interface if are stopped
        ComStatus SerialConfiguration; //!< Struct with some configurations
};






#endif
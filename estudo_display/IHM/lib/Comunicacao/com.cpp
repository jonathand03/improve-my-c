#include "com.h"

/*! @brief Begin the Serial Communication 
* @param[in] baud Serial Communication Baud Rate
* @param[in] rx Serial Reciver Pin
* @param[in] tx Serial Transciver Pin
*/
void SerialCom::SerialInit(int baud, uint8_t rx, uint8_t tx)
{
    Serial.begin(SERIAL_BAUD,SERIAL_8N1,this->SerialConfiguration.rxPin,this->SerialConfiguration.txPin);
    this->SerialConfiguration.IsWorking = true;
    this->SerialConfiguration.IsStopped = false;
}

/*! @brief Begin the Serial Communication 
* @param[in] baud Serial Communication Baud Rate
* @param[in] rx Serial Reciver Pin
* @param[in] tx Serial Transciver Pin
* @param[in] timeout Serial timeout in case of any commnunication error
*/
void SerialCom::SerialInit(int baud, uint8_t rx, uint8_t tx, uint32_t timeout)
{
    Serial.begin(SERIAL_BAUD,SERIAL_8N1,this->SerialConfiguration.rxPin,this->SerialConfiguration.txPin);
    Serial.setTimeout(timeout);
}

uint8_t SerialCom::SerialRead(void)
{
    if(Serial.available() > 0)
    {
        // tratamento de dados
        return COM_SUCESS;
    }
    else
        return COM_NO_DATA;
}

uint8_t SerialCom::SerialWrite(uint8_t *package)
{
    this->SerialConfiguration.StreamPackage = package; // Intermediate vector saves the data package
    this->SerialConfiguration.PackageSize = sizeof(this->SerialConfiguration.StreamPackage); //!< Save the sizof stream
    if(this->SerialConfiguration.IsWorking == true) //!< If the Serial interface are working, write in serial bus
    {
        Serial.write(this->SerialConfiguration.StreamPackage,this->SerialConfiguration.PackageSize); // Write in the serial bus
        return COM_SUCESS; //!< return sucess
    }  
    else
        return COM_ERROR; //!< return error if Serial interface are not working
}

#include <Arduino.h>
#include <stdlib.h>
#include "steve_debug.h"
#include "crc16.c"


/* ============================ Setup da main ============================*/
void setup()
{
        Serial.begin(115200);
}

/* ============================ Loop da main ============================*/
void loop()
{
        unsigned char const temp [1024] = "ABCDABCD";
        uint16_t x = 0;

        Serial.println("Estou na main");
        delay(2000);

        /*
        comando |       dado    |       crc16
        32bits  |       32bits  |       16bits
        */
       x = crc_16(temp, 8);
       Serial.printf("CRC: %d\n\r" , x);
}






//#endif
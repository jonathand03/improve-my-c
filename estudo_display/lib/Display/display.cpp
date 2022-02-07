/*******************************************************************
 * Lib do display do steve 2.1
 *  @author Francisco Jonathan Lima Drumond
 *   
 * 
 */

#include "display.h"

IHM::IHM()
{
    this->init();
    this->setRotation(0);       
    this->fillScreen(TFT_BLUE); 
}




/*\brief    This library was created to make ESP32 ISR easier.
*           I have use some callback functions of <driver/gpio.h> to create 
*           the ISR configuration.
*/




#include <isr_esp32.h>
#include <stdint.h>
#include <driver/gpio.h>
#include <esp_err.h>
#include <Arduino.h>
typedef __uint8_t uint8_t; //!< Make sense for me

uint8_t isr_fucntion(void)
{   
    Serial.println("Interrupted !!");
    return SUCESS;
}
/*!
*@brief Configures the port passed as a parameter for the ESP32 ISR
*@param[in] pin_to_configure It is an enumeration referring to the ESP32 pin
*@return [SUCESS] if the configuration has sucessful. [FAIL] if the configuration has broken
*/
uint8_t isr_pin_configuration(Pin pin_to_configure)
{
    esp_err_t return_gpio_set_intr_type;   //!< Variable that store the return of the function 'gpio_set_intr_type'
    esp_err_t return_gpio_intr_enable;     //!< Variable that store the return of the function 'gpio_intr_enable'
    esp_err_t return_gpio_isr_handler_add; //!< Variable that store the return of the function 'gpio_isr_handler_add'
    esp_err_t return_gpio_set_direction;   //!< Variable that store the return of the function 'gpio_set_direction'

    return_gpio_set_intr_type = gpio_set_intr_type((gpio_num_t) pin_to_configure, GPIO_INTR_NEGEDGE);
    if (return_gpio_set_intr_type != ESP_OK)
    return FAIL;

    return_gpio_intr_enable = gpio_intr_enable((gpio_num_t)pin_to_configure);
    if (return_gpio_intr_enable != ESP_OK)
    return FAIL;

    return_gpio_isr_handler_add = gpio_isr_handler_add((gpio_num_t)pin_to_configure, (gpio_isr_t)isr_fucntion,NULL);
    if (return_gpio_isr_handler_add != ESP_OK)
        return FAIL;

    return_gpio_set_direction = gpio_set_direction((gpio_num_t)pin_to_configure, GPIO_MODE_INPUT);
    if (return_gpio_set_direction != ESP_OK)
        return FAIL;
    return SUCESS;
}
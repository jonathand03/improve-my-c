#ifndef ISR_ESP32_H
#define ISR_ESP32_H



#ifdef RETURN_FLAGS
#define RETURN_FLAGS
#define SUCESS (0)
#define FAIL (-1)
#endif

//!< Export function area
enum Pin{
    pin_0,
    pin_1,
    pin_2,
}
#endif
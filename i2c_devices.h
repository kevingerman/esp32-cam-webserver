/* Copyright (C) 2023 - Kevin German
 * License MIT
 */
#ifndef APP_I2C_DEVICES_H
#define APP_I2C_DEVICES_H

#include <Wire.h>

#define TCAADDR 0x70

//device callback function pointer prototype

//device descriptor struct
const struct device_t{
    byte id;

};

error_t scan( &deviece_t * devices);

#endif
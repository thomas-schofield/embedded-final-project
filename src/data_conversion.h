#ifndef DATA_CONVERSION_H
#define DATA_CONVERSION_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

unsigned char* format_temperature(int32_t temp);
unsigned char* format_pressure(uint32_t pres);
unsigned char* format_humidity(uint32_t hum);

#endif

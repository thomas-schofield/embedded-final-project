#ifndef DATA_CONVERSION_H
#define DATA_CONVERSION_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

unsigned char* number_to_ascii_signed(int number, unsigned int* digit_count);
unsigned char* temp_string(int32_t raw_temp);
unsigned char* format_temperature(int32_t temp);
unsigned char* format_pressure(uint32_t pres);
unsigned char* format_humidity(uint32_t hum);
// int32_t bme280_compensate_temperature(int32_t temp_adc,
//                                       int32_t* compensation_values_t);

#endif

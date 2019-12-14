#ifndef DATA_CONVERSION
#define DATA_CONVERSION

#include "src/data_conversion.h"

// unsigned char* number_to_ascii_signed(int number, unsigned int* digit_count) {
//     int divisor = 1;
//     *(digit_count) = 1;

//     while(number/(divisor*10)) {
//         divisor *= 10;
//         ++(*(digit_count));
//     }

//     unsigned char* _ascii = (unsigned char*)malloc(sizeof(char) * (*(digit_count)));
//     int i;
//     for (i = 0; i < *(digit_count); i++) {
//         *(_ascii + i) = (number / divisor) + 0x30;
//         number %= divisor;
//         divisor /= 10;
//     }

//     if (divisor) {
//         free(_ascii);
//         return "ERROR";
//     }

//     return _ascii;
// }

unsigned char* format_temperature(int32_t temp) {
    unsigned char* _data = (unsigned char*)malloc(8*sizeof(unsigned char));
    uint32_t temp_dec;
    temp_dec = abs(temp%100);
    temp /= 100;
    temp += 273;

    if (temp_dec < 10) {
        sprintf(_data, "%d.0%d\r\n", (int)temp, (int)temp_dec);
    }
    else {
        sprintf(_data, "%d.%d\r\n", (int)temp, (int)temp_dec);
    }
    return _data;
}

unsigned char* format_pressure(uint32_t pres) {
    uint32_t pres_dec;
    pres_dec = abs((unsigned int)pres%100);
    pres /= 100;
    int size = 9;

    if (pres <= 1000) {
        size = 10;
    }

    unsigned char* _data = (unsigned char*)malloc(size*sizeof(unsigned char));

    if (pres_dec < 10) {
        sprintf(_data, "%d.00%d\r\n", (int)pres, (int)pres_dec);
    }
    else if (pres_dec >= 10 && pres_dec < 100) {
        sprintf(_data, "%d.0%d\r\n", (int)pres, (int)pres_dec);
    }
    else {
        sprintf(_data, "%d.%d\r\n", (int)pres, (int)pres_dec);
    }
    return _data;
}

unsigned char* format_humidity(uint32_t hum) {
    uint32_t hum_dec;
    hum_dec = abs((unsigned int)hum%1024);
    hum /= 1024;
    int size = 8;

    if (hum >= 100) {
        size = 9;
    }

    unsigned char* _data = (unsigned char*)malloc(size*sizeof(unsigned char));

    if (hum_dec < 10) {
        sprintf(_data, "%d.00%d\r\n", (int)hum, (int)hum_dec);
    }
    else if (hum_dec >= 10 && hum_dec < 100) {
        sprintf(_data, "%d.0%d\r\n", (int)hum, (int)hum_dec);
    }
    else {
        sprintf(_data, "%d.%d\r\n", (int)hum, (int)hum_dec);
    }
    return _data;
}

#endif

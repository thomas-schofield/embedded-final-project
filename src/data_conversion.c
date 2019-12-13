#ifndef DATA_CONVERSION
#define DATA_CONVERSION

#include "src/data_conversion.h"

unsigned char* number_to_ascii_signed(int number, unsigned int* digit_count) {
    int divisor = 1;
    *(digit_count) = 1;

    while(number/(divisor*10)) {
        divisor *= 10;
        ++(*(digit_count));
    }

    unsigned char* _ascii = (unsigned char*)malloc(sizeof(char) * (*(digit_count)));
    int i;
    for (i = 0; i < *(digit_count); i++) {
        *(_ascii + i) = (number / divisor) + 0x30;
        number %= divisor;
        divisor /= 10;
    }

    if (divisor) {
        free(_ascii);
        return "ERROR";
    }

    return _ascii;
}

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
    unsigned char* _data = (unsigned char*)malloc(9*sizeof(unsigned char));
    uint32_t pres_dec;
    pres_dec = abs((unsigned int)pres%256);
    pres /= 256;

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
    unsigned char* _data = (unsigned char*)malloc(8*sizeof(unsigned char));
    uint32_t hum_dec;
    hum_dec = abs((unsigned int)hum%1024);
    hum /= 1024;

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

// unsigned char digit_to_ascii(int number, int divisor) {
//     return (unsigned char) number/divisor + 0x30;
// }

// unsigned char* temp_string(int32_t raw_temp) {
//     int32_t
// }
// unsigned char* temp_string(int32_t raw_temp) {
//     unsigned char size = 5;
//     unsigned char dec_point = 2;

//     if (raw_temp < 0) {
//         size = 6;
//         dec_point = 3;
//     }

//     unsigned char *_out = (unsigned char*)malloc(size*sizeof(unsigned char));

//     unsigned char i;
//     for (i = 0; i < size; i++) {
//         if (i == 0 && size > 5) {
//             *(_out) = 0x2D;
//             continue;
//         }

//         if (i == dec_point) {
//             *(_out + i) = 0x2E;
//         }
//         else if (raw_temp < 0) {
//             if (i < dec_point) {
//                 *(_out + i) = digit_to_ascii(raw_temp, 100 - 10*(i-1));
//             }
//             else {
//                 *(_out + i) = digit_to_ascii(raw_temp, 100 - 10*(i-2));
//             }
//         }
//         else {
//             if (i < dec_point) {
//                 *(_out + i) = digit_to_ascii(raw_temp, 100 - 10*i);
//             }
//             else {
//                 *(_out + i) = digit_to_ascii(raw_temp, 100 - 10*(i-1));
//             }
//         }
//     }
//     return _out;
// }

// int32_t bme280_compensate_temperature(int32_t temp_adc,
//                                       int32_t* compensation_values_t) {
//     int32_t fine_res_temp;
//     int32_t _temp[2];

//     _temp[0] = ((((temp_adc >> 3) - ((int32_t)*(compensation_values_t) << 1))) * ((int32_t)*(compensation_values_t + 1))) >> 11;
//     _temp[1] = (((((temp_adc >> 4) - ((int32_t)*(compensation_values_t))) *
//         ((temp_adc >> 4) - ((int32_t)*(compensation_values_t)))) >> 12) * ((int32_t)*(compensation_values_t + 2))) >> 14;
//     fine_res_temp = _temp[0] + _temp[1];
//     return (int32_t)((fine_res_temp * 5 + 128) >> 8);
// }

// unsigned int bme280_compensate_pressure(signed int pres_adc,
//                                         signed short int* compensation_values_p) {

// }

// int32_t CalcTemp(void) //32-bit integer conversion formula from BME280 spec sheet
// {
//     volatile int32_t var1, var2, T;
//     var1 = (((((int32_t)RawTemp >> 3) - ((int32_t)dig_T1 << 1))) * (int32_t)dig_T2) >> 11;
//     var2 = (((int32_t)RawTemp >> 4) - (int32_t)dig_T1);
//     var2 = (((var2*var2) >> 12) * (int32_t)dig_T3) >> 14;
//     t_fine = var1 + var2;
//     T = ((t_fine * 5) + 128) >> 8;
//     return T;
// }

// uint32_t CalcHumid(void) //Implement integer conversion formula from BME280 spec sheet
// {
//     volatile int32_t var3;
//     var3 = t_fine - (int32_t)76800;
//     var3 = ((((((int32_t)RawHumid << 14) - (((int32_t)dig_H4) << 20) - (((int32_t)dig_H5) * var3)) +
//         ((int32_t)16384)) >> 15) * (((((((var3 * ((int32_t)dig_H6)) >> 10) * (((var3 *
//         ((int32_t)dig_H3)) >> 11) + ((int32_t)32768))) >> 10) + ((int32_t)2097152)) *
//         ((int32_t)dig_H2) + (int32_t)8192) >> 14));
//     var3 = (var3 - (((((var3 >> 15) * (var3 >> 15)) >> 7) * ((int32_t)dig_H1)) >> 4));
//     if(var3 < 0) var3 = 0;
//     if(var3 > 419430400) var3 = 419430400;
//     return (uint32_t)(var3 >> 12);
// }

// uint32_t CalcPress(void) //32-bit integer conversion formula from BME280 spec sheet
// {
//     volatile int32_t var4, var5;
//     volatile uint32_t p;
//     var4 = (((int32_t)t_fine)>>1) - (int32_t)0xFA00;
//     var5 = (((var4>>2) * (var4>>2)) >> 11 ) * ((int32_t)dig_P6);
//     var5 = var5 + ((var4*((int32_t)dig_P5))<<1);
//     var5 = (var5>>2)+(((int32_t)dig_P4)<<16);
//     var4 = (((dig_P3 * (((var4>>2) * (var4>>2)) >> 13 )) >> 3) + ((((int32_t)dig_P2) * var4)>>1))>>18;
//     var4 = ((((0x8000+var4))*((int32_t)dig_P1))>>15);
//     if (var4 == 0)
//     {
//         return 0; // Avoid exception caused by division by zero
//     }
//     p = (((uint32_t)(((int32_t)0x100000)-RawPress)-(var5>>12)))*0xC35;
//     if (p < 0x80000000)
//     {
//         p = (p << 1) / ((uint32_t)var4);
//     }
//     else
//     {
//         p = (p / (uint32_t)var4) * 2;
//     }
//     var4 = (((int32_t)dig_P9) * ((int32_t)(((p>>3) * (p>>3))>>13)))>>12;
//     var5 = (((int32_t)(p>>2)) * ((int32_t)dig_P8))>>13;
//     p = (uint32_t)((int32_t)p + ((var4 + var5 + dig_P7) >> 4));
//     return p;
// }

#endif

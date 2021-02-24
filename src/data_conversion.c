#ifndef DATA_CONVERSION
#define DATA_CONVERSION

#include "src/data_conversion.h"

/* 
 * 2/24/21 NOTE: Instead of using malloc, we could have created a buffer in main.c and passed that into the function
 *               along with the maximum size of the buffer. That way, we wouldn't have to dynamically allocate
 *               every time we wanted to do a calculation.
 */

unsigned char *format_temperature(int32_t temp)
{
    unsigned char *_data = (unsigned char *)malloc(7 *
                                                   sizeof(unsigned char));
    uint32_t temp_dec;
    temp_dec = abs(temp % 100);
    temp /= 100;
    temp += 273;

    if (temp_dec < 10)
    {
        sprintf(_data, "%d.0%d", (int)temp, (int)temp_dec);
    }
    else
    {
        sprintf(_data, "%d.%d", (int)temp, (int)temp_dec);
    }
    return _data;
}

unsigned char *format_pressure(uint32_t pres)
{
    uint32_t pres_dec;
    pres_dec = abs((unsigned int)pres % 100);
    pres /= 100;
    int size = 8;

    if (pres <= 1000)
    {
        size = 9;
    }

    unsigned char *_data = (unsigned char *)malloc(size *
                                                   sizeof(unsigned char));

    if (pres_dec < 10)
    {
        sprintf(_data, "%d.00%d", (int)pres, (int)pres_dec);
    }
    else if (pres_dec >= 10 && pres_dec < 100)
    {
        sprintf(_data, "%d.0%d", (int)pres, (int)pres_dec);
    }
    else
    {
        sprintf(_data, "%d.%d", (int)pres, (int)pres_dec);
    }
    return _data;
}

unsigned char *format_humidity(uint32_t hum)
{
    uint32_t hum_dec;
    hum_dec = abs((unsigned int)hum % 1024);
    hum /= 1024;
    int size = 7;

    if (hum >= 100)
    {
        size = 8;
    }

    unsigned char *_data = (unsigned char *)malloc(size *
                                                   sizeof(unsigned char));

    if (hum_dec < 10)
    {
        sprintf(_data, "%d.00%d", (int)hum, (int)hum_dec);
    }
    else if (hum_dec >= 10 && hum_dec < 100)
    {
        sprintf(_data, "%d.0%d", (int)hum, (int)hum_dec);
    }
    else
    {
        sprintf(_data, "%d.%d", (int)hum, (int)hum_dec);
    }
    return _data;
}

#endif

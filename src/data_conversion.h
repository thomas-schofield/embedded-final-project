/**
 * @brief      Custom number to char array conversion
 *             functions
 *
 * @author     Thomas Schofield
 * @date       2019
 */

#ifndef DATA_CONVERSION_H
#define DATA_CONVERSION_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

/**
 * @brief      Convert 32-bit temperature integer from BME280
 *             into character array.
 *
 * @param[in]  temp  32-bit temperature integer from BME280
 *                   EX: 2590 -> "25.90"
 *
 * @return     Dynamically-allocated character array with a
 *             formatted temperature (in K)
 *
 * WARNING: MUST USE FREE() FROM STANDARD LIBRARY TO PREVENT
 * MEMORY LEAK!!!
 */
unsigned char* format_temperature(int32_t temp);

/**
 * @brief      Convert unsigned 32-bit pressure integer
 *             from BME280 into a character array.
 *
 * @param[in]  pres  Unsigned 32-bit pressure integer
 *                   from BME280.
 *
 * @return     Dynamically-allocated character array with a
 *             formatted pressure (in hPa)
 *
 * WARNING: MUST USE FREE() FROM STANDARD LIBRARY TO PREVENT
 * MEMORY LEAK!!!
 */
unsigned char* format_pressure(uint32_t pres);

/**
 * @brief      Convert unsigned 32-bit humidity integer
 *             from BME280 into a character array.
 *
 * @param[in]  hum   Unsigned 32-bit humidity integer
 *                   from BME280.
 *
 * @return     Dynamically-allocated character array with a
 *             formatted humidity (in %)
 *
 * WARNING: MUST USE FREE() FROM STANDARD LIBRARY TO PREVENT
 * MEMORY LEAK!!!
 */
unsigned char* format_humidity(uint32_t hum);

#endif

/*
 * bme280_io.h
 *
 *  Created on: Dec 6, 2019
 *      Author: Thomas Schofield
 */

#ifndef SRC_BME280_IO_H_
#define SRC_BME280_IO_H_

int8_t i2c_read(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len);

#endif /* SRC_BME280_IO_H_ */

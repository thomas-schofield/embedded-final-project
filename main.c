#include <msp430.h> 
#include "Includes/bme280.h"

/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	struct bme280_dev device;
	int8_t rslt = BME280_OK;

	device.dev_id = BME280_I2C_ADDR_PRIM;
	device.intf = BME280_I2C_INTF;
	device.read = user_i2c_read;
	device.write = user_i2c_write;

	return 0;
}

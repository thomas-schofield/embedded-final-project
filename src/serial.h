#ifndef SERIAL_H
#define SERIAL_H

#include <msp430.h>
#include <stdlib.h>
#include "src/data_conversion.h"

#define PRES_ADDR 0xF7
#define HUM_ADDR 0xFD
#define TEMP_ADDR 0xFA

#define HUM_CTRL 0xF2
#define MEAS_CTRL 0xF4

#define RESET_ADDR 0xE0
#define RESET 0xB6
#define SLAVE_ADDR 0x77

void setup_spi(void);
void disable_spi(void);
void enable_spi(void);

// unsigned char write_byte_spi(unsigned char data);
// unsigned char* write_bytes_spi(unsigned char* data, unsigned int length);

void setup_uart(void);
unsigned char write_byte_uart(unsigned char data);
unsigned char* write_bytes_uart(unsigned char* data, unsigned char length);
void start_uart(void);
void stop_uart(void);
void enable_esp(void);
void disable_esp(void);

void setup_uart_debug(void);
void write_byte_uart_debug(unsigned char data);
void write_bytes_uart_debug(unsigned char* data, unsigned char length);
void start_uart_debug(void);
void stop_uart_debug(void);

#endif

/**
 * @brief      This file implements UART and SPI.
 *
 * @author     Thomas Schofield & Tyler Humbert
 * @date       2019
 */

#ifndef SERIAL_H
#define SERIAL_H

#include <msp430.h>
#include <stdlib.h>

/**
 * @brief      Setup SPI over USCI_B0
 *
 * P3.0 - MOSI
 * P3.1 - MISO
 * P3.2 - CLK
 * P1.4 - CS
 *
 * Clock speed: SMCLK
 *
 * Mode: Master, CS active low, send MSB
 */
void setup_spi(void);
// unsigned char write_byte_spi(unsigned char data);
// unsigned char* write_bytes_spi(unsigned char* data,
//                                unsigned int length);

/***** ESP8266 UART Communications *****/
/**
 * @brief      Setup MSP430 UART on over USCI_A0
 *
 * P3.4 - RX
 * P3.3 - TX
 *
 * Baud: 115200
 */
void setup_uart(void);

/**
 * @brief      Write a character over UART_A0
 *
 * @param[in]  data  The byte to send over UART
 */
void write_byte_uart(char data);

/**
 * @brief      Writes bytes over UART_A0.
 *
 * @param      data  Address to the character array to send
 *
 * This function is an abstraction of write_byte_uart.
 */
void write_bytes_uart(char* data);

/**
 * @brief      Starts the UART_A0 state machine.
 */
void start_uart(void);

/**
 * @brief      Stop the UART_A0 state machine.
 */
void stop_uart(void);

/***** MSP430 Debugging UART Communications *****/
/**
 * @brief      Setup MSP430 UART over USCI_A1
 *
 * Baud: 115200
 */
void setup_uart_debug(void);

/**
 * @brief      Write a byte using UART over USCI_A1
 *
 * @param[in]  data  The byte to send
 */
void write_byte_uart_debug(char data);

/**
 * @brief      Write an array of bytes over USCI_A1
 *
 * @param      data  Character array holding ASCII bytes
 *
 * This function is an abstraction of write_byte_uart_debug.
 */
void write_bytes_uart_debug(char* data);

/**
 * @brief      Start the UART_A1 state machine.
 */
void start_uart_debug(void);

/**
 * @brief      Stop the UART_A1 state machine
 */
void stop_uart_debug(void);

#endif

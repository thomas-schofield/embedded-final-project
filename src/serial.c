#ifndef SERIAL
#define SERIAL
#include "src/serial.h"

/**
 * Add 0x30 to each number to convert number digit to ascii digit
 */

/**
 * @brief      Setup SPI to communicate with the BME280 with 1MHz clock
 *
 * P3.0 - MOSI
 * P3.1 - MISO
 * P3.2 - CLK
 * P2.7 - CS
 */
void setup_spi(void) {
    /* Need to use B0 because A1 is the only other setup that supports UART */
    P3SEL |= (BIT2|BIT1|BIT0); /* Set up pins to use SPI */
    P1DIR |= BIT4;
    P1OUT |= BIT4;

    /* Choose clock and halt state machine while setting up */
    UCB0CTL1 |= UCSSEL_2|UCSWRST;

    /* Set MSP to master, transmit MSB, and set CS to active low */
    UCB0CTL0 |= UCMSB|UCMST|UCSYNC|UCCKPH;
    UCB0BR0 |= 0x01;
    UCB0BR1 |= 0x00;

    /* Enable receiving interrupt */
    UCB0IE |= UCTXIE|UCRXIE;
}

void disable_spi(void) {
    while(!(UCB0IFG & UCTXIFG));
    UCB0IE &= ~(UCTXIE|UCRXIE);
}

void enable_spi(void) {
    while(!(UCB0IFG & UCTXIFG));
    UCB0IE |= UCTXIE|UCRXIE;
}

// unsigned char write_byte_spi(unsigned char data) {
//     UCB0CTL1 &= ~UCSWRST;
//     while(!(UCB0IFG & UCTXIFG));
//     UCB0TXBUF = data;
//     while(!(UCB0IFG & UCRXIFG));
//     UCB0CTL1 |= UCSWRST;
//     return (unsigned char) UCB0RXBUF;
// }

// unsigned char* write_bytes_spi(unsigned char* data, unsigned int length) {
//     unsigned char* _data = malloc(length * sizeof(unsigned char));
//     unsigned char i;
//     for (i = 0; i < length; i++) {
//         *(_data+i) = write_byte_spi(*(data+i));
//     }
//     return _data;
// }

/**
 * @brief      Setup MSP430 UART on P3.4 and P3.3 (A0)
 *
 * P3.4 - RX
 * P3.3 - TX
 */
void setup_uart(void) {
    P3SEL |= (BIT4|BIT3);
    P8SEL &= ~BIT2;
    P8DIR |= BIT2; /* Enable pin */

    UCA0CTL1 |= UCSSEL_2 + UCSWRST;

    UCA0BR0 = 9;
    UCA0BR1 = 0;

    UCA0MCTL = UCBRF_0|UCBRS_1;

    // UCA0CTL1 &= ~UCSWRST;

    UCA0IE |= UCTXIE;
}

unsigned char write_byte_uart(unsigned char data) {
    while(!(UCA0IFG & UCTXIFG));
    UCA0TXBUF = data;
    while(!(UCA0IFG & UCRXIFG));
    return (unsigned char) UCA0RXBUF;
}

unsigned char* write_bytes_uart(unsigned char* data, unsigned char length) {
    unsigned char* _data = (unsigned char*)malloc(length*sizeof(unsigned char));
    unsigned char i;
    for (i = 0; i < length; i++) {
        *(_data + i) = write_byte_uart(*(data+i));
    }
    return _data;
}

void start_uart(void) {
    UCA0CTL1 &= ~UCSWRST;
    // UCA0IE |= UCTXIE;
}

void stop_uart(void) {
    UCA0CTL1 |= UCSWRST;
    // UCA0IE &= ~UCTXIE;
}

void enable_esp(void) {
    P8OUT |= BIT2;
}
void disable_esp(void) {
    P8OUT &= ~BIT2;
}

/**
 * @brief      Debugging UART
 */

void setup_uart_debug(void) {
    /* Setup UART to communicate at 9600 baud (USB) */
    P4SEL |= (BIT4|BIT5);

    UCA1CTL1 |= UCSSEL_2 + UCSWRST;

    UCA1BR0 = 109;
    UCA1BR1 = 0;

    UCA1MCTL = UCBRF_0|UCBRS_2;

    // UCA1CTL1 &= ~UCSWRST;

    UCA1IE |= UCTXIE;
}

void write_byte_uart_debug(unsigned char data) {
    while(!(UCA1IFG & UCTXIFG));
    UCA1TXBUF = data;
}

void write_bytes_uart_debug(unsigned char* data, unsigned char length) {
    unsigned char i;
    for (i = 0; i < length; i++) {
        write_byte_uart_debug(*(data+i));
    }
}

void start_uart_debug(void) {
    UCA1CTL1 &= ~UCSWRST;
    // UCA1IE |= UCTXIE;
}

void stop_uart_debug(void) {
    UCA1CTL1 |= UCSWRST;
    // UCA1IE &= ~UCTXIE;
}

#endif

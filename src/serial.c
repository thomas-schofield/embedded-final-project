#ifndef SERIAL
#define SERIAL

#include "src/serial.h"

void setup_spi(void) {
    P3SEL |= (BIT2|BIT1|BIT0);
    P1DIR |= BIT4;
    P1OUT |= BIT4;

    UCB0CTL1 |= UCSSEL_2|UCSWRST;

    UCB0CTL0 |= UCMSB|UCMST|UCSYNC|UCCKPH;
    UCB0BR0 |= 0x01;
    UCB0BR1 |= 0x00;

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

// unsigned char* write_bytes_spi(unsigned char* data,
//                                unsigned int length) {
//     unsigned char* _data = malloc(length *
//                                   sizeof(unsigned char));
//     unsigned char i;
//     for (i = 0; i < length; i++) {
//         *(_data+i) = write_byte_spi(*(data+i));
//     }
//     return _data;
// }

void setup_uart(void) {
    P3SEL |= (BIT4|BIT3);

    UCA0CTL1 |= UCSSEL_2 + UCSWRST;

    UCA0BR0 = 9;
    UCA0BR1 = 0;

    UCA0MCTL = UCBRF_0|UCBRS_1;

    UCA0IE |= UCTXIE;
}

void write_byte_uart(char data) {
    while(!(UCA0IFG & UCTXIFG));
    UCA0TXBUF = data;
}

void write_bytes_uart(char* data) {
    unsigned char* c;
    for (c = data; *c != 0x00; c=++data) {
        write_byte_uart(*c);
    }
    write_byte_uart(0x7C);
}

void start_uart(void) {
    UCA0CTL1 &= ~UCSWRST;
}

void stop_uart(void) {
    UCA0CTL1 |= UCSWRST;
}

void setup_uart_debug(void) {
    P4SEL |= (BIT4|BIT5);

    UCA1CTL1 |= UCSSEL_2 + UCSWRST;

    UCA1BR0 = 9;
    UCA1BR1 = 0;

    UCA1MCTL = UCBRF_0|UCBRS_1;

    UCA1IE |= UCTXIE;
}

void write_byte_uart_debug(char data) {
    while(!(UCA1IFG & UCTXIFG));
    UCA1TXBUF = data;
}

void write_bytes_uart_debug(char* data) {
    unsigned char* c;
    for (c = data; *c != 0x00; c=++data) {
        write_byte_uart_debug(*c);
    }
    write_byte_uart_debug(0x7C);
}

void start_uart_debug(void) {
    UCA1CTL1 &= ~UCSWRST;
}

void stop_uart_debug(void) {
    UCA1CTL1 |= UCSWRST;
}

#endif

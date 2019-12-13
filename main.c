#include <msp430.h>

#define DEBUG 1

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "src/serial.h"
#include "src/timer.h"
#include "src/data_conversion.h"
#include "Includes/BME280.h"

/**
 * main.c
 */

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
    P1SEL &= ~BIT0;
    P1DIR |= BIT0;
    P1OUT &= ~BIT0;

    setup_spi();
    setup_uart_debug();

    // setup_uart();
    //
    // Timer is working
    // setup_timer();

    unsigned char *str = (unsigned char*)malloc(24*sizeof(unsigned char));

    unsigned char* s_temp;
    unsigned char* s_pres;
    unsigned char* s_hum;

    int32_t temp;
    uint32_t pres, hum;

    if(ReadTHid()); //Check for presence of sensor; read its ID code
    else  //Trap CPU and turn on red LED if not found
    {
        P1OUT |= BIT0;
        while(1);
    }

    GetCompData();

    while(1) {
        /* Take measurements */
        ReadTHsensor();

        temp = CalcTemp();
        hum = CalcHumid();
        pres = CalcPress();

        /* TEMP IS GOOD HOLY FUK */
        // s_temp = format_temperature(temp);
        // s_hum = format_humidity(hum);
        s_pres = format_pressure(pres);

        sprintf(str, "%s", s_pres);
        // free(s_temp);
        // free(s_hum);
        free(s_pres);

        write_bytes_uart_debug(str, strlen(str));

        __delay_cycles(500000);

        /* Enter low power mode until the timer wakes up the processor */
        // __bis_SR_register(LPM0_bits + GIE);
        // __no_operation();
    }

	return 0;
}

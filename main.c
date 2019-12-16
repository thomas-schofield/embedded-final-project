/**
 * @brief      Routine entry point for the IoT project
 *
 * @author     Thomas Schofield & Tyler Humbert
 * @date       2019
 */

/* Library includes */
#include <msp430.h>
#include <stdint.h>
#include <string.h>

/* Custom includes */
#include "src/serial.h"
#include "src/timer.h"
#include "src/data_conversion.h"
#include "Includes/BME280.h" // BME280 library on Github

/**
 * main.c
 */

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

    /* Setup P1.0 LED to indicate if the BME is available */
    P1SEL &= ~BIT0;
    P1DIR |= BIT0;
    P1OUT &= ~BIT0;

    /* Setup P4.7 LED to indicate when the MSP reaches the timer interrupt */
    P4SEL &= ~BIT7;
    P4DIR |= BIT7;
    P4OUT &= ~BIT7;

    /* Setup all ports for UART, SPI, and setup timer */
    setup_spi();
    setup_uart();
    setup_uart_debug();
    setup_timer();

    /* Pointers for temperature, pressure, and humidity strings */
    unsigned char* s_temp;
    unsigned char* s_pres;
    unsigned char* s_hum;

    /* Variables to hold the data from the BME280 */
    int32_t temp;
    uint32_t pres, hum;

    /* Use the BME280's ID to see if the device is connected */
    if(ReadTHid());
    else
    {
        P1OUT |= BIT0;
        while(1);
    }

    /* Get the compensation data for the three calculations */
    GetCompData();

    while(1) {
        /* Enable UART comms between the MSP430 and ESP8266 */
        start_uart_debug(); // Used for viewing data over PuTTY
        start_uart();

        /* Read the raw data points from the BME280 */
        ReadTHsensor();

        temp = CalcTemp();
        /* Use custom string formatting function to format temperature data */
        s_temp = format_temperature(temp);
        /* Write the formatted character array to the ESP8266 */
        write_bytes_uart((signed char*)s_temp);
        /* Write the character array to PuTTY for debugging */
        write_bytes_uart_debug(s_temp);
        free(s_temp); // Release the dynamic memory

        hum = CalcHumid();
        s_hum = format_humidity(hum);
        write_bytes_uart((char*)s_hum);
        write_bytes_uart_debug(s_hum);
        free(s_hum);

        pres = CalcPress();
        s_pres = format_pressure(pres);
        write_bytes_uart((char*)s_pres);
        write_bytes_uart_debug(s_pres);
        free(s_pres);

        /* Wait to make sure data transfers properly */
        __delay_cycles(2500);
        /* Stop the UART comms */
        stop_uart_debug();
        stop_uart();

        /* Enter low power mode until the timer wakes up the processor */
        _BIS_SR(LPM0_bits|GIE);
        __no_operation();
    }

	return 0;
}

#include <msp430.h>
#include <stdint.h>
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

    P4SEL &= ~BIT7;
    P4DIR |= BIT7;
    P4OUT &= ~BIT7;

    setup_spi();
    setup_uart();
    setup_uart_debug();
    setup_timer();

    const char START[6] = "START";
    const char OK[3] = "OK";

    unsigned char* response;

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
        start_uart_debug();
        start_uart();

        ReadTHsensor();

        enable_esp();

        response = write_bytes_uart(&START, strlen(&START));
        while(strcmp(response, &OK) != 0) {
            write_bytes_uart_debug("NO\r\n", strlen("NO\r\n"));
            if (*(response) == "O") {
                free(response);
                break;
            }
            free(response);
            response = write_bytes_uart(&START, strlen(&START));
        }
        free(response);

        temp = CalcTemp();
        s_temp = format_temperature(temp);
        response = write_bytes_uart(s_temp, strlen(s_temp));
        write_bytes_uart_debug(s_temp, strlen(s_temp));
        free(s_temp);
        free(response);

        hum = CalcHumid();
        s_hum = format_humidity(hum);
        response = write_bytes_uart(s_hum, strlen(s_hum));
        write_bytes_uart_debug(s_hum, strlen(s_hum));
        free(s_hum);
        free(response);

        pres = CalcPress();
        s_pres = format_pressure(pres);
        response = write_bytes_uart(s_pres, strlen(s_pres));
        write_bytes_uart_debug(s_pres, strlen(s_pres));
        write_bytes_uart_debug(response, strlen(response));
        free(s_pres);
        free(response);

        disable_esp();

        __delay_cycles(2500);
        stop_uart_debug();
        stop_uart();

        /* Enter low power mode until the timer wakes up the processor */
        _BIS_SR(LPM0_bits|GIE);
        __no_operation();
    }

	return 0;
}

#ifndef TIMER
#define TIMER

#include "src/timer.h"

volatile unsigned char OVERFLOWS = 0;

void setup_timer(void) {
    /* Use ACLK, divide by 8, and Continuous Mode */
    TA0CTL |= TASSEL_1 + ID_3 + MC_2 + TAIE + TACLR;
    TA0EX0 |= TAIDEX_7; /* Need to divide the clock again by 8 */
}

#pragma vector = TIMER0_A1_VECTOR
__interrupt void timer_isr(void) {
    switch(__even_in_range(TA0IV, 14)) {
        case 0: break;
        case 2: break;
        case 4: break;
        case 6: break;
        case 8: break;
        case 10: break;
        case 12: break;
        case 14: {
            ++OVERFLOWS;
            if (OVERFLOWS >= MAX_OVERFLOW) {
                OVERFLOWS = 0;
                __bic_SR_register_on_exit(LPM0_bits);
            }
            break;
        }
    }
}

#endif /* TIMER */

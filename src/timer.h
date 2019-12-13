#ifndef TIMER_H
#define TIMER_H

#include <msp430.h>

#define MAX_OVERFLOW 13

/**
 * @brief      Function to setup Timer A
 */
void setup_timer(void);

__interrupt void timer_isr(void);

#endif /* TIMER_H */

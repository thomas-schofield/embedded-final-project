#ifndef TIMER_H
#define TIMER_H

#include <msp430.h>

#define MAX_OVERFLOW 1
// 13

/**
 * @brief      Function to setup Timer A
 */
void setup_timer(void);

void stop_timer(void);
void start_timer(void);
void restart_timer(void);

__interrupt void timer_isr(void);

#endif /* TIMER_H */

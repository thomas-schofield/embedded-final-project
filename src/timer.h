/**
 * @brief      This file implements timer.
 *
 * @author     Twsch
 * @date       2019
 */
#ifndef TIMER_H
#define TIMER_H

#include <msp430.h>

/**
 * @brief      Maximum number of times the interrupt counter can overflow.
 */
#define MAX_OVERFLOW 1

/**
 * @brief      Function to setup Timer A.
 *
 * Timer is set to use ACLK and divide the clock by 64
 */
void setup_timer(void);

/**
 * @brief      Stops Timer A.
 */
void stop_timer(void);

/**
 * @brief      Starts Timer A.
 */
void start_timer(void);

/**
 * @brief      Restarts Timer A.
 */
void restart_timer(void);

/**
 * @brief      Interrupt vector function for TimerA
 *
 * This function wakes up the microcontroller after MAX_OVERFLOW times.
 */
__interrupt void timer_isr(void);

#endif /* TIMER_H */

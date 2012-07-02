#include <thumips.h>
#include <trap.h>
#include <stdio.h>
#include <picirq.h>

volatile size_t ticks;

/* *
 * clock_init - initialize 8253 clock to interrupt 100 times per second,
 * and then enable IRQ_TIMER.
 * */
void
clock_init(void) {
    cprintf("++TODO setup timer interrupts\n");
}


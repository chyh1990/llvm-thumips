#include <defs.h>
#include <stdio.h>
#include <string.h>
#include <console.h>
#include <kdebug.h>
#include <picirq.h>
#include <trap.h>
#include <clock.h>
#include <intr.h>
#include <pmm.h>

void setup_exception_vector()
{
  //for QEMU sim
  extern unsigned char __exception_vector, __exception_vector_end;
  memcpy((unsigned int*)0xBFC00000, &__exception_vector,
      &__exception_vector_end - &__exception_vector);
}


void __noreturn
kern_init(void) {
    //setup_exception_vector();

    cons_init();                // init the console

    const char *message = "(THU.CST) os is loading ...\n\n";
    cprintf(message);

    print_kerninfo();

    cprintf("EX\n");
    __asm__ volatile("syscall");
    cprintf("EX RET\n");

    pmm_init();                 // init physical memory management

    pic_init();                 // init interrupt controller

    clock_init();               // init clock interrupt
    intr_enable();              // enable irq interrupt

    /* do nothing */
    while (1);
}


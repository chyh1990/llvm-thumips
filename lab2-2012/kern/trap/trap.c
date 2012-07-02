#include <defs.h>
#include <clock.h>
#include <trap.h>
#include <thumips.h>
#include <stdio.h>
#include <mmu.h>
#include <memlayout.h>
#include <assert.h>
#include <console.h>
#include <kdebug.h>

#define TICK_NUM 100
#define PRINT_HEX(str,x) {cprintf(str);printhex((unsigned int)x);cprintf("\n");}

static void print_ticks() {
    PRINT_HEX("%d ticks\n",TICK_NUM);
}


void
idt_init(void) {

}

static const char *
trapname(int trapno) {
    static const char * const excnames[] = {
        "Divide error",
        "Debug",
        "Non-Maskable Interrupt",
        "Breakpoint",
        "Overflow",
        "BOUND Range Exceeded",
        "Invalid Opcode",
        "Device Not Available",
        "Double Fault",
        "Coprocessor Segment Overrun",
        "Invalid TSS",
        "Segment Not Present",
        "Stack Fault",
        "General Protection",
        "Page Fault",
        "(unknown trap)",
        "x87 FPU Floating-Point Error",
        "Alignment Check",
        "Machine-Check",
        "SIMD Floating-Point Exception"
    };

    if (trapno < sizeof(excnames)/sizeof(const char * const)) {
        return excnames[trapno];
    }
    if (trapno >= IRQ_OFFSET && trapno < IRQ_OFFSET + 16) {
        return "Hardware Interrupt";
    }
    return "(unknown trap)";
}

bool
trap_in_kernel(struct trapframe *tf) {
    return (tf->tf_cs == (uint16_t)KERNEL_CS);
}

static const char *IA32flags[] = {
    "CF", NULL, "PF", NULL, "AF", NULL, "ZF", "SF",
    "TF", "IF", "DF", "OF", NULL, NULL, "NT", NULL,
    "RF", "VM", "AC", "VIF", "VIP", "ID", NULL, NULL,
};

void
print_trapframe(struct trapframe *tf) {
    PRINT_HEX("trapframe at ", tf);
    print_regs(&tf->tf_regs);
 
    int i, j;
    for (i = 0, j = 1; i < sizeof(IA32flags) / sizeof(IA32flags[0]); i ++, j <<= 1) {
        if ((tf->tf_eflags & j) && IA32flags[i] != NULL) {
            cprintf(IA32flags[i]);
        }
    }
    cprintf("IOPL=%d\n");

    if (!trap_in_kernel(tf)) {
    }
}

void
print_regs(struct pushregs *regs) {
  cprintf("PRINT_REGS\n");
}

static void
trap_dispatch(struct trapframe *tf) {
    char c;

    switch (tf->tf_trapno) {

    default:
        // in kernel, it must be a mistake
        if ((tf->tf_cs & 3) == 0) {
            print_trapframe(tf);
            panic("unexpected trap in kernel.\n");
        }
    }
}

void
trap(struct trapframe *tf) {
    // dispatch based on what type of trap occurred
    trap_dispatch(tf);
}


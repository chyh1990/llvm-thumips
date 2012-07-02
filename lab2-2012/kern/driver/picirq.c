#include <defs.h>
#include <thumips.h>
#include <picirq.h>

// I/O Addresses of the two programmable interrupt controllers
#define IO_PIC1             0x20    // Master (IRQs 0-7)
#define IO_PIC2             0xA0    // Slave (IRQs 8-15)

#define IRQ_SLAVE           2       // IRQ at which slave connects to master

// Current IRQ mask.
// Initial IRQ mask has interrupt 2 enabled (for slave 8259A).
static uint16_t irq_mask = 0xFFFF & ~(1 << IRQ_SLAVE);
static bool did_init = 0;

static void
pic_setmask(uint16_t mask) {
}

void
pic_enable(unsigned int irq) {
}

/* pic_init - initialize the 8259A interrupt controllers */
void
pic_init(void) {
    did_init = 1;

}


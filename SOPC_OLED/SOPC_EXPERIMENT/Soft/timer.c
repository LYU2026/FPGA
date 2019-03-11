/*
 * "Hello World" example.
 *
 * This example prints 'Hello from Nios II' to the STDOUT stream. It runs on
 * the Nios II 'standard', 'full_featured', 'fast', and 'low_cost' example
 * designs. It runs with or without the MicroC/OS-II RTOS and requires a STDOUT
 * device in your system's hardware.
 * The memory footprint of this hosted application is ~69 kbytes by default
 * using the standard reference design.
 *
 * For a reduced footprint version of this template, and an explanation of how
 * to reduce the memory footprint for a given application, see the
 * "small_hello_world" template.
 *
 */

#include <stdio.h>
#include "altera_avalon_timer_regs.h" 
#include "system.h" 
#include "sys/alt_irq.h" 
#include "altera_avalon_pio_regs.h" 

int i = 0;
void ISR_timer0()
{
    IOWR_ALTERA_AVALON_PIO_DATA(PIO_LED_BASE, ~(1 << i));
    i++;
    if(i == 4) i = 0;
    IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER0_BASE, 0x00);       //清楚timer0中断标志寄存器
}
void timer_init(void)     
{ 
     IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER0_BASE, 0x00);       //清楚timer0中断标志寄存器
     IOWR_ALTERA_AVALON_TIMER_PERIODL(TIMER0_BASE,50000000);   //设置timer0周期
     IOWR_ALTERA_AVALON_TIMER_PERIODH(TIMER0_BASE, 50000000 >> 16); 
     IOWR_ALTERA_AVALON_TIMER_CONTROL(TIMER0_BASE, 0x07);      //允许timer0中断
     alt_irq_register(TIMER0_IRQ, (void *)0, ISR_timer0);      //注册timer0中断
} 

int main()
{
    timer_init();
    while(1);
    return 0;
}

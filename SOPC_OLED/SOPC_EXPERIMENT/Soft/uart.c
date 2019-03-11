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
#include "altera_avalon_uart_regs.h"
#include "sys/alt_irq.h"
#include "system.h"
#include "string.h"

unsigned char UartBuffer[100] = {0};
unsigned char TimeUartBuffer[100] = {0};
int RxCounter = 0;
int TimeRxCounter = 0;
int TxCounter = 0;

/*串口配置*/
void SetBaudrate(unsigned int baudrate)  //波特率配置
{      
     IOWR_ALTERA_AVALON_UART_DIVISOR(UART0_BASE, ALT_CPU_FREQ/baudrate+0.5); 
}

/*void UartSendByte(unsigned char data)   //查询方式发送一个字符
{ 
    IOWR_ALTERA_AVALON_UART_TXDATA(UART0_BASE, data); 
    while(!(IORD_ALTERA_AVALON_UART_STATUS(UART0_BASE) & 0x40));  //等待发送准备好，可以发送下一个字符
} 

void UartSendString(unsigned int len, unsigned char *str) //发送字符串
{ 
    while(len--) 
     { 
         UartSendByte(*str++);    
     } 
} */

void Uart_ISR()
{
    int status = 0;
    unsigned char rx_buffer = 0;
    status = IORD_ALTERA_AVALON_UART_STATUS(UART0_BASE);  //读取状态寄存器
    IOWR_ALTERA_AVALON_UART_STATUS(UART0_BASE, 0);        //清状态寄存器
    if ((status & ALTERA_AVALON_UART_STATUS_RRDY_MSK) == ALTERA_AVALON_UART_STATUS_RRDY_MSK)  //接收字符准备好中断状态
    {
         rx_buffer = IORD_ALTERA_AVALON_UART_RXDATA(UART0_BASE) & 0x00FF;  //读取接收寄存器        
         if(rx_buffer != '$' && RxCounter == 0)
         {
            RxCounter = 0;
         }  
         else
         {
            UartBuffer[RxCounter] = rx_buffer;
            RxCounter++;
            if(rx_buffer == '\n')
            {                
                if((strncmp(UartBuffer, "$TIMERSTART", 11)) == 0)  //判断是否是开启定时器命令
                {
                    IOWR_ALTERA_AVALON_TIMER_CONTROL(TIMER0_BASE, 0x07);  //打开定时器中断
                }
                else if((strncmp(UartBuffer, "$TIMERSTOP", 10)) == 0)  //判断是否是关闭定时器命令
                {
                    IOWR_ALTERA_AVALON_TIMER_CONTROL(TIMER0_BASE, 0x00);   //关闭定时器中断
                }        
                else
                {   
                    
                    IOWR_ALTERA_AVALON_UART_CONTROL(UART0_BASE, 0);    //关闭串口所有中断
                   // IOWR_ALTERA_AVALON_UART_TXDATA(UART0_BASE, '\n'); 
                    IOWR_ALTERA_AVALON_UART_CONTROL(UART0_BASE, ALTERA_AVALON_UART_CONTROL_TRDY_MSK);  //打开允许传送准备好中断
                }
                TimeRxCounter = RxCounter;
                RxCounter = 0;                
            }
            if(RxCounter > 99)  RxCounter = 0;
         }
    }
      
    if ((status & ALTERA_AVALON_UART_STATUS_TRDY_MSK) == ALTERA_AVALON_UART_STATUS_TRDY_MSK)  //传送准备好中断
    { 
         if(TxCounter < TimeRxCounter)
         {              
            IOWR_ALTERA_AVALON_UART_TXDATA(UART0_BASE,UartBuffer[TxCounter]); 
            TxCounter++;       
         }
         else  //发送完成
         {
            TxCounter=0;
            IOWR_ALTERA_AVALON_UART_CONTROL(UART0_BASE,0);  //关闭串口所有中断
            IOWR_ALTERA_AVALON_UART_CONTROL(UART0_BASE,ALTERA_AVALON_UART_STATUS_RRDY_MSK);   //打开允许接收字符准备好中断                          
         }            
    }    
}
    
void UartInit(void)  //串口初始化
{
    SetBaudrate(9600);  //波特率9600
    IOWR_ALTERA_AVALON_UART_CONTROL(UART0_BASE, 0); 
    IOWR_ALTERA_AVALON_UART_CONTROL(UART0_BASE, ALTERA_AVALON_UART_CONTROL_RRDY_MSK);   //打开允许接收字符准备好中断
    IOWR_ALTERA_AVALON_UART_STATUS(UART0_BASE, 0);   //清状态寄存器
    alt_irq_register(UART0_IRQ, (void *)0, Uart_ISR);  //注册中断
}


/*定时器配置*/
void ISR_timer0()
{
    IOWR_ALTERA_AVALON_UART_CONTROL(UART0_BASE,0);
    IOWR_ALTERA_AVALON_UART_TXDATA(UART0_BASE, '\n'); 
    IOWR_ALTERA_AVALON_UART_CONTROL(UART0_BASE,ALTERA_AVALON_UART_CONTROL_TRDY_MSK);
    IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER0_BASE, 0x00);       //清楚timer0中断标志寄存器
}
void timer_init(void)     
{ 
     IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER0_BASE, 0x00);       //清楚timer0中断标志寄存器
     IOWR_ALTERA_AVALON_TIMER_PERIODL(TIMER0_BASE,50000000);   //设置timer0周期
     IOWR_ALTERA_AVALON_TIMER_PERIODH(TIMER0_BASE, 50000000 >> 16); 
     IOWR_ALTERA_AVALON_TIMER_CONTROL(TIMER0_BASE, 0x00);      //允许timer0中断
     alt_irq_register(TIMER0_IRQ, (void *)0, ISR_timer0);      //注册timer0中断
}
 
int main()
{
    //alt_irq_context status;  
    //status = alt_irq_disable_all();
    UartInit();  //串口初始化
    timer_init();  //定时器初始化
    //alt_irq_enable_all(status);
    while(1);
    return 0;
}

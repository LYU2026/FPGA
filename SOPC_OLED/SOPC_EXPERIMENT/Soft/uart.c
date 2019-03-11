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

/*��������*/
void SetBaudrate(unsigned int baudrate)  //����������
{      
     IOWR_ALTERA_AVALON_UART_DIVISOR(UART0_BASE, ALT_CPU_FREQ/baudrate+0.5); 
}

/*void UartSendByte(unsigned char data)   //��ѯ��ʽ����һ���ַ�
{ 
    IOWR_ALTERA_AVALON_UART_TXDATA(UART0_BASE, data); 
    while(!(IORD_ALTERA_AVALON_UART_STATUS(UART0_BASE) & 0x40));  //�ȴ�����׼���ã����Է�����һ���ַ�
} 

void UartSendString(unsigned int len, unsigned char *str) //�����ַ���
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
    status = IORD_ALTERA_AVALON_UART_STATUS(UART0_BASE);  //��ȡ״̬�Ĵ���
    IOWR_ALTERA_AVALON_UART_STATUS(UART0_BASE, 0);        //��״̬�Ĵ���
    if ((status & ALTERA_AVALON_UART_STATUS_RRDY_MSK) == ALTERA_AVALON_UART_STATUS_RRDY_MSK)  //�����ַ�׼�����ж�״̬
    {
         rx_buffer = IORD_ALTERA_AVALON_UART_RXDATA(UART0_BASE) & 0x00FF;  //��ȡ���ռĴ���        
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
                if((strncmp(UartBuffer, "$TIMERSTART", 11)) == 0)  //�ж��Ƿ��ǿ�����ʱ������
                {
                    IOWR_ALTERA_AVALON_TIMER_CONTROL(TIMER0_BASE, 0x07);  //�򿪶�ʱ���ж�
                }
                else if((strncmp(UartBuffer, "$TIMERSTOP", 10)) == 0)  //�ж��Ƿ��ǹرն�ʱ������
                {
                    IOWR_ALTERA_AVALON_TIMER_CONTROL(TIMER0_BASE, 0x00);   //�رն�ʱ���ж�
                }        
                else
                {   
                    
                    IOWR_ALTERA_AVALON_UART_CONTROL(UART0_BASE, 0);    //�رմ��������ж�
                   // IOWR_ALTERA_AVALON_UART_TXDATA(UART0_BASE, '\n'); 
                    IOWR_ALTERA_AVALON_UART_CONTROL(UART0_BASE, ALTERA_AVALON_UART_CONTROL_TRDY_MSK);  //����������׼�����ж�
                }
                TimeRxCounter = RxCounter;
                RxCounter = 0;                
            }
            if(RxCounter > 99)  RxCounter = 0;
         }
    }
      
    if ((status & ALTERA_AVALON_UART_STATUS_TRDY_MSK) == ALTERA_AVALON_UART_STATUS_TRDY_MSK)  //����׼�����ж�
    { 
         if(TxCounter < TimeRxCounter)
         {              
            IOWR_ALTERA_AVALON_UART_TXDATA(UART0_BASE,UartBuffer[TxCounter]); 
            TxCounter++;       
         }
         else  //�������
         {
            TxCounter=0;
            IOWR_ALTERA_AVALON_UART_CONTROL(UART0_BASE,0);  //�رմ��������ж�
            IOWR_ALTERA_AVALON_UART_CONTROL(UART0_BASE,ALTERA_AVALON_UART_STATUS_RRDY_MSK);   //�����������ַ�׼�����ж�                          
         }            
    }    
}
    
void UartInit(void)  //���ڳ�ʼ��
{
    SetBaudrate(9600);  //������9600
    IOWR_ALTERA_AVALON_UART_CONTROL(UART0_BASE, 0); 
    IOWR_ALTERA_AVALON_UART_CONTROL(UART0_BASE, ALTERA_AVALON_UART_CONTROL_RRDY_MSK);   //�����������ַ�׼�����ж�
    IOWR_ALTERA_AVALON_UART_STATUS(UART0_BASE, 0);   //��״̬�Ĵ���
    alt_irq_register(UART0_IRQ, (void *)0, Uart_ISR);  //ע���ж�
}


/*��ʱ������*/
void ISR_timer0()
{
    IOWR_ALTERA_AVALON_UART_CONTROL(UART0_BASE,0);
    IOWR_ALTERA_AVALON_UART_TXDATA(UART0_BASE, '\n'); 
    IOWR_ALTERA_AVALON_UART_CONTROL(UART0_BASE,ALTERA_AVALON_UART_CONTROL_TRDY_MSK);
    IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER0_BASE, 0x00);       //���timer0�жϱ�־�Ĵ���
}
void timer_init(void)     
{ 
     IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER0_BASE, 0x00);       //���timer0�жϱ�־�Ĵ���
     IOWR_ALTERA_AVALON_TIMER_PERIODL(TIMER0_BASE,50000000);   //����timer0����
     IOWR_ALTERA_AVALON_TIMER_PERIODH(TIMER0_BASE, 50000000 >> 16); 
     IOWR_ALTERA_AVALON_TIMER_CONTROL(TIMER0_BASE, 0x00);      //����timer0�ж�
     alt_irq_register(TIMER0_IRQ, (void *)0, ISR_timer0);      //ע��timer0�ж�
}
 
int main()
{
    //alt_irq_context status;  
    //status = alt_irq_disable_all();
    UartInit();  //���ڳ�ʼ��
    timer_init();  //��ʱ����ʼ��
    //alt_irq_enable_all(status);
    while(1);
    return 0;
}
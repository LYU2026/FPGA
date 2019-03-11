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

#define  CAN_MOD               0//ģʽ�Ĵ���
#define  CAN_CMR               1//����Ĵ���
#define  CAN_SR                2//״̬�Ĵ���
#define  CAN_IR                3//�жϼĴ���
#define  CAN_IER               4//�ж�ʹ�ܼĴ���
#define  CAN_BTR0              6//���߶�ʱ�Ĵ���1
#define  CAN_BTR1              7//���߶�ʱ�Ĵ���2
#define  CAN_OCR               8//�������
#define  CAN_ALC              11//�ٲö�ʧ��׽�Ĵ���
#define  CAN_ECC              12//������벶׽�Ĵ���
#define  CAN_EMLR             13//���󱨾����ƼĴ���
#define  CAN_RXERR            14//RX��������Ĵ���
#define  CAN_TXERR            15//TX��������Ĵ���
#define  CAN_TX_SFF_EFF_H     16//���շ���֡
#define  CAN_TX_SFF_EFF_C1    17//ʶ����1
#define  CAN_TX_SFF_EFF_C2    18//ʶ����2
#define  CAN_TX_EFF_C3        19//ʶ����3
#define  CAN_TX_EFF_C4        20//ʶ����4
#define  CAN_ACR0             16//������1
#define  CAN_ACR1             17//������2
#define  CAN_ACR2             18//������3
#define  CAN_ACR3             19//������4
#define  CAN_AMR0             20//������1
#define  CAN_AMR1             21//������2
#define  CAN_AMR2             22//������3
#define  CAN_AMR3             23//������4
#define  CAN_TX_RX_DATA1      21//��������1
#define  CAN_TX_RX_DATA2      22//��������2
#define  CAN_TX_RX_DATA3      23//��������3
#define  CAN_TX_RX_DATA4      24//��������4
#define  CAN_TX_RX_DATA5      25//��������5
#define  CAN_TX_RX_DATA6      26//��������6
#define  CAN_TX_RX_DATA7      27//��������7
#define  CAN_TX_RX_DATA8      28//��������8
#define  CAN_RMC              29//RX��Ϣ������
#define  CAN_RBSA             30//RX��������ʼ��ַ
#define  CAN_CDR              31//ʱ�ӷ�Ƶ��

#define  CAN1_CS              0x000//CAN1ѡͨ
#define  CAN2_CS              0x100//CAN2ѡͨ
#define  CAN_ALL              0x200//˫CANд����

#define  CAN_SELF_CHECK_ACR0_R         0x67//�Լ��������ʶ����
#define  CAN_SELF_CHECK_ACR1_R         0x85
#define  CAN_SELF_CHECK_ACR2_R         0x03
#define  CAN_SELF_CHECK_ACR3_R         0xC0

#define  CAN_STATUS_CHECK_ACR0_R       0x64//�����豸״̬��ѯ�������ʶ����
#define  CAN_STATUS_CHECK_ACR1_R       0x04
#define  CAN_STATUS_CHECK_ACR2_R       0x13
#define  CAN_STATUS_CHECK_ACR3_R       0xC0

#define  CAN_SELF_CHECK_ACR0_T         0x67//�Լ�������ʶ����
#define  CAN_SELF_CHECK_ACR1_T         0x84
#define  CAN_SELF_CHECK_ACR2_T         0x00
#define  CAN_SELF_CHECK_ACR3_T         0x08

#define  CAN_WORK_STATUS_ACR0_T        0x27//����״̬����ʶ����
#define  CAN_WORK_STATUS_ACR1_T        0x8f
#define  CAN_WORK_STATUS_ACR2_T        0x00
#define  CAN_WORK_STATUS_ACR3_T        0x08

#define  CAN_RESPONSE_ACR0_T           0x37//��Ӧ״̬����ʶ����
#define  CAN_RESPONSE_ACR1_T           0x40
#define  CAN_RESPONSE_ACR2_T           0x28
#define  CAN_RESPONSE_ACR3_T           0x08

#define  CAN_alarm_ACR0_T              0x27//�����źŷ���ʶ����
#define  CAN_alarm_ACR1_T              0x9D
#define  CAN_alarm_ACR2_T              0x84
#define  CAN_alarm_ACR3_T              0x10

#define  CAN_ACR0_DATA_R               0x23//0x03//����������
#define  CAN_ACR1_DATA_R               0x00//0x81
#define  CAN_ACR2_DATA_R               0x08//0x10
#define  CAN_ACR3_DATA_R               0x28//0x00

#define  CAN_AMR0_DATA_R               0XFF//0x54//0x03//����������
#define  CAN_AMR1_DATA_R               0XFF//0xf8//0x81
#define  CAN_AMR2_DATA_R               0XFF//0x00//0x10
#define  CAN_AMR3_DATA_R               0XFF//0x07//0x00

#define  CAN2_ACR0_DATA_R               0x23//0x03//����������
#define  CAN2_ACR1_DATA_R               0x00//0x81
#define  CAN2_ACR2_DATA_R               0x08//0x10
#define  CAN2_ACR3_DATA_R               0x28//0x00

#define  CAN2_AMR0_DATA_R               0x54//0x03//����������
#define  CAN2_AMR1_DATA_R               0xf8//0x81
#define  CAN2_AMR2_DATA_R               0x00//0x10
#define  CAN2_AMR3_DATA_R               0x07//0x00


unsigned char UartBuffer[100] = {0};
unsigned char TimeUartBuffer[100] = {0};
int RxCounter = 0;
int TimeRxCounter = 0;
int TxCounter = 0;

unsigned int time_1s=0,time_10ms=0,time_200ms=0,time_3s=0;
unsigned char time_1s_flag=0,time_10ms_flag=0,time_200ms_flag=0,time_3s_flag=0;

unsigned char receive_comm_flag,can1_rx_flag,can2_rx_flag,can1_bus_status_flag=0,can2_bus_status_flag=0;

unsigned char can1_rx_time_id,last_can1_rx_time_id,last_can1_ACR[4],can1_frame_repeat_flag;
unsigned char can2_rx_time_id,last_can2_rx_time_id,last_can2_ACR[4],can2_frame_repeat_flag;

unsigned char yibao_new5[4],check_result_ID[4],databuff[8];

unsigned char work_status=0x0f,work_status_num;//�豸״̬��OX0F������0XFF���ϣ����豸״̬���飨8λ�ֱ����ͬ�Ĺ�����ʽ���������ȷ����
unsigned char alarm_duji_flag,alarm_fushe_flag,alarm_yibao_flag,alarm_fun_open_flag,alarm_fun_close_flag,alarm_status_num;
//������־�����������������״̬���飨λ0��1����ͱ�����0�����������λ1��1����߱�����0�����������λ2��1����������0����������λ3��1����ֱ�������0����ֱ�������λ4��1���ȴ򿪣�0���ȹرգ���

unsigned char can1_self_check_send_complete_flag,can2_self_check_send_complete_flag,
              can2_work_status_send_complete_flag,can1_work_status_send_complete_flag,can1_response_valid_flag,
              can1_alarm_send_complete_flag,can2_alarm_send_complete_flag;
unsigned char alarm_send_time_id=1;

unsigned char status[8]={0,0x1e,0xfe,0,0,0,0,0};
unsigned char zjxx=0x00;//�Լ���Ϣ
unsigned char time_500ms_flag=0,rx_shibiao=1,tx_shibiao=1,last_shibiao=1;
unsigned int  time_500ms=0,shibiao;

//****************************TIMER*************************************************

static void alt_can_irq(void* context, alt_u32 id);

/*��ʱ������*/
static void alt_timer_irq(void* context, alt_u32 id)
{
   IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER0_BASE, 0);  //�����ʱ��״̬�Ĵ���
   
   time_10ms++;
   time_200ms++;
   time_1s++;
   time_3s++;
   time_500ms++;
   if(time_500ms>=500)  //����ʱ��Ϊ500umʱ��time_500ms>=1000// ��ʱ��1ms 500
       {
        time_500ms=0;
        time_500ms_flag=1;
       }
    
   if (time_10ms>=10) //5ms ����ʱ��Ϊ500umʱ��time_5ms>=10 //�޸�Ϊ10ms
      {
        time_10ms=0;
        time_10ms_flag=1;
      } 
   if (time_200ms>=200) //200ms ����ʱ��Ϊ500umʱ��time_200ms>=400
      {
        time_200ms=0;
        time_200ms_flag=1;
      } 
   if (time_1s>=1000) //1s ����ʱ��Ϊ500umʱ��time_1s>=2000
      {
        time_1s=0;
        time_1s_flag=1;
      }
   if (time_3s>=3000) //3s ����ʱ��Ϊ500umʱ��time_1s>=6000
      {
        time_3s=0;
        time_3s_flag=1;
      }    
}
void alt_timer_can_init(void)
{    
   IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER0_BASE, 0);
   IOWR_ALTERA_AVALON_TIMER_CONTROL(TIMER0_BASE, 0x07);    
   alt_irq_register(TIMER0_IRQ, (void *)0, alt_timer_irq);  
}

/*CAN����*/
void can1_init(void)
{
   unsigned int can_addr;
   unsigned char can_status;
   can_addr=CAN_IER | CAN1_CS;//��CAN1����
   IOWR(CAN_BASE,can_addr,0x00);//��ֹ�ж�
   
   can_addr=CAN_MOD | CAN1_CS;//��CAN1����
   IOWR(CAN_BASE,can_addr,0x09);//���븴λģʽ���������˲���
   
   can_addr=CAN_MOD | CAN1_CS;//��CAN1
   can_status=(unsigned char)IORD(CAN_BASE,can_addr);
   time_3s=0;
   time_3s_flag=0; //3s����ʱ�䣬��ʱ��ֹͣ����    
   while(((can_status&0x01)==0x00) && (time_3s_flag==0))//���CAN1�Ƿ���븴λģʽ
   {
      IOWR(CAN_BASE,can_addr,0x09);//CAN1 ���븴λģʽ���������˲���
      can_status=(unsigned char)IORD(CAN_BASE,can_addr);      
   } 
 
   can_addr=CAN_CDR | CAN1_CS;//��CAN1����
   IOWR(CAN_BASE,can_addr,0xC1);//peliCAN,��ֹʱ���������ֹTX1,RX1  c8
   can_addr=CAN_ACR0 | CAN1_CS;//��CAN1����
   IOWR(CAN_BASE,can_addr,0x00);//CAN_ACR0_DATA_R);//������1
   can_addr=CAN_ACR1 | CAN1_CS;//��CAN1����
   IOWR(CAN_BASE,can_addr,0x00);//CAN_ACR1_DATA_R);//������2
   can_addr=CAN_ACR2 | CAN1_CS;//��CAN1����
   IOWR(CAN_BASE,can_addr,0x00);//CAN_ACR2_DATA_R);//������3
   can_addr=CAN_ACR3 | CAN1_CS;//��CAN1����
   IOWR(CAN_BASE,can_addr,0x00);//CAN_ACR3_DATA_R);//������4
   can_addr=CAN_AMR0 | CAN1_CS;//��CAN1����
   IOWR(CAN_BASE,can_addr,0xFF);//CAN_AMR0_DATA_R);//������1
   can_addr=CAN_AMR1 | CAN1_CS;//��CAN1����
   IOWR(CAN_BASE,can_addr,0xFF);//CAN_AMR1_DATA_R);//������2
   can_addr=CAN_AMR2 | CAN1_CS;//��CAN1����
   IOWR(CAN_BASE,can_addr,0xFF);//CAN_AMR2_DATA_R);//������3
   can_addr=CAN_AMR3 | CAN1_CS;//��CAN1����
   IOWR(CAN_BASE,can_addr,0xFF);//CAN_AMR3_DATA_R);//������4
   can_addr=CAN_BTR0 | CAN1_CS;//��CAN1����
   IOWR(CAN_BASE,can_addr,0x01);//ͬ����ת3�����ڣ�ϵͳʱ��4������   ������
   can_addr=CAN_BTR1 | CAN1_CS;//��CAN1����
   IOWR(CAN_BASE,can_addr,0x1C);//������3����һ6���ζ�3
   can_addr=CAN_OCR | CAN1_CS;//��CAN1����
   IOWR(CAN_BASE,can_addr,0x1A);//���ƼĴ���
   can_addr=CAN_MOD | CAN1_CS;//��CAN1����
   IOWR(CAN_BASE,can_addr,0x08);//���빤��ģʽ���������˲���
   
   can_addr=CAN_MOD | CAN1_CS;//��CAN1
   can_status=(unsigned char)IORD(CAN_BASE,can_addr);
   time_3s=0;
   time_3s_flag=0; //3s����ʱ�䣬��ʱ��ֹͣ����
   while((can_status&0x01)==0x01 && time_3s_flag==0)//����Ƿ���븴λģʽ
   {
      IOWR(CAN_BASE,can_addr,0x08);//���빤��ģʽ���������˲���
      can_status=(unsigned char)IORD(CAN_BASE,can_addr);
   }
   can_addr=CAN_IER | CAN1_CS;//��CAN1����
   IOWR(CAN_BASE,can_addr,0x01);//�������ж�
   alt_irq_register (CAN_IRQ, (void *)0, alt_can_irq); 
}

static void alt_can_irq(void* context, alt_u32 id)
{
  unsigned int can_addr;
  unsigned char data_buff,rx1_acr[4],length_1,i;
  
  can_addr=CAN1_CS | CAN_IR;//�ж��Ƿ�CAN1�����ж�
  data_buff=IORD(CAN_BASE,can_addr);
  IOWR(CAN_BASE, can_addr, 0);
  if(data_buff&0x01)//CAN1�����ж�
  {
    can_addr=CAN1_CS | CAN_TX_SFF_EFF_C1;
    rx1_acr[0]=IORD(CAN_BASE,can_addr);//������1
    can_addr=CAN1_CS | CAN_TX_SFF_EFF_C2;
    rx1_acr[1]=IORD(CAN_BASE,can_addr);//������2
    can_addr=CAN1_CS | CAN_TX_EFF_C3;
    rx1_acr[2]=IORD(CAN_BASE,can_addr);//������3
    can_addr=CAN1_CS | CAN_TX_EFF_C4;
    rx1_acr[3]=IORD(CAN_BASE,can_addr);//������4
    
//    rx1_acr[3]=(rx1_acr[3]>>3)+(rx1_acr[2]<<5);//SA
//    rx1_acr[2]=(rx1_acr[2]>>3)+(rx1_acr[1]<<5);//PS/DA
//    rx1_acr[1]=(rx1_acr[1]>>3)+(rx1_acr[0]<<5);//PF
//    rx1_acr[0]=rx1_acr[0]>>3;              //���ȼ�
//    can_addr=CAN1_CS | CAN_TX_RX_DATA1;
//    rx_shibiao=IORD(CAN_BASE,can_addr);//��ȡ�Լ������ʱ�����
    
    can1_frame_repeat_flag=0;//can1֡�ظ���־λ����
    if ((rx1_acr[0]==last_can1_ACR[0]) && (rx1_acr[1]==last_can1_ACR[1]) && (rx1_acr[2]==last_can1_ACR[2]) && (rx1_acr[3]==last_can1_ACR[3]) && (time_200ms_flag==0)&&(rx_shibiao==last_shibiao))
       { //200ms�ڣ�can1֡��������last_can1֡��������ͬ��can1֡ʱ�������last_can1֡ʱ�������ͬ
         can1_frame_repeat_flag=1;//can1֡Ϊ�ظ�֡
       }
       
    can1_rx_flag=0;
    if (can1_frame_repeat_flag==0)//���can1֡�����ظ�֡
       { 
         if ((rx1_acr[0]==0x06)&&(rx1_acr[1]==0xEA)&&(rx1_acr[2]==0X01)&&(rx1_acr[3]==0X05))//��ѯ����  ���ͷ�������Աϵͳ0X01 ���շ�������Աϵͳ������ ���ȼ���3   PF:0XEA   PS:0X00
            {
              can1_rx_flag=1;//CAN1�յ���ѯ����
            }
         /*else if ((rx1_acr[0]==0X02)&&(rx1_acr[1]==0XF1)&&(rx1_acr[2]==0XE0)&&(rx1_acr[3]==0X01))//����Աϵͳ����������
                 {
                   can1_rx_flag=2;//����Աϵͳ����������
                 }*/
         can_addr=CAN1_CS | CAN_TX_SFF_EFF_H;
         length_1=IORD(CAN_BASE,can_addr) & 0x0f;//can1֡����    
         for (i=0;i<length_1;i++)
             {
               databuff[i]=IORD(CAN_BASE,21+i);//��can1֡����
             //  printf("%x ",databuff[i]);
             }
         if (can1_rx_flag!=0) receive_comm_flag=1;//���can1���ܵ�֡�ý��ձ�־λ
         //can1_rx_flag=1;
         can_addr=CAN_CMR | CAN1_CS;
         IOWR(CAN_BASE,can_addr,0x04);//�ͷ�CAN1���ջ�����
       }    
    last_can1_ACR[0]=rx1_acr[0];
    last_can1_ACR[1]=rx1_acr[1];
    last_can1_ACR[2]=rx1_acr[2];
    last_can1_ACR[3]=rx1_acr[3];
    last_shibiao=rx_shibiao;      
  }  
  time_200ms=0;
  time_200ms_flag=0;//��200ms�ж� 
}
void self_check_send(void)
  {
    unsigned int can_addr;
    unsigned char temple_value_1;
    int i;
    unsigned char fasong[]={0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};
    
    time_10ms=0;
    time_10ms_flag=0;//5ms����ʱ�䣬��ʱ��ֹͣ����
  while ((can1_self_check_send_complete_flag==1) && (time_10ms_flag==0)) 
  {
    can_addr=CAN1_CS | CAN_SR;//�ж�CAN1���ͻ������Ƿ��ͷ�  1�����ͷ�
    temple_value_1=IORD(CAN_BASE,can_addr);
    if (((temple_value_1&0x04)!=0) && (can1_self_check_send_complete_flag==1)) //���CAN1�������ͷ�,��CAN1û������ָ��
       {
       can1_self_check_send_complete_flag=0;
       //CAN1�����Լ�֡
       can_addr=CAN1_CS | CAN_TX_SFF_EFF_H;
       IOWR(CAN_BASE,can_addr,0x88);//������չ����֡              
       can_addr=CAN1_CS | CAN_TX_SFF_EFF_C1;
       IOWR(CAN_BASE,can_addr,0X00);//CAN_SELF_CHECK_ACR0_T);//ʶ����1
       can_addr=CAN1_CS | CAN_TX_SFF_EFF_C2;
       IOWR(CAN_BASE,can_addr,0X00);//CAN_SELF_CHECK_ACR1_T);//ʶ����2
       can_addr=CAN1_CS | CAN_TX_EFF_C3;
       IOWR(CAN_BASE,can_addr,0X00);//CAN_SELF_CHECK_ACR2_T);//ʶ����3
       can_addr=CAN1_CS | CAN_TX_EFF_C4;
       IOWR(CAN_BASE,can_addr,0X00);//CAN_SELF_CHECK_ACR3_T);//ʶ����4
       for(i=0;i<8;i++)
       {       
       can_addr=CAN1_CS | (21+i);
       IOWR(CAN_BASE,can_addr,fasong[i]);}//����1�豸״̬ 0x00������0x01���� 
       
       can_addr=CAN1_CS | CAN_CMR;
       IOWR(CAN_BASE,can_addr,0x01);//��������  
       }       
  }
  can1_self_check_send_complete_flag=0;//���������5ms����δ������߷��ͣ�ȡ��δ��ɵķ���    
}

/*��������*/
void SetBaudrate(unsigned int baudrate)  //����������
{      
     IOWR_ALTERA_AVALON_UART_DIVISOR(UART0_BASE, ALT_CPU_FREQ/baudrate+0.5); 
}
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
                IOWR_ALTERA_AVALON_UART_CONTROL(UART0_BASE, 0);    //�رմ��������ж�
                   // IOWR_ALTERA_AVALON_UART_TXDATA(UART0_BASE, '\n'); 
                IOWR_ALTERA_AVALON_UART_CONTROL(UART0_BASE, ALTERA_AVALON_UART_CONTROL_TRDY_MSK);  //��������׼�����ж�
            }
                TimeRxCounter = RxCounter;
                RxCounter = 0;                
          }
          if(RxCounter > 99)  RxCounter = 0;
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
            IOWR_ALTERA_AVALON_UART_CONTROL(UART0_BASE, 0);  //�رմ��������ж�
            IOWR_ALTERA_AVALON_UART_CONTROL(UART0_BASE,ALTERA_AVALON_UART_STATUS_RRDY_MSK);   //����������ַ�׼�����ж�                          
         }            
    }    
}
    
void UartInit(void)  //���ڳ�ʼ��
{
    SetBaudrate(9600);  //������9600
    IOWR_ALTERA_AVALON_UART_CONTROL(UART0_BASE, 0); 
    IOWR_ALTERA_AVALON_UART_CONTROL(UART0_BASE, ALTERA_AVALON_UART_CONTROL_RRDY_MSK);   //����������ַ�׼�����ж�
    IOWR_ALTERA_AVALON_UART_STATUS(UART0_BASE, 0);   //��״̬�Ĵ���
    alt_irq_register(UART0_IRQ, (void *)0, Uart_ISR);  //ע���ж�
}
int main()
{
  alt_timer_can_init();
  can1_init();

  while(1) 
  {
    can1_self_check_send_complete_flag = 1;
    self_check_send();
    usleep(100);
  }
  return 0;
}

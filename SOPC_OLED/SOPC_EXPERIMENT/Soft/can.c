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

#define  CAN_MOD               0//模式寄存器
#define  CAN_CMR               1//命令寄存器
#define  CAN_SR                2//状态寄存器
#define  CAN_IR                3//中断寄存器
#define  CAN_IER               4//中断使能寄存器
#define  CAN_BTR0              6//总线定时寄存器1
#define  CAN_BTR1              7//总线定时寄存器2
#define  CAN_OCR               8//输出控制
#define  CAN_ALC              11//仲裁丢失捕捉寄存器
#define  CAN_ECC              12//错误代码捕捉寄存器
#define  CAN_EMLR             13//错误报警限制寄存器
#define  CAN_RXERR            14//RX错误计数寄存器
#define  CAN_TXERR            15//TX错误计数寄存器
#define  CAN_TX_SFF_EFF_H     16//接收发送帧
#define  CAN_TX_SFF_EFF_C1    17//识别码1
#define  CAN_TX_SFF_EFF_C2    18//识别码2
#define  CAN_TX_EFF_C3        19//识别码3
#define  CAN_TX_EFF_C4        20//识别码4
#define  CAN_ACR0             16//验收码1
#define  CAN_ACR1             17//验收码2
#define  CAN_ACR2             18//验收码3
#define  CAN_ACR3             19//验收码4
#define  CAN_AMR0             20//屏蔽码1
#define  CAN_AMR1             21//屏蔽码2
#define  CAN_AMR2             22//屏蔽码3
#define  CAN_AMR3             23//屏蔽码4
#define  CAN_TX_RX_DATA1      21//发送数据1
#define  CAN_TX_RX_DATA2      22//发送数据2
#define  CAN_TX_RX_DATA3      23//发送数据3
#define  CAN_TX_RX_DATA4      24//发送数据4
#define  CAN_TX_RX_DATA5      25//发送数据5
#define  CAN_TX_RX_DATA6      26//发送数据6
#define  CAN_TX_RX_DATA7      27//发送数据7
#define  CAN_TX_RX_DATA8      28//发送数据8
#define  CAN_RMC              29//RX信息计数器
#define  CAN_RBSA             30//RX缓冲器起始地址
#define  CAN_CDR              31//时钟分频器

#define  CAN1_CS              0x000//CAN1选通
#define  CAN2_CS              0x100//CAN2选通
#define  CAN_ALL              0x200//双CAN写操作

#define  CAN_SELF_CHECK_ACR0_R         0x67//自检命令接收识别码
#define  CAN_SELF_CHECK_ACR1_R         0x85
#define  CAN_SELF_CHECK_ACR2_R         0x03
#define  CAN_SELF_CHECK_ACR3_R         0xC0

#define  CAN_STATUS_CHECK_ACR0_R       0x64//故障设备状态查询命令接收识别码
#define  CAN_STATUS_CHECK_ACR1_R       0x04
#define  CAN_STATUS_CHECK_ACR2_R       0x13
#define  CAN_STATUS_CHECK_ACR3_R       0xC0

#define  CAN_SELF_CHECK_ACR0_T         0x67//自检结果发送识别码
#define  CAN_SELF_CHECK_ACR1_T         0x84
#define  CAN_SELF_CHECK_ACR2_T         0x00
#define  CAN_SELF_CHECK_ACR3_T         0x08

#define  CAN_WORK_STATUS_ACR0_T        0x27//工作状态发送识别码
#define  CAN_WORK_STATUS_ACR1_T        0x8f
#define  CAN_WORK_STATUS_ACR2_T        0x00
#define  CAN_WORK_STATUS_ACR3_T        0x08

#define  CAN_RESPONSE_ACR0_T           0x37//响应状态发送识别码
#define  CAN_RESPONSE_ACR1_T           0x40
#define  CAN_RESPONSE_ACR2_T           0x28
#define  CAN_RESPONSE_ACR3_T           0x08

#define  CAN_alarm_ACR0_T              0x27//报警信号发送识别码
#define  CAN_alarm_ACR1_T              0x9D
#define  CAN_alarm_ACR2_T              0x84
#define  CAN_alarm_ACR3_T              0x10

#define  CAN_ACR0_DATA_R               0x23//0x03//接收屏蔽码
#define  CAN_ACR1_DATA_R               0x00//0x81
#define  CAN_ACR2_DATA_R               0x08//0x10
#define  CAN_ACR3_DATA_R               0x28//0x00

#define  CAN_AMR0_DATA_R               0XFF//0x54//0x03//接收屏蔽码
#define  CAN_AMR1_DATA_R               0XFF//0xf8//0x81
#define  CAN_AMR2_DATA_R               0XFF//0x00//0x10
#define  CAN_AMR3_DATA_R               0XFF//0x07//0x00

#define  CAN2_ACR0_DATA_R               0x23//0x03//接收屏蔽码
#define  CAN2_ACR1_DATA_R               0x00//0x81
#define  CAN2_ACR2_DATA_R               0x08//0x10
#define  CAN2_ACR3_DATA_R               0x28//0x00

#define  CAN2_AMR0_DATA_R               0x54//0x03//接收屏蔽码
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

unsigned char work_status=0x0f,work_status_num;//设备状态（OX0F正常，0XFF故障），设备状态详情（8位分别代表不同的故障形式，根据情况确定）
unsigned char alarm_duji_flag,alarm_fushe_flag,alarm_yibao_flag,alarm_fun_open_flag,alarm_fun_close_flag,alarm_status_num;
//报警标志（不需操作），报警状态详情（位0：1辐射低报警，0辐射低正常；位1：1辐射高报警，0辐射高正常；位2：1毒剂报警，0毒剂正常；位3：1灭火抑爆报警，0灭火抑爆正常；位4：1风扇打开，0风扇关闭；）

unsigned char can1_self_check_send_complete_flag,can2_self_check_send_complete_flag,
              can2_work_status_send_complete_flag,can1_work_status_send_complete_flag,can1_response_valid_flag,
              can1_alarm_send_complete_flag,can2_alarm_send_complete_flag;
unsigned char alarm_send_time_id=1;

unsigned char status[8]={0,0x1e,0xfe,0,0,0,0,0};
unsigned char zjxx=0x00;//自检信息
unsigned char time_500ms_flag=0,rx_shibiao=1,tx_shibiao=1,last_shibiao=1;
unsigned int  time_500ms=0,shibiao;

//****************************TIMER*************************************************

static void alt_can_irq(void* context, alt_u32 id);

/*定时器配置*/
static void alt_timer_irq(void* context, alt_u32 id)
{
   IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER0_BASE, 0);  //清除定时器状态寄存器
   
   time_10ms++;
   time_200ms++;
   time_1s++;
   time_3s++;
   time_500ms++;
   if(time_500ms>=500)  //当定时器为500um时，time_500ms>=1000// 定时器1ms 500
       {
        time_500ms=0;
        time_500ms_flag=1;
       }
    
   if (time_10ms>=10) //5ms 当定时器为500um时，time_5ms>=10 //修改为10ms
      {
        time_10ms=0;
        time_10ms_flag=1;
      } 
   if (time_200ms>=200) //200ms 当定时器为500um时，time_200ms>=400
      {
        time_200ms=0;
        time_200ms_flag=1;
      } 
   if (time_1s>=1000) //1s 当定时器为500um时，time_1s>=2000
      {
        time_1s=0;
        time_1s_flag=1;
      }
   if (time_3s>=3000) //3s 当定时器为500um时，time_1s>=6000
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

/*CAN配置*/
void can1_init(void)
{
   unsigned int can_addr;
   unsigned char can_status;
   can_addr=CAN_IER | CAN1_CS;//对CAN1操作
   IOWR(CAN_BASE,can_addr,0x00);//禁止中断
   
   can_addr=CAN_MOD | CAN1_CS;//对CAN1操作
   IOWR(CAN_BASE,can_addr,0x09);//进入复位模式，单验收滤波器
   
   can_addr=CAN_MOD | CAN1_CS;//读CAN1
   can_status=(unsigned char)IORD(CAN_BASE,can_addr);
   time_3s=0;
   time_3s_flag=0; //3s配置时间，超时后停止配置    
   while(((can_status&0x01)==0x00) && (time_3s_flag==0))//检测CAN1是否进入复位模式
   {
      IOWR(CAN_BASE,can_addr,0x09);//CAN1 进入复位模式，单验收滤波器
      can_status=(unsigned char)IORD(CAN_BASE,can_addr);      
   } 
 
   can_addr=CAN_CDR | CAN1_CS;//对CAN1操作
   IOWR(CAN_BASE,can_addr,0xC1);//peliCAN,禁止时钟输出，禁止TX1,RX1  c8
   can_addr=CAN_ACR0 | CAN1_CS;//对CAN1操作
   IOWR(CAN_BASE,can_addr,0x00);//CAN_ACR0_DATA_R);//验收码1
   can_addr=CAN_ACR1 | CAN1_CS;//对CAN1操作
   IOWR(CAN_BASE,can_addr,0x00);//CAN_ACR1_DATA_R);//验收码2
   can_addr=CAN_ACR2 | CAN1_CS;//对CAN1操作
   IOWR(CAN_BASE,can_addr,0x00);//CAN_ACR2_DATA_R);//验收码3
   can_addr=CAN_ACR3 | CAN1_CS;//对CAN1操作
   IOWR(CAN_BASE,can_addr,0x00);//CAN_ACR3_DATA_R);//验收码4
   can_addr=CAN_AMR0 | CAN1_CS;//对CAN1操作
   IOWR(CAN_BASE,can_addr,0xFF);//CAN_AMR0_DATA_R);//屏蔽码1
   can_addr=CAN_AMR1 | CAN1_CS;//对CAN1操作
   IOWR(CAN_BASE,can_addr,0xFF);//CAN_AMR1_DATA_R);//屏蔽码2
   can_addr=CAN_AMR2 | CAN1_CS;//对CAN1操作
   IOWR(CAN_BASE,can_addr,0xFF);//CAN_AMR2_DATA_R);//屏蔽码3
   can_addr=CAN_AMR3 | CAN1_CS;//对CAN1操作
   IOWR(CAN_BASE,can_addr,0xFF);//CAN_AMR3_DATA_R);//屏蔽码4
   can_addr=CAN_BTR0 | CAN1_CS;//对CAN1操作
   IOWR(CAN_BASE,can_addr,0x01);//同步跳转3个周期，系统时钟4倍周期   波特率
   can_addr=CAN_BTR1 | CAN1_CS;//对CAN1操作
   IOWR(CAN_BASE,can_addr,0x1C);//采样点3，段一6，段二3
   can_addr=CAN_OCR | CAN1_CS;//对CAN1操作
   IOWR(CAN_BASE,can_addr,0x1A);//控制寄存器
   can_addr=CAN_MOD | CAN1_CS;//对CAN1操作
   IOWR(CAN_BASE,can_addr,0x08);//进入工作模式，单验收滤波器
   
   can_addr=CAN_MOD | CAN1_CS;//读CAN1
   can_status=(unsigned char)IORD(CAN_BASE,can_addr);
   time_3s=0;
   time_3s_flag=0; //3s配置时间，超时后停止配置
   while((can_status&0x01)==0x01 && time_3s_flag==0)//检测是否进入复位模式
   {
      IOWR(CAN_BASE,can_addr,0x08);//进入工作模式，单验收滤波器
      can_status=(unsigned char)IORD(CAN_BASE,can_addr);
   }
   can_addr=CAN_IER | CAN1_CS;//对CAN1操作
   IOWR(CAN_BASE,can_addr,0x01);//开接收中断
   alt_irq_register (CAN_IRQ, (void *)0, alt_can_irq); 
}

static void alt_can_irq(void* context, alt_u32 id)
{
  unsigned int can_addr;
  unsigned char data_buff,rx1_acr[4],length_1,i;
  
  can_addr=CAN1_CS | CAN_IR;//判断是否CAN1接收中断
  data_buff=IORD(CAN_BASE,can_addr);
  IOWR(CAN_BASE, can_addr, 0);
  if(data_buff&0x01)//CAN1接收中断
  {
    can_addr=CAN1_CS | CAN_TX_SFF_EFF_C1;
    rx1_acr[0]=IORD(CAN_BASE,can_addr);//验收码1
    can_addr=CAN1_CS | CAN_TX_SFF_EFF_C2;
    rx1_acr[1]=IORD(CAN_BASE,can_addr);//验收码2
    can_addr=CAN1_CS | CAN_TX_EFF_C3;
    rx1_acr[2]=IORD(CAN_BASE,can_addr);//验收码3
    can_addr=CAN1_CS | CAN_TX_EFF_C4;
    rx1_acr[3]=IORD(CAN_BASE,can_addr);//验收码4
    
//    rx1_acr[3]=(rx1_acr[3]>>3)+(rx1_acr[2]<<5);//SA
//    rx1_acr[2]=(rx1_acr[2]>>3)+(rx1_acr[1]<<5);//PS/DA
//    rx1_acr[1]=(rx1_acr[1]>>3)+(rx1_acr[0]<<5);//PF
//    rx1_acr[0]=rx1_acr[0]>>3;              //优先级
//    can_addr=CAN1_CS | CAN_TX_RX_DATA1;
//    rx_shibiao=IORD(CAN_BASE,can_addr);//读取自检命令的时标序号
    
    can1_frame_repeat_flag=0;//can1帧重复标志位清零
    if ((rx1_acr[0]==last_can1_ACR[0]) && (rx1_acr[1]==last_can1_ACR[1]) && (rx1_acr[2]==last_can1_ACR[2]) && (rx1_acr[3]==last_can1_ACR[3]) && (time_200ms_flag==0)&&(rx_shibiao==last_shibiao))
       { //200ms内，can1帧验收码与last_can1帧验收码相同，can1帧时标序号与last_can1帧时标序号相同
         can1_frame_repeat_flag=1;//can1帧为重复帧
       }
       
    can1_rx_flag=0;
    if (can1_frame_repeat_flag==0)//如果can1帧不是重复帧
       { 
         if ((rx1_acr[0]==0x06)&&(rx1_acr[1]==0xEA)&&(rx1_acr[2]==0X01)&&(rx1_acr[3]==0X05))//查询命令  发送方：承载员系统0X01 接收方：承载员系统控制器 优先级：3   PF:0XEA   PS:0X00
            {
              can1_rx_flag=1;//CAN1收到查询命令
            }
         /*else if ((rx1_acr[0]==0X02)&&(rx1_acr[1]==0XF1)&&(rx1_acr[2]==0XE0)&&(rx1_acr[3]==0X01))//承载员系统控制器参数
                 {
                   can1_rx_flag=2;//承载员系统控制器参数
                 }*/
         can_addr=CAN1_CS | CAN_TX_SFF_EFF_H;
         length_1=IORD(CAN_BASE,can_addr) & 0x0f;//can1帧长度    
         for (i=0;i<length_1;i++)
             {
               databuff[i]=IORD(CAN_BASE,21+i);//读can1帧数据
             //  printf("%x ",databuff[i]);
             }
         if (can1_rx_flag!=0) receive_comm_flag=1;//如果can1接受到帧置接收标志位
         //can1_rx_flag=1;
         can_addr=CAN_CMR | CAN1_CS;
         IOWR(CAN_BASE,can_addr,0x04);//释放CAN1接收缓冲区
       }    
    last_can1_ACR[0]=rx1_acr[0];
    last_can1_ACR[1]=rx1_acr[1];
    last_can1_ACR[2]=rx1_acr[2];
    last_can1_ACR[3]=rx1_acr[3];
    last_shibiao=rx_shibiao;      
  }  
  time_200ms=0;
  time_200ms_flag=0;//打开200ms中断 
}
void self_check_send(void)
  {
    unsigned int can_addr;
    unsigned char temple_value_1;
    int i;
    unsigned char fasong[]={0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};
    
    time_10ms=0;
    time_10ms_flag=0;//5ms发送时间，超时后停止发送
  while ((can1_self_check_send_complete_flag==1) && (time_10ms_flag==0)) 
  {
    can_addr=CAN1_CS | CAN_SR;//判断CAN1发送缓冲区是否释放  1——释放
    temple_value_1=IORD(CAN_BASE,can_addr);
    if (((temple_value_1&0x04)!=0) && (can1_self_check_send_complete_flag==1)) //如果CAN1缓冲区释放,且CAN1没发送完指令
       {
       can1_self_check_send_complete_flag=0;
       //CAN1发送自检帧
       can_addr=CAN1_CS | CAN_TX_SFF_EFF_H;
       IOWR(CAN_BASE,can_addr,0x88);//发送扩展数据帧              
       can_addr=CAN1_CS | CAN_TX_SFF_EFF_C1;
       IOWR(CAN_BASE,can_addr,0X00);//CAN_SELF_CHECK_ACR0_T);//识别码1
       can_addr=CAN1_CS | CAN_TX_SFF_EFF_C2;
       IOWR(CAN_BASE,can_addr,0X00);//CAN_SELF_CHECK_ACR1_T);//识别码2
       can_addr=CAN1_CS | CAN_TX_EFF_C3;
       IOWR(CAN_BASE,can_addr,0X00);//CAN_SELF_CHECK_ACR2_T);//识别码3
       can_addr=CAN1_CS | CAN_TX_EFF_C4;
       IOWR(CAN_BASE,can_addr,0X00);//CAN_SELF_CHECK_ACR3_T);//识别码4
       for(i=0;i<8;i++)
       {       
       can_addr=CAN1_CS | (21+i);
       IOWR(CAN_BASE,can_addr,fasong[i]);}//数据1设备状态 0x00正常，0x01故障 
       
       can_addr=CAN1_CS | CAN_CMR;
       IOWR(CAN_BASE,can_addr,0x01);//发送请求  
       }       
  }
  can1_self_check_send_complete_flag=0;//如果发送在5ms内仍未完成总线发送，取消未完成的发送    
}

/*串口配置*/
void SetBaudrate(unsigned int baudrate)  //波特率配置
{      
     IOWR_ALTERA_AVALON_UART_DIVISOR(UART0_BASE, ALT_CPU_FREQ/baudrate+0.5); 
}
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
                IOWR_ALTERA_AVALON_UART_CONTROL(UART0_BASE, 0);    //关闭串口所有中断
                   // IOWR_ALTERA_AVALON_UART_TXDATA(UART0_BASE, '\n'); 
                IOWR_ALTERA_AVALON_UART_CONTROL(UART0_BASE, ALTERA_AVALON_UART_CONTROL_TRDY_MSK);  //打开允许传送准备好中断
            }
                TimeRxCounter = RxCounter;
                RxCounter = 0;                
          }
          if(RxCounter > 99)  RxCounter = 0;
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
            IOWR_ALTERA_AVALON_UART_CONTROL(UART0_BASE, 0);  //关闭串口所有中断
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

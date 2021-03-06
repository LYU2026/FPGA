#include <stdio.h>
#include "io.h"
#include "system.h"
#include "oled.h"



//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  Patterns
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

void Write_Command(unsigned char Command)   //OLED_IP WRITE COMMAND
{
    IOWR(OLED_BASE,0,Command);
}

void Write_Data(unsigned char  data)   //OLED_IP WRITE DATA
{
   IOWR(OLED_BASE,1, data);
}


void uDelay(unsigned char l)
{
    while(l--)
    usleep(1);
    
}


void Delay(unsigned char n)
{
unsigned char i,j,k;

    for(k=0;k<n;k++)
    {
        for(i=0;i<131;i++)
        {
            for(j=0;j<15;j++)
            {
                uDelay(203);    
            }
        }
    }
}

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  Instruction Setting
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void Set_Start_Column(unsigned char d)
{
    Write_Command(0x00+d%16);       // Set Lower Column Start Address for Page Addressing Mode
                        //   Default => 0x00
    Write_Command(0x10+d/16);       // Set Higher Column Start Address for Page Addressing Mode
                        //   Default => 0x10
}


void Set_Addressing_Mode(unsigned char d)
{
    Write_Command(0x20);            // Set Memory Addressing Mode
    Write_Command(d);           //   Default => 0x02
                        //     0x00 => Horizontal Addressing Mode
                        //     0x01 => Vertical Addressing Mode
                        //     0x02 => Page Addressing Mode
}


void Set_Column_Address(unsigned char a, unsigned char b)
{
    Write_Command(0x21);            // Set Column Address
    Write_Command(a);           //   Default => 0x00 (Column Start Address)
    Write_Command(b);           //   Default => 0x83 (Column End Address)
}


void Set_Page_Address(unsigned char a, unsigned char b)
{
    Write_Command(0x22);            // Set Page Address
    Write_Command(a);           //   Default => 0x00 (Page Start Address)
    Write_Command(b);           //   Default => 0x07 (Page End Address)
}


void Set_Start_Line(unsigned char d)
{
    Write_Command(0x40|d);          // Set Display Start Line
                        //   Default => 0x40 (0x00)
}


void Set_Contrast_Control(unsigned char d)
{
    Write_Command(0x81);            // Set Contrast Control for Bank 0
    Write_Command(d);           //   Default => 0x80
}


void Set_Area_Brightness(unsigned char d)
{
    Write_Command(0x82);            // Set Brightness for Area Color Banks
    Write_Command(d);           //   Default => 0x80
}


void Set_Segment_Remap(unsigned char d)
{
    Write_Command(0xA0|d);          // Set Segment Re-Map
                        //   Default => 0xA0
                        //     0xA0 (0x00) => Column Address 0 Mapped to SEG0
                        //     0xA1 (0x01) => Column Address 0 Mapped to SEG131
}


void Set_Entire_Display(unsigned char d)
{
    Write_Command(0xA4|d);          // Set Entire Display On / Off
                        //   Default => 0xA4
                        //     0xA4 (0x00) => Normal Display
                        //     0xA5 (0x01) => Entire Display On
}


void Set_Inverse_Display(unsigned char d)
{
    Write_Command(0xA6|d);          // Set Inverse Display On/Off
                        //   Default => 0xA6
                        //     0xA6 (0x00) => Normal Display
                        //     0xA7 (0x01) => Inverse Display On
}


void Set_Multiplex_Ratio(unsigned char d)
{
    Write_Command(0xA8);            // Set Multiplex Ratio
    Write_Command(d);           //   Default => 0x3F (1/64 Duty)
}


void Set_Dim_Mode(unsigned char a, unsigned char b)
{
    Write_Command(0xAB);            // Set Dim Mode Configuration
    Write_Command(0X00);            //           => (Dummy Write for First Parameter)
    Write_Command(a);           //   Default => 0x80 (Contrast Control for Bank 0)
    Write_Command(b);           //   Default => 0x80 (Brightness for Area Color Banks)
    Write_Command(0xAC);            // Set Display On in Dim Mode
}


void Set_Master_Config(unsigned char d)
{
    Write_Command(0xAD);            // Set Master Configuration
    Write_Command(0x8E|d);          //   Default => 0x8E
                        //     0x8E (0x00) => Select External VCC Supply
                        //     0x8F (0x01) => Select Internal DC/DC Voltage Converter
}


void Set_Display_On_Off(unsigned char d)    
{
    Write_Command(0xAE|d);          // Set Display On/Off
                        //   Default => 0xAE
                        //     0xAE (0x00) => Display Off
                        //     0xAF (0x01) => Display On
}


void Set_Start_Page(unsigned char d)
{
    Write_Command(0xB0|d);          // Set Page Start Address for Page Addressing Mode
                        //   Default => 0xB0 (0x00)
}


void Set_Common_Remap(unsigned char d)
{
    Write_Command(0xC0|d);          // Set COM Output Scan Direction
                        //   Default => 0xC0
                        //     0xC0 (0x00) => Scan from COM0 to 63
                        //     0xC8 (0x08) => Scan from COM63 to 0
}


void Set_Display_Offset(unsigned char d)
{
    Write_Command(0xD3);            // Set Display Offset
    Write_Command(d);           //   Default => 0x00
}


void Set_Display_Clock(unsigned char d)
{
    Write_Command(0xD5);            // Set Display Clock Divide Ratio / Oscillator Frequency
    Write_Command(d);           //   Default => 0x70
                        //     D[3:0] => Display Clock Divider
                        //     D[7:4] => Oscillator Frequency
}


void Set_Area_Color(unsigned char d)
{
    Write_Command(0xD8);            // Set Area Color Mode On/Off & Low Power Display Mode
    Write_Command(d);           //   Default => 0x00 (Monochrome Mode & Normal Power Display Mode)
}


void Set_Precharge_Period(unsigned char d)
{
    Write_Command(0xD9);            // Set Pre-Charge Period
    Write_Command(d);           //   Default => 0x22 (2 Display Clocks [Phase 2] / 2 Display Clocks [Phase 1])
                        //     D[3:0] => Phase 1 Period in 1~15 Display Clocks
                        //     D[7:4] => Phase 2 Period in 1~15 Display Clocks
}


void Set_Common_Config(unsigned char d)
{
    Write_Command(0xDA);            // Set COM Pins Hardware Configuration
    Write_Command(0x02|d);          //   Default => 0x12 (0x10)
                        //     Alternative COM Pin Configuration
                        //     Disable COM Left/Right Re-Map
}


void Set_VCOMH(unsigned char d)
{
    Write_Command(0xDB);            // Set VCOMH Deselect Level
    Write_Command(d);           //   Default => 0x34 (0.77*VCC)
}


void Set_Read_Modify_Write(unsigned char d)
{
    Write_Command(0xE0|d);          // Set Read Modify Write Mode
                        //   Default => 0xE0
                        //     0xE0 (0x00) => Enter Read Modify Write
                        //     0xEE (0x0E) => Exit Read Modify Write
}


void Set_NOP()
{
    Write_Command(0xE3);            // Command for No Operation
}



//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  Show Regular Pattern (Full Screen)
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void Fill_RAM(unsigned char Data)
{
unsigned char i,j;

    for(i=0;i<8;i++)
    {
        Set_Start_Page(i);
        Set_Start_Column(0x00);

        for(j=0;j<132;j++)
        {
            Write_Data(Data);
        }
    }
}


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  Show Regular Pattern (Partial or Full Screen)
//
//    a: Start Page
//    b: End Page
//    c: Start Column
//    d: Total Columns
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void Fill_Block(unsigned char Data, unsigned char a, unsigned char b, unsigned char c, unsigned char d)
{
unsigned char i,j;
    
    for(i=a;i<(b+1);i++)
    {
        Set_Start_Page(i);
        Set_Start_Column(c);

        for(j=0;j<d;j++)
        {
            Write_Data(Data);
        }
    }
}


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  Show Checkboard (Full Screen)
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void Checkerboard()
{
unsigned char i,j;
    
    for(i=0;i<8;i++)
    {
        Set_Start_Page(i);
        Set_Start_Column(0x00);

        for(j=0;j<66;j++)
        {
            Write_Data(0x55);   //note one write_data updata one line
            Write_Data(0xaa);
        }
    }
}


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  Show Frame (Full Screen)
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void Frame()
{
unsigned char i,j;
    
    Set_Start_Page(0x00);
    Set_Start_Column(XLevel);

    for(i=0;i<Max_Column;i++)  
    {
        Write_Data(0x01);  //0X01最上面点亮
    }

    Set_Start_Page(0x07); 
    Set_Start_Column(XLevel);

    for(i=0;i<Max_Column;i++)
    {
        Write_Data(0x80);  //最下面点亮
    }

    for(i=0;i<8;i++)
    {
        Set_Start_Page(i);

        for(j=4;j<Max_Column;j+=(Max_Column-5))
        {
            Set_Start_Column(XLevel+j);

            Write_Data(0xFF);
        }
    }
}


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  Show Character (5x7)
//
//    a: Database
//    b: Ascii
//    c: Start Page
//    d: Start Column
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void Show_Font57(unsigned char a, unsigned char b, unsigned char c, unsigned char d)
{
unsigned char *Src_Pointer;
unsigned char i;
i=0;
Src_Pointer=&Ascii_1[(b-1)][i];


    switch(a)
    {
        case 1:
            Src_Pointer=&Ascii_1[(b-1)][i];
            break;
        case 2:
            Src_Pointer=&Ascii_2[(b-1)][i];
            break;
    }
    Set_Start_Page(c);
    Set_Start_Column(d);

    for(i=0;i<5;i++)
    {
        Write_Data(*Src_Pointer);
        Src_Pointer++;
    }
    Write_Data(0x00);
}


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  Show String
//
//    a: Database
//    b: Start Page
//    c: Start Column
//    * Must write "0" in the end...
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void Show_String(unsigned char a, unsigned char *Data_Pointer, unsigned char b, unsigned char c)
{
unsigned char *Src_Pointer;

    Src_Pointer=Data_Pointer;
    Show_Font57(1,96,b,c);          // No-Break Space
                        //   Must be written first before the string start...

    while(1)
    {
        Show_Font57(a,*Src_Pointer,b,c);
        Src_Pointer++;
        c+=6;
        if(*Src_Pointer == 0) break;
    }
}


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  Show Pattern (Partial or Full Screen)
//
//    a: Start Page
//    b: End Page
//    c: Start Column
//    d: Total Columns
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void Show_Pattern(unsigned char *Data_Pointer, unsigned char a, unsigned char b, unsigned char c, unsigned char d)
{
unsigned char *Src_Pointer;
unsigned char i,j;

    Src_Pointer=Data_Pointer;
    for(i=a;i<(b+1);i++)
    {
        Set_Start_Page(i);
        Set_Start_Column(c);

        for(j=0;j<d;j++)
        {
            Write_Data(*Src_Pointer);
            Src_Pointer++;
        }
    }
}


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  Vertical / Fade Scrolling (Partial or Full Screen)
//
//    a: Scrolling Direction
//       "0x00" (Upward)
//       "0x01" (Downward)
//    b: Set Top Fixed Area
//    c: Set Vertical Scroll Area
//    d: Set Numbers of Row Scroll per Step
//    e: Set Time Interval between Each Scroll Step
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void Vertical_Scroll(unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned char e)
{
unsigned int i,j;   

    Write_Command(0xA3);            // Set Vertical Scroll Area
    Write_Command(b);           //   Default => 0x00 (Top Fixed Area)
    Write_Command(c);           //   Default => 0x40 (Vertical Scroll Area)

    switch(a)
    {
        case 0:
            for(i=0;i<c;i+=d)
            {
                Set_Start_Line(i);
                for(j=0;j<e;j++)
                {
                    uDelay(200);
                }
            }
            break;
        case 1:
            for(i=0;i<c;i+=d)
            {
                Set_Start_Line(c-i);
                for(j=0;j<e;j++)
                {
                    uDelay(200);
                }
            }
            break;
    }
    Set_Start_Line(0x00);
}


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  Continuous Horizontal Scrolling (Partial or Full Screen)
//
//    a: Scrolling Direction
//       "0x00" (Rightward)
//       "0x01" (Leftward)
//    b: Set Numbers of Column Scroll per Step
//    c: Define Start Page Address
//    d: Define End Page Address
//    e: Set Time Interval between Each Scroll Step in Terms of Frame Frequency
//    f: Delay Time
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void Horizontal_Scroll(unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned char e, unsigned char f)
{
    Write_Command(0x26|a);          // Horizontal Scroll Setup
    Write_Command(b);
    Write_Command(c);
    Write_Command(e);
    Write_Command(d);
    Write_Command(0x2F);            // Activate Scrolling
    Delay(f);
}


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  Continuous Vertical / Horizontal / Diagonal Scrolling (Partial or Full Screen)
//
//    a: Scrolling Direction
//       "0x00" (Vertical & Rightward)
//       "0x01" (Vertical & Leftward)
//    b: Set Numbers of Column Scroll per Step (Horizontal / Diagonal Scrolling)
//    c: Define Start Row Address (Horizontal / Diagonal Scrolling)
//    d: Define End Page Address (Horizontal / Diagonal Scrolling)
//    e: Set Top Fixed Area (Vertical Scrolling)
//    f: Set Vertical Scroll Area (Vertical Scrolling)
//    g: Set Numbers of Row Scroll per Step (Vertical / Diagonal Scrolling)
//    h: Set Time Interval between Each Scroll Step in Terms of Frame Frequency
//    i: Delay Time
//    * e+f must be less than or equal to the Multiplex Ratio...
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void Continuous_Scroll(unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned char e, unsigned char f, unsigned char g, unsigned char h, unsigned char i)
{
    Write_Command(0xA3);            // Set Vertical Scroll Area
    Write_Command(e);           //   Default => 0x00 (Top Fixed Area)
    Write_Command(f);           //   Default => 0x40 (Vertical Scroll Area)

    Write_Command(0x29+a);          // Continuous Vertical & Horizontal Scroll Setup
    Write_Command(b);
    Write_Command(c);
    Write_Command(h);
    Write_Command(d);
    Write_Command(g);
    Write_Command(0x2F);            // Activate Scrolling
    Delay(i);
}


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  Deactivate Scrolling (Full Screen)
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void Deactivate_Scroll()
{
    Write_Command(0x2E);            // Deactivate Scrolling
}


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  Fade In (Full Screen)
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void Fade_In()
{
unsigned int i; 

    Set_Display_On_Off(0x01);
    for(i=0;i<(Brightness+1);i++)
    {
        Set_Contrast_Control(i);
        uDelay(200);
        uDelay(200);
        uDelay(200);
    }
}


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  Fade Out (Full Screen)
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void Fade_Out()
{
unsigned int i; 

    for(i=(Brightness+1);i>0;i--)
    {
        Set_Contrast_Control(i-1);
        uDelay(200);
        uDelay(200);
        uDelay(200);
    }
    Set_Display_On_Off(0x00);
}


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  Sleep Mode
//
//    "0x00" Enter Sleep Mode
//    "0x01" Exit Sleep Mode
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void Sleep(unsigned char a)
{
    switch(a)
    {
        case 0:
            Set_Display_On_Off(0x00);
            Set_Entire_Display(0x01);
            break;
        case 1:
            Set_Entire_Display(0x00);
            Set_Display_On_Off(0x01);
            break;
    }
}


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  Connection Test
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void Test()
{
unsigned char i;

  //  RES=0;
    for(i=0;i<200;i++)
    {
        uDelay(200);
    }
   // RES=1;

    Set_Entire_Display(0x01);       // Enable Entire Display On (0x00/0x01)

    while(1)
    {
        Set_Display_On_Off(0x01);   // Display On (0x00/0x01)
        Delay(2);
        Set_Display_On_Off(0x00);   // Display Off (0x00/0x01)
        Delay(2);
    }
}


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  Bank Color & Look Up Table Setting (Partial Screen)
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void Set_LUT(unsigned char a, unsigned char b, unsigned char c, unsigned char d)
{
    Write_Command(0x91);            // Define Look Up Table of Area Color
    Write_Command(a);           //   Define Bank 0 Pulse Width
    Write_Command(b);           //   Define Color A Pulse Width
    Write_Command(c);           //   Define Color B Pulse Width
    Write_Command(d);           //   Define Color C Pulse Width
}


void Set_Bank_Color()
{
    Write_Command(0x92);            // Define Area Color for Bank 1~16 (Page 0)
    Write_Command(0x00);            //   Define Bank 1~4 as Color A
    Write_Command(0xEA);            //   Define Bank 5~7 as Color C
    Write_Command(0xAF);            //   Define Bank 8~10 as Color D
    Write_Command(0x56);            //   Define Bank 11~13 as Color C
                        //   Define Bank 12~16 as Color B

    Write_Command(0x93);            // Define Area Color for Bank 17~32 (Page 1)
    Write_Command(0x00);            //   Define Bank 17~20 as Color A
    Write_Command(0xEA);            //   Define Bank 21~23 as Color C
    Write_Command(0xAF);            //   Define Bank 24~26 as Color D
    Write_Command(0x56);            //   Define Bank 27~29 as Color C
                        //   Define Bank 30~32 as Color B
}


//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  Initialization
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void OLED_Init()
{
    unsigned char i;
    unsigned char hello_world[] = {41,38,45,45,48,97,56,48,51,45,37,0};
    IOWR(RST_BASE, 0, 0);//复位
    for(i=0;i<200;i++)
    {
        uDelay(200);
    }
    IOWR(RST_BASE, 0, 1);//取消复位
    Set_Display_On_Off(0x00);       // Display Off (0x00/0x01)
    Set_Display_Clock(0xA0);        // Set Clock as 80 Frames/Sec
    Set_Multiplex_Ratio(0x3F);      // 1/64 Duty (0x0F~0x3F)
    Set_Display_Offset(0x00);       // Shift Mapping RAM Counter (0x00~0x3F)
    Set_Start_Line(0x00);           // Set Mapping RAM Display Start Line (0x00~0x3F)
    Set_Master_Config(0x00);        // Disable Embedded DC/DC Converter (0x00/0x01)
    Set_Area_Color(0x05);           // Set Monochrome & Low Power Save Mode
    Set_Addressing_Mode(0x02);      // Set Page Addressing Mode (0x00/0x01/0x02)
    Set_Segment_Remap(0x01);        // Set SEG/Column Mapping (0x00/0x01)
    Set_Common_Remap(0x08);         // Set COM/Row Scan Direction (0x00/0x08)
    Set_Common_Config(0x10);        // Set Alternative Configuration (0x00/0x10)
    Set_LUT(0x3F,0x3F,0x3F,0x3F);       // Define All Banks Pulse Width as 64 Clocks
    Set_Contrast_Control(Brightness);   // Set SEG Output Current
    Set_Area_Brightness(Brightness);    // Set Brightness for Area Color Banks
    Set_Precharge_Period(0xD2);     // Set Pre-Charge as 13 Clocks & Discharge as 2 Clock
    Set_VCOMH(0x34);            // Set VCOM Deselect Level
    Set_Entire_Display(0x00);       // Disable Entire Display On (0x00/0x01)
    Set_Inverse_Display(0x00);      // Disable Inverse Display On (0x00/0x01)

    Fill_RAM(0x00);             // Clear Screen

    Set_Display_On_Off(0x01);       // Display On (0x00/0x01)
    Show_String(1,hello_world,3,35);
}

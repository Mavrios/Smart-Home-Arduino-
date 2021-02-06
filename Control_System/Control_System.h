#ifndef CONTROL_SYSTEM_H
#define CONTROL_SYSTEM_H

            /* TYPE DEFINE */
    /*u -> UNSIGNED and '8' -> 8 bit */
    /*u -> UNSIGNED and '16' -> 16 bit */
typedef unsigned char       u8;
typedef unsigned short int u16;
    /*Macros TO SET AND CLR AND GET BITS*/
#define SET_BIT(BYTE,No_Bit)  BYTE |=(1<<No_Bit)
#define CLR_BIT(BYTE,No_Bit)  BYTE &=~(1<<No_Bit)
#define GET_BIT(BYTE,Bit_NO) ((BYTE>>Bit_NO)&(0x01))


#define FALSE     0
#define TRUE      1


    /*RELAY */
#define RELAY_PD  5          //RELAY PORT BIT_NO   (PD -> PORTD)

      /*LDR*/
#define LDR         A0      //LDR PIN
 /*SETTING LDR RANGE*/
#define LDR_OFF     400
#define LDR_ON      600

 /*TEMPREATURE*/
#define TEMP        A1      //TEMPRATURE SENSOR PIN
 /*SETTING TEMP RANGE*/
#define TEMP_MIN    15      
#define TEMP_MID    25
#define TEMP_UPMID  35
#define TEMP_MAX    45

#define FAN         9      //FAN PIN
#define FAN_PB      1      //FAN PORT BIT_NO   (PB -> PORTB)
 /*FAN SPEED RANGE*/  
#define FAN_SPEED_0 0
#define FAN_SPEED_1 85 
#define FAN_SPEED_2 170
#define FAN_SPEED_3 255

#define ENCODER      2   //ENCODER PIN

#define Buzzer_PD   4    //BUZZER PORT BIT_NO   (PD -> PORTD)

#define ShiftReg_SHIFT_PD  6      //SHIFT PORT BIT_NO   (PD -> PORTD)
#define ShiftReg_DATA_PD   7      //DATA PORT BIT_NO   (PD -> PORTD)
#define ShiftReg_STORE_PB  0      //STORE PORT BIT_NO   (PB -> PORTB)

#define EIGHT_BITS            8   //FOR LOOP

#define SevenSegment_D1_PB    2      //D1 PORT BIT_NO   (PB -> PORTB)
#define SevenSegment_D2_PB    3      //D2 PORT BIT_NO   (PB -> PORTB)
#define SevenSegment_D3_PB    4      //D3 PORT BIT_NO   (PB -> PORTB)
#define SevenSegment_D4_PB    5      //D4 PORT BIT_NO   (PB -> PORTB)


#define ONE_SECOND          1000     //ONE SECOND IN ms

#define BUTTON_CLOSE_PD        3    //BUTTON PORT BIT_NO   (PD -> PORTD)


  /*FUNCTION PROTOTYPES*/  
void ShiftRegister_voidStore(void); //Function to store
void Encoder_voidInit(void);        //Function to Init Encoder with interrupt
void LCD_voidDraw(u8 u8_Num);       //FUNCTION TO DRAW IN 7-SEGMENT


  /*Definitions*/
bool bool_Start = FALSE;            //SET START FLAG FALSE (0)

long previousMillis = 0;            //TO CALCULATE 1 SECOND

volatile long u32_Encoder =0;       //ENCONDER COUNTER
u16 LDR_Sensor = 0;                 //LDR SENSOR READING
u16 TEMP_Sensor = 0;                //TEMPRATURE SENSOR READING
u16 RPM =0;                         //RPM OF FAN   
float Temprature =0;                //TEMPRATURE IN *C
u8  i=0;                            //LOOP ITERATOR

  /*7-SEGMENTS*/
u8 ShiftReg_7Seg[10]={0b11111100,0b01100000,0b11011010,0b11110010,0b01100110,0b10110110,0b10111110,0b11100000,0b11111110,0b11100110};
#endif

#ifndef SECURITY_SYSTEM_H
#define SECURITY_SYSTEM_H

    /* INCLUDING LIBERARY */
    #include <LiquidCrystal.h>
      /* TYPE DEFINE */
    /*u -> UNSIGNED and '8' -> 8 bit */
    /*u -> UNSIGNED and '16' -> 16 bit */
    typedef unsigned char u8;
    typedef unsigned short int  u16;

        /*Macros TO SET AND CLR AND GET BITS*/
    #define SET_BIT(BYTE,Bit_NO) (BYTE) |= (1<<(Bit_NO))
    #define CLR_BIT(BYTE,Bit_NO) (BYTE) &= ~(1<<(Bit_NO))
    #define GET_BIT(BYTE,Bit_NO) ((BYTE>>Bit_NO)&(0x01))


                      /*LCD INITS*/
    const u8 rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7; //Define LCD PINS
    LiquidCrystal lcd(rs, en, d4, d5, d6, d7);              //INIT LCD

        /*SERVO*/
    #define SERVO_PB  1          //SERVO PORT BIT_NO   (PB -> PORTB)
    #define TWENTY_MS 39999      //NUMBER OF COUNTS TO GET 20ms (50HZ) for TIMER1 
       
    #define CLEAR   0x00         //TO CLEAR TIMER REGISTERS
    #define NINTY_DEGREE  2999   //NUMBER OF COUNTS TO GET 1.5ms to GET (90 Degree)
    #define ZERO_DEGREE   1999   //NUMBER OF COUNTS TO GET 1ms   to GET (0  Degree)

      /* LED */
    #define LED_PB    0          //LED PORT BIT_NO   (PB -> PORTB)


  #define PASSWORD_LENGTH 17   /* PASSWORD IS 16 DIGITS AND 1 FOR NULL TERMILATOR*/
  #define TRUE 1
  #define FALSE 0

  #define PASSWORD_APPEAR   FALSE   //SET TRUE TO APPEAR PASSWORD AND FALSE TO DISAPPEAR PASSWORD

    /* s -> SIGNED , '8' -> 8 Bit */
  char s8_Password[PASSWORD_LENGTH]="151998"; //ARRAY TO SET PASSWORD (CHANGE IT TO CHANGE PASSWORD)
  char s8_EnterPassword[PASSWORD_LENGTH];     //ARRAY TO RECIEVE PASSWORD FROM USR
  /*FLAG VARIABLE*/
  bool bool_Close = FALSE ,bool_Password =FALSE;
  u8 counter =0;                             //Counter to check number of keypad input
  /*FUNCTION PROTOTYPES*/  
  void PASSWORD_CLEAR(u8 *ptr);             //FUCTION TO CLEAR ARRAY
  bool PASSWORD_CHECK(u8 *ptr1,u8 *ptr2);   //FUNCTION TO CHECK PASSWORD EQUAL THE MASTER PASSWORD
  void True_Password (void);                //FUCTION  TO APPLY IF THE ENTERED PASSWORD IS TRUE 
  void WRONG_Password(void);                 //FUNCTION TO APPLY IF THE ENTERED PASSWORD IS WRONG
  void HOME_CLOSING(void) ;                  //FUNCTION TO APPLY IF THE CLOSE BUTTON IS PRESSED
  void TIMER_voidInit(void);                 //FUNCTION TO INIT TIMER1 TO CONTROL SERVO 
  
  /*Definitions*/
  u8 i = 0 ;                                  //LOOP ITERATOR
  char KEY=0;                                 //Variable to save recieved Char from KEYPAD


    
      /* KEYPAD */
    #define ROWS  2                           //NUMBER OF ROWS
    #define COLS  16                          //NUMBER OF COLS
    /* KEYPAD PORTS CONNECTIONS */
    #define RAW01_PC  0                       //RAW PORT BIT_NO   (PC -> PORTC)
    #define RAW02_PC  1                       //RAW PORT BIT_NO   (PC -> PORTC)
    #define RAW03_PC  2                       //RAW PORT BIT_NO   (PC -> PORTC)
    #define RAW04_PC  3                       //RAW PORT BIT_NO   (PC -> PORTC)

    #define COL01_PB  2                       //COL PORT BIT_NO   (PB -> PORTB)
    #define COL02_PB  3                       //COL PORT BIT_NO   (PB -> PORTB)
    #define COL03_PB  4                       //COL PORT BIT_NO   (PB -> PORTB)
    /*KEYPAD NUMBER OF BUTTONS*/
    #define BUTTON  12                        //NUMBER OF KEYPAD BUTTONS
    /*KEYPAD Functions Prototype*/
    void KEYPAD_voidInit(void);       // FUNCTION TO INIT KEYPAD (ENABLE INTERNAL PULLUP RESISTOR AND SET COL AS OUTPUT)
    void KEYPAD_voidChar (void);     // FUNCTION TO SET 1 COL TO CHECK THE OTHERS ROWS IN (KEYPAD_voidCheckRAWS) FUNCTION
    u8 KEYPAD_GetChar(void);         // FUNCTION TO RETURN THE EQUIVLENT CHAR
    void KEYPAD_voidCheckRAWS(void); // FUNCTION TO CHECK RAWS

    /*KEYPAD ARRAY */
    u8 keys[BUTTON] = 
    {'1', '2', '3',
    '4', '5', '6',
    '7', '8', '9',
    '*', '0', '#'};
    /*KEYPAD DEFINATIONS*/
    u16 Keypad_u16KeypadVal = 0; //16 bit Variable to (every bit is equivlent for char in the array
#endif

#include "Security_System.h"

void setup() {
  Serial.begin(9600);                                         //START SERIAL FOR UART PROTOCOL
  TIMER_voidInit();                                           //INIT TIMER1 TO CONTROL SERVO MOTOR
  SET_BIT(DDRB,SERVO_PB);                                     //SET SERVO PIN AS OUTPUT
  SET_BIT(DDRB,LED_PB);                                       //SET LED AS OUTPUT
       /*INIT LCD*/
  lcd.begin(ROWS,COLS);                                       
  lcd.setCursor(4,0);
  lcd.print("MOMENTUM");                                     //PRINT MOMENTUM IN LCD
  lcd.setCursor(3,1);
  lcd.print("SMART HOME");                                  //PRINT SMART HOME IN SECOND COL IN LCD
  KEYPAD_voidInit();                                        //INIT KEYPAD FUNCTION
  delay(1000);                                              //DELAY 1s
  lcd.clear();                                              //CLEAR LCD
}

void loop() {
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //                                                      SECUIRTY SYSTEM                                                              //
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  if(!bool_Password)                                                    //CHECK IF PASSWORD DOESN'T ENTERED
   {
      lcd.setCursor(1, 0);
      lcd.print("Enter Password");                                     //PRINT ENTER PASSWORD IN LCD
      KEY = KEYPAD_GetChar();                                          //If any button pressed receive the Char in (KEY)
      if (KEY)                                                         //Check If Keypad Button Pressed
      {
          ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
          //                                                        ENTER PASSWORD                                                             //
          ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if(KEY != '#'){                                                //CHECK IF KEY DOESN'T EQUAL "#" (ENTER) THEN THE USER STILL ENTERING PASSWORD
          s8_EnterPassword[counter]=KEY;                               //SAVE THE ENTERED KEY IN ARRAY
          lcd.setCursor(counter, 1);                                   //MOVE LCD Cursor with counter
          #if PASSWORD_APPEAR                                          //IF YOU WANT TO APPEAR OR DISAPPEAR PASSWORD OPTION GO TO (Security_System.h)
          lcd.print(s8_EnterPassword[counter]);                        //IF OPTION APPEAR PASSWORD THEN PRINT THE ENTERED KEY
          #else
          lcd.print("*");                                              //IF OPTION DISAPPEAR PASSWORD THEN PRINT "*" 
          #endif
          counter++;                                                   //INCREMENT COUNTER TO MOVE CURSOR
        }
        else{
          if(PASSWORD_CHECK(s8_Password,s8_EnterPassword)){            //IF THE USR PRESSED "#" (ENTER KEY) THEN CHECK PASSWORD BY FUNCTION (PASSWORD_CHECK(,)) 
            True_Password();                                           //IF PASSWORD TRUE THEN APPLY FUNCTION (True_Password())
          }
          else{
            WRONG_Password();                                          //IF PASSWORD WRONG THEN APPLY FUNCTION (WRONG_Password())
          }
        }
     }
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //                                                        CLOSE SMART HOME                                                           //
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
  if(Serial.available()){                                             //CHECK IF THERE ANY Receive DATA FROM CONTROL ARDUINO 
    bool_Close=Serial.read();                                         //SAVE THE RECIEVED DATA IN CLOSE FLAG
  }
  if(bool_Close){                                                     //IF CLOSE FLAG == TRUE (RECIEVED 1 FROM CONTROL ARDUINO)
    HOME_CLOSING();                                                   //APPLY CLOSING FUNCTION (HOME_CLOSING())
  }
  
  while(KEYPAD_GetChar());                                            //TO AVOID CONTINOUS RECEVING DATA FROM KEYPAD
}





///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                      FUNCTIONS DEFINITIONS                                                        //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
void PASSWORD_CLEAR(u8 *ptr){
  for(i = 0 ; i< PASSWORD_LENGTH ; i++){
    ptr[i]=0;                               //CLEARING ALL ARRAY DATA
}
}


bool PASSWORD_CHECK(u8 *ptr1,u8 *ptr2){
  for(i=0;i<PASSWORD_LENGTH;i++){
    if(ptr1[i]!=ptr2[i]){               //CHECK IF ELEMENTS OF ARRAY NOT EQUAL
      return FALSE;                     // RETURNING FALSE (THE PASSWORD WRONG)
    }
 }
  return TRUE;                          //IF THE ARRAY EQUALS THEN RETURN TRUE (THE PASSWORD CORRECT)
}

void True_Password (void){
  lcd.clear();                         //CLEARING LCD DATA
  lcd.setCursor(2,0);                  //CHANGING CURSOR POSTION
  lcd.print("WELCOME HOME");           //PRINT WELCOME HOME IN LCD
  Serial.print(TRUE);                  //SEND SEGNIAL (1 BIT) TO CONTROL SYSTEM ARDUINO TO START
  OCR1A=NINTY_DEGREE;                  //START SERVO MOTOR IN 90 Degree
  SET_BIT(PORTB,LED_PB);               //LED ON 
  bool_Password = TRUE;                //SET PASSWORD FLAG TRUE TO AVOID ENTERING PASSWORD
  PASSWORD_CLEAR(s8_EnterPassword);    //CLEARING ARRAY DATA
  counter=0;                           //SET COUNTER 0
  delay(1000);                         //DELAY 1s
  lcd.clear();                         //CLEARING LCD DATA
  lcd.setCursor(4,0);                  //CHANGING CURSOR POSTION                   
  lcd.print("MOMENTUM");               //PRINT MOMENTUM IN LCD
  lcd.setCursor(2,1);                  //CHANGING CURSOR POSTION
  lcd.print("FINAL PROJECT");          //PRINT FINAL PROJECT IN LCD

  
}

void WRONG_Password(void){
 lcd.clear();                         //CLEARING LCD DATA
 lcd.setCursor(1,0);                  //CHANGING CURSOR POSTION
 lcd.print("WRONG PASSWORD");         //PRINT WRONG PASSWORD IN LCD
 delay(1000);                         //DELAY 1s
 PASSWORD_CLEAR(s8_EnterPassword);    //CLEARING ARRAY DATA
 counter=0;                           //SET COUNTER 0
 bool_Password = FALSE;                //SET PASSWORD FLAG FALSE TO RENTERING PASSWORD
}

void HOME_CLOSING(void){
    lcd.clear();                         //CLEARING LCD DATA
    lcd.setCursor(2,0);                  //CHANGING CURSOR POSTION
    lcd.print("CLOSING HOME");           //PRINT CLOSING HOME IN LCD
    OCR1A=ZERO_DEGREE;                   //START SERVO MOTOR IN 0 Degree
    CLR_BIT(PORTB,LED_PB);               //LED OFF
    delay(1000);                         //DELAY 1s
    bool_Password=FALSE;                 //SET PASSWORD FLAG FALSE TO RENTERING PASSWORD
    bool_Close=FALSE;                    //SET CLOSING FLAG FALSE TO AVOID ENTERING THIS FUNCTION AGAIN
}

void TIMER_voidInit(void){
  noInterrupts();                                             //DISABLE ALL INTERRUPTS
  TCCR1A=CLEAR;                                               //CLEAR REGISTER BITS
  TCCR1B=CLEAR;                                               //CLEAR REGISTER BITS
  /*ENABLE PWM FAST MODE */
  SET_BIT(TCCR1A,WGM11);                                      //SET WGM11 BIT IN TCCR1A      
  SET_BIT(TCCR1B,WGM12);                                      //SET WGM12 BIT IN TCCR1B   
  SET_BIT(TCCR1B,WGM13);                                      //SET WGM13 BIT IN TCCR1B   
  SET_BIT(TCCR1B,CS11);                                       //SET PRESCALER 8 
  SET_BIT(TCCR1A,COM1A1);                                     //USE NON-INVERTED MODE
  ICR1=TWENTY_MS;                                             //START COUNTING FOR 20ms (20ms/(1/(16000000/8)) = 40000 START COUNTING FROM ZERO SO 39999
  interrupts();                                               //RE ENABLE INTERRUPT

}











        /*KEYPAD*/
void KEYPAD_voidInit(void){
  /*Active PULLUP RESISTOR*/
  SET_BIT(PORTC,RAW01_PC);
  SET_BIT(PORTC,RAW02_PC);
  SET_BIT(PORTC,RAW03_PC);
  SET_BIT(PORTC,RAW04_PC);

  /*SETTING COL AS OUTPUT*/
  SET_BIT(DDRB,COL01_PB);
  SET_BIT(DDRB,COL02_PB);
  SET_BIT(DDRB,COL03_PB);
}
void KEYPAD_voidChar (void){
  
    Keypad_u16KeypadVal = 0;
    
  /*SET COL01 HIGH AND CHECK RAWS*/
  CLR_BIT(PORTB,COL01_PB);                  //SET COL01 HIGH
  SET_BIT(PORTB,COL02_PB);                  //SET COL01 LOW
  SET_BIT(PORTB,COL03_PB);                  //SET COL01 LOW 
  KEYPAD_voidCheckRAWS(0);
  
  /*SET COL02 HIGH AND CHECK RAWS*/
  
  SET_BIT(PORTB,COL01_PB);                    //SET COL01 LOW                 
  CLR_BIT(PORTB,COL02_PB);                    //SET COL01 HIGH
  SET_BIT(PORTB,COL03_PB);                    //SET COL01 LOW 
  KEYPAD_voidCheckRAWS(1);

  /*SET COL03 HIGH AND CHECK RAWS*/

  SET_BIT(PORTB,COL01_PB);                   //SET COL01 LOW                   
  SET_BIT(PORTB,COL02_PB);                   //SET COL01 LOW 
  CLR_BIT(PORTB,COL03_PB);                   //SET COL01 HIGH 
  KEYPAD_voidCheckRAWS(2);
  
  return Keypad_u16KeypadVal;
}



unsigned char KEYPAD_GetChar(void){
KEYPAD_voidChar();
if(Keypad_u16KeypadVal != 0){
for(i=0;i<BUTTON;i++){
  if(GET_BIT(Keypad_u16KeypadVal,i)==1){
    return keys[i];
  }
}
}
  else{
    return 0;
  }
  
}



void KEYPAD_voidCheckRAWS(unsigned char Cpy_Num){
    if(GET_BIT(PINC,RAW01_PC)== 0){
      SET_BIT(Keypad_u16KeypadVal,Cpy_Num);
    }
    if(GET_BIT(PINC,RAW02_PC)== 0){
      SET_BIT(Keypad_u16KeypadVal,Cpy_Num+3);
    }
    if(GET_BIT(PINC,RAW03_PC)==0){
      SET_BIT(Keypad_u16KeypadVal,Cpy_Num+6);
    }
    if(GET_BIT(PINC,RAW04_PC)==0){
      SET_BIT(Keypad_u16KeypadVal,Cpy_Num+9);
    }
}

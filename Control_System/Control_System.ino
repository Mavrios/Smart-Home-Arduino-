#include "Control_System.h"


void setup() {
  Serial.begin(9600);                                         //START SERIAL FOR UART PROTOCOL
  SET_BIT(DDRD,RELAY_PD);                                     //SET RELAY PIN AS OUTPUT
  SET_BIT(DDRD,Buzzer_PD);                                    //SET BUZZER PIN AS OUTPUT
  SET_BIT(DDRB,FAN_PB);                                       //SET FAN PIN AS OUTPUT
  SET_BIT(DDRD,ShiftReg_SHIFT_PD);                            //SET SHIFT PIN AS OUTPUT
  SET_BIT(DDRD,ShiftReg_DATA_PD);                             //SET DATA PIN AS OUTPUT
  SET_BIT(DDRB,ShiftReg_STORE_PB);                            //SET STORE PIN AS OUTPUT
  SET_BIT(DDRB,SevenSegment_D1_PB);                           //SET SEGMENT_1 PIN AS OUTPUT
  SET_BIT(DDRB,SevenSegment_D2_PB);                           //SET SEGMENT_2 PIN AS OUTPUT
  SET_BIT(DDRB,SevenSegment_D3_PB);                           //SET SEGMENT_3 PIN AS OUTPUT
  SET_BIT(DDRB,SevenSegment_D4_PB);                           //SET SEGMENT_4 PIN AS OUTPUT

  SET_BIT(PORTD,ENCODER);                                     //ENABLE PULLUP RESISTOR FOR ENCODER
  SET_BIT(PORTD,BUTTON_CLOSE_PD);                             //ENABLE PULLUP RESISTOR FOR BUTTON
  Encoder_voidInit();                                         //INIT ENCODER 
  previousMillis = millis();                                  //COUNTING MILLIS

}

void loop() {
  if(Serial.available()){                                     //CHECK IF RECIEVED DATA FROM SYCURITY ARDUINO
    bool_Start=Serial.read();                                 //SAVE RECIEVED DATA IN START FLAG
  }
  if(bool_Start){
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //                                                    LIGHT CONTROL SYSTEM                                                           //
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    LDR_Sensor=analogRead(LDR);                               //SAVE LDR READING
    if(LDR_Sensor>LDR_ON){                                    //CHECK IF LDR>400 and LDR<600
      CLR_BIT(PORTD,RELAY_PD);                                //SET RELAY PIN LOW (CLOSE LIGHTS)
    }
    else if(LDR_Sensor<LDR_OFF){
      SET_BIT(PORTD,RELAY_PD);                                //SET RELAY PIN HIGH (OPEN LIGHTS)
    }

 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //                                               TEMPRATURE CONTROL SYSTEM                                                           //
 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    TEMP_Sensor=analogRead(TEMP);                             //SAVE TEMP READING
    Temprature=(float)TEMP_Sensor*(5.0/1023.0)*100;           //Calculate TEMP IN *C
    
    if(Temprature<TEMP_MIN){                                  //CHECK IF TEMP<15
      CLR_BIT(PORTD,Buzzer_PD);                               //SET BUZZER LOW
      analogWrite(FAN,FAN_SPEED_0);                           //TURN OFF FAN
    }
    if(Temprature>TEMP_MIN&&Temprature<TEMP_MID){             //CHECK IF TEMP>15 and TEMP<25
      CLR_BIT(PORTD,Buzzer_PD);                               //SET BUZZER LOW
      analogWrite(FAN,FAN_SPEED_1);                           //START THE FAN IN FIRST SPEED
    }
    if(Temprature>TEMP_MID&&Temprature<TEMP_UPMID){           //CHECK IF TEMP>25 and TEMP<35
      CLR_BIT(PORTD,Buzzer_PD);                               //SET BUZZER LOW
      analogWrite(FAN,FAN_SPEED_2);                           //START THE FAN IN SECOND SPEED
    }
    if(Temprature>TEMP_UPMID&&Temprature<TEMP_MAX){           //CHECK IF TEMP>35 and TEMP<45
      CLR_BIT(PORTD,Buzzer_PD);                               //SET BUZZER LOW
      analogWrite(FAN,FAN_SPEED_3);                           //START THE FAN IN SECOND SPEED
    }
    if(Temprature>TEMP_MAX){                                  //CHECK IF TEMP>45
      SET_BIT(PORTD,Buzzer_PD);                               //SET BUZZER HIGH
    }

 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //                                            RPM & 7-SEGEMENT CONTROL SYSTEM                                                        //
 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   if (millis() - previousMillis > ONE_SECOND) {              //CALCULATE 1 SECOND
    RPM=(float)((60* u32_Encoder)/24);                        //CALCULATE RPM (60 SECOND * NO_PULSES) / (24 ONE REV)
    u32_Encoder=0;                                            //SET ENCODER COUNTER = 0
    previousMillis=millis();                                  //RESET TIMER TO RECALCULTE 1 SECOND
   }
  /* PRINT IN D4-SEVEN SEGMENT */ 
  SET_BIT(PORTB,SevenSegment_D1_PB);                          //SETTING D1 HIGH
  SET_BIT(PORTB,SevenSegment_D2_PB);                          //SETTING D2 HIGH
  SET_BIT(PORTB,SevenSegment_D3_PB);                          //SETTING D3 HIGH
  CLR_BIT(PORTB,SevenSegment_D4_PB);                          //SETTING D4 LOW
  LCD_voidDraw(RPM%10);                                       //DRAW FRIST NUMBER IN RPM i.e (32'1')
  delay(1);
  
  /* PRINT IN D3-SEVEN SEGMENT */ 
  SET_BIT(PORTB,SevenSegment_D1_PB);                          //SETTING D1 HIGH
  SET_BIT(PORTB,SevenSegment_D2_PB);                          //SETTING D2 HIGH
  SET_BIT(PORTB,SevenSegment_D4_PB);                          //SETTING D4 HIGH
  CLR_BIT(PORTB,SevenSegment_D3_PB);                          //SETTING D3 LOW
  LCD_voidDraw((RPM)%100 / 10);                               //DRAW SECOND NUMBER IN RPM i.e (3'2'1)
  delay(1);
  
  /* PRINT IN D2-SEVEN SEGMENT */ 
  SET_BIT(PORTB,SevenSegment_D1_PB);                          //SETTING D1 HIGH
  SET_BIT(PORTB,SevenSegment_D3_PB);                          //SETTING D3 HIGH
  SET_BIT(PORTB,SevenSegment_D4_PB);                          //SETTING D4 HIGH
  CLR_BIT(PORTB,SevenSegment_D2_PB);                          //SETTING D2 LOW
  LCD_voidDraw(RPM / 100);                                    //DRAW THIRD NUMBER IN RPM i.e ('3'21)
  delay(1);
  
  /* PRINT IN D1-SEVEN SEGMENT */ 
  SET_BIT(PORTB,SevenSegment_D2_PB);                          //SETTING D2 HIGH
  SET_BIT(PORTB,SevenSegment_D3_PB);                          //SETTING D3 HIGH
  SET_BIT(PORTB,SevenSegment_D4_PB);                          //SETTING D4 HIGH
  CLR_BIT(PORTB,SevenSegment_D1_PB);                          //SETTING D1 LOW
  LCD_voidDraw(0);                                            //DRAW 0 IN FORTH NUMBER (MAXIMUM DOESN'T EXCIT 1000
  delay(1);
  

 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //                                                       CLOSE CONTROL SYSTEM                                                        //
 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  if(!GET_BIT(PIND,BUTTON_CLOSE_PD)){  /*CHECK IF CLOSING BUTTON PRESSED*/
    /*TURN OFF ALL*/
    SET_BIT(PORTB,SevenSegment_D1_PB);
    SET_BIT(PORTB,SevenSegment_D2_PB);
    SET_BIT(PORTB,SevenSegment_D3_PB);
    SET_BIT(PORTB,SevenSegment_D4_PB);
    analogWrite(FAN,FAN_SPEED_0);
    
    CLR_BIT(PORTD,RELAY_PD);
    Serial.print(TRUE);                                      //SEND BIT TO SECUIRTY CONTROL ARDUINO TO CLOSE  
    bool_Start=FALSE;                                        //SET START FLAG FALSE
  }

 
    }
}

 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //                                                       FUNCTIONS                                                                   //
 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Encoder_voidInit(void){
    attachInterrupt(digitalPinToInterrupt(ENCODER), ISR_Encoder, RISING);                 //START INTERRUPT IN RISING EDGE FOR ENCODER
}

void ISR_Encoder(void){
    u32_Encoder++;                                                                        //INCREMENT ENCODER CONTER
}

void ShiftRegister_voidStore(void){
  SET_BIT(PORTB,ShiftReg_STORE_PB);            //SET BIT 0 IN PORTB 1 (PIN 8 HIGH)
  delayMicroseconds(10);                       // DELAY 10us
  CLR_BIT(PORTB,ShiftReg_STORE_PB);            // CLR BIT 0 IN PORTB 1 (PIN 8 LOW)
  delayMicroseconds(10);                       // DELAY 10us
}

void LCD_voidDraw(u8 u8_Num){
         for(i=0 ;i<EIGHT_BITS;i++){
         shiftOut(ShiftReg_DATA_PD, ShiftReg_SHIFT_PD, LSBFIRST,ShiftReg_7Seg[u8_Num]); //PRINT ON 7-SEGEMENT RECIVED BITS
         ShiftRegister_voidStore();                                                     //STORING
    }
}

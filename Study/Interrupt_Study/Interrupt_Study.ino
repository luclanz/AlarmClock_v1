#include "Arduino.h"

// ROTARY ENCODER
  #define ROT_CLK 6
  #define ROT_DT 5


    struct alarmClock_struct {

      //Rotary Encoder
        uint8_t rotaryCounter :7;             //Value of the knob, MAX: 99, 7bits
        uint8_t rotaryCurrentStateCLK :1;     //Value of CLK output: boolean
        uint8_t rotaryLastStateCLK :1;  

        uint8_t rotaryOverflow[3] = {23, 59, 99};
        uint8_t rotaryOverflowIndex :2;
        
        uint8_t rotaryInitCounter :1;  
    };
    
    typedef struct alarmClock_struct alarmClock_struct;
    alarmClock_struct alarmData;

void setup ()
{

      //Serial port -> Open
      Serial.begin(9600);
      while (!Serial) {}
      
      alarmData.rotaryCounter = 0;
      alarmData.rotaryOverflowIndex = 0;
      alarmData.rotaryInitCounter = 0;
      alarmData.rotaryOverflowIndex = 0; 

      rotarySetupRoutine();

      enableRotaryISR();
}

void loop ()
{
  // loop doing nothing 
} 

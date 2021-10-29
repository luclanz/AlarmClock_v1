/*

  Functions:

    - rotarySetupRoutine()                          * check when managing the interrupt
    - rotaryPolling()
    - rotaryUpdateTime()                            * those next three function may be called less frequently
    - rotaryUpdateAlarm()
    - rotaryUpdateTimer()
    - enableRotaryISR() / disableRotaryISR()

  TODO:
    - remember to remove the print line in the ISR, too much time to execute!

   !- change |= into &= and flip every bit in disableRotaryISR()!!!

*/

void rotarySetupRoutine(){
  
  // Input pin setup
    pinMode(ROT_CLK,INPUT);
    pinMode(ROT_DT,INPUT);
  
  // Read the initial state of CLK
    alarmData.rotaryLastStateCLK = digitalRead(ROT_CLK);
  
  // Interrupt setup
    PCMSK2 |= B01100000;
}


void enableRotaryISR() {
  PCICR |= B00000100;   // flip this 1 to activate / deactivate the interrupt
}

void disableRotaryISR() {
  PCICR &= B11111011;      //<--- TEST THIS!
  //PCICR |= B00000000;   // flip this 1 to activate / deactivate the interrupt
}

//ISR
ISR (PCINT2_vect){
  
  //Read the current state of CLK
    alarmData.rotaryCurrentStateCLK = digitalRead(ROT_CLK);

  // If last and current state of CLK are different, then pulse occurred (react to only 1 state change to avoid double count)
    if (alarmData.rotaryCurrentStateCLK != alarmData.rotaryLastStateCLK  && alarmData.rotaryCurrentStateCLK == 1){


    //here I'm also considering the overflow depending on the rotaryOverflowIndex
      if (digitalRead(ROT_DT) != alarmData.rotaryCurrentStateCLK) {
        
        //CCW direction!
        //I'm decreasing the value, if it is 0 I'll pick the overflow number (i.e: 0 - 1 = 59 w/ minutes or seconds)
          if (alarmData.rotaryCounter == 0) {
            alarmData.rotaryCounter = alarmData.rotaryOverflow[alarmData.rotaryOverflowIndex];
          } else {
            alarmData.rotaryCounter --;
          }
        
      } else {
        
        //CW diraction!
        //I'm increasing the value, if it is 59 I'll go to 0 when considering minutes or seconds
          if (alarmData.rotaryCounter == alarmData.rotaryOverflow[alarmData.rotaryOverflowIndex]) {
            alarmData.rotaryCounter = 0;
          } else {
            alarmData.rotaryCounter ++;
          }
      }

      //print some info  
        //Serial.println(alarmData.rotaryCounter);
  }

  // Remember last CLK state
    alarmData.rotaryLastStateCLK = alarmData.rotaryCurrentStateCLK;
  
}

void rotaryUpdateTime() {
  if (alarmData.twoStepSet == 0) {
    
    //limit at h23
      alarmData.rotaryOverflowIndex = 0;
    //update hours
      alarmData.hoursOffset = alarmData.rotaryCounter;
    return;
    
  } else {
    
    //limit at m59
      alarmData.rotaryOverflowIndex = 1;
    //update minutes
      alarmData.minutesOffset = alarmData.rotaryCounter;
      
  }
}

void rotaryUpdateAlarm() {
  
  if (alarmData.twoStepSet == 0) {
    
    //limit at h23
      alarmData.rotaryOverflowIndex = 0;
    //update hours
      alarmData.alarmHours = alarmData.rotaryCounter;
    return;
    
  } else {
    
    //limit at m59
      alarmData.rotaryOverflowIndex = 1;  
    //update minutes
      alarmData.alarmMinutes = alarmData.rotaryCounter;
      
  }
}

void rotaryUpdateTimer() {
  
  if (alarmData.twoStepSet == 0) {
    
    //limit at m99
      alarmData.rotaryOverflowIndex = 2;
    //update hours
      alarmData.timerMinutes = alarmData.rotaryCounter;
    return;
    
  } else {
    
    //limit at s59
      alarmData.rotaryOverflowIndex = 1;  
    //update minutes
      alarmData.timerSeconds = alarmData.rotaryCounter;
      
  }
}

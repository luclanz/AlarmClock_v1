/*

  Functions:

    - rotarySetupRoutine()                          * check when managing the interrupt
    - rotaryPolling()
    - rotaryUpdateTime()
    - rotaryUpdateAlarm()
    - rotaryUpdateTimer()

*/

void rotarySetupRoutine(){
  
  // Input pin setup
    pinMode(ROT_CLK,INPUT);
    pinMode(ROT_DT,INPUT);
  
  // Read the initial state of CLK
    alarmData.rotaryLastStateCLK = digitalRead(ROT_CLK);
  
  // Interrupt setup
    attachInterrupt(digitalPinToInterrupt(ROT_CLK), rotaryPolling, CHANGE);
        //detachInterrupt(digitalPinToInterrupt(ROT_CLK));                                    <-- MAYBE IT CAN GET HANDY IN THE FUTURE
        
    attachInterrupt(digitalPinToInterrupt(ROT_DT), rotaryPolling, CHANGE);
        //detachInterrupt(digitalPinToInterrupt(ROT_DT));
}


void rotaryPolling(){
  // Read the current state of CLK
  alarmData.rotaryCurrentStateCLK = digitalRead(ROT_CLK);

  // If last and current state of CLK are different, then pulse occurred
  // React to only 1 state change to avoid double count
  if (alarmData.rotaryCurrentStateCLK != alarmData.rotaryLastStateCLK  && alarmData.rotaryCurrentStateCLK == 1){

    // If the DT state is different than the CLK state then
    // the encoder is rotating CCW so decrement
    if (digitalRead(ROT_DT) != alarmData.rotaryCurrentStateCLK) {
      if (alarmData.rotaryCounter == 0) {
        alarmData.rotaryCounter = alarmData.rotaryOverflow[alarmData.rotaryOverflowIndex];
      } else {
        alarmData.rotaryCounter --;
      }
      alarmData.rotaryCurrentDir = F("CCW");
    } else {
      // Encoder is rotating CW so increment
      if (alarmData.rotaryCounter == alarmData.rotaryOverflow[alarmData.rotaryOverflowIndex]) {
        alarmData.rotaryCounter = 0;
      } else {
        alarmData.rotaryCounter ++;
      }
      alarmData.rotaryCurrentDir = F("CW");
    }

    Serial.print(F("Direction: "));
    Serial.print(alarmData.rotaryCurrentDir);
    Serial.print(F(" | Counter: "));
    Serial.println(alarmData.rotaryCounter);
  }

  // Remember last CLK state
  alarmData.rotaryLastStateCLK = alarmData.rotaryCurrentStateCLK;
  
  // Put in a slight delay to help debounce the reading
  //delay(1);
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

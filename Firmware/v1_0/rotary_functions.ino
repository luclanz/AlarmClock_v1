// this file will contain every function used to control the rotary encoder
// everything that starts with rotaryEtc..()

void rotarySetupRoutine(){
  // Set encoder pins as inputs
  pinMode(ROT_CLK,INPUT);
  pinMode(ROT_DT,INPUT);
  // Read the initial state of CLK
  rotaryLastStateCLK = digitalRead(ROT_CLK);
  // activate interrupt
  attachInterrupt(digitalPinToInterrupt(ROT_CLK), rotaryPolling, CHANGE);
  //detachInterrupt(digitalPinToInterrupt(ROT_CLK));
  attachInterrupt(digitalPinToInterrupt(ROT_DT), rotaryPolling, CHANGE);
  //detachInterrupt(digitalPinToInterrupt(ROT_DT));
  
}
void rotaryPolling(){
  // Read the current state of CLK
  rotaryCurrentStateCLK = digitalRead(ROT_CLK);

  // If last and current state of CLK are different, then pulse occurred
  // React to only 1 state change to avoid double count
  if (rotaryCurrentStateCLK != rotaryLastStateCLK  && rotaryCurrentStateCLK == 1){

    // If the DT state is different than the CLK state then
    // the encoder is rotating CCW so decrement
    if (digitalRead(ROT_DT) != rotaryCurrentStateCLK) {
      if (rotaryCounter == 0) {
        rotaryCounter = rotaryOverflow[rotaryOverflowIndex];
      } else {
        rotaryCounter --;
      }
      rotaryCurrentDir ="CCW";
    } else {
      // Encoder is rotating CW so increment
      if (rotaryCounter == rotaryOverflow[rotaryOverflowIndex]) {
        rotaryCounter = 0;
      } else {
        rotaryCounter ++;
      }
      rotaryCurrentDir ="CW";
    }

    Serial.print("Direction: ");
    Serial.print(rotaryCurrentDir);
    Serial.print(" | Counter: ");
    Serial.println(rotaryCounter);
  }

  // Remember last CLK state
  rotaryLastStateCLK = rotaryCurrentStateCLK;
  
  // Put in a slight delay to help debounce the reading
  //delay(1);
}

void rotaryUpdateTime() {
  if (alarmClockData.twoStepSet == 0) {
    
    //limit at h23
    rotaryOverflowIndex = 0;
    //update hours
    alarmClockData.hoursOffset = rotaryCounter;
    return;
    
  } else {
    //limit at m59
    rotaryOverflowIndex = 1;  
    //update minutes
    alarmClockData.minutesOffset = rotaryCounter;
  }
}

void rotaryUpdateAlarm() {
  
  if (alarmClockData.twoStepSet == 0) {
    
    //limit at h23
    rotaryOverflowIndex = 0;
    //update hours
    alarmClockData.alarmHours = rotaryCounter;
    return;
    
  } else {
    //limit at m59
    rotaryOverflowIndex = 1;  
    //update minutes
    alarmClockData.alarmMinutes = rotaryCounter;
  }
}

void rotaryUpdateTimer() {
  
  if (alarmClockData.twoStepSet == 0) {
    
    //limit at m99
    rotaryOverflowIndex = 2;
    //update hours
    alarmClockData.timerMinutes = rotaryCounter;
    return;
    
  } else {
    //limit at s59
    rotaryOverflowIndex = 1;  
    //update minutes
    alarmClockData.timerSeconds = rotaryCounter;
  }
}

/*
 
  Functions:
  
    - goFromX()
    - printState()
  
*/

void goFromHome(){   

  if (upButton.buttonClicked) {
    alarmData.stateFSM = FSM_ALARM;
    return;
  }
  
  if (downButton.buttonHolded) {
    alarmData.stateFSM = FSM_SETTIME;
    return;
  }
 
}

void goFromSetTime(){

  //reset any change to the time, back to the ds3231 value
    if (downButton.buttonHolded) {
      alarmData.stateFSM = FSM_HOME;
      alarmData.hoursOffset = 0;
      alarmData.minutesOffset = 0;
    }
  
  if (topButton.buttonClicked) {
    alarmData.stateFSM = FSM_HOME;
    return;  
  };
  
  if (downButton.buttonClicked) {
    alarmData.stateFSM = FSM_HOME;  
    return;
  }
  
  if (upButton.buttonClicked) {

    alarmData.twoStepSet = alarmData.twoStepSet + 1;

    if (alarmData.twoStepSet == 2) alarmData.stateFSM = FSM_HOME;
    
    return;  
  };

  if (downButton.buttonHolded) {
      //reset any change to the time, back to the ds3231 value
    alarmData.stateFSM = FSM_HOME;
    alarmData.hoursOffset = 0;
    alarmData.minutesOffset = 0;
  }
  
}

void goFromAlarm(){

  //toggle alarm
  if (downButton.buttonClicked) {
    alarmData.alarmOnOff = !alarmData.alarmOnOff;
    lcd.clear();
  }

  if (topButton.buttonClicked) {
    alarmData.stateFSM = FSM_HOME;
    return;
  }
  
  if (upButton.buttonClicked) {
    alarmData.stateFSM = FSM_TIMER;
    return;
  }
  
  if (downButton.buttonHolded) {
    alarmData.stateFSM = FSM_SETALARM;
    return;
  }
  
}

void goFromSetAlarm(){
  
  if (topButton.buttonClicked) {
    alarmData.stateFSM = FSM_HOME;
    return;
  }

  if (downButton.buttonClicked) {
    alarmData.stateFSM = FSM_ALARM;
    return;
  }
  
  if (upButton.buttonClicked) {

    alarmData.twoStepSet = alarmData.twoStepSet + 1;

    if (alarmData.twoStepSet == 2) alarmData.stateFSM = FSM_ALARM;
    
    return;  
  };
  
}

void goFromTimer(){

  //toggle timer
  if (downButton.buttonClicked) {
    alarmData.timerOnOff = !alarmData.timerOnOff;
    lcd.clear();
  }
  
  if (topButton.buttonClicked || upButton.buttonClicked) {
    alarmData.stateFSM = FSM_HOME;
    return;
  }
  
  if (downButton.buttonHolded) {
    alarmData.stateFSM = FSM_SETTIMER;
    return;
  }
  
}

void goFromSetTimer(){
  
  if (topButton.buttonClicked) {
    alarmData.stateFSM = FSM_HOME;
    return;
  }

  if (downButton.buttonClicked) {
    alarmData.stateFSM = FSM_TIMER;  
    return;
  }

  if (upButton.buttonClicked) {

    alarmData.twoStepSet = alarmData.twoStepSet + 1;

    if (alarmData.twoStepSet == 2) alarmData.stateFSM = FSM_ALARM;
    
    return;  
  };
  
}


void printState(int state) {
  switch(state) {
    case 0:
      Serial.println(F("IDLE"));
      break;
      
    case 1:
      Serial.println(F("HOME"));
      break;
      
    case 2:
      Serial.println(F("SET TIME"));
      break;
      
    case 3: 
      Serial.println(F("ALARM"));
      break;
      
    case 4:
      Serial.println(F("SET ALARM"));
      break;
      
    case 5:
      Serial.println(F("TIMER"));
      break;
      
    case 6: 
      Serial.println(F("SET TIMER"));
      break; 
  }      
}

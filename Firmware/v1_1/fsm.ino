/*
 
  Functions:
  
    - goFromX()
    - printState()
    - updateOffset()
  
*/

void goFromHome(){   
  
  if (downButton.buttonHolded) {
    alarmData.stateFSM = FSM_SETTIME;
    return;
  }

  if (upButton.buttonClicked) {
    alarmData.stateFSM = FSM_ALARM;
    return;
  }
 
}

void goFromSetTime(){

  //reset any change to the time, back to the ds3231 value
    if (downButton.buttonHolded) {
      alarmData.stateFSM = FSM_HOME;
      alarmData.hoursOffset = 0;
      alarmData.minutesOffset = 0;
      alarmData.twoStepSet = 0;
    }
  
  if (topButton.buttonClicked || downButton.buttonClicked) {
    
    alarmData.twoStepSet = 0;
    updateOffset();
    
    alarmData.stateFSM = FSM_HOME;
    return;  
  };
  
  
  if (upButton.buttonClicked) {
    if (alarmData.twoStepSet == 1) {
      
      updateOffset();
      
      alarmData.stateFSM = FSM_HOME;
      alarmData.twoStepSet = 0;
      return;  
    };
    alarmData.rotaryInitCounter = true;
    alarmData.twoStepSet += 1;
    alarmData.refresh = 1;
  };
  
}

void goFromAlarm(){

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

  //reset any change to the time, back to the ds3231 value
    if (downButton.buttonHolded) {
      alarmData.stateFSM = FSM_ALARM;
      alarmData.alarmHours = 7;
      alarmData.alarmMinutes = 0;
      alarmData.alarmOnOff = 0;
      alarmData.twoStepSet = 0;
    }

  if (topButton.buttonClicked) {
    
    alarmData.stateFSM = FSM_HOME;
    alarmData.twoStepSet = 0;
    return;
  }

  if (downButton.buttonClicked) {
    
    alarmData.stateFSM = FSM_ALARM;
    alarmData.twoStepSet = 0;
    return;
  }
  
  if (upButton.buttonClicked) {

    if (alarmData.twoStepSet == 1) {
      alarmData.stateFSM = FSM_ALARM;
      alarmData.twoStepSet = 0;
      return;  
    }
    
    alarmData.rotaryInitCounter = true;
    alarmData.twoStepSet += 1; 
    alarmData.refresh = 1;
  };
  
}

void goFromTimer(){
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

  //reset any change to the time, back to the ds3231 value
    if (downButton.buttonHolded) {
      alarmData.stateFSM = FSM_TIMER;
      alarmData.timerMinutes = 10;
      alarmData.timerSeconds = 0;
      alarmData.timerOnOff = 0;
      alarmData.twoStepSet = 0;
    }
  
  if (topButton.buttonClicked) {
    alarmData.stateFSM = FSM_HOME;
    alarmData.twoStepSet = 0;
    return;
  }

  if (downButton.buttonClicked) {
    alarmData.stateFSM = FSM_TIMER;  
    alarmData.twoStepSet = 0;
    return;
  }

  if (upButton.buttonClicked) {

    if (alarmData.twoStepSet == 1) {
      alarmData.stateFSM = FSM_TIMER;
      alarmData.twoStepSet = 0;
      return;  
    };
    alarmData.rotaryInitCounter = true;
    alarmData.twoStepSet += 1; 
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

    case 7:
      Serial.println(F("RING"));
  }      
}

void updateOffset() {

    // Serial.println(F("UPDATED OFFSET"));

    alarmData.hoursOffset = alarmData.hoursOffset - rtc.now().hour();
    alarmData.minutesOffset = alarmData.minutesOffset - rtc.now().minute();


}

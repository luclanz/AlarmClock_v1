//every auxiliary functions for the fsm machine

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
  
  if (topButton.buttonClicked) {
    alarmData.stateFSM = FSM_HOME;
    return;  
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
  
  if (topButton.buttonClicked) {
    alarmData.stateFSM = FSM_HOME;
    return;
  }
  
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
  
  if (topButton.buttonClicked) {
    alarmData.stateFSM = FSM_HOME;
    return;
  }
  
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
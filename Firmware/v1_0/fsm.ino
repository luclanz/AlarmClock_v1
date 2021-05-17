// this file will contain the main fsm engine and the printState function

void fsm(){
  //update old state value
    prevStateFSM = stateFSM;
    
  //polling of main inputs
    topButton.poll();
    upButton.poll();
    downButton.poll();
  //updating time
    alarmClockData.now = rtc.now(); 

  //pulse
    if (alarmClockData.pulseInfo) {
      if (millis() > (alarmClockData.startTimePulse + TIMEDELAY)) {
        digitalWrite(LCD_LIGHT, HIGH);
        alarmClockData.pulseInfo = false;
      }
    }
    
  //fsm engine
    switch(stateFSM) {
      case FSM_RST:
        stateFSM = FSM_HOME;
        break;
        
      case FSM_HOME:
        if (topButton.buttonClicked) {
          alarmClockData.pulseInfo = true;
          digitalWrite(LCD_LIGHT, LOW); 
          alarmClockData.startTimePulse = millis();  
        }
        
        displayHome();
        goFromHome();
        
        break;
        
      case FSM_SETTIME:

        //routine to inizialize the counter of the rotary when you want to change the time
        if (rotaryInitCounter) {
          if (alarmClockData.twoStepSet == 0) {
            alarmClockData.hoursOffset = alarmClockData.hoursOffset + alarmClockData.now.hour();
            alarmClockData.minutesOffset = alarmClockData.minutesOffset + alarmClockData.now.minute();
            rotaryCounter = alarmClockData.hoursOffset;
          } else {
            rotaryCounter = alarmClockData.minutesOffset;
          }
          rotaryInitCounter = false;
        }

        
        rotaryUpdateTime();
        displaySetHome();
        goFromSetTime();
  
        break;
        
      case FSM_ALARM:
        displayAlarm();
        goFromAlarm();

        break;
        
      case FSM_SETALARM:
      
       //routine to inizialize the counter of the rotary when you want to change the time
        if (rotaryInitCounter) {
          if (alarmClockData.twoStepSet == 0) {
            rotaryCounter = alarmClockData.alarmHours;
          } else {
            rotaryCounter = alarmClockData.alarmMinutes;
          }
          rotaryInitCounter = false;
        }
      
        rotaryUpdateAlarm();
        displaySetAlarm();
        goFromSetAlarm();

        break;
        
      case FSM_TIMER:
        displayTimer();
        goFromTimer();

        break;
        
      case FSM_SETTIMER:

        //routine to inizialize the counter of the rotary when you want to change the time
        if (rotaryInitCounter) {
          if (alarmClockData.twoStepSet == 0) {
            rotaryCounter = alarmClockData.timerMinutes;
          } else {
            rotaryCounter = alarmClockData.timerSeconds;
          }
          rotaryInitCounter = false;
        }
        
        rotaryUpdateTimer();
        displaySetTimer();
        goFromSetTimer();

        break;
    }
    
  if (prevStateFSM != stateFSM) {
    printState(stateFSM);
    if (stateFSM == FSM_SETALARM or stateFSM == FSM_SETTIMER or stateFSM == FSM_SETTIME ) {
      rotaryInitCounter = true;
    }
    rotaryCounter = 0;
  }
}

void printState(int state) {
  switch(state) {
    case 0:
      Serial.println("IDLE");
      break;
      
    case 1:
      Serial.println("HOME");
      break;
      
    case 2:
      Serial.println("SET TIME");
      break;
      
    case 3: 
      Serial.println("ALARM");
      break;
      
    case 4:
      Serial.println("SET ALARM");
      break;
      
    case 5:
      Serial.println("TIMER");
      break;
      
    case 6: 
      Serial.println("SET TIMER");
      break; 
  }      
}

void goFromHome(){
    
  if (upButton.buttonClicked) {
    stateFSM = FSM_ALARM;
    return;
  }
  if (downButton.buttonHolded) {
    stateFSM = FSM_SETTIME;
    return;
  }
}

void goFromSetTime(){
  if (upButton.buttonClicked) {
    if (alarmClockData.twoStepSet == 1) {
      
      updateOffset();
      
      stateFSM = FSM_HOME;
      alarmClockData.twoStepSet = 0;
      return;  
    };
    rotaryInitCounter = true;
    alarmClockData.twoStepSet += 1;
  }
  
  if (downButton.buttonHolded) {
      //reset any change to the time, back to the ds3231 value
    alarmClockData.twoStepSet = 0;
    stateFSM = FSM_HOME;
    alarmClockData.hoursOffset = 0;
    alarmClockData.minutesOffset = 0;
  }
  
  if (topButton.buttonClicked || downButton.buttonClicked) {
      //here i'm escaping the settime via the two available ways (saving the changes)
    alarmClockData.twoStepSet = 0;

    updateOffset();
    
    stateFSM = FSM_HOME;
    return;
  }
}

void goFromAlarm(){
  if (topButton.buttonClicked) {
    stateFSM = FSM_HOME;
    return;
  }
  if (upButton.buttonClicked) {
    stateFSM = FSM_TIMER;
    return;
  }

  if (downButton.buttonClicked) {
    alarmClockData.alarmOnOff = !alarmClockData.alarmOnOff;
  }
  
  if (downButton.buttonHolded) {
    stateFSM = FSM_SETALARM;
    return;
  }
}

void goFromSetAlarm(){
  if (upButton.buttonClicked) {
    if (alarmClockData.twoStepSet == 1) {
      stateFSM = FSM_ALARM;
      alarmClockData.twoStepSet = 0;
      return;  
    };
    rotaryInitCounter = true;
    alarmClockData.twoStepSet += 1;
  }
  
  
  if (topButton.buttonClicked) {
    stateFSM = FSM_HOME;
    alarmClockData.twoStepSet = 0;
    return;
  }
  if (downButton.buttonClicked) {
    stateFSM = FSM_ALARM;
    alarmClockData.twoStepSet = 0;
    return;
  }
}

void goFromTimer(){
  if (topButton.buttonClicked || upButton.buttonClicked) {
    stateFSM = FSM_HOME;
    return;
  }
  
  if (downButton.buttonClicked) {
    alarmClockData.timerOnOff = !alarmClockData.timerOnOff;
  }
  
  if (downButton.buttonHolded) {
    stateFSM = FSM_SETTIMER;
    return;
  }
}

void goFromSetTimer(){
  if (upButton.buttonClicked) {
    if (alarmClockData.twoStepSet == 1) {
      stateFSM = FSM_TIMER;
      alarmClockData.twoStepSet = 0;
      return;  
    };
    rotaryInitCounter = true;
    alarmClockData.twoStepSet += 1;
  }
  
  if (topButton.buttonClicked) {
    stateFSM = FSM_HOME;
    alarmClockData.twoStepSet = 0;
    return;
  }
  if (downButton.buttonClicked) {
    stateFSM = FSM_TIMER;
    alarmClockData.twoStepSet = 0;
    return;
  }
}

void updateOffset() {

    Serial.println("UPDATED OFFSET");

    alarmClockData.hoursOffset = alarmClockData.hoursOffset - alarmClockData.now.hour();
    alarmClockData.minutesOffset = alarmClockData.minutesOffset - alarmClockData.now.minute();


}

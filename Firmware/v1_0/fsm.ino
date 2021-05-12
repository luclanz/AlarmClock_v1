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
        displayHome();

        if (topButton.buttonClicked) {
          alarmClockData.pulseInfo = true;
          digitalWrite(LCD_LIGHT, LOW); 
          alarmClockData.startTimePulse = millis();  
        }
        
        if (upButton.buttonClicked) {
          stateFSM = FSM_ALARM;
          break;
        }
        if (downButton.buttonHolded) {
          stateFSM = FSM_SETTIME;
          break;
        }
        break;
        
      case FSM_SETTIME:
        rotaryUpdateTime();
        displaySetHome();

        if (upButton.buttonClicked) {
          if (alarmClockData.twoStepSet == 1) {
            stateFSM = FSM_HOME;
            alarmClockData.twoStepSet = 0;
            break;  
          };
          alarmClockData.twoStepSet += 1;
        }

        if (downButton.buttonHolded) {
          alarmClockData.twoStepSet = 0;
          stateFSM = FSM_HOME;
          alarmClockData.hoursOffset = 0;
          alarmClockData.minutesOffset = 0;
        }
      
        if (topButton.buttonClicked || downButton.buttonClicked) {
          alarmClockData.twoStepSet = 0;
          stateFSM = FSM_HOME;
          break;
        }

        
        break;
        
      case FSM_ALARM:
        displayAlarm();
        if (topButton.buttonClicked) {
          stateFSM = FSM_HOME;
          break;
        }
        if (upButton.buttonClicked) {
          stateFSM = FSM_TIMER;
          break;
        }

        if (downButton.buttonClicked) {
          alarmClockData.alarmOnOff = !alarmClockData.alarmOnOff;
        }
        
        if (downButton.buttonHolded) {
          stateFSM = FSM_SETALARM;
          break;
        }
        break;
        
      case FSM_SETALARM:
        rotaryUpdateAlarm();
        displaySetAlarm();

        if (upButton.buttonClicked) {
          if (alarmClockData.twoStepSet == 1) {
            stateFSM = FSM_ALARM;
            alarmClockData.twoStepSet = 0;
            break;  
          };
          alarmClockData.twoStepSet += 1;
        }
        
        
        if (topButton.buttonClicked) {
          stateFSM = FSM_HOME;
          alarmClockData.twoStepSet = 0;
          break;
        }
        if (downButton.buttonClicked) {
          stateFSM = FSM_ALARM;
          alarmClockData.twoStepSet = 0;
          break;
        }
        break;
        
      case FSM_TIMER:
        displayTimer();
        if (topButton.buttonClicked || upButton.buttonClicked) {
          stateFSM = FSM_HOME;
          break;
        }
        
        if (downButton.buttonClicked) {
          alarmClockData.timerOnOff = !alarmClockData.timerOnOff;
        }
        
        if (downButton.buttonHolded) {
          stateFSM = FSM_SETTIMER;
          break;
        }
        break;
        
      case FSM_SETTIMER:
        rotaryUpdateTimer();
        displaySetTimer();

        if (upButton.buttonClicked) {
          if (alarmClockData.twoStepSet == 1) {
            stateFSM = FSM_TIMER;
            alarmClockData.twoStepSet = 0;
            break;  
          };
          alarmClockData.twoStepSet += 1;
        }
        
        if (topButton.buttonClicked) {
          stateFSM = FSM_HOME;
          alarmClockData.twoStepSet = 0;
          break;
        }
        if (downButton.buttonClicked) {
          stateFSM = FSM_TIMER;
          alarmClockData.twoStepSet = 0;
          break;
        }
        break;
    }
    
  if (prevStateFSM != stateFSM) {
    printState(stateFSM);
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
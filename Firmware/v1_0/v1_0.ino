//LIBs --------------------------------------------------------------------------------
  #include <RTClib.h>
  #include <LCD5110_Graph.h>
//HEADERs -----------------------------------------------------------------------------
  #include "classes.h"
  #include "config.h"

//Declaration ------------------------------------------------------------------------
  //buttons
    Button topButton("TOP", BT_TOP);
    Button upButton("UP", BT_UP);
    Button downButton("DOWN", BT_DOWN);
  //DS3231
    RTC_DS3231 rtc;  
    char daysOfTheWeek[7][12] = {"dom", "lun", "mar", "mer", "gio", "ven", "sab"};


void setup() {
  Serial.begin(9600);
  //init
    //buttons
      topButton.setup();
      upButton.setup();
      downButton.setup();
    //rtc
      rtcSetupRoutine();

}

void loop() {

  fsm();
  
}


//-----------------------------------------------------------------------------------------
void fsm(){
  //update old state value
    prevStateFSM = stateFSM;
    
  //polling of main inputs
    topButton.poll();
    upButton.poll();
    downButton.poll();
    
  //fsm engine
    switch(stateFSM) {
      case FSM_RST:
        stateFSM = FSM_HOME;
        break;
        
      case FSM_HOME:
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
        if (topButton.buttonClicked || downButton.buttonClicked) {
          stateFSM = FSM_HOME;
          break;
        }
        break;
        
      case FSM_ALARM:
        if (topButton.buttonClicked) {
          stateFSM = FSM_HOME;
          break;
        }
        if (upButton.buttonClicked) {
          stateFSM = FSM_TIMER;
          break;
        }
        if (downButton.buttonHolded) {
          stateFSM = FSM_SETALARM;
          break;
        }
        break;
        
      case FSM_SETALARM:
        if (topButton.buttonClicked) {
          stateFSM = FSM_HOME;
          break;
        }
        if (downButton.buttonClicked) {
          stateFSM = FSM_ALARM;
          break;
        }
        break;
        
      case FSM_TIMER:
        if (topButton.buttonClicked || upButton.buttonClicked) {
          stateFSM = FSM_HOME;
          break;
        }
        if (downButton.buttonHolded) {
          stateFSM = FSM_SETTIMER;
          break;
        }
        break;
        
      case FSM_SETTIMER:
        if (topButton.buttonClicked) {
          stateFSM = FSM_HOME;
          break;
        }
        if (downButton.buttonClicked) {
          stateFSM = FSM_TIMER;
          break;
        }
        break;
    }
    
  if (prevStateFSM != stateFSM) {
    printState(stateFSM);
  }
}
//-----------------------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------------------
void rtcSetTimerInterrupt (int secondToTimer) {

  if(!rtc.setAlarm1(rtc.now() + TimeSpan(secondToTimer), DS3231_A1_Second)) {
      Serial.println("Error, alarm wasn't set!");
  }else {
      Serial.print("Alarm will happen in ");  
      Serial.print(secondToTimer);
      Serial.println(" Seconds");
  }

}
//-----------------------------------------------------------------------------------------
void onAlarm() {
  Serial.println("Alarm OCCURED!");
}
//-----------------------------------------------------------------------------------------
void rtcSetupRoutine() {

    // initializing the rtc
    if(!rtc.begin()) {
        Serial.println("Couldn't find RTC!");
        Serial.flush();
        abort();
    }
    
    // this will adjust to the date and time at compilation
    if(rtc.lostPower()) {
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
    
    // Making it so, that the alarm will trigger an interrupt
    pinMode(RTC_INTERRUPT, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(RTC_INTERRUPT), onAlarm, FALLING);      //here's the func to call

    rtc.disable32K();
    rtc.clearAlarm(1);
    rtc.clearAlarm(2);
    rtc.writeSqwPinMode(DS3231_OFF);
    rtc.disableAlarm(2);

}

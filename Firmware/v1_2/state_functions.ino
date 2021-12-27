/*
  Here are some of the state function, to declutter the v1.1.ino file
  Functions:

    - state_X();          <- Rountine to do in the FSM

*/

void state_alarm() {
  //toggle alarm
    if (downButton.buttonClicked) {
      alarmData.alarmOnOff = !alarmData.alarmOnOff;
      alarmData.refresh = 1;
      lcd.LCDClear(0x00);

      if (alarmData.alarmOnOff) {
        // set alarm  
          rtc_set_alarm(rtc_hours_to_alarm(   (rtc.now().hour() + alarmData.hoursOffset) & 0x00FF, 
                                              alarmData.alarmHours, 
                                              alarmData.alarmMinutes < (rtc.now().minute() + alarmData.minutesOffset) & 0x00FF),
                        rtc_minutes_to_alarm( (rtc.now().minute() + alarmData.minutesOffset) & 0x00FF,
                                              alarmData.alarmMinutes)
                    );
      } else {
        // abort alarm
          rtc_disable_alarm();
      }
    }

}

void state_timer() {
  //toggle timer
  if (downButton.buttonClicked) {
    alarmData.timerOnOff = !alarmData.timerOnOff;
    alarmData.refresh = 1; 
    lcd.LCDClear(0x00);

    if (alarmData.timerOnOff) {
      // set timer
        rtc_set_timer( alarmData.timerSeconds + 60 * alarmData.timerMinutes);  
    } else {
      // abort alarm
        rtc_disable_timer();
    }
  }
  

}

void state_setTime () {
  
  //routine to inizialize the counter of the rotary when you want to change the time
    if (alarmData.rotaryInitCounter) {
      if (alarmData.twoStepSet == 0) {
        
        //here is the first time we enter the setup -> we are tweaking the hours
          alarmData.hoursOffset = alarmData.hoursOffset + rtc.now().hour();
          alarmData.minutesOffset = alarmData.minutesOffset + rtc.now().minute();

        //this line is so that the rotary counts along the current time
          alarmData.rotaryCounter = alarmData.hoursOffset;
          
      } else {
        
        //this line is so that the rotary counts along the current time
          alarmData.rotaryCounter = alarmData.minutesOffset;
      }

      //the rotary counter has been initialized so now back to false
        alarmData.rotaryInitCounter = false;
      
    }
    rotaryUpdateTime();

}

void state_setAlarm () {
  
  //routine to inizialize the counter of the rotary when you want to change the time
    if (alarmData.rotaryInitCounter) {
      if (alarmData.twoStepSet == 0) {
        alarmData.rotaryCounter = alarmData.alarmHours;
      } else {
        alarmData.rotaryCounter = alarmData.alarmMinutes;
      }
      alarmData.rotaryInitCounter = false;
    }
    rotaryUpdateAlarm();

}

void state_setTimer() {
  
  //routine to inizialize the counter of the rotary when you want to change the time
    if (alarmData.rotaryInitCounter) {
      if (alarmData.twoStepSet == 0) {
        alarmData.rotaryCounter = alarmData.timerMinutes;
      } else {
        alarmData.rotaryCounter = alarmData.timerSeconds;
      }
      alarmData.rotaryInitCounter = false;
    }
    rotaryUpdateTimer();  

}

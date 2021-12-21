/*

  Functions:

    - rtc_setup()
    - rtc_set_timer()
    - rtc_set_alarm()
    - rtc_minutes_to_alarm()
    - rtc_hours_to_alarm()
    - rtc_disable_alarm/timer()
    - rtc_onAlarm()

*/


  
void rtc_setup(int interrupt) {
  //This function needs the interrupt pin for the alarms (also wake / sleep)

  //Check RTC module correctly connected
    if(!rtc.begin()) {
        Serial.println(F("Couldn't find RTC!"));
        Serial.flush();
        abort();
    }

  //Check if the device went out of juice (never tried this line of code)
    if(rtc.lostPower()) {
      rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); 
    }

  // RUN THIS LINE IF THE TIME GETS OUT OF TRACK
    //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
        
  //Disable the 32K Pin
    rtc.disable32K();
    
  //Setup the interrupt
    pinMode(interrupt, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(interrupt), rtc_onAlarm, FALLING);

  //Clear the old alarms (just in case)
    rtc.clearAlarm(1);
    rtc.clearAlarm(2);
    
  //Set the right responce for the interrupt, now the SQW pin will stay up untill an alarm occurs
    rtc.writeSqwPinMode(DS3231_OFF);
    
  // turn off alarms
    rtc.disableAlarm(1);
    rtc.disableAlarm(2);
}


void rtc_set_timer (int sec_to_alarm) { 
  //This function sets the timer alarm, the input are the seconds 

  //Set the alarm, check the DS3231_A1_Hour mode
    if(!rtc.setAlarm1(
            rtc.now() + TimeSpan(0,0,0,sec_to_alarm),     //with this it will set a timespan of (dd, hh, mm, ss).
            DS3231_A1_Hour                                //This mode triggers the alarm when the seconds match.
                                                          //See Doxygen for other options
    )) {
        Serial.println(F("Error, alarm wasn't set!"));
    }else {
        Serial.print(F("Timer will happen in "));
        Serial.println(sec_to_alarm);  
    }
}

void rtc_set_alarm (int delta_h, int delta_m) {
  //This function sets the alarm, the input are the hours and minutes from the alarm.

  //Set the alarm, check the DS3231_A2_Hour mode
    if(!rtc.setAlarm2(
            rtc.now() + TimeSpan(0, delta_h, delta_m, 0),     //With this it will set a timespan of (dd, hh, mm, ss).
            DS3231_A2_Hour                                    //This mode triggers the alarm when the seconds match. 
                                                              //See Doxygen for other options
    )) {
        Serial.println(F("Error, alarm wasn't set!"));
    }else {
        Serial.print(F("Alarm will happen in "));
        Serial.print(delta_h); 
        Serial.print(F(" hours and "));
        Serial.print(delta_m); 
        Serial.println(F(" minutes"));
    }
}

int rtc_minutes_to_alarm (int m, int m_alarm) {
  //This function will calculate the missing minutes from the desired alarm.
  // m: actual minutes, m_alarm: minutes of the alarm
    if (m_alarm < m) {
      return (m_alarm + 60 - m);
    }
    return (m_alarm - m);
}

int rtc_hours_to_alarm (int h, int h_alarm, bool carrier) {
  //This function will calculate the missing hours from the desired alarm
  //first: actual time, second: desired alarm time, third: (m_alarm < m) <-- NOTE: this must result a bool value
    if (h_alarm < h) {
      return (h_alarm + 24 - h - 1 * carrier); 
    }
  
    return (h_alarm - h - 1 * carrier);
}

void rtc_disable_timer() {
  rtc.clearAlarm(1);
  rtc.disableAlarm(1);
  alarmData.timerOnOff = 0;
}

void rtc_disable_alarm() {
  rtc.clearAlarm(2);
  rtc.disableAlarm(2);
  alarmData.alarmOnOff = 0;
}

void rtc_onAlarm() {
    alarmData.enteringRingMode = 1;
    alarmData.stateFSM = FSM_RING;
    sdAndSpeaker_stopMusic();
}

/*

  Functions:

    - rtc_setup()                 <-- REMEMBER TO ACTIVATE THE INTERRUPT ONCE PROPER MANAGEMENT IS DONE
    - rtc_set_timer()
    - rtc_set_alarm()
    - rtc_minutes_to_alarm()
    - rtc_hours_to_alarm()
    - rtc_onAlarm()               <-- TODO

*/



void rtc_setup(int interrupt) //int: interrupt pin for the ds3231
{
  
    if(!rtc.begin()) {
        Serial.println(F("Couldn't find RTC!"));
        Serial.flush();
        abort();
    }

    if(rtc.lostPower()) {
        // if 1 it means the RTC lost track of time, first member: const DateTime, secondo member: dt
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
    
    //we don't need the 32K Pin, so disable it
    rtc.disable32K();
    
    // Making it so, that the alarm will trigger an interrupt


    //TODO: INTERRUPT MANAGEMENT##########################################################################################################

    
//    pinMode(interrupt, INPUT_PULLUP);
//    attachInterrupt(digitalPinToInterrupt(interrupt), rtc_onAlarm, FALLING);


    //####################################################################################################################################
    
    // set alarm 1, 2 flag to false (so alarm 1, 2 didn't happen so far)
    // if not done, this easily leads to problems, as both register aren't reset on reboot/recompile
    rtc.clearAlarm(1);
    rtc.clearAlarm(2);
    
    // stop oscillating signals at SQW Pin
    // now the SQW pin will stay up untill an alarm occurs
    rtc.writeSqwPinMode(DS3231_OFF);
    
    // turn off alarms
    rtc.disableAlarm(1);
    rtc.disableAlarm(2);
}


void rtc_set_timer (int sec_to_alarm) //int: second of the timer 
{
      // schedule an alarm sec_to_alarm seconds in the future --> NOTE: FOR THE TIMER WE SET THE SECOND ALARM
    if(!rtc.setAlarm1(
            rtc.now() + TimeSpan(0,0,0,sec_to_alarm),     //with this it will set a timespan of (dd, hh, mm, ss).
            DS3231_A1_Hour                                // this mode triggers the alarm when the seconds match. See Doxygen for other options
    )) {
        Serial.println(F("Error, alarm wasn't set!"));
    }else {
        Serial.print(F("Alarm1 (timer_related) will happen in "));
        Serial.println(sec_to_alarm);  
    }
}

void rtc_set_alarm (int delta_h, int delta_m) 
{
    if(!rtc.setAlarm2(
            rtc.now() + TimeSpan(0, delta_h, delta_m, 0),     //with this it will set a timespan of (dd, hh, mm, ss).
            DS3231_A2_Hour                              // this mode triggers the alarm when the seconds match. See Doxygen for other options
    )) {
        Serial.println(F("Error, alarm wasn't set!"));
    }else {
        Serial.print(F("Alarm2 (alarm_related) will happen in "));
        Serial.print(delta_h); 
        Serial.print(F(" hours and "));
        Serial.print(delta_m); 
        Serial.println(F(" minutes"));
    }
}

int rtc_minutes_to_alarm (int m, int m_alarm) //first: actual time, second: desired alarm time
{
  if (m_alarm < m) {
    return (m_alarm + 60 - m);
  }

  return (m_alarm - m);
}

int rtc_hours_to_alarm (int h, int h_alarm, bool carrier) //first: actual time, second: desired alarm time, third: (m_alarm < m)
{
  if (h_alarm < h) {
    return (h_alarm + 24 - h - 1 * carrier); 
  }

  return (h_alarm - h - 1 * carrier);
}

void rtc_onAlarm() {
    Serial.print(F("Alarm occured!"));
    //this must be really small and quick
    
    /*

    TODO

    */
}

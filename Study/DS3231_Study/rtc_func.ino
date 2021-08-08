
void rtc_setup(int interrupt) //int: interrupt pin for the ds3231
{

    // initializing the rtc, if pins SDA and SCL are not connected to the I2C port, the program will stop
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
    pinMode(interrupt, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(interrupt), onAlarm, FALLING);
    
    // set alarm 1, 2 flag to false (so alarm 1, 2 didn't happen so far)
    // if not done, this easily leads to problems, as both register aren't reset on reboot/recompile
    rtc.clearAlarm(1);
    rtc.clearAlarm(2);
    
    // stop oscillating signals at SQW Pin
    // now the SQW pin will stay up untill an alarm occurs
    rtc.writeSqwPinMode(DS3231_OFF);
    
    // turn off alarm 2 (in case it isn't off already)
    // again, this isn't done at reboot, so a previously set alarm could easily go overlooked
    rtc.disableAlarm(2);
}


void set_timer_alarm (int sec_to_alarm) //int: second of the timer 
{
  
      // schedule an alarm sec_to_alarm seconds in the future --> NOTE: FOR THE TIMER WE SET THE SECOND ALARM
    if(!rtc.setAlarm1(
            rtc.now() + TimeSpan(sec_to_alarm),
            DS3231_A1_Second // this mode triggers the alarm when the seconds match. See Doxygen for other options
    )) {
        Serial.println("Error, alarm wasn't set!");
    }else {
        Serial.print("Alarm will happen in ");
        Serial.println(sec_to_alarm);  
    }
}

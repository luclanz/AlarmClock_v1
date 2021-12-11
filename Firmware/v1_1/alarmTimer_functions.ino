void alarm_checkAlarm () {

  // Check if timer went ON
    if(rtc.alarmFired(1)) {                   // TODO
      rtc_disable_timer();
      alarmData.timerRinging = 1;
      Serial.println("Timer went ON");
    }

  // Check if alarm went ON
    if(rtc.alarmFired(2)) {
      rtc_disable_alarm();
      alarmData.alarmRinging = 1;
      Serial.println("Alarm went ON");
      display_ring();
      delay(100);
      sdAndSpeaker_startMusicAlarm();
    }  
}

void exitRingAlarm(){   

  if (topButton.buttonClicked) {
    alarmData.stateFSM = FSM_RST;
    alarmData.startPulsing = 0;
    alarmData.alarmRinging = 0;
    sdAndSpeaker_stopMusicAlarm();
    delay(100);
    digitalWrite(LCD_LIGHT, HIGH);

    /*
     * Stops Music!
     */
    
  }
 
}

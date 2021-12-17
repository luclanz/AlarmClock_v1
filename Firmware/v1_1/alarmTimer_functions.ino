void alarm_checkAlarmRountine () {

  // Check if timer went ON
  /* 
    if(rtc.alarmFired(1)) {                   // TODO
      rtc_disable_timer();
      alarmData.timerRinging = 1;
      Serial.println("Timer went ON");
    }
   */

  // Check if alarm went ON
    if(rtc.alarmFired(2)) {
      
      Serial.println("Alarm went ON");

      // disable alarm and set alarm bit
        rtc_disable_alarm();
        alarmData.alarmRinging = 1;

      // display message
        lcd.LCDClear(0x00);
        delay(100);
        display_ring();

      // (delay to close SPI) + starts music
        delay(100);
        sdAndSpeaker_startMusicAlarm();
    }  
}

void exitRingAlarm(){   

  if (topButton.buttonClicked) {

    // reset alarm bit & FSM
      alarmData.stateFSM = FSM_RST;
      alarmData.alarmRinging = 0;

    // stops music + (delay to close SPI)
      sdAndSpeaker_stopMusicAlarm();
      delay(100);

    // reset LCD light
      digitalWrite(LCD_LIGHT, HIGH); 
  }
 
}

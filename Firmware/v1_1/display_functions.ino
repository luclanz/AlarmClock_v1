void display_setup() 
{
  lcd.begin();
  lcd.setPowerSave(0);
}

void display_home()
{
  //print main time
    char time_string[5];
    lcd.clear();
    lcd.setFont(u8x8_font_inr21_2x4_n);
    sprintf(time_string, "%02d:%02d", rtc.now().hour(), rtc.now().minute());
    lcd.drawString(0, 1, time_string); 
  //print date when top button is pressed
//    if (topButton.buttonClicked) {
//      alarmData.pulseInfo = true;
//      digitalWrite(LCD_LIGHT, LOW); 
//      alarmData.startTimePulse = (millis() & 0x0000FFFF);  
//    }  

  
}

void display_setTime()
{
  
}

void display_alarm()
{
  
}

void display_setAlarm()
{
  
}

void display_timer()
{
  
}

void display_setTimer()
{
  
}

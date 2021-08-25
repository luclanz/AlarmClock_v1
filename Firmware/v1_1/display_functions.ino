void display_setup() 
{
  lcd.begin();
  lcd.setPowerSave(0);
}

void display_home()
{
  //print main time
    char time_string[10];
    lcd.setFont(u8x8_font_inr21_2x4_n);
    sprintf(time_string, "%02d:%02d", rtc.now().hour(), rtc.now().minute());    
//    if (alarmData.pulsing) {      //THIS WORKS
//      sprintf(time_string, "%02d:%02d", rtc.now().hour(), rtc.now().minute());    
//    } else {
//      sprintf(time_string, "%02d %02d", rtc.now().hour(), rtc.now().minute());
//    }
    lcd.drawString(0, 1, time_string); 

  //print extra info when display lights up
    if (alarmData.pulseInfo) {
      lcd.setFont(u8x8_font_chroma48medium8_r);
      sprintf(time_string, "%s %d %s", daysOfTheWeek[rtc.now().dayOfTheWeek()], rtc.now().day(), monthsOfTheYear[rtc.now().month()]);
      lcd.drawString(0, 5, time_string); 
    }

    //TODO: extra info for alarm / time in the first line
}

void display_setTime()
{

    //TODO: once the rotary encoder is implemented i need to display the correct time

  
    char time_string[5];
    lcd.setFont(u8x8_font_inr21_2x4_n);    
    if (alarmData.pulsing) {
        sprintf(time_string, "%02d:%02d", rtc.now().hour(), rtc.now().minute()); 
        lcd.drawString(0, 1, time_string);  
          
    } else {
      if (alarmData.twoStepSet) {
        //twoStepSet = 1:
        sprintf(time_string, "%02d:", rtc.now().hour()); 
        lcd.drawString(0, 1, time_string); 
   
      } else {
        //twoStepSet = 0:
        sprintf(time_string, ":%02d", rtc.now().minute()); 
        lcd.drawString(4, 1, time_string); 
      }
    }
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

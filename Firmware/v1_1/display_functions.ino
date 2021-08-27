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
    lcd.drawString(0, 1, time_string); 

  //print extra info when display lights up
    if (alarmData.pulseInfo) {
      lcd.setFont(u8x8_font_chroma48medium8_r);
      sprintf(time_string, "%s %d %s", daysOfTheWeek[rtc.now().dayOfTheWeek()], rtc.now().day(), monthsOfTheYear[rtc.now().month()]);
      lcd.drawString(0, 5, time_string); 

      if (alarmData.alarmOnOff & alarmData.timerOnOff) {
        lcd.drawString(0, 0, "Alarm Timer"); 
      } else {
        if (alarmData.alarmOnOff) lcd.drawString(0, 0, "Alarm");  
        if (alarmData.timerOnOff) lcd.drawString(0, 0, "Timer");         
      }
      
    }
         
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
  //print alarm time
    char time_string[10];

  //upper and bottom text
    lcd.setFont(u8x8_font_chroma48medium8_r);

    lcd.drawString(3,0, "Alarm");
    
    if (alarmData.alarmOnOff) {
      lcd.drawString(4, 5, "ON");
    } else {
      lcd.drawString(4, 5, "OFF"); 
    }
    
  //main text
    lcd.setFont(u8x8_font_inr21_2x4_n);
    sprintf(time_string, "%02d:%02d", alarmData.alarmHours, alarmData.alarmMinutes);    
    lcd.drawString(0, 1, time_string); 
}

void display_setAlarm()
{

    //TODO: rotary update
  
    char time_string[10];

  //upper and bottom text
    lcd.setFont(u8x8_font_chroma48medium8_r);

    lcd.drawString(3,0, "Alarm");
    lcd.drawString(4, 5, "SET");

  //main text
    lcd.setFont(u8x8_font_inr21_2x4_n);    
    if (alarmData.pulsing) {
        sprintf(time_string, "%02d:%02d", alarmData.alarmHours, alarmData.alarmMinutes); 
        lcd.drawString(0, 1, time_string);  
          
    } else {
      if (alarmData.twoStepSet) {
        //twoStepSet = 1:
        sprintf(time_string, "%02d:", alarmData.alarmHours); 
        lcd.drawString(0, 1, time_string); 
   
      } else {
        //twoStepSet = 0:
        sprintf(time_string, ":%02d", alarmData.alarmMinutes); 
        lcd.drawString(4, 1, time_string); 
      }
    }
}

void display_timer()
{
  //print timer
    char time_string[10];

  //upper and bottom text
    lcd.setFont(u8x8_font_chroma48medium8_r);

    lcd.drawString(3,0, "Timer");
    
    if (alarmData.timerOnOff) {
      lcd.drawString(4, 5, "ON");
    } else {
      lcd.drawString(4, 5, "OFF"); 
    }
    
  //main text
    lcd.setFont(u8x8_font_inr21_2x4_n);
    sprintf(time_string, "%02d:%02d", alarmData.timerMinutes, alarmData.timerSeconds);    
    lcd.drawString(0, 1, time_string);  
}

void display_setTimer()
{

    //TODO: Rotary update
  
    char time_string[10];

  //upper and bottom text
    lcd.setFont(u8x8_font_chroma48medium8_r);

    lcd.drawString(3,0, "Timer");
    lcd.drawString(4, 5, "SET");

  //main text
    lcd.setFont(u8x8_font_inr21_2x4_n);    
    if (alarmData.pulsing) {
        sprintf(time_string, "%02d:%02d", alarmData.timerMinutes, alarmData.timerSeconds); 
        lcd.drawString(0, 1, time_string);  
          
    } else {
      if (alarmData.twoStepSet) {
        //twoStepSet = 1:
        sprintf(time_string, "%02d:", alarmData.timerMinutes); 
        lcd.drawString(0, 1, time_string); 
   
      } else {
        //twoStepSet = 0:
        sprintf(time_string, ":%02d", alarmData.timerSeconds); 
        lcd.drawString(4, 1, time_string); 
      }
    }
}

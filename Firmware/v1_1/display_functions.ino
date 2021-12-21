/*
 * Functions        - display_setup()
 *                  - display_X()
 *  
 * Init arguments   1: bool, set to true to invert display pixel color
 *                  2: HEX, default is 0xBF set in LCDinit, Try 0xB1 <-> 0xBF if your display is too dark
 *                  3: HEX, LCD bias mode 1:48: Try 0x12 or 0x13 or 0x14
 *                  
 * (X , Y)          0-84 columns, 0-5 blocks / from top left corner   
 * 
 * Fonts            8: numbers (big)
 *                  6: small letters
 *                  2: bold letters
 */


void display_setup() 
{
  // Init
    lcd.LCDInit(false,  0xBF, 0x13);
    lcd.LCDClear(0x00);

  // Backlight Init
    pinMode(LCD_LIGHT, OUTPUT);
    digitalWrite(LCD_LIGHT, HIGH);
}

void display_home()
{
  if (alarmData.refresh) {
    alarmData.refresh = 0;
    //Print
      char time_string[10];
      lcd.LCDFont(fontNumber);
                                                        //I honestly don't know why the 0x00FF works...
      sprintf(time_string, "%02d:%02d", 
                      (rtc.now().hour() + alarmData.hoursOffset)     & 0x00FF, 
                      (rtc.now().minute() + alarmData.minutesOffset) & 0x00FF );    
      lcd.LCDgotoXY(0, 2);
      lcd.LCDString(time_string);
      lcd.LCDFont(fontLetter);
      lcd.LCDgotoXY(0, 1);
      if (alarmData.alarmOnOff & alarmData.timerOnOff) {
        lcd.LCDString("A T");
      } else {
        if (alarmData.alarmOnOff) {
          lcd.LCDString("A");
        }  
        if (alarmData.timerOnOff) {
          lcd.LCDString("T");
        }     
      } 
  
    //Print Extra Info
      //Date
        lcd.LCDFont(fontLetter);
        if (alarmData.pulseInfo) {
          sprintf(time_string, "%s %d %s", 
                        daysOfTheWeek[rtc.now().dayOfTheWeek()], 
                        rtc.now().day(), 
                        monthsOfTheYear[rtc.now().month()]);
          lcd.LCDgotoXY(18, 5);
          lcd.LCDString(time_string);
      //Alarm / Timer active
        lcd.LCDgotoXY(0, 1);
        if (alarmData.alarmOnOff & alarmData.timerOnOff) {
          lcd.LCDString("Alarm Timer");
        } else {
          if (alarmData.alarmOnOff) {
            lcd.LCDString("Alarm");
          }  
          if (alarmData.timerOnOff) {
            lcd.LCDString("Timer");
          }     
        } 
      } 
  }      
}

void display_setTime()
{  
  if (alarmData.refresh) {
    alarmData.refresh = 0;  
    //upper and bottom text
      lcd.LCDFont(fontLetter);
      
      lcd.LCDgotoXY(0, 1);
      lcd.LCDString("Time SET");
  
    //main text
      char time_string[5];
      lcd.LCDFont(fontNumber);  
      if (alarmData.pulsing) {
          lcd.LCDgotoXY(0, 2);
          sprintf(time_string, "%02d:%02d", alarmData.hoursOffset, alarmData.minutesOffset); 
          lcd.LCDString(time_string);  
            
      } else {
        if (alarmData.twoStepSet) {
          //twoStepSet = 1:
          lcd.LCDgotoXY(0, 2);
          sprintf(time_string, "%02d:", alarmData.hoursOffset); 
          lcd.LCDString(time_string); 
     
        } else {
          //twoStepSet = 0:
          lcd.LCDgotoXY(32, 2);
          sprintf(time_string, ":%02d", alarmData.minutesOffset); 
          lcd.LCDString(time_string); 
        }
      }
  }
}

void display_alarm()
{
  if (alarmData.refresh) {
    alarmData.refresh = 0;
    // Print Alarm Time
      char time_string[10];
  
      // Upper and Bottom Text
        lcd.LCDFont(fontLetter); 
  
        lcd.LCDgotoXY(0, 1);
        lcd.LCDString("Alarm");    
  
        lcd.LCDgotoXY(66, 5);
        if (alarmData.alarmOnOff) {
          lcd.LCDString("ON");
        } else {
          lcd.LCDString("OFF"); 
        }
  
      // Main Text
        lcd.LCDFont(fontNumber);
        lcd.LCDgotoXY(0, 2);
        sprintf(time_string, "%02d:%02d", alarmData.alarmHours, alarmData.alarmMinutes);    
        lcd.LCDString(time_string); 
  }
}

void display_setAlarm()
{ 
  if (alarmData.refresh) {
    alarmData.refresh = 0;
    char time_string[10];

    //upper and bottom text
      lcd.LCDFont(fontLetter);
      
      lcd.LCDgotoXY(0, 1);
      lcd.LCDString("Alarm SET");
  
    //main text
      lcd.LCDFont(fontNumber);    
      if (alarmData.pulsing) {
        lcd.LCDgotoXY(0, 2);
        sprintf(time_string, "%02d:%02d", alarmData.alarmHours, alarmData.alarmMinutes); 
        lcd.LCDString(time_string);  
      } else {
        if (alarmData.twoStepSet) {
          //twoStepSet = 1:
          lcd.LCDgotoXY(0, 2);
          sprintf(time_string, "%02d:", alarmData.alarmHours); 
          lcd.LCDString(time_string); 
     
        } else {
          //twoStepSet = 0:
          lcd.LCDgotoXY(32, 2);
          sprintf(time_string, ":%02d", alarmData.alarmMinutes); 
          lcd.LCDString(time_string); 
        }
      }
  }
}

void display_timer()
{  
  if (alarmData.refresh) {
    alarmData.refresh = 0;
    // Print Timer
      char time_string[10];
      
    // Upper and Bottom text
      // Upper and Bottom Text
        lcd.LCDFont(fontLetter); 
  
        lcd.LCDgotoXY(0, 1);
        lcd.LCDString("Timer");    
  
        lcd.LCDgotoXY(66, 5);
        if (alarmData.timerOnOff) {
          lcd.LCDString("ON");
        } else {
          lcd.LCDString("OFF"); 
        }
            
    // Main Text
      lcd.LCDFont(fontNumber);
      lcd.LCDgotoXY(0, 2);
      sprintf(time_string, "%02d:%02d", alarmData.timerMinutes, alarmData.timerSeconds);    
      lcd.LCDString(time_string); 
  }  
}

void display_setTimer()
{
  if (alarmData.refresh) {
    alarmData.refresh = 0;
    char time_string[10];

    //upper and bottom text
      lcd.LCDFont(fontLetter);
      
      lcd.LCDgotoXY(0, 1);
      lcd.LCDString("Timer SET");
  
    //main text
      lcd.LCDFont(fontNumber);     
      if (alarmData.pulsing) {
        lcd.LCDgotoXY(0, 2);
        sprintf(time_string, "%02d:%02d", alarmData.timerMinutes, alarmData.timerSeconds); 
        lcd.LCDString(time_string);        
      } else {
        if (alarmData.twoStepSet) {
          //twoStepSet = 1:
          lcd.LCDgotoXY(0, 2);
          sprintf(time_string, "%02d:", alarmData.timerMinutes); 
          lcd.LCDString(time_string); 
     
        } else {
          //twoStepSet = 0:
          lcd.LCDgotoXY(32, 2);
          sprintf(time_string, ":%02d", alarmData.timerSeconds); 
          lcd.LCDString(time_string); 
        }
      }
  }
}

void display_ring()
{
  // NO REFRESH ON THIS, the program automatically displays this once
  lcd.LCDFont(fontBold);
  lcd.LCDgotoXY(10, 2);
  lcd.LCDString("WAKE UP");
  
  lcd.LCDFont(fontLetter);
  lcd.LCDgotoXY(15, 3);
  lcd.LCDString("you dumbass");
    
}

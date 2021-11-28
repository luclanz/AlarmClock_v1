/*
 * Functions        display_setup()
 *                  display_X()
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
  //Print
    char time_string[10];
    lcd.LCDFont(fontNumber);
                                                      //I honestly don't know why the 0x00FF works...
    sprintf(time_string, "%02d:%02d", 
                    (rtc.now().hour() + alarmData.hoursOffset) & 0x00FF, 
                    (rtc.now().minute() + alarmData.minutesOffset) & 0x00FF);    
    lcd.LCDgotoXY(0, 2);
    lcd.LCDString(time_string);

  //Print Extra Info
    //Date
      if (alarmData.pulseInfo) {
        lcd.LCDFont(fontLetter);
        sprintf(time_string, "%s %d %s", 
                      daysOfTheWeek[rtc.now().dayOfTheWeek()], 
                      rtc.now().day(), 
                      monthsOfTheYear[rtc.now().month()]);
        lcd.LCDgotoXY(18, 5);
        lcd.LCDString(time_string);
    //Alarm / Timer active
      if (alarmData.alarmOnOff & alarmData.timerOnOff) {
        lcd.LCDgotoXY(0, 1);
        lcd.LCDString("Alarm Timer");
      } else {
        if (alarmData.alarmOnOff) {
          lcd.LCDgotoXY(0, 1);
          lcd.LCDString("Alarm");
        }  
        if (alarmData.timerOnOff) {
          lcd.LCDgotoXY(0, 1);
          lcd.LCDString("Timer");
        }     
      } 
    }       
}

void display_setTime()
{    
//  //upper and bottom text
//    lcd.setFont(u8x8_font_chroma48medium8_r);
//
//    lcd.drawString(3,0, "Time");
//    lcd.drawString(4, 5, "SET");
//
//  //main text
//    char time_string[5];
//    lcd.setFont(u8x8_font_inr21_2x4_n);    
//    if (alarmData.pulsing) {
//        sprintf(time_string, "%02d:%02d", alarmData.hoursOffset, alarmData.minutesOffset); 
//        lcd.drawString(0, 1, time_string);  
//          
//    } else {
//      if (alarmData.twoStepSet) {
//        //twoStepSet = 1:
//        sprintf(time_string, "%02d:", alarmData.hoursOffset); 
//        lcd.drawString(0, 1, time_string); 
//   
//      } else {
//        //twoStepSet = 0:
//        sprintf(time_string, ":%02d", alarmData.minutesOffset); 
//        lcd.drawString(4, 1, time_string); 
//      }
//    }
}

void display_alarm()
{
//  //print alarm time
//    char time_string[10];
//
//  //upper and bottom text
//    lcd.setFont(u8x8_font_chroma48medium8_r);
//
//    lcd.drawString(3,0, "Alarm");
//    
//    if (alarmData.alarmOnOff) {
//      lcd.drawString(4, 5, "ON");
//    } else {
//      lcd.drawString(4, 5, "OFF"); 
//    }
//    
//  //main text
//    lcd.setFont(u8x8_font_inr21_2x4_n);
//    sprintf(time_string, "%02d:%02d", alarmData.alarmHours, alarmData.alarmMinutes);    
//    lcd.drawString(0, 1, time_string); 
}

void display_setAlarm()
{ 
//    char time_string[10];
//
//  //upper and bottom text
//    lcd.setFont(u8x8_font_chroma48medium8_r);
//
//    lcd.drawString(3,0, "Alarm");
//    lcd.drawString(4, 5, "SET");
//
//  //main text
//    lcd.setFont(u8x8_font_inr21_2x4_n);    
//    if (alarmData.pulsing) {
//        sprintf(time_string, "%02d:%02d", alarmData.alarmHours, alarmData.alarmMinutes); 
//        lcd.drawString(0, 1, time_string);  
//          
//    } else {
//      if (alarmData.twoStepSet) {
//        //twoStepSet = 1:
//        sprintf(time_string, "%02d:", alarmData.alarmHours); 
//        lcd.drawString(0, 1, time_string); 
//   
//      } else {
//        //twoStepSet = 0:
//        sprintf(time_string, ":%02d", alarmData.alarmMinutes); 
//        lcd.drawString(4, 1, time_string); 
//      }
//    }
}

void display_timer()
{
//  //print timer
//    char time_string[10];
//
//  //upper and bottom text
//    lcd.setFont(u8x8_font_chroma48medium8_r);
//
//    lcd.drawString(3,0, "Timer");
//    
//    if (alarmData.timerOnOff) {
//      lcd.drawString(4, 5, "ON");
//    } else {
//      lcd.drawString(4, 5, "OFF"); 
//    }
//    
//  //main text
//    lcd.setFont(u8x8_font_inr21_2x4_n);
//    sprintf(time_string, "%02d:%02d", alarmData.timerMinutes, alarmData.timerSeconds);    
//    lcd.drawString(0, 1, time_string);  
}

void display_setTimer()
{
//    char time_string[10];
//
//  //upper and bottom text
//    lcd.setFont(u8x8_font_chroma48medium8_r);
//
//    lcd.drawString(3,0, "Timer");
//    lcd.drawString(4, 5, "SET");
//
//  //main text
//    lcd.setFont(u8x8_font_inr21_2x4_n);    
//    if (alarmData.pulsing) {
//        sprintf(time_string, "%02d:%02d", alarmData.timerMinutes, alarmData.timerSeconds); 
//        lcd.drawString(0, 1, time_string);  
//          
//    } else {
//      if (alarmData.twoStepSet) {
//        //twoStepSet = 1:
//        sprintf(time_string, "%02d:", alarmData.timerMinutes); 
//        lcd.drawString(0, 1, time_string); 
//   
//      } else {
//        //twoStepSet = 0:
//        sprintf(time_string, ":%02d", alarmData.timerSeconds); 
//        lcd.drawString(4, 1, time_string); 
//      }
//    }
}

void display_ring()
{
//  
//    lcd.setFont(u8x8_font_chroma48medium8_r);
//
//    lcd.drawString(1,2, "Coglione");
//    
}

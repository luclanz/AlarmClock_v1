// this file contains every function used to control the display


void displayHome () {
  myGLCD.clrScr();
  myGLCD.setFont(BigNumbers);
                  //(num, x, y, lenght, spacer)
  myGLCD.printNumI(alarmClockData.now.hour() + alarmClockData.hoursOffset, 13, 12, 2, '0');        //position of minutes / hours
  myGLCD.printNumI(alarmClockData.now.minute() + alarmClockData.minutesOffset, 47, 12, 2, '0');

  myGLCD.setFont(TinyFont);

  if (alarmClockData.pulseInfo) {
   
    String weekDisplay = daysOfTheWeek[alarmClockData.now.dayOfTheWeek()];
    String numberDisplay = String(alarmClockData.now.day());
    String monthDisplay = monthsOfTheYear[alarmClockData.now.month()];

    if (alarmClockData.timerOnOff) {
      myGLCD.print(F("Timer"), 50, 4);
    }
    
    if (alarmClockData.alarmOnOff) {
      myGLCD.print(F("Alarm"), 15, 4);
    }
    
    myGLCD.print(weekDisplay + " " + numberDisplay + " " + monthDisplay, 28, 41);
    
  }
  
  myGLCD.drawCircle(44, 21, 1);               //circles that makes my ":"
  myGLCD.drawCircle(44, 27, 1);

  myGLCD.update();
}


void displaySetHome() {
  
  myGLCD.clrScr();
  myGLCD.setFont(BigNumbers);
                  //(num, x, y, lenght, spacer)
  myGLCD.printNumI(alarmClockData.hoursOffset, 13, 12, 2, '0');        //position of minutes / hours
  myGLCD.printNumI(alarmClockData.minutesOffset, 47, 12, 2, '0');

  myGLCD.drawCircle(44, 21, 1);               //circles that makes my ":"
  myGLCD.drawCircle(44, 27, 1);

  myGLCD.setFont(TinyFont);

  myGLCD.print(F("<--"), 0, 33);
  myGLCD.print(F("res"), 0, 40);
  myGLCD.drawLine(0, 46, 3, 46);
  myGLCD.drawLine(4, 46, 6, 46);
  myGLCD.drawLine(7, 46, 10, 46);
  
  myGLCD.print(F("okay"), 0, 5);

  if (alarmClockData.twoStepSet == 0) {
      //hour block
      myGLCD.drawLine(20, 38, 36, 38);
      myGLCD.drawLine(20, 10, 36, 10);
  } else {
      //min block
      myGLCD.drawLine(53, 38, 69, 38);
      myGLCD.drawLine(53, 10, 69, 10);  
  };

  myGLCD.update();
}



void displaySetAlarm() {
  myGLCD.clrScr();
  myGLCD.setFont(BigNumbers);
                  //(num, x, y, lenght, spacer)
  myGLCD.printNumI(alarmClockData.alarmHours, 13, 12, 2, '0');        //position of minutes / hours
  myGLCD.printNumI(alarmClockData.alarmMinutes, 47, 12, 2, '0');

  myGLCD.drawCircle(44, 21, 1);               //circles that makes my ":"
  myGLCD.drawCircle(44, 27, 1);

  myGLCD.setFont(TinyFont);

  myGLCD.print(F("back"), 0, 37);
  myGLCD.print(F("okay"), 0, 5);

  if (alarmClockData.twoStepSet == 0) {
      //hour block
      myGLCD.drawLine(20, 38, 36, 38);
      myGLCD.drawLine(20, 10, 36, 10);
  } else {
      //min block
      myGLCD.drawLine(53, 38, 69, 38);
      myGLCD.drawLine(53, 10, 69, 10);  
  };

  myGLCD.update();
}

void displaySetTimer() {
  myGLCD.clrScr();
  myGLCD.setFont(BigNumbers);
                  //(num, x, y, lenght, spacer)
  myGLCD.printNumI(alarmClockData.timerMinutes, 13, 12, 2, '0');        //position of seconds / minutes
  myGLCD.printNumI(alarmClockData.timerSeconds, 47, 12, 2, '0');

  myGLCD.drawCircle(44, 21, 1);               //circles that makes my ":"
  myGLCD.drawCircle(44, 27, 1);

  myGLCD.setFont(TinyFont);

  myGLCD.print(F("back"), 0, 37);
  myGLCD.print(F("okay"), 0, 5);

  if (alarmClockData.twoStepSet == 0) {
      //min block
      myGLCD.drawLine(20, 38, 36, 38);
      myGLCD.drawLine(20, 10, 36, 10);
  } else {
      //sec block
      myGLCD.drawLine(53, 38, 69, 38);
      myGLCD.drawLine(53, 10, 69, 10);  
  };
  
  myGLCD.update();
}

void displayTimer () {
  myGLCD.clrScr();
  myGLCD.setFont(BigNumbers);
                  //(num, x, y, lenght, spacer)
  myGLCD.printNumI(alarmClockData.timerMinutes, 13, 12, 2, '0');        //position of seconds / minutes
  myGLCD.printNumI(alarmClockData.timerSeconds, 47, 12, 2, '0');

  myGLCD.drawCircle(44, 21, 1);               //circles that makes my ":"
  myGLCD.drawCircle(44, 27, 1);

  myGLCD.setFont(TinyFont);

  if (alarmClockData.timerOnOff) {
    myGLCD.print(F("Timer: ON"), 25, 4);
  } else {
    myGLCD.print(F("Timer: PAUSE"), 25, 4);  
  }
 
  myGLCD.print(F("(m)"), 23, 39);
  myGLCD.print(F("(s)"), 57, 39);
  myGLCD.print(F("I/0"), 0, 33);
  myGLCD.print(F("set"), 0, 40);
  myGLCD.drawLine(0, 46, 3, 46);
  myGLCD.drawLine(4, 46, 6, 46);
  myGLCD.drawLine(7, 46, 10, 46);
  myGLCD.print(F("cyc"), 0, 5);
  myGLCD.update();
}

void displayAlarm () {
  myGLCD.clrScr();
  myGLCD.setFont(BigNumbers);
                  //(num, x, y, lenght, spacer)
  myGLCD.printNumI(alarmClockData.alarmHours, 13, 12, 2, '0');        //position of minutes (15) / hours (9)
  myGLCD.printNumI(alarmClockData.alarmMinutes, 47, 12, 2, '0');

  myGLCD.drawCircle(44, 21, 1);               //circles that makes my ":"
  myGLCD.drawCircle(44, 27, 1);

  myGLCD.setFont(TinyFont);

  if (alarmClockData.alarmOnOff) {
    myGLCD.print(F("Alarm: ON"), 25, 4);
  } else {
    myGLCD.print(F("Alarm: OFF"), 25, 4);  
  }

  myGLCD.print(F("(h)"), 23, 39);
  myGLCD.print(F("(m)"), 57, 39);
  myGLCD.print(F("tog"), 0, 33);
  myGLCD.print(F("set"), 0, 40);
  myGLCD.drawLine(0, 46, 3, 46);
  myGLCD.drawLine(4, 46, 6, 46);
  myGLCD.drawLine(7, 46, 10, 46); 
  myGLCD.print(F("cyc"), 0, 5);
  myGLCD.update();
}

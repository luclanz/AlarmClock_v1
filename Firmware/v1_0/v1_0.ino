//LIBs --------------------------------------------------------------------------------
  #include "RTClib.h"
  #include "LCD5110_Graph.h"
//HEADERs -----------------------------------------------------------------------------
  #include "classes.h"
  #include "config.h"

//Declaration ------------------------------------------------------------------------
  //MAIN STRUCT ALARM
    struct alarmClock_struct {

      uint8_t timerMinutes = 10;            //how can I set these in turn-on? 
      uint8_t timerSeconds = 0;
      boolean timerOnOff = 0;

      uint8_t alarmHours = 7;
      uint8_t alarmMinutes = 0;
      uint8_t alarmOnOff = 0;  
    };
    typedef struct alarmClock_struct alarmClock_struct;
    alarmClock_struct alarmClockData;
  //FSM  
    int stateFSM = 0;
    int prevStateFSM = 0;
  //buttons
    Button topButton("TOP", BT_TOP);
    Button upButton("UP", BT_UP);
    Button downButton("DOWN", BT_DOWN);
  //DS3231
    RTC_DS3231 rtc;  
    char daysOfTheWeek[7][12] = {"dom", "lun", "mar", "mer", "gio", "ven", "sab"};
  //5110LCD
    LCD5110 myGLCD(LCD_CLK, LCD_MOSI, LCD_DC, LCD_RST, LCD_CS);
    
    extern uint8_t SmallFont[];                   // uint8_t -> byte
    extern uint8_t TinyFont[];
    extern uint8_t MediumNumbers[];
    extern uint8_t BigNumbers[];
    

void setup() {
  Serial.begin(9600);
  //init
    //buttons
      topButton.setup();
      upButton.setup();
      downButton.setup();
    //rtc
      rtcSetupRoutine();
    //lcd 
      myGLCD.InitLCD(65);

}

void loop() {
  fsm(); 
}


//-----------------------------------------------------------------------------------------
void fsm(){
  //update old state value
    prevStateFSM = stateFSM;
    
  //polling of main inputs
    topButton.poll();
    upButton.poll();
    downButton.poll();
    
  //fsm engine
    switch(stateFSM) {
      case FSM_RST:
        stateFSM = FSM_HOME;
        break;
        
      case FSM_HOME:
        displayHome();
        if (upButton.buttonClicked) {
          stateFSM = FSM_ALARM;
          break;
        }
//        if (downButton.buttonHolded) {
//          stateFSM = FSM_SETTIME;
//          break;
//        }
        break;
        
//      case FSM_SETTIME:
//        if (topButton.buttonClicked || downButton.buttonClicked) {
//          stateFSM = FSM_HOME;
//          break;
//        }
//        break;
        
      case FSM_ALARM:
        displayAlarm();
        if (topButton.buttonClicked) {
          stateFSM = FSM_HOME;
          break;
        }
        if (upButton.buttonClicked) {
          stateFSM = FSM_TIMER;
          break;
        }
        if (downButton.buttonHolded) {
          stateFSM = FSM_SETALARM;
          break;
        }
        break;
        
      case FSM_SETALARM:
        displaySetAlarm();
        if (topButton.buttonClicked) {
          stateFSM = FSM_HOME;
          break;
        }
        if (downButton.buttonClicked) {
          stateFSM = FSM_ALARM;
          break;
        }
        break;
        
      case FSM_TIMER:
        displayTimer();
        if (topButton.buttonClicked || upButton.buttonClicked) {
          stateFSM = FSM_HOME;
          break;
        }
        if (downButton.buttonHolded) {
          stateFSM = FSM_SETTIMER;
          break;
        }
        break;
        
      case FSM_SETTIMER:
        displaySetTimer();
        if (topButton.buttonClicked) {
          stateFSM = FSM_HOME;
          break;
        }
        if (downButton.buttonClicked) {
          stateFSM = FSM_TIMER;
          break;
        }
        break;
    }
    
  if (prevStateFSM != stateFSM) {
    printState(stateFSM);
  }
}
//-----------------------------------------------------------------------------------------
void printState(int state) {
  switch(state) {
    case 0:
      Serial.println("IDLE");
      break;
      
    case 1:
      Serial.println("HOME");
      break;
      
    case 2:
      Serial.println("SET TIME");
      break;
      
    case 3: 
      Serial.println("ALARM");
      break;
      
    case 4:
      Serial.println("SET ALARM");
      break;
      
    case 5:
      Serial.println("TIMER");
      break;
      
    case 6: 
      Serial.println("SET TIMER");
      break; 
  }      
}
//-----------------------------------------------------------------------------------------
void rtcSetTimerInterrupt (int secondToTimer) {

  if(!rtc.setAlarm1(rtc.now() + TimeSpan(secondToTimer), DS3231_A1_Second)) {
      Serial.println("Error, alarm wasn't set!");
  }else {
      Serial.print("Alarm will happen in ");  
      Serial.print(secondToTimer);
      Serial.println(" Seconds");
  }

}
//-----------------------------------------------------------------------------------------
void onAlarm() {
  Serial.println("Alarm OCCURED!");
}
//-----------------------------------------------------------------------------------------
void rtcSetupRoutine() {

    // initializing the rtc
    if(!rtc.begin()) {
        Serial.println("Couldn't find RTC!");
        Serial.flush();
        abort();
    }
    
    // this will adjust to the date and time at compilation
    if(rtc.lostPower()) {
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
    
    // Making it so, that the alarm will trigger an interrupt
    pinMode(RTC_INTERRUPT, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(RTC_INTERRUPT), onAlarm, FALLING);      //here's the func to call

    rtc.disable32K();
    rtc.clearAlarm(1);
    rtc.clearAlarm(2);
    rtc.writeSqwPinMode(DS3231_OFF);
    rtc.disableAlarm(2);
}
// Display func ---------------------------------------------------------------------------
void displaySetAlarm() {
  myGLCD.clrScr();
  myGLCD.setFont(BigNumbers);
                  //(num, x, y, lenght, spacer)
  myGLCD.printNumI(30, 13, 12, 2, '0');        //position of seconds (23) / minutes (10)
  myGLCD.printNumI(23, 47, 12, 2, '0');

  myGLCD.drawCircle(44, 21, 1);               //circles that makes my ":"
  myGLCD.drawCircle(44, 27, 1);

  myGLCD.setFont(TinyFont);
  //voglio che venga scritto "Orologio" appena entro in questa pagina per 1 secondo prima di scomparire"

  myGLCD.print("back", 0, 37);
  myGLCD.print("okay", 0, 5);

  //min block
  myGLCD.drawLine(20, 38, 36, 38);
  myGLCD.drawLine(20, 10, 36, 10);
  //sec block
  myGLCD.drawLine(53, 38, 69, 38);
  myGLCD.drawLine(53, 10, 69, 10);
  myGLCD.update();
}

void displaySetTimer() {
  myGLCD.clrScr();
  myGLCD.setFont(BigNumbers);
                  //(num, x, y, lenght, spacer)
  myGLCD.printNumI(30, 13, 12, 2, '0');        //position of seconds (23) / minutes (10)
  myGLCD.printNumI(23, 47, 12, 2, '0');

  myGLCD.drawCircle(44, 21, 1);               //circles that makes my ":"
  myGLCD.drawCircle(44, 27, 1);

  myGLCD.setFont(TinyFont);
  //voglio che venga scritto "Orologio" appena entro in questa pagina per 1 secondo prima di scomparire"

  myGLCD.print("back", 0, 37);
  myGLCD.print("okay", 0, 5);

  //min block
  myGLCD.drawLine(20, 38, 36, 38);
  myGLCD.drawLine(20, 10, 36, 10);
  //sec block
  myGLCD.drawLine(53, 38, 69, 38);
  myGLCD.drawLine(53, 10, 69, 10);
  myGLCD.update();
}

void displayTimer () {
  myGLCD.clrScr();
  myGLCD.setFont(BigNumbers);
                  //(num, x, y, lenght, spacer)
  myGLCD.printNumI(10, 13, 12, 2, '0');        //position of seconds (23) / minutes (10)
  myGLCD.printNumI(23, 47, 12, 2, '0');

  myGLCD.drawCircle(44, 21, 1);               //circles that makes my ":"
  myGLCD.drawCircle(44, 27, 1);

  myGLCD.setFont(TinyFont);
  //voglio che venga scritto "Orologio" appena entro in questa pagina per 1 secondo prima di scomparire"
  myGLCD.print("Timer: ON", CENTER, 4);
  myGLCD.print("(m)", 23, 39);
  myGLCD.print("(s)", 57, 39);
  myGLCD.print("tog", 0, 33);
  myGLCD.print("set", 0, 40);
  myGLCD.drawLine(0, 46, 3, 46);
  myGLCD.drawLine(4, 46, 6, 46);
  myGLCD.drawLine(7, 46, 10, 46);
  myGLCD.print("cyc", 0, 5);
  myGLCD.update();
}

void displayAlarm () {
  myGLCD.clrScr();
  myGLCD.setFont(BigNumbers);
                  //(num, x, y, lenght, spacer)
  myGLCD.printNumI(9, 13, 12, 2, '0');        //position of minutes (15) / hours (9)
  myGLCD.printNumI(15, 47, 12, 2, '0');

  myGLCD.drawCircle(44, 21, 1);               //circles that makes my ":"
  myGLCD.drawCircle(44, 27, 1);

  myGLCD.setFont(TinyFont);
  //voglio che venga scritto "Orologio" appena entro in questa pagina per 1 secondo prima di scomparire"
  myGLCD.print("Alarm: ON", CENTER, 4);
  myGLCD.print("(h)", 23, 39);
  myGLCD.print("(m)", 57, 39);
  myGLCD.print("tog", 0, 33);
  myGLCD.print("set", 0, 40);
  myGLCD.drawLine(0, 46, 3, 46);
  myGLCD.drawLine(4, 46, 6, 46);
  myGLCD.drawLine(7, 46, 10, 46); 
  myGLCD.print("cyc", 0, 5);
  myGLCD.update();
}

void displayHome () {
  myGLCD.clrScr();
  myGLCD.setFont(BigNumbers);
                  //(num, x, y, lenght, spacer)
  myGLCD.printNumI(9, 13, 12, 2, '0');        //position of minutes (15) / hours (9)
  myGLCD.printNumI(15, 47, 12, 2, '0');

  myGLCD.setFont(TinyFont);
  //voglio che venga scritto "Orologio" appena entro in questa pagina per 1 secondo prima di scomparire"
  myGLCD.print("SAB 10 APR", RIGHT, 43);

//  if (toggle == true) 
//  {
    myGLCD.drawCircle(44, 21, 1);               //circles that makes my ":"
    myGLCD.drawCircle(44, 27, 1);
//    toggle = false;
//  }
//  else 
//  {
//    toggle = true;
//  }
  myGLCD.update();
}

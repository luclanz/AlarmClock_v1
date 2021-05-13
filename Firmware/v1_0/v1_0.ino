//LIBs --------------------------------------------------------------------------------
  #include "RTClib.h"
  #include "LCD5110_Graph.h"
//HEADERs -----------------------------------------------------------------------------
  #include "classes.h"
  #include "config.h"
//Declaration ------------------------------------------------------------------------
  //FSM  
    int stateFSM = 0;
    int prevStateFSM = 0;
  //buttons
    Button topButton("TOP", BT_TOP);
    Button upButton("UP", BT_UP);
    Button downButton("DOWN", BT_DOWN);
  //DS3231
    RTC_DS3231 rtc;  
    char daysOfTheWeek[7][4] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
    char monthsOfTheYear [13][4] = {"DEC", "JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};
  //5110LCD
    LCD5110 myGLCD(LCD_CLK, LCD_DIN, LCD_DC, LCD_RST, LCD_CE);
    extern uint8_t SmallFont[];                   // uint8_t -> byte
    extern uint8_t TinyFont[];
    extern uint8_t MediumNumbers[];
    extern uint8_t BigNumbers[];
  //MAIN STRUCT ALARM
    struct alarmClock_struct {

      boolean pulseInfo = false;            //two variables to make the display light up for a brief period
      uint32_t startTimePulse;

      uint8_t hoursOffset = 0;
      uint8_t minutesOffset = 0;
      
      uint8_t timerMinutes = 10;            //how can I set these in turn-on? 
      uint8_t timerSeconds = 0;
      boolean timerOnOff = 0;

      uint8_t alarmHours = 7;
      uint8_t alarmMinutes = 0;
      uint8_t alarmOnOff = 0;

      uint8_t twoStepSet = 0;               //this value goes 0, 1, 2 while in the set menu (minutes -> second -> back)

      DateTime now;                         //this variable will contain every data related to the time (updated at the beginning of the fsm)
    };
    typedef struct alarmClock_struct alarmClock_struct;
    alarmClock_struct alarmClockData;
    
  // rotary encoder variables
    int rotaryCounter = 0;                            //Value of the knob
    int rotaryCurrentStateCLK, rotaryLastStateCLK;          //Value of CLK output
    String rotaryCurrentDir ="";                      //Direction
    uint8_t rotaryOverflow[3] = {23, 59, 99};
    uint8_t rotaryOverflowIndex = 0;
    bool rotaryInitCounter = false;

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
      pinMode(LCD_LIGHT, OUTPUT);
      digitalWrite(LCD_LIGHT, HIGH);
      myGLCD.InitLCD(60);
    //rotary enc
      rotarySetupRoutine();
}

void loop() {

// check alarm / timer routine
  fsm(); 
  //delay(5);
}


// RTC -------------------------------------------------------------------------------------
void rtcSetTimerInterrupt (int secondToTimer) {

  if(!rtc.setAlarm1(rtc.now() + TimeSpan(secondToTimer), DS3231_A1_Second)) {
      Serial.println("Error, alarm wasn't set!");
  }else {
      Serial.print("Alarm will happen in ");  
      Serial.print(secondToTimer);
      Serial.println(" Seconds");
  }

}
void onAlarm() {
  Serial.println("Alarm OCCURED!");
}
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
//    pinMode(RTC_INTERRUPT, INPUT_PULLUP);
//    attachInterrupt(digitalPinToInterrupt(RTC_INTERRUPT), onAlarm, FALLING);      //here's the func to call
//
//    rtc.disable32K();
//    rtc.clearAlarm(1);
//    rtc.clearAlarm(2);
//    rtc.writeSqwPinMode(DS3231_OFF);
//    rtc.disableAlarm(2);
}

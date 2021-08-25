//Libraries
  #include "RTClib.h"
  #include <U8x8lib.h>
  
  #ifdef U8X8_HAVE_HW_SPI
    #include <SPI.h>
  #endif


//Files
  #include "classes.h"
  #include "config.h"

//Declarations----------------------------------------------------------------------------------------------------------------------

  //Button Variables
    Button topButton(BT_TOP);
    Button upButton(BT_UP);
    Button downButton(BT_DOWN);

  //Alarm Clock General Data
    struct alarmClock_struct {
      
      //FSM state variables
        uint8_t stateFSM :3;                  //7 states -> 3bits (0 to 7)
        uint8_t prevStateFSM :3;

      //For setting time (UX)
        boolean pulsing :1;
        uint32_t pulsingTime;

      //For lighting the display
        boolean pulseInfo :1;
        uint32_t startTimePulse;
        
      //Offset to change time
        uint8_t hoursOffset :4;               //12h max -> 4bits (0 to 15)
        uint8_t minutesOffset :6;             //59m max -> 6bits (0 to 63)

      //Timer / Alam set variables
        uint8_t timerMinutes;                 //up to 255minutes
        uint8_t timerSeconds :6;              //59s max -> 6bits (0 to 63)  
        boolean timerOnOff :1;                
        uint8_t alarmHours :5;                //23h max -> 5bits (0 to 31)
        uint8_t alarmMinutes :6;              //59m max -> 6bits (0 to 63) 
        uint8_t alarmOnOff :1;

      //Value 0 to 2 to navigate the menu
        uint8_t twoStepSet :2;

      //TODO
      //DateTime now;                         //WE MIGHT NOT NEED THIS
    };
    
    typedef struct alarmClock_struct alarmClock_struct;
    alarmClock_struct alarmData;

  //RTC
    RTC_DS3231 rtc;
        //NOTE: those two array occupy around 80 bytes of dynamic memory, they are not really required
    char daysOfTheWeek[7][4] = {"sun", "mon", "tue", "wed", "thu", "fri", "sat"};
    char monthsOfTheYear [13][4] = {"dec", "jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec"};

  //Display
    U8X8_PCD8544_84X48_4W_SW_SPI lcd(LCD_CLK, LCD_DIN, LCD_CE, LCD_DC, LCD_RST);

//----------------------------------------------------------------------------------------------------------------------------------

void setup() {

  //Serial port -> Open
    Serial.begin(9600);
    while (!Serial) {}
  
  //init
  
    //buttons
      topButton.setup();
      upButton.setup();
      downButton.setup();
      
    //alarmData
      alarmData.stateFSM = 0;
      alarmData.prevStateFSM = 0;
      alarmData.pulsing = 0;
      alarmData.pulsingTime = millis();
      alarmData.pulseInfo = 0;      
      alarmData.startTimePulse = millis();
      alarmData.hoursOffset = 0;     
      alarmData.minutesOffset = 0;
      alarmData.timerMinutes = 10;       
      alarmData.timerSeconds = 0;
      alarmData.timerOnOff = 0;
      alarmData.alarmHours = 7;
      alarmData.alarmMinutes = 0;
      alarmData.alarmOnOff = 0;
      alarmData.twoStepSet = 0; 

    //RTC
      rtc_setup(RTC_INTERRUPT_PIN);
    //LCD
      display_setup();
      pinMode(LCD_LIGHT, OUTPUT);
      digitalWrite(LCD_LIGHT, HIGH);

}

//--------------------------------------------------------------------------------------------------

void loop() {

  //update state  
    alarmData.prevStateFSM = alarmData.stateFSM;

  //pulsing:
    if (millis() > alarmData.pulsingTime + PULSE) {
      alarmData.pulsingTime = millis();
      alarmData.pulsing = !alarmData.pulsing;
      lcd.clear();
    }
    
  //Polling
    topButton.poll();
    upButton.poll();
    downButton.poll();

  //light pulse 
    if (alarmData.pulseInfo) {
      if (millis() > (alarmData.startTimePulse + TIMEDELAY)) {      //here we might have a bug when we get an overflow
        digitalWrite(LCD_LIGHT, HIGH);
        alarmData.pulseInfo = false;
        lcd.clear();
      }
    }

  //fsm switch engine
    switch(alarmData.stateFSM) {
      
      case FSM_RST:
        
        alarmData.stateFSM = FSM_HOME;
        break;
    
      case FSM_HOME:

        //print date when top button is pressed
        if (topButton.buttonClicked) {
          alarmData.pulseInfo = true;
          digitalWrite(LCD_LIGHT, LOW); 
          alarmData.startTimePulse = millis();  
        }  

        display_home();
        goFromHome();
        break;
    
      case FSM_SETTIME:
      
        display_setTime();
        goFromSetTime();
        break;
    
      case FSM_ALARM:

        display_alarm();
        goFromAlarm();
        break;
    
      case FSM_SETALARM:

        display_setAlarm();
        goFromSetAlarm();
        break;
    
      case FSM_TIMER:
    
        display_timer();
        goFromTimer();
        break;
    
      case FSM_SETTIMER:

        display_setTimer();
        goFromSetTimer();
        break;
    } 

    
    //print state
      if (alarmData.prevStateFSM != alarmData.stateFSM) {
        printState(alarmData.stateFSM);
        lcd.clear();
      }
}

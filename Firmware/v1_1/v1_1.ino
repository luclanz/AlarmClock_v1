//Libraries
  #include "RTClib.h"


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

      //For lighting the display
        boolean pulseInfo :1;
        uint16_t startTimePulse;
        
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
      alarmData.pulseInfo = 0;      
      alarmData.startTimePulse;
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

}

void loop() {

  //Polling
    topButton.poll();
    upButton.poll();
    downButton.poll();

  //update state  
    alarmData.prevStateFSM = alarmData.stateFSM;

  //fsm switch engine
    switch(alarmData.stateFSM) {
      
      case FSM_RST:
        
        alarmData.stateFSM = FSM_HOME;
        break;
    
      case FSM_HOME:
        
        goFromHome();
        break;
    
      case FSM_SETTIME:
    
        goFromSetTime();
        break;
    
      case FSM_ALARM:
    
        goFromAlarm();
        break;
    
      case FSM_SETALARM:

        goFromSetAlarm();
        break;
    
      case FSM_TIMER:
    
        goFromTimer();
        break;
    
      case FSM_SETTIMER:
    
        goFromSetTimer();
        break;
    } 
       
    //print state
      if (alarmData.prevStateFSM != alarmData.stateFSM) {
        printState(alarmData.stateFSM);
      }
}

//Libraries
  //#include <U8x8lib.h>
  #include <NOKIA5110_TEXT.h>
  #include <SPI.h>
  #include "SD.h"
  #include "TMRpcm.h"
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

      //Display Refresh
        uint8_t refresh :1;

      //For setting time (UX)
        boolean pulsing :1;
        boolean startPulsing :1;
        uint32_t pulsingTime;

      //For lighting the display
        boolean pulseInfo :1;
        uint32_t startTimePulse;
        
      //Offset to change time
        uint8_t hoursOffset;              
        uint8_t minutesOffset;             

      //Timer - Alam set variables
        uint8_t timerMinutes;                 
        uint8_t timerSeconds;              
        boolean timerOnOff :1;                
        uint8_t alarmHours;                
        uint8_t alarmMinutes;              
        uint8_t alarmOnOff :1;

      //Value 0 to 2 to navigate the menu
        uint8_t twoStepSet :2;

      //Rotary Encoder
        uint8_t rotaryCounter :7;             //Value of the knob, MAX: 99, 7bits
        uint8_t rotaryCurrentStateCLK :1;     //Value of CLK output: boolean
        uint8_t rotaryLastStateCLK :1;  
        
        uint8_t rotaryOverflow[3] = {23, 59, 99};
        uint8_t rotaryOverflowIndex :2;
        uint8_t rotaryInitCounter :1;

      //Timer - Alarm Management
        uint8_t enteringRingMode :1;
        uint8_t alarmRinging :1;
        uint8_t timerRinging :1;          // Later
        
    };
    
    typedef struct alarmClock_struct alarmClock_struct;
    alarmClock_struct alarmData;

  //RTC
    RTC_DS3231 rtc;
        //NOTE: those two array occupy around 80 bytes of dynamic memory, they are not really required
    char daysOfTheWeek[7][4] = {"sun", "mon", "tue", "wed", "thu", "fri", "sat"};
    char monthsOfTheYear [13][4] = {"dec", "jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec"};

  //Display
    //U8X8_PCD8544_84X48_4W_SW_SPI lcd(LCD_CLK, LCD_DIN, LCD_CE, LCD_DC, LCD_RST); 
    NOKIA5110_TEXT lcd(LCD_RST, LCD_CE, LCD_DC);

  //Speaker & SD
    TMRpcm music;

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
      alarmData.stateFSM = FSM_RST;                               // CHANGE THIS TO DEBUG
      alarmData.prevStateFSM = FSM_RST;
      alarmData.pulsing = 0;
      alarmData.startPulsing = 0;
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

      alarmData.rotaryCounter = 0;
      alarmData.rotaryOverflowIndex = 0;
      alarmData.rotaryInitCounter = 0;

      alarmData.enteringRingMode = 0;
      alarmData.timerRinging = 0;
      alarmData.alarmRinging = 0;

      alarmData.refresh = 1;

    //RTC
      rtc_setup(RTC_INTERRUPT_PIN);
      
    //LCD
      display_setup();

    //ROTARY
      rotarySetupRoutine();

    //SD and Speaker
      sdAndSpeaker_setup();

}

//--------------------------------------------------------------------------------------------------

void loop() {

  //update state  
    alarmData.prevStateFSM = alarmData.stateFSM;

  //Polling
    topButton.poll();
    upButton.poll();
    downButton.poll();

  //pulsing digit when setting new time / alarm / timer
    if (alarmData.startPulsing) {
      if (millis() > alarmData.pulsingTime + PULSE) {
        alarmData.pulsingTime = millis();
        alarmData.pulsing = !alarmData.pulsing;
        //lcd.clear();
        alarmData.refresh = 1;
        lcd.LCDClear(0x00);
      }
    }

  //light pulse when pressing top in home
    if (alarmData.pulseInfo) {
      if (millis() > (alarmData.startTimePulse + TIMEDELAY)) {      //here we might have a bug when we get an overflow
        digitalWrite(LCD_LIGHT, HIGH);
        alarmData.pulseInfo = false;
        alarmData.refresh = 1;
        lcd.LCDClear(0x00);
      }
    }

  //fsm switch engine
    switch(alarmData.stateFSM) {
      
      case FSM_RST:
        alarmData.stateFSM = FSM_HOME;

        //Disable alarm / timer
          rtc_disable_alarm();
          rtc_disable_timer();
        break;
    
      case FSM_HOME:
        //print date when top button is pressed
          if (topButton.buttonClicked) {
            alarmData.pulseInfo = true;
            digitalWrite(LCD_LIGHT, LOW); 
            alarmData.startTimePulse = millis();
            alarmData.refresh = 1; 
          }  
        display_home();
        goFromHome();
        break;
    
      case FSM_SETTIME:
        state_setTime();
        display_setTime();
        goFromSetTime();
        break;
    
      case FSM_ALARM:
        state_alarm();
        display_alarm();
        goFromAlarm();
        break;
    
      case FSM_SETALARM:
        state_setAlarm();
        display_setAlarm();
        goFromSetAlarm();
        break;
    
      case FSM_TIMER:
        display_timer();
        goFromTimer();
        break;
    
      case FSM_SETTIMER:
        state_setTimer();
        display_setTimer();
        goFromSetTimer();
        break;

      case FSM_RING:
        // first time entering
          if (alarmData.enteringRingMode) {
            Serial.println(F("Alarm occured!"));
            
            alarmData.enteringRingMode = 0;
            alarm_checkAlarmRountine();
            digitalWrite(LCD_LIGHT, LOW);
          }

        // alarm handling
          if (alarmData.alarmRinging) {
            exitRingAlarm();
          }

        /*                                                                                  TODO
         * if (alarmData.timerRinging) {
         *   display_ring();
         * }
         */

        break;
    } 

    
    //print state
      if (alarmData.prevStateFSM != alarmData.stateFSM) {

        //print new state
          printState(alarmData.stateFSM);
          
        //clear / refresh lcd
          if (alarmData.stateFSM != FSM_RING) {
            lcd.LCDClear(0x00);
            alarmData.refresh = 1;
          }
          
        //reset pulsing
          alarmData.startPulsing = 0;
        
        // Activate ROTARY and PULSING when entering "time_setting" states
          if (alarmData.stateFSM == FSM_SETTIMER or alarmData.stateFSM == FSM_SETTIME or alarmData.stateFSM == FSM_SETALARM) {
            
            alarmData.rotaryInitCounter = true;
            alarmData.startPulsing = 1;
            enableRotaryISR();
            
          } else {
            
            disableRotaryISR();
            
          }

        alarmData.rotaryCounter = 0;
      }
}

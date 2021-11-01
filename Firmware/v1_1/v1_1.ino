//Libraries
  #include "RTClib.h"
  #include <U8x8lib.h>
  
  //#ifdef U8X8_HAVE_HW_SPI
    #include <SPI.h>
  //#endif

  #include "SD.h"
  #include "TMRpcm.h"


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
      alarmData.stateFSM = 0;
      alarmData.prevStateFSM = 0;
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

    //RTC
      rtc_setup(RTC_INTERRUPT_PIN);
      
    //LCD
      display_setup();

    //ROTARY
      rotarySetupRoutine();

    //SD and Speaker
      sdAndSpeaker_setup();

      //display_setup();
//      digitalWrite(LM_IN, HIGH);
      Serial.println(digitalRead(LM_IN));
      Serial.println(digitalRead(LCD_CE));
//      digitalWrite(LCD_CE, LOW);
    

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
        lcd.clear();
      }
    }

  //light pulse when pressing top in home
    if (alarmData.pulseInfo) {
      if (millis() > (alarmData.startTimePulse + TIMEDELAY)) {      //here we might have a bug when we get an overflow
        digitalWrite(LCD_LIGHT, HIGH);
        alarmData.pulseInfo = false;
        lcd.clear();
      }
    }

  //Serial.println(digitalRead(SD_CS));

  //fsm switch engine
    switch(alarmData.stateFSM) {
      
      case FSM_RST:
        alarmData.stateFSM = FSM_HOME;
        //alarmData.stateFSM = FSM_RING;
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
        //Serial.println("hi");
        break;
    
      case FSM_SETTIME:
        //Serial.println("hi");
        //routine to inizialize the counter of the rotary when you want to change the time
          if (alarmData.rotaryInitCounter) {
            if (alarmData.twoStepSet == 0) {
              
              //here is the first time we enter the setup -> we are tweaking the hours
                alarmData.hoursOffset = alarmData.hoursOffset + rtc.now().hour();
                alarmData.minutesOffset = alarmData.minutesOffset + rtc.now().minute();
  
              //this line is so that the rotary counts along the current time
                alarmData.rotaryCounter = alarmData.hoursOffset;
                
            } else {
              
              //this line is so that the rotary counts along the current time
                alarmData.rotaryCounter = alarmData.minutesOffset;
            }
  
            //the rotary counter has been initialized so now back to false
              alarmData.rotaryInitCounter = false;
            
          }
          rotaryUpdateTime();

      
        display_setTime();
        goFromSetTime();
        break;
    
      case FSM_ALARM:

        display_alarm();
        goFromAlarm();
        break;
    
      case FSM_SETALARM:

        //routine to inizialize the counter of the rotary when you want to change the time
          if (alarmData.rotaryInitCounter) {
            if (alarmData.twoStepSet == 0) {
              alarmData.rotaryCounter = alarmData.alarmHours;
            } else {
              alarmData.rotaryCounter = alarmData.alarmMinutes;
            }
            alarmData.rotaryInitCounter = false;
          }
          rotaryUpdateAlarm();

        display_setAlarm();
        goFromSetAlarm();
        break;
    
      case FSM_TIMER:
    
        display_timer();
        goFromTimer();
        break;
    
      case FSM_SETTIMER:

        //routine to inizialize the counter of the rotary when you want to change the time
          if (alarmData.rotaryInitCounter) {
            if (alarmData.twoStepSet == 0) {
              alarmData.rotaryCounter = alarmData.timerMinutes;
            } else {
              alarmData.rotaryCounter = alarmData.timerSeconds;
            }
            alarmData.rotaryInitCounter = false;
          }
          rotaryUpdateTimer();

        display_setTimer();
        goFromSetTimer();
        break;

      case FSM_RING:
          display_ring();

        break;
    } 

    
    //print state
      if (alarmData.prevStateFSM != alarmData.stateFSM) {

        //print new state
          printState(alarmData.stateFSM);
          
        //clear lcd
          lcd.clear();
          
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

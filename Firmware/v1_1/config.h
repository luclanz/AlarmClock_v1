#ifndef config_h
#define config_h

#include "Arduino.h"

//IOs ---------------------------------------------------------------------------------
  // PUSHBUTTON
    #define BT_TOP 7    //CONSTRAINT: pin is unsigned nibble -> range 0 to 15 
    #define BT_UP 6
    #define BT_DOWN 5

  // INTERRUPT FOR RTC
    #define RTC_INTERRUPT_PIN 2
    
  // LCD MODULE
    #define LCD_RST A0      //10k ohm level shifter
    #define LCD_CE A1       //220 ohm level shifter   
    #define LCD_DC 8        //10k ohm level shifter
    #define LCD_DIN A3      //10k ohm level shifter 
    #define LCD_CLK A2      //10k ohm level shifter
    #define LCD_LIGHT 10    //330 ohm level shifter

  // ROTARY ENCODER
    #define ROT_CLK 2
    #define ROT_DT 3


//CONSTANTS---------------------------------------------------------------------------------
  // internal pulse
    #define TIMEDELAY 2000
    #define PULSE 400
  // FSM
    #define FSM_RST 0
    #define FSM_HOME 1
    #define FSM_SETTIME 2
    #define FSM_ALARM 3
    #define FSM_SETALARM 4
    #define FSM_TIMER 5
    #define FSM_SETTIMER 6

#endif

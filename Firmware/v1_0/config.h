#ifndef config_h
#define config_h

#include "Arduino.h"

//IOs ---------------------------------------------------------------------------------
  // PUSHBUTTON
    #define BT_TOP 7    // might plan on using analog pin if needed
    #define BT_UP 6
    #define BT_DOWN 5
  // DS3231
    #define RTC_INTERRUPT 2

  // LCD MODULE
    #define LCD_CLK 8
    #define LCD_MOSI 9
    #define LCD_DC 10
    #define LCD_CS 11
    #define LCD_RST 12

//FSM ---------------------------------------------------------------------------------
  #define FSM_RST 0
  #define FSM_HOME 1
  #define FSM_SETTIME 2
  #define FSM_ALARM 3
  #define FSM_SETALARM 4
  #define FSM_TIMER 5
  #define FSM_SETTIMER 6

  int stateFSM = 0;
  int prevStateFSM = 0;


#endif

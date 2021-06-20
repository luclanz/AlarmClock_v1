#ifndef config_h
#define config_h

#include "Arduino.h"

//IOs ---------------------------------------------------------------------------------
  // PUSHBUTTON
    #define BT_TOP 7    // might plan on using analog pin if needed
    #define BT_UP 6
    #define BT_DOWN 5
  // DS3231
//    #define RTC_INTERRUPT 2
//    #define RTC_SCL A5
//    #define RTC_SDA A4
  // LCD MODULE
    #define LCD_CLK A2      //10k ohm level shifter
    #define LCD_DIN A3       //10k ohm level shifter
    #define LCD_DC 8        //10k ohm level shifter
    #define LCD_CE A1       //220 ohm level shifter
    #define LCD_RST A0      //10k ohm level shifter
    #define LCD_LIGHT 10    //330 ohm level shifter
  // ROTARY ENCODER
    #define ROT_CLK 2
    #define ROT_DT 3
  // SD MODULE      CARE, THIS STILL GOES WITH 5V, NEED TO ORDER A DIFFERENT MODULE!
//    #define SD_CS 4
//    #define SD_SCK 13
//    #define SD_MOSI 11
//    #define SD_MISO 12
//  // LM386
//    #define LM_IN 9

//CONSTANTS---------------------------------------------------------------------------------
  // internal pulse
    #define TIMEDELAY 2000
  // FSM
    #define FSM_RST 0
    #define FSM_HOME 1
    #define FSM_SETTIME 2
    #define FSM_ALARM 3
    #define FSM_SETALARM 4
    #define FSM_TIMER 5
    #define FSM_SETTIMER 6


#endif

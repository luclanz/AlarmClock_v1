#ifndef config_h
#define config_h

#include "Arduino.h"

//IOs ---------------------------------------------------------------------------------
  // PUSHBUTTON           CONSTRAINT: pin is unsigned nibble -> range 0 to 15 <- NOT ANYMORE!!! 
    #define BT_TOP 7      // TODO: might plan on making this into an external interrupt so I can wake this up (during pow management)
    #define BT_UP 8
    #define BT_DOWN 9

  // INTERRUPT FOR RTC
    #define RTC_INTERRUPT_PIN 2
    
  // LCD MODULE
    #define LCD_RST A0      //10k ohm level shifter
    #define LCD_CE A1       //220 ohm level shifter   //SPI CE
    #define LCD_DC A5        //10k ohm level shifter   //SPI MISO: 12 << Those three need to have different pins assigned to avoid conflict with SD.h / TMRcpm.h
    #define LCD_DIN A4      //10k ohm level shifter   //SPI MOSI: 11
    #define LCD_CLK A3      //10k ohm level shifter   //SPI CLK: 13
    #define LCD_LIGHT A2    //330 ohm level shifter

  // SD MODULE
    #define SD_CS 4
    #define SD_SCK 13
    #define SD_MOSI 11
    #define SD_MISO 12

  // LM386
    #define LM_IN 10

  // ROTARY ENCODER
    #define ROT_CLK 6       //Those two pin are FIXED by the mask / PCINT setup (need to tweak bits if you want to change this)
    #define ROT_DT 5

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
    #define FSM_RING 7

#endif

#ifndef config_h
#define config_h

#include "Arduino.h"

//IOs ---------------------------------------------------------------------------------
  // PUSHBUTTON           CONSTRAINT: pin is unsigned nibble -> range 0 to 15 <- NOT ANYMORE!!! 
    #define BT_TOP 7      // TODO: might plan on making this into an external interrupt so I can wake this up (during pow management)
    #define BT_UP A5
    #define BT_DOWN A4

  // INTERRUPT FOR RTC
    #define RTC_INTERRUPT_PIN 2
    
  // LCD MODULE
    #define LCD_RST A0      //10k ohm level shifter
    #define LCD_CE A1       //220 ohm level shifter   //SPI CE
    #define LCD_DC 8        //10k ohm level shifter   //SPI MISO: 12
    #define LCD_DIN A3      //10k ohm level shifter   //SPI MOSI: 11
    #define LCD_CLK A2      //10k ohm level shifter   //SPI CLK: 13
    #define LCD_LIGHT 10    //330 ohm level shifter

  // SD MODULE
    #define SD_CS 4
    #define SD_SCK 13
    #define SD_MOSI 11
    #define SD_MISO 12

  // LM386
    #define LM_IN 9

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

#endif

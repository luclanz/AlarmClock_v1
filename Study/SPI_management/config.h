#ifndef config_h
#define config_h

#include "Arduino.h"

//IOs ---------------------------------------------------------------------------------
  // PUSHBUTTON
    #define BT_TOP 7
  // LCD MODULE
    #define LCD_RST A0      //10k ohm level shifter
    #define LCD_CE A1       //220 ohm level shifter   //SPI CE
    #define LCD_DC 5        //10k ohm level shifter   //SPI MISO: 12, w/ 12 doesn't seem to work
    #define LCD_DIN 11      //10k ohm level shifter   //SPI MOSI: 11, previous 11
    #define LCD_CLK 13      //10k ohm level shifter   //SPI CLK: 13, previous A2
    #define LCD_LIGHT A2    //330 ohm level shifter

  // SD MODULE
    #define SD_CS 4
    #define SD_SCK 13
    #define SD_MOSI 11 //11
    #define SD_MISO 12 // 12

  // LM386
    #define LM_IN 10

//CONSTANTS---------------------------------------------------------------------------------

#endif

#ifndef config_h
#define config_h

#include "Arduino.h"

//IOs ---------------------------------------------------------------------------------
  // PUSHBUTTON
    #define BT_TOP 7
  // LCD MODULE
    #define LCD_RST A0      //10k ohm level shifter
    #define LCD_CE A1       //220 ohm level shifter   //SPI CE
    #define LCD_DC A5        //10k ohm level shifter   //SPI MISO: 12, previaus 12
    #define LCD_DIN A4      //10k ohm level shifter   //SPI MOSI: 11, previous 11
    #define LCD_CLK A3      //10k ohm level shifter   //SPI CLK: 13, previous A2
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

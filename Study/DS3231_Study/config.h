#ifndef config_h
#define config_h

#include "Arduino.h"


  /*
    DS3231
  VDD connected to 3.3V
  SDA, SCL connected to the respecting pin on Arduino UNO
  SQW connected to PIN2 (which has it's own interrupt
  32K is kept disabled
  */

  // the pin that is connected to SQW
  #define CLOCK_INTERRUPT_PIN 2

  /*
    Alarm notes: 

    DS3231Alarm1Mode:
      - DS3231_A1_Minute -> Alarm when minutes and seconds match
      - DS3231_A1_hour -> Alarm when hours, minutes and seconds match <--   THIS IS GOING TO BE USED FOR THE TIMER / ALSO FOR POWER SAVING

    DS3231Alarm2Mode:
      - DS3231_A2_Hour -> Alarm when hours and minutes match <-- THIS IS GOING TO BE USED FOR THE ALAR
  */


#endif

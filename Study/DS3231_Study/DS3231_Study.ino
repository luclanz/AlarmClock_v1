//LIBRARIES
#include <RTClib.h>
#include "config.h"

RTC_DS3231 rtc;

bool a = 0;


void setup() {
    Serial.begin(9600);

    rtc_setup(CLOCK_INTERRUPT_PIN);

    rtc_set_timer (15);
    rtc_set_alarm(0,1);

//    Serial.print(rtc_hours_to_alarm(21, 12, 18 < 49));
//    Serial.print(":");
//    Serial.println(rtc_minutes_to_alarm(49, 18));

}

void loop() {
    // print current time
    char date[10] = "hh:mm:ss";
    rtc.now().toString(date);
    //date[5] = '\0';
    Serial.print(date);
    // the value at SQW-Pin (because of pullup 1 means no alarm)
//    Serial.print(" SQW: ");
//    Serial.print(digitalRead(CLOCK_INTERRUPT_PIN));
    // whether a alarm happened happened
    Serial.print(" Alarm1: ");
    Serial.print(rtc.alarmFired(1));
    Serial.print(" Alarm2: ");
    Serial.println(rtc.alarmFired(2));

    //check alarm flags
    if(rtc.alarmFired(1)) {
      rtc.clearAlarm(1);
      rtc.disableAlarm(1);
      Serial.println("Alarm1 for the timer cleared");
    }
    
    if(rtc.alarmFired(2)) {
      rtc.clearAlarm(2);
      rtc.disableAlarm(2);
      Serial.println("Alarm2 for the alarm cleared");
    }

    delay(5000);
}

/*static uint8_t read_i2c_register(uint8_t addr, uint8_t reg) {
    Wire.beginTransmission(addr);
    Wire.write((byte)reg);
    Wire.endTransmission();

    Wire.requestFrom(addr, (byte)1);
    return Wire.read();
}*/

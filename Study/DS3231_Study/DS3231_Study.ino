//LIBRARIES
#include <RTClib.h>
#include "config.h"

RTC_DS3231 rtc;



void setup() {
    Serial.begin(9600);

    rtc_setup(CLOCK_INTERRUPT_PIN);

    rtc_set_timer_alarm (10);

    Serial.print(rtc_hours_to_alarm(21, 12, 18 < 49));
    Serial.print(":");
    Serial.println(rtc_minutes_to_alarm(49, 18));

}

void loop() {
//    // print current time
//    char date[10] = "hh:mm:ss";
//    rtc.now().toString(date);
//    Serial.print(date);
//    // the value at SQW-Pin (because of pullup 1 means no alarm)
//    Serial.print(" SQW: ");
//    Serial.print(digitalRead(CLOCK_INTERRUPT_PIN));
//    // whether a alarm happened happened
//    Serial.print(" Alarm1: ");
//    Serial.print(rtc.alarmFired(1));
//    Serial.print(" Alarm2: ");
//    Serial.println(rtc.alarmFired(2));
//    // control register values (see https://datasheets.maximintegrated.com/en/ds/DS3231.pdf page 13)
//    // Serial.print(" Control: 0b");
//    // Serial.println(read_i2c_register(DS3231_ADDRESS, DS3231_CONTROL), BIN);
//    
//    // resetting SQW and alarm 1 flag
//    // using setAlarm1, the next alarm could now be configurated
//    if(rtc.alarmFired(1)) {
//        rtc.clearAlarm(1);
//        Serial.println("Alarm cleared");
//    }
//    
//    delay(2000);
}

void onAlarm() {
    Serial.println("Alarm occured!");
}

/*static uint8_t read_i2c_register(uint8_t addr, uint8_t reg) {
    Wire.beginTransmission(addr);
    Wire.write((byte)reg);
    Wire.endTransmission();

    Wire.requestFrom(addr, (byte)1);
    return Wire.read();
}*/

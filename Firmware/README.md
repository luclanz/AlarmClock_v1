# Firmware Description

    ###### As of the 12/21/21 the firmware (v1.1) of the Alarm clock is complete.

    There have been some issues with the management of the SPI for both the SD card and the LCD display but now it is solved. There are however still some issues like:
        * In case of reset, the alarm values are not saved and thus get cancelled and reinitialized

## New step: Power Management

    With the new firmware (v1.2) the aim is to reduce power consumption in order to be able to power the alarm clock with a standard 9V lipo battery for at least 3 months. This is going to be done by:
        * stripping the Arduino board
        * using a sleep / wake routine

    After this I'll have to solve some reliability issues, like resuming from reset, led indicator when battery is low ect..

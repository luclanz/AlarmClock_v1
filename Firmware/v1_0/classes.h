//Thanks to PaulMurrayCbr for the basic template for this class <3 
//(from forum.ardiuno.cc)

#ifndef classes_h
#define classes_h

#include "Arduino.h"

class Button {
// but.setup(), but.poll() <- looks what is happening to the button
// I can access to the public bool (buttonClicked, buttonHolded) to check what has happened
  private:
    const byte pin;
    const char* name;

    byte state;
    
    uint32_t debounceMs;
    
    static const uint8_t DEBOUNCE_ms = 50;             //   static const uint32_t DEBOUNCE_ms = 50; old line
    static const uint16_t HOLD_ms = 1500;               //   static const uint32_t HOLD_ms = 1500;

    uint32_t prevClickMs;
    uint32_t holdStartMs;

    boolean holdFired;

  public:

    boolean buttonClicked, buttonHolded;
    
    Button (const char *name, const byte pin) : pin(pin), name(name) {}


//------------------------------------------ SETUP BUTTON -------------------------------------------------------------
    void setup() {
      pinMode(pin, INPUT_PULLUP);
      Serial.print(F("Button "));
      Serial.print(name);
      Serial.println(F(" set up."));

      state = digitalRead(pin);
      debounceMs = millis();   
    }
//------------------------------------------ BUTTON POLLING -----------------------------------------------------------
    void poll() {
      
      buttonClicked = false;
      buttonHolded = false;
      
      if (millis() - debounceMs < DEBOUNCE_ms) return;
      
      byte prevState = state;
      state = digitalRead(pin);

      if (state !=prevState) {
        debounceMs = millis();
      }

      if (state == HIGH && prevState == LOW) {
//        Serial.print("Button ");                                          //button has been released
//        Serial.print(name);
//        Serial.println(" released.");        

        if (!holdFired) {
//          Serial.print("Button ");                                        //button has been clicked
//          Serial.print(name);
//          Serial.println(" clicked");
          
          buttonClicked = true;
//          Serial.println(buttonClicked);
//          Serial.println(buttonHolded);
        }

        prevClickMs = millis();


      }
      else if (state == LOW && prevState == HIGH) {
        //Serial.print("Button ");                                          //button has been pressed
        //Serial.print(name);
        //Serial.println(" pressed.");

        //start the hold counter

        holdStartMs = millis();
        holdFired = false;

      }
      else if (state == LOW && prevState == LOW) {
        //button is being held. Do we have a hold event?

        if (!holdFired && millis() - holdStartMs >= HOLD_ms) {
//          Serial.print("Button ");                                        //button had been short holded
//          Serial.print(name);
//          Serial.println(" holded");
          
          buttonHolded = true;
//          Serial.println(buttonClicked);
//          Serial.println(buttonHolded);

          holdFired = true;
        }
      }

    }

};

#endif

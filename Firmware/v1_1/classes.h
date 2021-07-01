//Thanks to PaulMurrayCbr for the basic template for this class <3 
//(from forum.ardiuno.cc)

#ifndef classes_h
#define classes_h

class Button {
  
// but.setup(), but.poll() <- looks what is happening to the button
// I can access to the public bool (buttonClicked, buttonHolded) to check what has happened

  private:
    
    const byte pin :4;
    byte state :1;
    
    uint16_t debounceMs;
    
    static const uint8_t DEBOUNCE_ms = 50;
    static const uint16_t HOLD_ms = 1250;

    uint16_t prevClickMs;
    uint16_t holdStartMs;

    boolean holdFired :1;

  public:

    boolean buttonClicked :1, buttonHolded :1;
    
    Button (const byte pin) : pin(pin) {}


//------------------------------------------ SETUP BUTTON -------------------------------------------------------------
    void setup() {
      pinMode(pin, INPUT_PULLUP);

//        Serial.print(F("Button "));
//        Serial.print(pin);
//        Serial.print(F(" set up. "));

      state = digitalRead(pin);
      debounceMs = millis();   
    }
//------------------------------------------ BUTTON POLLING -----------------------------------------------------------
    void poll() {
      //init state variables
        buttonClicked = false;
        buttonHolded = false;

      uint16_t t = millis() & 0x0000FFFF; 

      //debounce test: I want to wait DEBOUNCE_ms from the first time the state went up, otherwise return for the next polling.
        if (t - debounceMs < DEBOUNCE_ms) return;
      //now the signal has been decounced correctly


      //save the previous state and get the new one
        byte prevState = state;
        state = digitalRead(pin);

      //update the debounce ms variable
        if (state !=prevState) {
          debounceMs = t;
        }


      if (state == HIGH && prevState == LOW) {
        
        //button has been released

        if (!holdFired) {
          
          //button has been clicked
          buttonClicked = true;
          
//          Serial.print(F("Button "));                                        
//          Serial.print(pin);
//          Serial.println(F(" clicked"));
        }

        //save time
          prevClickMs = t;
      }
   
      else if (state == LOW && prevState == HIGH) {

        //button has been pressed
        
        //start the hold counter
        holdStartMs = t;
        holdFired = false;

      }
      else if (state == LOW && prevState == LOW) {
        
        //button is being held. Do we have a hold event?

        if (!holdFired && t - holdStartMs >= HOLD_ms) {
          
          //button had been short holded
//              Serial.print(F("Button "));                                        
//              Serial.print(pin);
//              Serial.println(F(" holded"));
            
          buttonHolded = true;
          holdFired = true;
        }
      }
    }
};

#endif




// IMPROVED --> FROM 17bytes down to 8bytes for each obj
// this new button management system uses 632byte of flash memory and 24bytes of SRAM

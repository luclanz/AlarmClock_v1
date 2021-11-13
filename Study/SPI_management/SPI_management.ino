//Libraries ---------------------------------------------------------------------
  #include <U8x8lib.h>
  #include <SPI.h>
  #include "SD.h"
  #include "TMRpcm.h"


//Files -------------------------------------------------------------------------
  #include "config.h"
  #include "classes.h"

//Declaration -------------------------------------------------------------------
  //Display
    U8X8_PCD8544_84X48_4W_SW_SPI lcd(LCD_CLK, LCD_DIN, LCD_CE, LCD_DC, LCD_RST); 
    
  //Button Variables
    Button topButton(BT_TOP);

  //Speaker & SD
    TMRpcm music;


void setup() {
  
  //buttons
    topButton.setup();
  
  //Serial port -> Open
    Serial.begin(9600);
    while (!Serial) {}

  //LCD
    display_setup();
    display_somethingElse();

  //SD and Speaker
    sdAndSpeaker_setup();

}

void loop() {

  topButton.poll();

  if (topButton.buttonClicked) {
    //music.disable();
    display_something();  
  }

  
}

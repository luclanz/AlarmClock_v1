//Libraries ---------------------------------------------------------------------
  #include <SPI.h>
  #include <NOKIA5110_TEXT.h>
  #include "SD.h"
  #include "TMRpcm.h"


//Files -------------------------------------------------------------------------
  #include "config.h"
  #include "classes.h"

//Declaration -------------------------------------------------------------------
  //Display
    NOKIA5110_TEXT lcd(LCD_RST, LCD_CE, LCD_DC);
    
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
    music.pause();
    display_something(); 
    music.pause(); 
  }

  
}

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


void setup() {
  
  //buttons
    topButton.setup();
  
  //Serial port -> Open
    Serial.begin(9600);
    while (!Serial) {}

  //LCD
    display_setup();
    display_something();

}

void loop() {
  //Polling
    //topButton.poll();

//  if (topButton.buttonClicked) {
//    lcd.clear();
//    display_somethingElse();
//  }
//
//  if (topButton.buttonHolded) {
//    lcd.clear();
//    display_something();
//  }

// --------------------------------------------------
/*
  CE rimane stranamente sempre alto.... perché?
*/

//  int i;
//
//  if (i == 0) {
//    lcd.clear();
//    display_something();
//    i = 1;
//  }
//  
//  if (i == 1) {
//    lcd.clear();
//    display_somethingElse();
//    i = 0;
//  }
//
//if (!digitalRead(LCD_CE)) {
//  Serial.println("hey");
//}
  
  
}

//LIBs --------------------------------------------------------------------------------
  #include <LCD5110_Graph.h>
//IOs ---------------------------------------------------------------------------------
  // LCD MODULE
    #define LCD_CLK 8
    #define LCD_MOSI 9
    #define LCD_DC 10
    #define LCD_CS 11
    #define LCD_RST 12
//OBJs & Vars -------------------------------------------------------------------------
  LCD5110 myDisplay (LCD_CLK, LCD_MOSI, LCD_DC, LCD_RST, LCD_CS);
    extern uint8_t SmallFont[], TinyFont[], MediumNumbers[], BigNumbers[];
    bool toggle;
//FUNCs -------------------------------------------------------------------------------


void setup() {
  Serial.begin(9600);                                                                                     //DEBUGGING purposes
  //init
    //LCD
      myDisplay.InitLCD(55);
      toggle = true;


}

void loop() {
  // put your main code here, to run repeatedly:
  
}

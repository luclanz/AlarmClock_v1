void display_setup() {
  
  lcd.LCDInit(false, 0xBF, 0x13); // init  the lCD
  lcd.LCDClear(0x00); // Clear whole screen

  pinMode(LCD_LIGHT, OUTPUT);
  digitalWrite(LCD_LIGHT, HIGH);
}


void display_something () {
  lcd.LCDClear(0x00); // Clear whole screen
  lcd.LCDFont(2); // Set the font
  lcd.LCDgotoXY(0, 0); // (go to (X , Y) (0-84 columns, 0-5 blocks) top left corner
  lcd.LCDString("HELLO"); // print
}

void display_somethingElse () {
  lcd.LCDClear(0x00); // Clear whole screen
  lcd.LCDFont(8);
  lcd.LCDgotoXY(0, 2); 
  lcd.LCDString("10:15"); // print
}

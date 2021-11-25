void display_setup() {
  
  lcd.begin();

  pinMode(LCD_LIGHT, OUTPUT);
  digitalWrite(LCD_LIGHT, HIGH);
}


void display_something () {
    lcd.setFont(u8x8_font_chroma48medium8_r);
    lcd.drawString(1,2, "Coglione");
}

void display_somethingElse () {
    lcd.setFont(u8x8_font_chroma48medium8_r);
    lcd.drawString(1,2, "Pirla");
}

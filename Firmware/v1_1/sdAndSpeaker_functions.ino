void sdAndSpeaker_setup() {

    music.speakerPin = LM_IN;
    //music.disable();
    //digitalWrite(LM_IN, HIGH);
    //Serial.println(digitalRead(LM_IN));

            // those line creates a conflict w/in the spi interface. Once initializing the SD I won't be able to use the LCD...
    if (!SD.begin(SD_CS)) {
    Serial.println("SD fail");
    Serial.flush();
    abort();
    //return;
    }
    
//    music.setVolume(4);
//    music.play("Daybreak.wav");
//    music.quality(2);
    
}

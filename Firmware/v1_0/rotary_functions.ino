// this file will contain every function used to control the rotary encoder
// everything that starts with rotaryEtc..()

void rotarySetupRoutine(){
  // Set encoder pins as inputs
  pinMode(ROT_CLK,INPUT);
  pinMode(ROT_DT,INPUT);
  // Read the initial state of CLK
  rotaryLastStateCLK = digitalRead(ROT_CLK);
  // activate interrupt
  attachInterrupt(digitalPinToInterrupt(ROT_CLK), rotaryPolling, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ROT_DT), rotaryPolling, CHANGE);
  
}
void rotaryPolling(){
  // Read the current state of CLK
  rotaryCurrentStateCLK = digitalRead(ROT_CLK);

  // If last and current state of CLK are different, then pulse occurred
  // React to only 1 state change to avoid double count
  if (rotaryCurrentStateCLK != rotaryLastStateCLK  && rotaryCurrentStateCLK == 1){

    // If the DT state is different than the CLK state then
    // the encoder is rotating CCW so decrement
    if (digitalRead(ROT_DT) != rotaryCurrentStateCLK) {
      rotaryCounter --;
      rotaryCurrentDir ="CCW";
    } else {
      // Encoder is rotating CW so increment
      rotaryCounter ++;
      rotaryCurrentDir ="CW";
    }

    Serial.print("Direction: ");
    Serial.print(rotaryCurrentDir);
    Serial.print(" | Counter: ");
    Serial.println(rotaryCounter);
  }

  // Remember last CLK state
  rotaryLastStateCLK = rotaryCurrentStateCLK;
  
  // Put in a slight delay to help debounce the reading
  //delay(1);
}

void rotaryUpdateTime() {

}

void rotaryUpdateAlarm() {

  if (alarmClockData.twoStepSet == 0) {
    //update hours

    // alarmClockData.alarmHours = rotaryCounter;

    return;
  }

  if (alarmClockData.twoStepSet == 1) {
    //update minutes

    return;
  }
}

void rotaryUpdateTimer() {
  
}

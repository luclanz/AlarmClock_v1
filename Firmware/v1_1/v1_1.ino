#include "classes.h"
#include "config.h"


  Button topButton(BT_TOP);
  Button upButton(BT_UP);
  Button downButton(BT_DOWN);


void setup() {

  //Serial port -> Open
    Serial.begin(9600);
    while (!Serial) {}
  
  //init
    //buttons
      topButton.setup();
      upButton.setup();
      downButton.setup();

}

void loop() {

    topButton.poll();
    upButton.poll();
    downButton.poll();

}

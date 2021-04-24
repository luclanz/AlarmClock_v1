//LIBs --------------------------------------------------------------------------------
  #include <LCD5110_Graph.h>
//HEADERs -----------------------------------------------------------------------------
  #include "classes.h"
  #include "config.h"

//Declaration ------------------------------------------------------------------------
  Button topButton("TOP", BT_TOP);
  Button upButton("UP", BT_UP);
  Button downButton("DOWN", BT_DOWN);

void setup() {
  Serial.begin(9600);
  //init
    //buttons
      topButton.setup();
      upButton.setup();
      downButton.setup();


}

void loop() {
  // put your main code here, to run repeatedly:
  
}

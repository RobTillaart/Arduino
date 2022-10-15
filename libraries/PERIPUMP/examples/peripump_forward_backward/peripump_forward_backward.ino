//
//    FILE: peripump_forward_backward.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/PERIPUMP.git
//


#include "PERIPUMP.h"

PERIPUMP pump(5);


//  add switches between pin and GND.
const int STOP_PIN     = 2;
const int FORWARD_PIN  = 3;
const int BACKWARD_PIN = 4;

//  prevent sudden reversal.
int mode = 0; // 0 == stop,  1 == forward,  -1 == backward


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PERIPUMP_LIB_VERSION: ");
  Serial.println(PERIPUMP_LIB_VERSION);

  pinMode(STOP_PIN, INPUT_PULLUP);
  pinMode(FORWARD_PIN, INPUT_PULLUP);
  pinMode(BACKWARD_PIN, INPUT_PULLUP);

  pump.begin();
}


void loop()
{
  if (digitalRead(STOP_PIN) == LOW)
  {
    pump.stop();
    mode = 0;
  }
  if (digitalRead(FORWARD_PIN) == LOW)
  {
    // prevent sudden reversal
    if (mode == 1) pump.forward();
    else pump.stop();
    mode = 1;
  }
  if (digitalRead(BACKWARD_PIN) == LOW)
  {
    // prevent sudden reversal
    if (mode == -1) pump.backward();
    else pump.stop();
    mode = -1;
  }

  //  debounce etc
  delay(100);
}


//  -- END OF FILE --

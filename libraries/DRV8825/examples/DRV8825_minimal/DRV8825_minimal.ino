//
//    FILE: DRV8825_minimal.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2022-11-14

#include "DRV8825.h"

DRV8825 stepper;
const int DIRECTION_PIN = 4;
const int STEP_PIN = 5;


//  connect to ground if pushed
const int FORWARD_PIN = 8;
const int BACKWARD_PIN = 9;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("DRV8825_LIB_VERSION: ");
  Serial.println(DRV8825_LIB_VERSION);

  stepper.begin(DIRECTION_PIN, STEP_PIN);

  pinMode(FORWARD_PIN, INPUT_PULLUP);
  pinMode(BACKWARD_PIN, INPUT_PULLUP);
}


void loop()
{
  //  read both buttons
  bool fw = digitalRead(FORWARD_PIN) == LOW;
  bool bw = digitalRead(BACKWARD_PIN) == LOW;

  // process the button state
  if (fw && bw)  //  both buttons pressed
  {
     Serial.println("not allowed, please release both buttons.");
     delay(1000);  //  block  
  }
  else if (fw)
  {
    stepper.setDirection(DRV8825_CLOCK_WISE);
    delay(50);
    stepper.step();
    delay(50);
  }
  else if (bw)
  {
    stepper.setDirection(DRV8825_COUNTERCLOCK_WISE);
    delay(50);
    stepper.step();
    delay(50);
  }

}


// -- END OF FILE --

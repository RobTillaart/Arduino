//
//    FILE: PID_basic.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//
//  connect an LED to the PWM pin
//  connect a potentiometer to A0
//  play :)


#include "PID_RT.h"

PID_RT PID;

const int PWM_PIN = 3;  // UNO PWM pin

int op = 0;
float input = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  PID.setPoint(125);
  PID.setOutputRange(0, 255);  // PWM range
  PID.setInterval(50);
  PID.setK(2, 5, 1);
  PID.start();
  
  op = analogRead(A0);
}


void loop()
{
  input = analogRead(A0);
  if (PID.compute(input))
  {
    op = PID.getOutput();
    analogWrite(PWM_PIN, op);
    
    Serial.print(PID.getInput());
    Serial.print('\t');
    Serial.println(op);
  }
}


// -- END OF FILE --


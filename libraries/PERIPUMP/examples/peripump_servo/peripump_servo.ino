//
//    FILE: peripump_servo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test for peri pump with servo library only.
//     URL: https://github.com/RobTillaart/PERIPUMP.git
//


#include "Arduino.h"
#include "Servo.h"

Servo s;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println("PERIPUMP SERVO ONLY TEST");

  s.attach(5);   //  Connect to PIN 5

  //  EXTREMES test
  s.write(0);
  delay(5000);

  s.write(90);
  delay(5000);

  s.write(180);
  delay(5000);

  s.write(0);
  delay(5000);

  //  RANGE test
  for (int i = 0; i <= 180; i += 5)
  {
    Serial.write(i);
    s.write(i);
    delay(5000);
  }

  //  VERY slow test.
  for (int i = 90; i <= 180; i++)
  {
    Serial.write(i);
    s.write(i);
    delay(10000);
  }

  s.write(90);
  delay(2000);
}

void loop()
{
}


//  -- END OF FILE --

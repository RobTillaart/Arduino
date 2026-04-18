//
//    FILE: FSR40X_alarm.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo sketch
//     URL: https://github.com/RobTillaart/FSR40X
//
//   sound an alarm if a weight is removed

#include "FSR40X.h"


FSR40X FSR(A0, 5.0, 1023);

float reference;
uint16_t count = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("FSR40X_LIB_VERSION: ");
  Serial.println(FSR40X_LIB_VERSION);
  Serial.println();

  FSR.begin(10000);
  
  //  measure reference weight
  reference = FSR.readNewton(10);
}


void loop()
{
  float x = FSR.readNewton();
  //  allow 2% noise
  if ((x < (reference * 0.95)) || (x > (reference * 1.05)))
  {
    //  log the timestamp.
    Serial.print(millis());
    Serial.print(": ");
    Serial.print(x);
    Serial.print(": ");
    Serial.println("ALARM!!!");
    //  or any other form of alarm.
  }
  count++;
  if (count >= 10000)
  {
    Serial.print(millis());
    Serial.print(": ");
    Serial.println("alive.");
    count = 0;
  }
}


//  -- END OF FILE --

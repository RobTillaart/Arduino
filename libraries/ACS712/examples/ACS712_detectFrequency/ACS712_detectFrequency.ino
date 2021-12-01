//
//    FILE: ACS712_detectFrequency.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo function
//    DATE: 2021-12-01
//     URL: https://github.com/RobTillaart/


#include "Arduino.h"
#include "ACS712.h"

// Arduino UNO has 5.0 volt with a max ADC value of 1023 steps
// ACS712 5A  uses 185 mV per A
// ACS712 20A uses 100 mV per A
// ACS712 30A uses  66 mV per A
ACS712  ACS(A0, 5.0, 1023, 100);

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
}


void loop()
{
  //  e.g. detect 50 or 60 Hz sinus signal
  //  blocks on bad signals.
  start = micros();
  float frequency = ACS.detectFrequency(45);
  stop = micros();

  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println(frequency, 1);
}


// -- END OF FILE --

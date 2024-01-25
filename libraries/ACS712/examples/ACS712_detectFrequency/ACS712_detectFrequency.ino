//
//    FILE: ACS712_detectFrequency.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo detect frequency + timing indication.
//     URL: https://github.com/RobTillaart/ACS712


#include "ACS712.h"


//  Arduino UNO has 5.0 volt with a max ADC value of 1023 steps
//  ACS712 5A  uses 185 mV per A
//  ACS712 20A uses 100 mV per A
//  ACS712 30A uses  66 mV per A
ACS712  ACS(A0, 5.0, 1023, 100);
//  ESP 32 example (might requires resistors to step down the logic voltage)
//  ACS712  ACS(25, 3.3, 4095, 185);


uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);
  Serial.print("ACS712_LIB_VERSION: ");
  Serial.println(ACS712_LIB_VERSION);
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
  delay(100);
}


//  -- END OF FILE --


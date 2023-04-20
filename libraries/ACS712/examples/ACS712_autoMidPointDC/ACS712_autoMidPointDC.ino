//
//    FILE: ACS712_autoMidPointDC.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo detect DC midpoint.
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

uint16_t midPoint = 0;

void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);
  Serial.print("ACS712_LIB_VERSION: ");
  Serial.println(ACS712_LIB_VERSION);
  delay(10);

  //  might be different 1 cycle or 100.
  start = micros();
  midPoint = ACS.autoMidPointDC(1);
  stop = micros();
  Serial.println("ACS.autoMidPointDC()");
  Serial.print("us:\t");
  Serial.println(stop - start);
  Serial.print("MP 1:\t");
  Serial.println(midPoint);
  
  midPoint = ACS.autoMidPointDC(100);
  Serial.print("MP 100:\t");
  Serial.println(midPoint);
}


void loop()
{
}


//  -- END OF FILE --

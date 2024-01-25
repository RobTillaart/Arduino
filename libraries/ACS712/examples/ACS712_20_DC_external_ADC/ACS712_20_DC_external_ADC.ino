//
//    FILE: ACS712_20_DC_external_ADC.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo to measure mA DC with external ADC
//     URL: https://github.com/RobTillaart/ACS712
//
//  see also ACS712_ESP32_external_ADC.ino
//  use with Arduino Serial Plotter

#include "ACS712.h"


//  Arduino UNO has 5.0 volt with a max ADC value of 1023 steps
//  ACS712 5A  uses 185 mV per A
//  ACS712 20A uses 100 mV per A
//  ACS712 30A uses  66 mV per A


ACS712  ACS(A0, 5.0, 1023, 100);
//  ESP 32 example (might requires resistors to step down the logic voltage)
//  ACS712  ACS(25, 3.3, 4095, 185);


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);
  Serial.print("ACS712_LIB_VERSION: ");
  Serial.println(ACS712_LIB_VERSION);

  ACS.setADC(testADC, 10, 1023);
  
  //  ACS.autoMidPoint();
  //  Serial.println(ACS.getMidPoint());
}


void loop()
{
  int mA = ACS.mA_DC();
  Serial.println(mA);
  delay(1000);
}

//  wrapper needed for external analogRead()
//  as casting behaviour is undefined between different function signatures.
uint16_t testADC(uint8_t p)
{
  //  simulation
  return 600 + p;
  //  replace with an external ADC call.
  //  return ADS.readADC(p);
  //  return analogRead(p + 1);  // use another internal ADC
}


//  -- END OF FILE --

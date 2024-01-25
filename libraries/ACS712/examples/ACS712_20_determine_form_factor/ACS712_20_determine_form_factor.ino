//
//    FILE: ACS712_20_determine_form_factor.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo to determine form factor
//     URL: https://github.com/RobTillaart/ACS712


#include "ACS712.h"


//  Arduino UNO has 5.0 volt with a max ADC value of 1023 steps
//  ACS712 5A  uses 185 mV per A
//  ACS712 20A uses 100 mV per A
//  ACS712 30A uses  66 mV per A


ACS712  ACS(A0, 5.0, 1023, 100);
//  ESP 32 example (might requires resistors to step down the logic voltage)
//  ACS712  ACS(25, 3.3, 4095, 185);

int i = 0;

void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);
  Serial.print("ACS712_LIB_VERSION: ");
  Serial.println(ACS712_LIB_VERSION);

  ACS.autoMidPoint();
}


void loop()
{

  Serial.println("\n\nAC \tP2P \tCREST");
  for (int i = 0; i < 10; i++)
  {
    float mA_1 = ACS.mA_AC_sampling();
    float mA_2 = ACS.mA_peak2peak();
    float crest = 2.0 * mA_1 / mA_2;
    Serial.print(mA_1);
    Serial.print("\t");
    Serial.print(mA_2);
    Serial.print("\t");
    Serial.println(crest, 4);
    delay(100);
  }
  delay(100);
}


//  -- END OF FILE --

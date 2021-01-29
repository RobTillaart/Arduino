//
//    FILE: ADS_continuous.ino
//  AUTHOR: Rob.Tillaart
// VERSION: 0.1.1
// PURPOSE: read analog input
//

// test
// connect 1 potmeter
//
// GND ---[   x   ]------ 5V
//            |
//
// measure at x (connect to AIN0).


#include "ADS1X15.h"

// choose you sensor
// ADS1013 ADS(0x48);
// ADS1014 ADS(0x48);
// ADS1015 ADS(0x48);
// ADS1113 ADS(0x48);
// ADS1114 ADS(0x48);
ADS1115 ADS(0x48);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("ADS1X15_LIB_VERSION: ");
  Serial.println(ADS1X15_LIB_VERSION);

  ADS.begin();
  ADS.setGain(0);      // 6.144 volt
  ADS.setDataRate(7);  // fast
  ADS.setMode(0);      // continuous mode
  ADS.readADC(0);      // first read to trigger
}

void loop()
{
  Serial.println(ADS.getValue());
}

// -- END OF FILE --
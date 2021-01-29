//
//    FILE: ADS_read_RDY.ino
//  AUTHOR: Rob.Tillaart
// VERSION: 0.1.0
// PURPOSE: read analog inputs - straightforward.
//

// test
// connect 1 potmeter per port.
//
// GND ---[   x   ]------ 5V
//            |
//
// measure at x (connect to AIN0).
//

// EXPERIMENTAL
//
// The RDY pin (or ALERT Pin) is triggered when conversion is ready
//

#include "ADS1X15.h"

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
  ADS.setMode(1);      // continuous mode
  ADS.readADC(0);      // first read to trigger
  
  // set the thresholds to Trigger RDY pin
  ADS.setComparatorThresholdLow(0x0000);
  ADS.setComparatorThresholdHigh(0x0200);
  ADS.setComparatorQueConvert(0);             // enable RDY pin !!
  ADS.setComparatorLatch(0);
}

void loop() 
{
  ADS.setGain(0);

  int16_t val_0 = ADS.readADC(0);

  float f = ADS.toVoltage(1);   // voltage factor

  Serial.print("\tAnalog0: ");
  Serial.print(val_0);
  Serial.print('\t');
  Serial.println(val_0 * f, 3);
  
  delay(1000);
}

// -- END OF FILE --

//
//    FILE: ADS_read_async_rdy.ino
//  AUTHOR: Rob.Tillaart
// PURPOSE: read analog inputs - straightforward.
//     URL: https://github.com/RobTillaart/ADS1X15

//  test
//  connect 1 potmeter per port.
//
//  GND ---[   x   ]------ 5V
//             |
//
//  measure at x (connect to AIN0).
//

//  EXPERIMENTAL
//
//  The ALERT/RDY pin is triggered when threshold is exceeded.
//


#include "ADS1X15.h"

ADS1115 ADS(0x48);
float factor = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("ADS1X15_LIB_VERSION: ");
  Serial.println(ADS1X15_LIB_VERSION);

  Wire.begin();

  ADS.begin();
  ADS.setGain(0);            //  6.144 volt

  //  select slow so the led blinks visible for the eye.
  ADS.setDataRate(0);        //  0 = slow   4 = medium   7 = fast
  factor = ADS.toVoltage();  //  voltage factor
  ADS.requestADC(0);

  //  set the thresholds to trigger ALERT/RDY pin when exceeded.
  ADS.setComparatorThresholdLow(0x0000);
  ADS.setComparatorThresholdHigh(0x0200);
  ADS.setComparatorQueConvert(0);  //  enable RDY pin !!
  ADS.setComparatorLatch(0);
}


void loop()
{
  if (ADS.isReady())
  {
    //  read the value.
    int16_t value0 = ADS.getValue();
    //  request a new one.
    ADS.requestADC(0);
    //  process the read value.
    Serial.print("\tAnalog0: ");
    Serial.print(value0);
    Serial.print('\t');
    Serial.println(value0 * factor, 3);
  }
  //  simulate other tasks...
  delay(2000);
}


//  -- END OF FILE --


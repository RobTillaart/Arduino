//
//    FILE: ADS1113_getMaxVoltage.ino
//  AUTHOR: Rob.Tillaart
// PURPOSE: read analog inputs - straightforward.
//     URL: https://github.com/RobTillaart/ADS1X15

//  test for issue #68 behaviour ADS1113 / ADS1013
//
//  connect 1 potmeter per port.
//
//  GND ---[   x   ]------ 5V
//             |
//
//  measure at x (connect to AIN0).


#include "ADS1X15.h"

ADS1113 ADS(0x48);


void setup() 
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("ADS1X15_LIB_VERSION: ");
  Serial.println(ADS1X15_LIB_VERSION);

  Wire.begin();
  ADS.begin();

  for (int g = 0; g < 8; g++)
  {
    ADS.setGain(g);
    Serial.print(g);
    Serial.print('\t');
    Serial.print(ADS.getGain());             //  should all print 2
    Serial.print('\t');
    Serial.println(ADS.getMaxVoltage(), 3);  //  should all print 2.048
  }
}


void loop() 
{
}


//  -- END OF FILE --

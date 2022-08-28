//
//    FILE: INA226_compare_normalize.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: show difference in normalize flag
//     URL: https://github.com/RobTillaart/INA226


#include "INA226.h"
#include "Wire.h"

INA226 INA(0x40);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  Wire.begin();
  if (!INA.begin() )
  {
    Serial.println("could not connect. Fix and Reboot");
  }
  INA.setMaxCurrentShunt(79, 0.001, true);
  Serial.print("\nNormalize = true\n");
  Serial.print("MaxCurrent:\t");
  Serial.println(INA.getMaxCurrent(), 3);
  Serial.print("currentLSB:\t");
  Serial.println(INA.getCurrentLSB(), 5);

  INA.setMaxCurrentShunt(79, 0.001, false);
  Serial.print("\nNormalize = false\n");
  Serial.print("MaxCurrent:\t");
  Serial.println(INA.getMaxCurrent(), 3);
  Serial.print("currentLSB:\t");
  Serial.println(INA.getCurrentLSB(), 5);
}


void loop()
{
}


// -- END OF FILE --

//
//    FILE: INA236_compare_normalize.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: show difference in normalize flag
//     URL: https://github.com/RobTillaart/INA236


#include "INA236.h"


INA236 INA(0x40);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("INA236_LIB_VERSION: ");
  Serial.println(INA236_LIB_VERSION);
  Serial.println();

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

  INA.setMaxCurrentShunt(8, 0.01, true);

  INA.setMaxCurrentShunt(8, 0.01, false);

  INA.setMaxCurrentShunt(1, 0.01, true);

  INA.setMaxCurrentShunt(1, 0.01, false);

  INA.setMaxCurrentShunt(0.5, 0.01, true);

  INA.setMaxCurrentShunt(0.5, 0.001, true);

  Serial.println("done...");
}


void loop()
{
}


//  -- END OF FILE --

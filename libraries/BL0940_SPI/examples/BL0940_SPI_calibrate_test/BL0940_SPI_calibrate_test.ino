//
//    FILE: BL0940_SPI_calibrate_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: verify the formulas against the magic numbers from other lib
//     URL: https://github.com/RobTillaart/BL0940_SPI
//     URL: https://github.com/RobTillaart/printHelpers
//

#include "BL0940_SPI.h"    //  latest develop version.
#include "printHelpers.h"  //  not needed

BL0940_SPI mySensor(5, 6, 7);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("BL0940_SPI_LIB_VERSION: ");
  Serial.println(BL0940_SPI_LIB_VERSION);
  Serial.println();

  SPI.begin();

  mySensor.begin();

  //  calibrate manually 
  //  hard coded values from BL0940_SPI_calibrate.ino  (1/x)
  //  shunt 1 mOhm, voltage reduction factor 3824.53
  mySensor.setVoltageLSB(5.828E-05);
  mySensor.setCurrentLSB(3.759E-06);
  mySensor.setPowerLSB(1.402E-03);
  mySensor.setEnergyLSB(1.634E-04);

  Serial.println("VOLTAGE\t\tCURRENT\t\tPOWER\t\tENERGY");
  
  Serial.print(sci(mySensor.getVoltageLSB(), 4));
  Serial.print("\t");
  Serial.print(sci(mySensor.getCurrentLSB(), 4));
  Serial.print("\t");
  Serial.print(sci(mySensor.getPowerLSB(), 4));
  Serial.print("\t");
  Serial.println(sci(mySensor.getEnergyLSB(), 4));
}

void loop()
{
  delay(2000);
}


//  -- END OF FILE --

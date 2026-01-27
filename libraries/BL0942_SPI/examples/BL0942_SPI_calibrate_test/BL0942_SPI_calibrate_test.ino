//
//    FILE: BL0942_SPI_calibrate_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: verify the formulas against the magic numbers from other lib
//     URL: https://github.com/RobTillaart/BL0942_SPI
//     URL: https://github.com/RobTillaart/printHelpers
//

#include "BL0942_SPI.h"    //  latest develop version.
#include "printHelpers.h"  //  not needed

BL0942_SPI mySensor(4, 5, 6, 7);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("BL0942_SPI_LIB_VERSION: ");
  Serial.println(BL0942_SPI_LIB_VERSION);
  Serial.println();

  SPI.begin();

  mySensor.begin();

  //  calibrate manually - hard coded values from serial lib (1 / x)
  mySensor.setVoltageLSB(6.296E-05);
  mySensor.setCurrentLSB(8.053E-06);
  mySensor.setPowerLSB(3.2354E-03);
  mySensor.setEnergyLSB(3.769E-04);

  Serial.println("VOLTAGE\t\tCURRENT\t\tPOWER\t\tENERGY");
}

void loop()
{
  Serial.print(mySensor.getVoltageLSB(), 4);
  Serial.print("\t");
  Serial.print(mySensor.getCurrentLSB(), 4);
  Serial.print("\t");
  Serial.print(mySensor.getPowerLSB(), 4);
  Serial.print("\t");
  Serial.println(mySensor.getEnergyLSB(), 4);

  delay(2000);
}


//  -- END OF FILE --

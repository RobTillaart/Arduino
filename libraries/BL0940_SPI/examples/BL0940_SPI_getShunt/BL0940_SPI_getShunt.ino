//
//    FILE: BL0940_SPI_getShunt.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: calculate the shunt and voltage divider ratio from constants.
//     URL: https://github.com/RobTillaart/BL0940_SPI
//     URL: https://github.com/RobTillaart/printHelpers


#include "BL0940_SPI.h"
#include "printHelpers.h"  //  


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("BL0940_SPI_LIB_VERSION: ");
  Serial.println(BL0940_SPI_LIB_VERSION);
  Serial.println();

  //  Calibration values not used
  //  float PREF = 309.1;
  //  float EREF = 2653;

  //  Calibration values
  //  float UREF = 15968;
  //  float IREF = 124180;
  //  SHUNT:  4.9432E-04
  //  RATIO:  3.8043E+03

  float UREF = 1 / 6.296E-05;
  float IREF = 1 / 3.98E-06;
  //  SHUNT:  1.0002E-03
  //  RATIO:  3.8246E+03


  float BL0940_VREF          = 1.218;
  float BL0940_MAGIC_CURRENT = 305978000;
  float BL0940_MAGIC_VOLT    = 73989000;
  //  const float BL0940_MAGIC_POWER   = 3537000000;


  float shunt = BL0940_VREF * IREF / (BL0940_MAGIC_CURRENT);
  float ratio = BL0940_MAGIC_VOLT / (BL0940_VREF * UREF);

  Serial.print("SHUNT:\t");
  Serial.println(sci(shunt, 4));
  Serial.print("RATIO:\t");
  Serial.println(sci(ratio, 4));
  Serial.println();

  Serial.println("Done...");
}


void loop()
{
}


//  -- END OF FILE --

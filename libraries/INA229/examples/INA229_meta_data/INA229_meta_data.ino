//
//    FILE: INA229_meta_data.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: dump metadata
//     URL: https://github.com/RobTillaart/INA229

#include "INA229.h"

//  select, dataIn, dataOut, clock == SOFTWARE SPI
INA229 INA(5, 6, 7, 8);
//  select, &SPI === HW SPI
// INA229 INA(9, &SPI);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("INA229_LIB_VERSION: ");
  Serial.println(INA229_LIB_VERSION);
  Serial.println();

  SPI.begin();
  if (!INA.begin() )
  {
    Serial.println("Could not connect. Fix and Reboot");
    while(1);
  }

  INA.setMaxCurrentShunt(10, 0.015);

  //  REGISTER 0
  Serial.print("Manufacturer: ");
  Serial.println(INA.getManufacturer(), HEX);
  Serial.print("DIE_ID: ");
  Serial.println(INA.getDieID(), HEX);
  Serial.print("Revision: ");
  Serial.println(INA.getRevision(), HEX);
  Serial.println();

  Serial.print("\nDone");
}


void loop()
{
}


//  -- END OF FILE --

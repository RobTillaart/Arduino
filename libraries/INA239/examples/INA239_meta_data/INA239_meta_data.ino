//
//    FILE: INA239_meta_data.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: dump metadata
//     URL: https://github.com/RobTillaart/INA239


#include "INA239.h"


//  select, dataIn, dataOut, clock == SOFTWARE SPI
//  INA239 INA(5, 6, 7, &SPI);

//  select, &SPI === HW SPI
INA239 INA(5, &SPI);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println();
  Serial.print("INA239_LIB_VERSION: ");
  Serial.println(INA239_LIB_VERSION);
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

//
//    FILE: INA228_meta_data.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: dump metadata
//     URL: https://github.com/RobTillaart/INA228


#include "INA228.h"


INA228 INA(0x40);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println();
  Serial.print("INA228_LIB_VERSION: ");
  Serial.println(INA228_LIB_VERSION);
  Serial.println();

  Wire.begin();
  if (!INA.begin() )
  {
    Serial.println("Could not connect. Fix and Reboot");
    while(1);
  }

  //  REGISTER 0
  Serial.print("Manufacturer: ");
  Serial.println(INA.getManufacturer());
  Serial.print("DIE_ID: ");
  Serial.println(INA.getDieID());
  Serial.print("Revision: ");
  Serial.println(INA.getRevision());
  Serial.println();

  bool     getManufacturer();
  uint16_t getDieID();
  uint16_t getRevision();


  Serial.print("\n done");
}


void loop()
{
}


//  -- END OF FILE --

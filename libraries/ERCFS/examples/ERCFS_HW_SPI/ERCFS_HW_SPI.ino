//
//    FILE: ERCFS_HW_SPI.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo dump millis + position.
//     URL: https://github.com/RobTillaart/ERCFS
//

#include "ERCFS.h"

ERCFS re(9);  //  hardware SPI

void setup()
{
  while(!Serial);
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("ERCFS_LIB_VERSION: ");
  Serial.println(ERCFS_LIB_VERSION);
  Serial.println();

  SPI.begin();

  bool b = re.begin();
  Serial.print("BEGIN:\t");
  Serial.println(b);
}


void loop()
{
  uint16_t position = re.getRawValue();
  Serial.print(millis());
  Serial.print("\t");
  Serial.println(position);
  delay(50);
}



//  -- END OF FILE --

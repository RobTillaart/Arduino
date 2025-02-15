//
//    FILE: AMT25_HW_SPI.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo dump millis + position.
//     URL: https://github.com/RobTillaart/AMT25
//

#include "AMT25.h"

AMT25 re(9);  //  hardware SPI

void setup()
{
  while(!Serial);
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("AMT25_LIB_VERSION: ");
  Serial.println(AMT25_LIB_VERSION);
  Serial.println();

  SPI.begin();

  bool b = re.begin(14);
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

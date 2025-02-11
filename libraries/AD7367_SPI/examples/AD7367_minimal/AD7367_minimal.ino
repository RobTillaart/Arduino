//
//    FILE: AD7367_minimal.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour
//     URL: https://github.com/RobTillaart/AD7367


#include "AD7367_SPI.h"

//  select, convert, busy, SPI (optional)
//  adjust pins if needed
AD7367_SPI AD(5, 6, 7);

void setup()
{
  while(!Serial);
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AD7367_SPI_LIB_VERSION: ");
  Serial.println(AD7367_SPI_LIB_VERSION);
  Serial.println();

  SPI.begin();

  AD.begin();

  delay(100);
}


void loop()
{
  AD.read();
  Serial.print(AD.getLastADCA());
  Serial.print("\t");
  Serial.println(AD.getLastADCB());
}


//  -- END OF FILE --

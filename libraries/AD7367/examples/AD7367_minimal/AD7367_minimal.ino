//
//    FILE: AD7367_minimal.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour
//     URL: https://github.com/RobTillaart/AD7367


#include "AD7367.h"

//  select, clock, convert, busy, data0, data1
//  adjust pins if needed
AD7367 AD(5, 6, 7, 8, 9, 10);

void setup()
{
  while(!Serial);
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AD7367_LIB_VERSION: ");
  Serial.println(AD7367_LIB_VERSION);
  Serial.println();

  AD.begin();

  delay(100);
}


void loop()
{
  AD.read();
  Serial.print(AD.getValue(0));
  Serial.print("\t");
  Serial.println(AD.getValue(1));
}


//  -- END OF FILE --

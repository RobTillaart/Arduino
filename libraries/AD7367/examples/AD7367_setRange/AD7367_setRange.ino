//
//    FILE: AD7367_addr_select.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour
//     URL: https://github.com/RobTillaart/AD7367


#include "AD7367.h"

//  select, clock, convert, busy, data0, data1
//  adjust pins if needed
AD7367 AD(5, 6, 7, 8, 9, 10);

void setup()
{
  while (!Serial);
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AD7367_LIB_VERSION: ");
  Serial.println(AD7367_LIB_VERSION);
  Serial.println();

  AD.begin();
  AD.setADDRpin(11);       //  use pin 11 to control ADDR pin.
  AD.setRangePin(12, 13);  //  use pin 12, 13 to control RANGE.

  delay(100);
}


void loop()
{
  //  select (Va1, Vb1)
  AD.ADDRwrite(LOW);
  //  select +- 10V
  AD.setRange(0);
  AD.read();
  Serial.print(AD.getLastADCA());
  Serial.print("\t");
  Serial.println(AD.getLastADCB());

  //  select (Va2, Vb2)
  AD.ADDRwrite(HIGH);
  //  select +- 5V
  AD.setRange(1);
  AD.read();
  Serial.print(AD.getLastADCA());
  Serial.print("\t");
  Serial.println(AD.getLastADCB());
}


//  -- END OF FILE --

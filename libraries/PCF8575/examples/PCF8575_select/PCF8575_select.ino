//
//    FILE: PCF8575_select.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo PCF8575 library select functions
//     URL: https://github.com/RobTillaart/PCF8575


#include "PCF8575.h"

PCF8575 PCF(0x20);

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PCF8575_LIB_VERSION:\t");
  Serial.println(PCF8575_LIB_VERSION);

  Wire.begin();

  PCF.begin();
  Serial.println(PCF.isConnected());
  Serial.println();

  PCF.selectAll();
  delay(1000);
  PCF.selectNone();
  delay(1000);
  
  //  VU meter up
  for (int i = 0; i < 15; i++)
  {
    PCF.selectN(i);
    delay(100);
  }

  //  VU meter down
  for (int i = 15; i >= 0; i--)
  {
    PCF.selectN(i);
    delay(100);
  }
}


void loop()
{
  //  night rider
  for (int i = 0; i < 15; i++)
  {
    PCF.select(i);
    delay(100);
  }
  for (int i = 15; i >= 0; i--)
  {
    PCF.select(i);
    delay(100);
  }
}


//  -- END OF FILE --


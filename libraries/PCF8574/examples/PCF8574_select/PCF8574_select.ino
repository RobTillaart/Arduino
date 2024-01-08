//
//    FILE: PCF8574_select.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2022-06-18
// PURPOSE: demo PCF8574 library select functions
//     URL: https://github.com/RobTillaart/PCF8574


#include "PCF8574.h"

PCF8574 PCF(0x38);

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PCF8574_LIB_VERSION:\t");
  Serial.println(PCF8574_LIB_VERSION);

  Wire.begin();

  PCF.begin();
  Serial.println(PCF.isConnected());
  Serial.println();

  PCF.selectAll();
  delay(1000);
  PCF.selectNone();
  delay(1000);
  
  //  VU meter up
  for (int i = 0; i < 7; i++)
  {
    PCF.selectN(i);
    delay(100);
  }

  //  VU meter down
  for (int i = 7; i >= 0; i--)
  {
    PCF.selectN(i);
    delay(100);
  }
}


void loop()
{
  //  night rider
  for (int i = 0; i < 7; i++)
  {
    PCF.select(i);
    delay(100);
  }
  for (int i = 7; i >= 0; i--)
  {
    PCF.select(i);
    delay(100);
  }
}


//  -- END OF FILE --

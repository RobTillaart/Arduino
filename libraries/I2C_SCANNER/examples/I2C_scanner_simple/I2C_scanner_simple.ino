//    FILE: I2C_scanner_simple.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo simple scanner
//     URL: https://github.com/RobTillaart/I2C_SCANNER


#include "I2C_SCANNER.h"

I2C_SCANNER scanner;


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("I2C_SCANNER_LIB_VERSION: ");
  Serial.println(I2C_SCANNER_LIB_VERSION);

  Wire.begin();
  scanner.begin();
}


void loop()
{
  for (int addr = 0; addr < 128; addr++)
  {
    if (addr % 8 == 0) Serial.println();
    if (scanner.ping(addr))
    {
      Serial.print(addr);
    }
    else
    {
      Serial.print("-");
    }
    Serial.print("\t");
  }
  Serial.println();
  Serial.println();
  delay(1000);
}


//  -- END OF FILE --


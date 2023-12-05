//    FILE: I2C_scanner_minimal.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo minimal I2C scanner
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

  for (int addr = 0; addr < 128; addr++)
  {
    Serial.print(addr);
    Serial.print("\t");
    Serial.println(scanner.ping(addr));
  }
}


void loop()
{
}


//  -- END OF FILE --


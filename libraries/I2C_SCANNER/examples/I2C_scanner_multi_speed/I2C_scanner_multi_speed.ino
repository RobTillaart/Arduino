//    FILE: I2C_scanner_multi_speed.ino
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
  Serial.println();

  Wire.begin();
  Wire.setClock(100000);

  scanner.begin();

  for (int addr = 0; addr < 128; addr++)
  {
    Wire.setClock(100000);
    int x = scanner.ping(addr);
    Serial.print(addr, HEX);
    Serial.print("\t");
    Serial.print(addr);
    Serial.print("\t");
    Serial.println(x);
    if (x == 0)
    {
      for (uint32_t cl = 100000; cl <= 600000; cl += 50000)
      {
        Wire.setClock(cl);
        Serial.print("\t");
        Serial.print(cl);
        Serial.print("\t");
        Serial.println(scanner.ping(addr));
      }
    }
  }
  Wire.setClock(100000);
}


void loop()
{
}


//  -- END OF FILE --

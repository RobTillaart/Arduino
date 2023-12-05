//    FILE: I2C_scanner_getWirePortCount.ino
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

  Serial.print("I2C ports: \t");
  Serial.println(scanner.getWirePortCount());

  for (int port = 0; port < scanner.getWirePortCount(); port++)
  {
    if (scanner.setWire(port))
    {
      Serial.println();
      Serial.print("Scan port: \t");
      Serial.println(port);

      int fnd = simpleScan();
      Serial.print("found: \t");
      Serial.println(fnd);
    }
  }
}


void loop()
{
}


int simpleScan()
{
  int count = 0;
  for (int addr = 0; addr < 128; addr++)
  {
    if (addr % 8 == 0) Serial.println();
    if (scanner.ping(addr))
    {
      Serial.print(addr);
      count++;
    }
    else
    {
      Serial.print("-");
    }
    Serial.print("\t");
  }
  Serial.println();
  Serial.println();
  return count;
}


//  -- END OF FILE --

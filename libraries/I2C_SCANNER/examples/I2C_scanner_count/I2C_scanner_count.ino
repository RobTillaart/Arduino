//    FILE: I2C_scanner_count.ino
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

  scanner.begin();

  for (int port = 0; port < scanner.getWirePortCount(); port++)
  {
    scanner.setWire(port);
    int cnt = scanner.count();
    Serial.print(port);
    Serial.print("\t");
    Serial.println(cnt);
  }

  Serial.println("\ndone...");
}

void loop()
{
}

// -- END OF FILE --

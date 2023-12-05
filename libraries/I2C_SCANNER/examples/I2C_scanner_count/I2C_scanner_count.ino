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

  Wire.begin();
  scanner.begin();

  int ports = scanner.getWirePortCount();
  Serial.print("PORTS: \t");
  Serial.println(ports);

  for (int port = 0; port < ports; port++)
  {
    scanner.setWire(port);
    int cnt = scanner.count();
    Serial.print("Port: \t");
    Serial.print(port);
    Serial.print("\tCount: \t");
    Serial.println(cnt);
  }

  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --

//    FILE: I2C_scanner_meta_info.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test experimental functions
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
  scanner.begin();

  Serial.println(F("META INFO\n=========\n"));

  Serial.print("has timeout: \t");
  Serial.println(scanner.hasWireTimeout());

  Serial.print("set timeout: \t");
  Serial.println(scanner.setWireTimeout(1000, false));

  Serial.print("get deviceID: \t");
  Serial.println(scanner.getDeviceID(0x7C), HEX);

  Serial.print("I2C ports: \t");
  Serial.println(scanner.getWirePortCount());
}


void loop()
{
}



//  -- END OF FILE --

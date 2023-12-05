//    FILE: I2C_scanner_ping_count.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
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
    if (addr % 8 == 0)
    {
      Serial.println();
      Serial.print("0x");
      if (addr < 0x10) Serial.print("0");;
      Serial.print(addr, HEX);
      Serial.print(":\t");
    }
    uint8_t n = scanner.ping(addr, 5);
    if (n > 0)
    {
      if (addr < 0x10) Serial.print("0");
      Serial.print(addr, HEX);
      Serial.print("(");
      Serial.print(n);
      Serial.print(")");
    }
    else
    {
      Serial.print("-");
    }
    Serial.print("\t");
  }
  Serial.println();
  Serial.println();

  //  AVR only (prevents hang)
  //  Wire.setWireTimeout(2000000);  //  micros.
  Serial.println("10K calls\tTime (us)");
  uint32_t start = micros();
  uint8_t addr = 0x41;
  uint16_t n = scanner.ping(addr, 10000);
  uint32_t stop = micros();

  if (addr < 0x10) Serial.print("0");
  Serial.print(addr, HEX);
  Serial.print("(");
  Serial.print(n);
  Serial.print(")\t");
  Serial.print((stop - start) * 0.0001, 2);
  Serial.print(" per call.");
  Serial.println();
}


void loop()
{
}


//  -- END OF FILE --

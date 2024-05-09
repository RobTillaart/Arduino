//
//    FILE: LTR390_dump_registers.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: dump registers
//     URL: https://github.com/RobTillaart/LTR390


#include "LTR390.h"


LTR390 uv;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("LTR390_LIB_VERSION: ");
  Serial.println(LTR390_LIB_VERSION);
  Serial.println();

  Wire.begin();
  Wire.setClock(100000);

  if (uv.begin() == false)
  {
    Serial.println("Could not connect, fix and reboot");
  }
  else
  {
    Serial.println("Device found.");
  }
  uv.reset();

  //  registers according to datasheet

  for (uint8_t reg = 0x00; reg < 0x01; reg++)
  {
    Serial.print(reg, HEX);
    Serial.print("\t");
    Serial.print(uv.readRegister(reg), HEX);
    Serial.print("\t(");
    Serial.print(uv.readRegister(reg));
    Serial.print(")\n");
  }
  Serial.println();

  for (uint8_t reg = 0x04; reg < 0x08; reg++)
  {
    Serial.print(reg, HEX);
    Serial.print("\t");
    Serial.print(uv.readRegister(reg), HEX);
    Serial.print("\t(");
    Serial.print(uv.readRegister(reg));
    Serial.print(")\n");
  }
  Serial.println();

  for (uint8_t reg = 0x0D; reg < 0x13; reg++)
  {
    Serial.print(reg, HEX);
    Serial.print("\t");
    Serial.print(uv.readRegister(reg), HEX);
    Serial.print("\t(");
    Serial.print(uv.readRegister(reg));
    Serial.print(")\n");
  }
  Serial.println();

  for (uint8_t reg = 0x19; reg < 0x1B; reg++)
  {
    Serial.print(reg, HEX);
    Serial.print("\t");
    Serial.print(uv.readRegister(reg), HEX);
    Serial.print("\t(");
    Serial.print(uv.readRegister(reg));
    Serial.print(")\n");
  }
  Serial.println();

  for (uint8_t reg = 0x21; reg < 0x27; reg++)
  {
    Serial.print(reg, HEX);
    Serial.print("\t");
    Serial.print(uv.readRegister(reg), HEX);
    Serial.print("\t(");
    Serial.print(uv.readRegister(reg));
    Serial.print(")\n");
  }
  Serial.println();

  Serial.println("\ndone...");
}


void loop()
{
  // lower bits of DATA
  Serial.println(uv.readRegister(0x0E) * 256 + uv.readRegister(0x0D));
  delay(100);
  Serial.println(uv.readRegister(0x11) * 256 + uv.readRegister(0x10));
  delay(100);
}


//  -- END OF FILE --

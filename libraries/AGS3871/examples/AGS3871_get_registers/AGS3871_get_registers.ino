//
//    FILE: AGS3871_get_registers.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: low level develop application
//     URL: https://github.com/RobTillaart/AGS3871
//
// PURPOSE: this is a debugging tool for developing / investigating.
//          Do not use it unless you are willing to crash your sensor.
//
//          USE AT OWN RISK

#include "AGS3871.h"

AGS3871 AGS;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("AGS3871_LIB_VERSION: ");
  Serial.println(AGS3871_LIB_VERSION);
  Serial.println();

  Wire.begin();

  bool b = AGS.begin();
  Serial.print("BEGIN:\t");
  Serial.println(b);
  Serial.print("VERSION:\t");
  Serial.println(AGS.getVersion());
  Serial.print("ADDRESS:\t");
  Serial.println(AGS.getAddress());
}


void loop()
{
  //  need to be optimized as not all are meaningful
  for (uint8_t addr = 0; addr < 33; addr++)
  {
    dumpRegister(addr);
  }

  delay(2000);
}


void dumpRegister(uint8_t addr)
{
  AGS3871::RegisterData reg;
  bool b = AGS.readRegister(addr, reg);

  Serial.print(millis());
  Serial.print("\tREG[0x");
  Serial.print(addr, HEX);
  Serial.print("]\t");

  for (int i = 0; i < 4; i++)
  {
    Serial.print(reg.data[i]);
    Serial.print("\t");
  }
  Serial.println();
  Serial.println();
}


//  -- END OF FILE --

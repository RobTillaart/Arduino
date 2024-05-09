//
//    FILE: LTR390_dump_registers.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: dump
//     URL: https://github.com/RobTillaart/LTR390_DFR


#include "LTR390_DFR.h"


LTR390_DFR uv;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.println();
  Serial.print("LTR390_DFR_LIB_VERSION: ");
  Serial.println(LTR390_DFR_LIB_VERSION);
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

  //  register range according to DFrobotics
  for (uint8_t reg = 0x00; reg < 0x14; reg++)
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

  //  select mode
  //  uv.setUVSMode();
  uv.setALSMode();
}


void loop()
{
  //  Serial.print("ALS:\t");
  //  Serial.println(uv.getALSData());
  //  delay(1000);
  //  Serial.print("UVS:\t");
  //  Serial.println(uv.getUVSData());
  //  delay(1000);
}


//  -- END OF FILE --

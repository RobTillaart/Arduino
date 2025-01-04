//
//    FILE: AGS3871_get_registers.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: low level develop application
//     URL: https://github.com/RobTillaart/AGS3871
//
// PURPOSE: this is a debugging tool for developing / investigating.
//          Do not use it unless you are willing to crash your sensor.
//
//  usage:  make _readRegister(), _writeRegister() and _buffer public
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


  for (uint8_t reg = 0; reg < 33; reg++)
  {
    dumpRegister(reg);
  }
}


void loop()
{
}


uint32_t dumpRegister(uint8_t reg)
{
  Serial.print("REG[");
  Serial.print(reg);
  Serial.print("]");

  bool b = AGS._readRegister(reg);
  for (int i = 0; i < 4; i++)
  {
    Serial.print("\t");
    Serial.print(AGS._buffer[i]);
  }

  Serial.println();
  delay(100);

  return value;
}


//  -- END OF FILE --

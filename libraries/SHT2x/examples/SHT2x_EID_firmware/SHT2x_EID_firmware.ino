//
//    FILE: SHT2x_EID.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/SHT2x


#include "Wire.h"
#include "SHT2x.h"

uint32_t start, stop;

SHT2x sht;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("SHT2x_LIB_VERSION: \t");
  Serial.println(SHT2x_LIB_VERSION);

  Wire.begin();
  sht.begin();

  uint32_t EIDA = sht.getEIDA();
  Serial.print(EIDA, HEX);
  Serial.println();
  
  uint32_t EIDB = sht.getEIDB();
  Serial.print(EIDB, HEX);
  Serial.println();
  
  uint8_t firmware = sht.getFirmwareVersion();
  Serial.print(firmware, HEX);
  Serial.println();

  Serial.println("\n done...");
}


void loop()
{
}


//  -- END OF FILE --


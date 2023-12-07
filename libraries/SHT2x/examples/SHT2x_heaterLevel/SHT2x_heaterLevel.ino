//
//    FILE: SHT2x_heaterLevel.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo heaterLevel functions
//     URL: https://github.com/RobTillaart/SHT2x


#include "Wire.h"
#include "SHT2x.h"

SHT2x sht;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("SHT2x_LIB_VERSION: \t");
  Serial.println(SHT2x_LIB_VERSION);

  Wire.begin();
  sht.begin();

  for (int i = 0 ; i < 16; i++)
  {
    sht.setHeaterLevel(i);
    uint8_t level;
    sht.getHeaterLevel(level);
    Serial.println(level);
  }

  Serial.println("\n Done...");
}


void loop()
{
}


//  -- END OF FILE --

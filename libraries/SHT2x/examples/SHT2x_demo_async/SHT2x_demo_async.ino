//
//    FILE: SHT2x_demo_async.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo asynchronous interface
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

  uint8_t stat = sht.getStatus();
  Serial.print(stat, HEX);
  Serial.println();

  sht.requestTemperature();
}


void loop()
{
  if (sht.reqTempReady())
  {
    sht.readTemperature();
    Serial.print("TEMP:\t");
    Serial.println(sht.getTemperature(), 1);
    sht.requestTemperature();
  }

  //  do other things here
  delay(1000);
}


//  -- END OF FILE --

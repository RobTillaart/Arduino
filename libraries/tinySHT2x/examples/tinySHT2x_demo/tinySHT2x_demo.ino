//
//    FILE: tinySHT2x_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/tinySHT2x


#include "Wire.h"
#include "tinySHT2x.h"

tinySHT2x sht;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("TINY_SHT2x_LIB_VERSION: ");
  Serial.println(TINY_SHT2x_LIB_VERSION);
  Serial.println();

  Wire.begin();
  sht.begin();
}


void loop()
{
  Serial.print(sht.getTemperature());
  Serial.print("\t");
  Serial.println(sht.getHumidity());
  delay(1000);
}


//  -- END OF FILE --


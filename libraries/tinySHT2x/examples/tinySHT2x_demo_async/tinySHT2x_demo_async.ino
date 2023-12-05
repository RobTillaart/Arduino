//
//    FILE: tinySHT2x_demo_async.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/tinySHT2x


#include "Wire.h"
#include "tinySHT2x.h"

tinySHT2x sht;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  Wire.begin();
  sht.begin();
}


void loop()
{
  sht.requestTemperature();
  delay(65);  //  tune to work
  Serial.print(sht.readTemperature());
  Serial.print("\t");
  
  sht.requestHumidity();
  delay(28);  //  tune to work
  Serial.println(sht.getHumidity());
  delay(1000);
}


//  -- END OF FILE --

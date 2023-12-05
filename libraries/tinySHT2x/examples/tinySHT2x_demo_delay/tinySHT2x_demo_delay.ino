//
//    FILE: tinySHT2x_demo_delay.ino
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
  Serial.print(sht.getTemperature(65));  //  adjust delay if needed
  Serial.print("\t");
  Serial.println(sht.getHumidity(28));  //  adjust delay if needed
  delay(1000);
}


//  -- END OF FILE --

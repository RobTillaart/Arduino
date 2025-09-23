//
//    FILE: DCT532_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/DCT532


#include "DCT532.h"

//  adjust address if needed
DCT532 DCT(0x50);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("DCT532_LIB_VERSION: ");
  Serial.println(DCT532_LIB_VERSION);
  Serial.println();

  Wire.begin();
  if (DCT.begin(10.0, 0.0) == false)   //  explicit configuration
  {
    Serial.print("Could not connect to ");
    Serial.println(DCT.getAddress(), HEX);
    while (1);
  }
}


void loop()
{
  DCT.readSensor();
  Serial.print(DCT.getPressure());
  Serial.print("\t");
  Serial.println(DCT.getTemperature());

  delay(2000);
}


//  -- END OF FILE --

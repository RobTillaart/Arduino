//
//    FILE: AD5144A_test_isConnected.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: check isConnected()
//     URL: https://github.com/RobTillaart/AD5144A


#include "AD5144A.h"

//  select the right type
//  adjust address if needed
AD5144A AD(0x77);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  Wire.begin();

  Serial.println();
  Serial.print("Begin: ");
  Serial.println(AD.begin());
  Serial.print("Connected: ");
  Serial.println(AD.isConnected());
  Serial.print("CHANNELS:\t");
  Serial.println(AD.pmCount());
  Serial.print("MAXVALUE:\t");
  Serial.println(AD.maxValue());
  Serial.println();

  Serial.println("done...");
}


void loop()
{
}


//  -- END OF FILE --


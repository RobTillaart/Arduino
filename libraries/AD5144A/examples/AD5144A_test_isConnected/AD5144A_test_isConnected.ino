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
  //  while(!Serial);  //  uncomment if needed
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AD51XXA_VERSION: ");
  Serial.println(AD51XXA_VERSION);
  Serial.println();

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


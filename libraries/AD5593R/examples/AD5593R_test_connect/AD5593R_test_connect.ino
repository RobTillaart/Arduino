//
//    FILE: AD5593R_test_connect.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test connection (debug sketch)
//     URL: https://github.com/RobTillaart/AD5593R


#include "AD5593R.h"
#include "Wire.h"

AD5593R AD(0x10);


void setup()
{
  while (!Serial);
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AD5593R_LIB_VERSION: ");
  Serial.println(AD5593R_LIB_VERSION);
  Serial.println();

  Wire.begin();
}


void loop()
{
  Serial.print("Connect: ");
  Serial.println(AD.isConnected());
  delay(1000);
}


//  -- END OF FILE --

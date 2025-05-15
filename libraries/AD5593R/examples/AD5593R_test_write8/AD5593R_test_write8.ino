//
//    FILE: AD5593R_test_write8.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test output mode
//     URL: https://github.com/RobTillaart/AD5593R


#include "AD5593R.h"
#include "Wire.h"

AD5593R AD(0x10);


void setup()
{
  while(!Serial);
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AD5593R_LIB_VERSION: ");
  Serial.println(AD5593R_LIB_VERSION);
  Serial.println();

  Wire.begin();

  //  set all eight pins to OUTPUT mode.
  AD.setOUTPUTmode(0xFF);
}


void loop()
{
  Serial.println(AD.write8(random(256)));
  delay(1000);
}


//  -- END OF FILE --

//
//    FILE: AD5593R_test_input.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test input mode
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

  //  set all eight pins to INPUT mode.
  AD.setINPUTmode(0xFF);
}


void loop()
{
  for (int pin = 0; pin < 8; pin++)
  {
    Serial.print(AD.read1(pin));
    Serial.print("\t");
  }
  Serial.println();
  delay(1000);
}


//  -- END OF FILE --

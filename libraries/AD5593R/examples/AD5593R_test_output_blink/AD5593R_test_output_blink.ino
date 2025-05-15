//
//    FILE: AD5593R_test_output_blink.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test output mode
//     URL: https://github.com/RobTillaart/AD5593R


#include "AD5593R.h"
#include "Wire.h"

AD5593R AD(0x10);

uint8_t flag = HIGH;

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
  for (int pin = 0; pin < 8; pin++)
  {
    Serial.print(AD.write1(pin, flag));
    Serial.print("\t");
  }
  Serial.println();
  //  toggle blink flag.
  if (flag == HIGH) flag = LOW;
  else flag = HIGH;
  delay(1000);
}


//  -- END OF FILE --

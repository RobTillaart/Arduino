//
//    FILE: DAC8571_demo_read.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo read()
//     URL: https://github.com/RobTillaart/DAC8571


#include "DAC8571.h"

DAC8571 dev(0x4C);


void setup()
{
  Serial.begin(115200);
  while(!Serial);
  delay(2000);

  Serial.println(__FILE__);
  Serial.print("DAC8571_LIB_VERSION: ");
  Serial.println(DAC8571_LIB_VERSION);
  Serial.println();

  Wire.begin();
  Wire.setClock(100000UL);

  dev.begin();  //  implicit 0

  Serial.print("Address: ");
  Serial.println(dev.getAddress(), HEX);
  Serial.println();
}


void loop()
{
  test_DAC();
  delay(1000);
}


void test_DAC()
{
  Serial.println(__FUNCTION__);
  Serial.println("--------------");
  for (int i = 0; i < 628; i++)
  {
    uint16_t val = 32767 + 32767 * sin(i * 0.01);
    dev.write(val);

    Serial.print(val);
    Serial.print("\t");
    Serial.print(dev.lastWrite());
    Serial.print("\t");
    Serial.println(dev.read());
    delay(1);              //  just to slow the effect
  }
  Serial.println();
}


//  -- END OF FILE --

//
//    FILE: DAC8574_demo_extended_address.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo write(value)
//     URL: https://github.com/RobTillaart/DAC8574


#include "DAC8574.h"

DAC8574 dev(0x4C);


void setup()
{
  Serial.begin(115200);
  while(!Serial);
  delay(2000);

  Serial.println(__FILE__);
  Serial.print("DAC8574_LIB_VERSION: ");
  Serial.println(DAC8574_LIB_VERSION);
  Serial.println();

  Wire.begin();
  Wire.setClock(100000UL);

  dev.begin();  //  implicit all channels to 0
  dev.setExtendedAddress(3);

  Serial.print("Address:  ");
  Serial.println(dev.getAddress(), HEX);
  Serial.print("Ext Addr: ");
  Serial.println(dev.getExtendedAddress(), HEX);
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
    Serial.println(val);
    dev.write(0, val);
    delay(1);              //  just to slow the effect
  }
  Serial.println();
}


//  -- END OF FILE --

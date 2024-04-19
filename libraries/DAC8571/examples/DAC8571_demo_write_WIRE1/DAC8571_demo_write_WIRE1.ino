//
//    FILE: DAC8571_demo_write_WIRE1.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo Wire1
//     URL: https://github.com/RobTillaart/DAC8571


#include "DAC8571.h"

DAC8571 dev(0x4C, &Wire1);


void setup()
{
  Serial.begin(115200);
  while(!Serial);
  delay(2000);

  Serial.println(__FILE__);
  Serial.print("DAC8571_LIB_VERSION: ");
  Serial.println(DAC8571_LIB_VERSION);
  Serial.println();

  Wire1.begin();
  Wire1.setClock(100000UL);

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
    Serial.println(val);
    dev.write(val);
    delay(1);              //  just to slow the effect
  }
  Serial.println();
}


//  -- END OF FILE --

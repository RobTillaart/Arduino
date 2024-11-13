//
//    FILE: DAC8574_demo_write_array.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo write(arr, length)
//     URL: https://github.com/RobTillaart/DAC8574


#include "DAC8574.h"

DAC8574 dev(0x4C);

uint16_t arr[14];  //  MAX buffer (Arduino UNO)


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
  for (int i = 0; i < 14; i++)
  {
    arr[i] = random(65535);
    Serial.println(arr[i]);
    dev.write(0, arr, 14);
  }
  Serial.println();
}


//  -- END OF FILE --

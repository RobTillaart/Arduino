//
//    FILE: AD5144A_test_writeAll.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test writeAll + wrappers
//     URL: https://github.com/RobTillaart/AD5144A


#include "AD5144A.h"

//  select the right type
//  adjust address
AD5144A AD(0x77);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  Wire.begin();
  if (AD.begin() == false)
  {
    Serial.println("device not found");
    return;
  }

  Serial.println();
  Serial.print("CHANNELS:\t");
  Serial.println(AD.pmCount());
  Serial.print("MAXVALUE:\t");
  Serial.println(AD.maxValue());
  Serial.println();

  test_writeAll();
  test_zeroAll();
  test_midScaleAll();
  test_maxAll();

  Serial.println("done...");
}


void loop()
{
}


void test_writeAll()
{
  Serial.println();
  Serial.println(__FUNCTION__);

  for (int v = 0; v < 256; v++)
  {
    uint8_t rv = AD.writeAll(v);
    Serial.print(v);
    Serial.print('\t');
    Serial.print(AD.read(0));
    Serial.print('\t');
    Serial.println(rv);
  }
}


void test_zeroAll()
{
  Serial.println();
  Serial.println(__FUNCTION__);

  uint8_t rv = AD.zeroAll();
  Serial.println(rv);
  
  for (int i = 0; i < AD.pmCount(); i++)
  {
    Serial.print(i);
    Serial.print('\t');
    Serial.println(AD.read(i));
  }
  Serial.println();
}


void test_midScaleAll()
{
  Serial.println();
  Serial.println(__FUNCTION__);

  uint8_t rv = AD.midScaleAll();
  Serial.println(rv);

  for (int i = 0; i < AD.pmCount(); i++)
  {
    Serial.print(i);
    Serial.print('\t');
    Serial.println(AD.read(i));
  }
  Serial.println();
}


void test_maxAll()
{
  Serial.println();
  Serial.println(__FUNCTION__);

  uint8_t rv = AD.maxAll();
  Serial.println(rv);

  for (int i = 0; i < AD.pmCount(); i++)
  {
    Serial.print(i);
    Serial.print('\t');
    Serial.println(AD.read(i));
  }
  Serial.println();
}


//  -- END OF FILE --


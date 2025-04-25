//
//    FILE: AD5144A_test_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: indication performance methods of the class
//     URL: https://github.com/RobTillaart/AD5144A


#include "AD5144A.h"

//  select the right type
//  adjust address
AD5144A AD(0x77);

uint32_t start, stop;


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

  test_1000_writes();
  test_1000_reads();

  test_midScaleAll();
  test_zeroAll();
  test_maxAll();

  test_zero();
  test_midScale();
  test_maxValue();

  Serial.println("done...");
}


void loop()
{
}


void test_1000_writes()
{
  Serial.println();
  Serial.println(__FUNCTION__);
  delay(10);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    AD.write(0, i & 0xFF);
  }
  stop = micros();
  Serial.println(stop - start);
  Serial.println();
}


void test_1000_reads()
{
  uint32_t sum = 0;
  Serial.println();
  Serial.println(__FUNCTION__);
  delay(10);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    sum += AD.read(0);
  }
  stop = micros();
  Serial.println(stop - start);
  Serial.println(sum);
  Serial.println();
}


void test_midScaleAll()
{
  Serial.println();
  Serial.println(__FUNCTION__);

  AD.reset();
  delay(10);

  start = micros();
  AD.midScaleAll();
  stop = micros();
  Serial.println(stop - start);
  Serial.println();

  for (int potMeter = 0; potMeter < AD.pmCount(); potMeter++)
  {
    if (AD.read(potMeter) != AD.maxValue()/2)
    {
      Serial.print("non-mid:\t");
      Serial.println(potMeter);
    }
  }
  Serial.println();
}


void test_zeroAll()
{
  Serial.println();
  Serial.println(__FUNCTION__);

  AD.reset();
  delay(10);

  start = micros();
  AD.zeroAll();
  stop = micros();
  Serial.println(stop - start);
  Serial.println();

  for (int potMeter = 0; potMeter < AD.pmCount(); potMeter++)
  {
    if (AD.read(potMeter) != 0)
    {
      Serial.print("non-zero:\t");
      Serial.println(potMeter);
    }
  }
  Serial.println();
}


void test_maxAll()
{
  Serial.println();
  Serial.println(__FUNCTION__);

  AD.reset();
  delay(10);

  start = micros();
  AD.maxAll();
  stop = micros();
  Serial.println(stop - start);
  Serial.println();

  for (int potMeter = 0; potMeter < AD.pmCount(); potMeter++)
  {
    if (AD.read(potMeter) != 0)
    {
      Serial.print("non-zero:\t");
      Serial.println(potMeter);
    }
  }
  Serial.println();
}


void test_zero()
{
  Serial.println();
  Serial.println(__FUNCTION__);

  AD.reset();
  delay(10);

  start = micros();
  AD.zero(0);
  AD.zero(1);
  AD.zero(2);
  AD.zero(3);
  stop = micros();
  Serial.println(stop - start);
  Serial.println();

  for (int potMeter = 0; potMeter < AD.pmCount(); potMeter++)
  {
    if (AD.read(potMeter) != 0)
    {
      Serial.print("non-zero:\t");
      Serial.println(potMeter);
    }
  }
  Serial.println();
}


void test_midScale()
{
  Serial.println();
  Serial.println(__FUNCTION__);

  AD.reset();
  delay(10);

  start = micros();
  AD.midScale(0);
  AD.midScale(1);
  AD.midScale(2);
  AD.midScale(3);
  stop = micros();
  Serial.println(stop - start);
  Serial.println();

  for (int potMeter = 0; potMeter < AD.pmCount(); potMeter++)
  {
    if (AD.read(potMeter) != 0)
    {
      Serial.print("non-zero:\t");
      Serial.println(potMeter);
    }
  }
  Serial.println();
}


void test_maxValue()
{
  Serial.println();
  Serial.println(__FUNCTION__);

  AD.reset();
  delay(10);

  start = micros();
  AD.maxValue(0);
  AD.maxValue(1);
  AD.maxValue(2);
  AD.maxValue(3);
  stop = micros();
  Serial.println(stop - start);
  Serial.println();

  for (int potMeter = 0; potMeter < AD.pmCount(); potMeter++)
  {
    if (AD.read(potMeter) != 0)
    {
      Serial.print("non-zero:\t");
      Serial.println(potMeter);
    }
  }
  Serial.println();
}


//  -- END OF FILE --

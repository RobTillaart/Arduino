//
//    FILE: PCA9552_test_registers.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test PCA9552 device registers read back
//     URL: https://github.com/RobTillaart/PCA9552


#include "PCA9552.h"


PCA9552 leds(0x62);


void test_GPIO()
{
  Serial.println(__FUNCTION__);
  for (int i = 0; i < leds.outputCount(); i++)
  {
    leds.write1(i, LOW);
    Serial.print(i);
    Serial.print("\t");
    Serial.print(leds.read1(i));
    Serial.print("\t");
    leds.write1(i, HIGH);
    Serial.print(leds.read1(i));
    Serial.print("\n");
  }
  Serial.println();
}


void test_prescaler()
{
  Serial.println(__FUNCTION__);
  for (uint8_t val = 0; val < 255; val += 5)
  {
    leds.setPrescaler(0, val);
    leds.setPrescaler(1, val);
    Serial.print(leds.getPrescaler(0));
    Serial.print("\t");
    Serial.println(leds.getPrescaler(1));
    Serial.print("\n");
  }
  Serial.println();
}


void test_PWM()
{
  Serial.println(__FUNCTION__);
  for (uint8_t val = 0; val < 255; val += 5)
  {
    leds.setPWM(0, val);
    leds.setPWM(1, val);
    Serial.print(leds.getPWM(0));
    Serial.print("\t");
    Serial.println(leds.getPWM(1));
    Serial.print("\n");
  }
  Serial.println();
}

void test_source()
{
  Serial.println(__FUNCTION__);
  for (uint8_t mode = 0; mode < 4; mode++)
  {
    leds.setOutputMode(0, mode);
    leds.setOutputMode(1, mode);
    leds.setOutputMode(2, mode);
    leds.setOutputMode(3, mode);

    Serial.print(leds.getOutputMode(0));
    Serial.print("\t");
    Serial.print(leds.getOutputMode(1));
    Serial.print("\t");
    Serial.print(leds.getOutputMode(2));
    Serial.print("\t");
    Serial.print(leds.getOutputMode(3));
    Serial.print("\n");
  }
  Serial.println();
}


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PCA9552_LIB_VERSION: ");
  Serial.println(PCA9552_LIB_VERSION);
  Serial.println();

  Wire.begin();

  if (leds.begin() == false)
  {
    Serial.println("Could not connect.");
    while(1);
  }

  Serial.println(leds.getAddress(), HEX);
  Serial.println(leds.outputCount());
  Serial.println();
  
  test_GPIO();
  test_prescaler();
  test_PWM();
  test_source();

  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --

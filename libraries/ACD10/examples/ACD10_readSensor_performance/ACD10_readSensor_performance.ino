//
//    FILE: ACD10_readSensor_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/ACD10


#include "ACD10.h"


ACD10 mySensor;


void test(uint32_t speed)
{
  Wire.setClock(speed);
  delay(100);

  uint32_t start = micros();
  mySensor.requestSensor();
  uint32_t duration1 = micros() - start;

  while(mySensor.requestReady() == false) delay(10);
  
  start = micros();
  mySensor.readSensor();
  uint32_t duration2 = micros() - start;

  Serial.print("|  ");
  Serial.print(speed);
  Serial.print("  |  ");
  Serial.print(duration1);
  Serial.print("  |  ");
  Serial.print(duration2);
  Serial.print("  |");
  Serial.println();
  //  reset I2C bus
  Wire.setClock(100000);
}


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("ACD10_LIB_VERSION: ");
  Serial.println(ACD10_LIB_VERSION);

  Wire.begin();
  mySensor.begin();

  test(100000);
  test(200000);
  test(300000);
  test(400000);
  test(500000);
  test(600000);
  test(700000);
  test(800000);

  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --

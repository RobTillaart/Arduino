//
//    FILE: DCT532_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: measure performance
//     URL: https://github.com/RobTillaart/DCT532


#include "DCT532.h"

//  adjust address (fixed ?)
DCT532 DCT(0x28);

//  explicit parameters for begin()
const float maxPressure = 10.0;
const float minPressure = 0.0;

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("DCT532_LIB_VERSION: ");
  Serial.println(DCT532_LIB_VERSION);
  Serial.println();

  Wire.begin();
  if (DCT.begin(maxPressure, minPressure) == false)  //  explicit configuration
  {
    Serial.print("Could not connect to ");
    Serial.println(DCT.getAddress(), HEX);
    while (1);
  }

  for (uint32_t speed = 100000; speed <= 600000; speed += 50000)
  {
    test(speed);
  }

  Serial.println("\ndone...");
}


void loop()
{
}

void test(uint32_t speed)
{
  Wire.setClock(speed);
  delay(1000);
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    DCT.readSensor();
  }
  stop = micros();

  Serial.print(speed);
  Serial.print("\t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(DCT.getPressure());
  Serial.print("\t");
  Serial.println(DCT.getTemperature());
}


//  -- END OF FILE --

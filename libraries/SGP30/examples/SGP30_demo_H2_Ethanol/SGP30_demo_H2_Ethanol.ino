//
//    FILE: SGP30_demo_H2_Ethanol.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo SGP30
//     URL: https://github.com/RobTillaart/SGP30
//          https://www.adafruit.com/product/3709
//
// 20 samples per second RAW data
// calculates the average, which can be used to determine the Sref
// for the H2 and Ethanol concentration functions.


#include "SGP30.h"


SGP30 SGP;

uint8_t count = 0;
uint32_t lastTime = 0;


float avgH2;
float avgEth;


void setup()
{
  Serial.begin(115200);
  while (!Serial) {
    delay(1);
    yield();
  };

  Serial.println(__FILE__);
  Serial.print("SGP30_LIB_VERSION: ");
  Serial.println(SGP30_LIB_VERSION);
  Serial.println();

  Wire.begin();

  Serial.print("BEGIN:\t");
  Serial.println(SGP.begin());
  Serial.print("TEST:\t");
  Serial.println(SGP.measureTest());
}


void loop()
{
  if (SGP.readRaw())
  {
    if (count == 0)
    {
      Serial.println("\nH2_raw \tEth_raw\tavgH2\tAvgEth\tH2_ppm\tEthanol_ppm");
      count = 10;
    }

    avgH2 = avgH2 + 0.1 * (SGP.getH2_raw() - avgH2);
    avgEth = avgEth + 0.1 * (SGP.getEthanol_raw() - avgEth);

    Serial.print(SGP.getH2_raw());
    Serial.print("\t");
    Serial.print(SGP.getEthanol_raw());
    Serial.print("\t");
    Serial.print(avgH2 / 1000, 3);
    Serial.print("\t");
    Serial.print(avgEth / 1000, 3);
    Serial.print("\t");
    Serial.print(SGP.getH2(), 3);
    Serial.print("\t");
    Serial.print(SGP.getEthanol(), 3);
    Serial.print("\t");
    Serial.println();

    count--;
  }


  if (millis() - lastTime >= 50)
  {
    lastTime = millis();
    SGP.requestRaw();
  }

}


//  -- END OF FILE --


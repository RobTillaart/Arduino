//
//    FILE: FSR40X_formula_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test for conversion algorithm.
//     URL: https://github.com/RobTillaart/FSR40X
//
//  First results  UNO R3      ESP32
//  formula takes  324 micros  TODO
//  approx. takes   44 micros  TODO
//
//  approx. has a serious bump in the graph.
//  could be smoothed by using some more if's.

#include "FSR40X.h"

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("FSR40X_LIB_VERSION: ");
  Serial.println(FSR40X_LIB_VERSION);
  Serial.println();

  for (float FSR = 100; FSR < 10000000; FSR *= 1.03)
  {
    //  graph interpolation (datapoints datasheet)
    float fg1 = 9.80655 * 2.69117452575 * pow(FSR * 0.001, -1.114166333);
    //  approximation (google)
    float fg2 = 1e6 / FSR;
    if (fg2 < 1000) fg2 /= 80.0;
    else fg2 /= 30.0;

    //  tweaked approx
    //    if (fg2 < 500) fg2 /= 70.0;
    //    else if (fg2 < 1000) fg2 /= 40.0;
    //    else if (fg2 < 2000) fg2 /= 35.0;
    //    else fg2 /= 30.0;

    //    Serial.print(FSR, 4);
    //    Serial.print("\t");
    Serial.print(fg1, 4);
    Serial.print("\t");
    Serial.print(fg2, 4);
    Serial.print("\t");
    Serial.print(fg1 / fg2, 4);
    Serial.println();
  }

  delay(100);
  volatile float FSR = 100000;
  uint32_t start = micros();
  float x = (9.80655 * 2.69117452575) * pow(FSR * 0.001, -1.114166333);
  uint32_t duration1 = micros() - start;

  start = micros();
  float y = 1e6 / FSR;
  if (y < 1000) y *= (1.0 / 80.0);
  else y *= (1.0 / 30.0);
  uint32_t duration2 = micros() - start;

  //  Serial.print("FORM:\t");
  //  Serial.println(duration1);
  //  Serial.print("APPR:\t");
  //  Serial.println(duration2);
  //  Serial.println(x);
  //  Serial.println(y);
}


void loop()
{
  delay(100);
}


//  -- END OF FILE --

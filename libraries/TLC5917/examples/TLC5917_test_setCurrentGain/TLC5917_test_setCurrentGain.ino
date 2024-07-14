//
//    FILE: TLC5917_test_setCurrentGain.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test setCurrentGain function.
//     URL: https://github.com/RobTillaart/TLC5917


#include "TLC5917.h"


const int DEVICES = 1;
const int CLOCK   = 13;
const int DATA    = 12;
const int LATCH   = 11;
const int ENABLE  = 10;

TLC5917 tlc(DEVICES, CLOCK, DATA, LATCH, ENABLE);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("TLC5917_LIB_VERSION: \t");
  Serial.println(TLC5917_LIB_VERSION);
  Serial.println();

  if (tlc.begin() == false)
  {
    Serial.println("error");
    while (1);
  }

  tlc.setSpecialMode();
  float averageError = 0;
  float maxError = 0;
  //  above 2.989 the abs error goes beyond 0.012
  //  at 3.000 the error is 0.023
  for (float gain = 0.250; gain <= 2.989; gain += 0.001)
  {
    tlc.setCurrentGain(gain);
    float tmp = tlc.getCurrentGain();
    float diff = gain - tmp;
    Serial.print(gain, 3);
    Serial.print("\t");
    Serial.print(tmp, 3);
    Serial.print("\t");
    Serial.print(diff, 3);
    Serial.println();

    averageError += diff;
    if (maxError < abs(diff)) maxError = abs(diff);
  }

  Serial.println();
  Serial.print("AVGERR: \t");
  Serial.println(averageError, 4);
  Serial.print("MAXERR: \t");
  Serial.println(maxError, 4);

  tlc.setNormalMode();
  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --

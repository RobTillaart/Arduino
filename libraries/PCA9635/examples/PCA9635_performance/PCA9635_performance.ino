//
//    FILE: PCA9635_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test PCA9635 library
//     URL: https://github.com/RobTillaart/PCA9635


#include "PCA9635.h"


PCA9635 ledArray(0x20);

uint32_t start, stop;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PCA9635_LIB_VERSION: ");
  Serial.println(PCA9635_LIB_VERSION);
  Serial.println();

  Wire.begin();

  ledArray.begin();

  delay(100);  //  flush Serial buffer / interrupts
  start = micros();
  ledArray.write1(0, 127);  //  PWM at ~50%
  stop = micros();
  Serial.print("ONE:\t");
  Serial.println(stop - start);

  delay(100);  //  flush Serial buffer / interrupts
  start = micros();
  ledArray.write1(0, 127);  //  PWM at ~50%
  ledArray.write1(1, 128);  //  PWM at ~50%
  stop = micros();
  Serial.print("TWO:\t");
  Serial.println(stop - start);

  delay(100);  //  flush Serial buffer / interrupts
  uint8_t n = 123;
  start = micros();
  ledArray.writeN(0, &n, 1);  //  PWM at ~50%
  stop = micros();
  Serial.print("wrN:\t");
  Serial.println(stop - start);

  Serial.println("done...");
}


void loop()
{
}


//  -- END OF FILE --

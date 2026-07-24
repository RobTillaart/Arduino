//    FILE: M61538FP_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo M61538FP 6 channel volume processor.
//     URL: https://github.com/RobTillaart/M61538FP


#include "M61538FP.h"


const uint8_t dataPin = 6;
const uint8_t clockPin = 7;

M61538FP vp(dataPin, clockPin);

uint32_t start, stop;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("M61538FP_LIB_VERSION: ");
  Serial.println(M61538FP_LIB_VERSION);
  Serial.println();

  vp.begin();  //  default pulseDelay of 4 us
  delay(300);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    vp.setVolumeAll(10, 10, 10, 10, 10, 10);
  }
  stop = micros();
  Serial.print("SET ALL:\t");
  Serial.println((stop - start) * 0.001);
  delay(100);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    vp.setVolumeFrontLeftRight(10, 10);
  }
  stop = micros();
  Serial.print("SET PAIR:\t");
  Serial.println((stop - start) * 0.001);
  delay(100);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    vp.setVolumeFrontLeft(10);
  }
  stop = micros();
  Serial.print("SET SINGLE:\t");
  Serial.println((stop - start) * 0.001);
  delay(100);

  volatile uint16_t vol;
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    vol = vp.getVolumeFrontLeft();
  }
  stop = micros();
  Serial.print("GET SINGLE:\t");
  Serial.println((stop - start) * 0.001);
  delay(100);

  Serial.println("\nDone...");
}

void loop()
{
}


//  -- END OF FILE --

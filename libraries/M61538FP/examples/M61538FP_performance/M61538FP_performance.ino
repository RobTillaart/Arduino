//    FILE: M61538FP_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo M61538FP 6 channel volume processor.
//     URL: https://github.com/RobTillaart/M61538FP


#include "M61538FP.h"


//  adjust pins if needed
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
  Serial.print("SET ALL VOL:\t");
  Serial.println((stop - start) * 0.001);
  delay(100);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    vp.setVolumeFrontLeftRight(10, 10);
  }
  stop = micros();
  Serial.print("SET PAIR VOL:\t");
  Serial.println((stop - start) * 0.001);
  delay(100);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    vp.setVolumeFrontLeft(10);
  }
  stop = micros();
  Serial.print("SET SINGLE VOL:\t");
  Serial.println((stop - start) * 0.001);
  delay(100);

  volatile uint16_t vol;
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    vol = vp.getVolumeFrontLeft();
  }
  stop = micros();
  Serial.print("GET SINGLE VOL:\t");
  Serial.println((stop - start) * 0.001);
  Serial.println();
  delay(100);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    vp.muteAll();
  }
  stop = micros();
  Serial.print("MUTE ALL:\t");
  Serial.println((stop - start) * 0.001);
  Serial.println();
  delay(100);


  /////////////////////////////////////
  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    vp.setAttnAll(10, 10, 10, 10, 10, 10);
  }
  stop = micros();
  Serial.print("SET ALL ATTN:\t");
  Serial.println((stop - start) * 0.001);
  delay(100);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    vp.setAttnFrontLeftRight(10, 10);
  }
  stop = micros();
  Serial.print("SET PAIR ATTN:\t");
  Serial.println((stop - start) * 0.001);
  delay(100);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    vp.setAttnFrontLeft(10);
  }
  stop = micros();
  Serial.print("SET SINGLE ATTN:\t");
  Serial.println((stop - start) * 0.001);
  delay(100);

  start = micros();
  for (int i = 0; i < 1000; i++)
  {
    vol = vp.getAttnFrontLeft();
  }
  stop = micros();
  Serial.print("GET SINGLE ATTN:\t");
  Serial.println((stop - start) * 0.001);
  delay(100);

  Serial.println("\nDone...");
}

void loop()
{
}


//  -- END OF FILE --

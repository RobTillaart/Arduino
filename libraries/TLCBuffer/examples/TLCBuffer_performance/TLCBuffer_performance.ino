//
//    FILE: TLCBuffer_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic performance
//     URL: https://github.com/RobTillaart/TLCBuffer


#include "TLCBuffer.h"


TLCBuffer TLCB(20);
uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("TLCBUFFER_LIB_VERSION: ");
  Serial.println(TLCBUFFER_LIB_VERSION);
  Serial.println();
  delay(100);

  start = micros();
  if (TLCB.begin('m') == false)
  {
    Serial.println("TLCB failed allocating mem");
    while (1);
  }
  stop = micros();
  Serial.println("TLCBuffer(20) elements");
  Serial.print("BEGIN:  \t");
  Serial.println(stop - start);
  delay(100);

  TLCB.writeData(123);
  delay(10);
  start = micros();
  TLCB.writeData(123);
  stop = micros();
  Serial.print("WRITE1: \t");
  Serial.println(stop - start);
  delay(100);

  delay(10);
  start = micros();
  TLCB.writeData(345);
  stop = micros();
  Serial.print("WRITE2: \t");
  Serial.println(stop - start);
  delay(100);

  start = micros();
  uint32_t x = TLCB.readData(1);
  stop = micros();
  Serial.print("READ 1: \t");
  Serial.println(stop - start);
  delay(100);

  start = micros();
  uint32_t y = TLCB.readData(2);
  stop = micros();
  Serial.print("READ 2: \t");
  Serial.println(stop - start);
  delay(100);

  start = micros();
  uint32_t z = TLCB.readDuration(1);
  stop = micros();
  Serial.print("DURATION: \t");
  Serial.println(stop - start);
  delay(100);

  Serial.println();
  Serial.println(x);
  Serial.println(y);
  Serial.println(z);

  Serial.println("\ndone...");

}


void loop()
{
}


//  -- END OF FILE --

//
//    FILE: RLCBuffer_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic performance
//     URL: https://github.com/RobTillaart/RLCBuffer


#include "RLCBuffer.h"


RLCBuffer RLCB(20);
uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("RLCBUFFER_LIB_VERSION: ");
  Serial.println(RLCBUFFER_LIB_VERSION);
  Serial.println();
  delay(100);

  start = micros();
  if (RLCB.begin() == false)
  {
    Serial.println("RLCB failed allocating mem");
    while (1);
  }
  stop = micros();
  Serial.println("RLCBuffer(20) elements");
  Serial.print("BEGIN:  \t");
  Serial.println(stop - start);
  delay(100);

  RLCB.writeData(123);
  delay(10);
  start = micros();
  RLCB.writeData(123);
  stop = micros();
  Serial.print("WRITE1: \t");
  Serial.println(stop - start);
  delay(100);

  delay(10);
  start = micros();
  RLCB.writeData(345);
  stop = micros();
  Serial.print("WRITE2: \t");
  Serial.println(stop - start);
  delay(100);

  start = micros();
  uint32_t x = RLCB.readData(1);
  stop = micros();
  Serial.print("READ 1: \t");
  Serial.println(stop - start);
  delay(100);

  start = micros();
  uint32_t y = RLCB.readData(2);
  stop = micros();
  Serial.print("READ 2: \t");
  Serial.println(stop - start);
  delay(100);

  start = micros();
  uint32_t z = RLCB.readCount(1);
  stop = micros();
  Serial.print("COUNT:   \t");
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

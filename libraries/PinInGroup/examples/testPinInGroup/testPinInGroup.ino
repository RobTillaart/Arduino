//    FILE: testPinInGroup.ino
//  AUTHOR: Rob dot Tillaart at gmail dot com
// VERSION: 0.1.0
// PURPOSE: demo PinInGroup library for Arduino
// HISTORY: 20-08-2017 
//
// Released to the public domain
//

#include "PinInGroup.h"

int ar[4] = {2, 3, 4, 13};

void setup()
{
  Serial.begin(115200);
  Serial.print("\nPININGROUP_LIB_VERSION: ");
  Serial.println(PININGROUP_LIB_VERSION);

  test0();
  test1();
  test2();
 
  Serial.println("done...");
}

void loop()
{
}

// TEST1 verifies and times basic working
void test0()
{
  pinMode(2, INPUT);
  uint32_t t1 = micros();
  digitalRead(2);
  digitalRead(2);
  digitalRead(2);
  digitalRead(2);
  uint32_t t2 = micros();

  Serial.print("time: ");
  Serial.println(t2 - t1);
  Serial.println("Test0 done...");
  Serial.println();
}

void test1()
{
  uint16_t n1;
  
  PinInGroup PIG;
  PIG.add(2);
  PIG.add(4);
  PIG.add(5);
  PIG.add(13);

  Serial.print("size: ");
  Serial.println(PIG.size());
  Serial.print("free: ");
  Serial.println(PIG.free());

  uint32_t t1 = micros();
  n1 = PIG.read();
  uint32_t t2 = micros();

  Serial.print(" val: ");
  Serial.println(n1);
  Serial.print("time: ");
  Serial.println(t2 - t1);
  Serial.println("Test1 done...");
  Serial.println();
}

void test2()
{
  uint16_t n1;
  
  PinInGroup PIG;
  for (int p=2; p<14; p++) PIG.add(p);

  Serial.print("size: ");
  Serial.println(PIG.size());
  Serial.print("free: ");
  Serial.println(PIG.free());

  uint32_t t1 = micros();
  n1 = PIG.read();
  uint32_t t2 = micros();

  Serial.print(" val: ");
  Serial.println(n1);
  Serial.print("time: ");
  Serial.println(t2 - t1);
  Serial.println("Test1 done...");
  Serial.println();
}

// END OF FILE
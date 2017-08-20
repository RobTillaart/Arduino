//    FILE: testPinOutGroup.ino
//  AUTHOR: Rob dot Tillaart at gmail dot com
// VERSION: 0.1.0
// PURPOSE: demo PinOutGroup library for Arduino
// HISTORY:
//
// Released to the public domain
//

#include "PinOutGroup.h"

int ar[4] = {2, 3, 4, 13};

void setup()
{
  Serial.begin(115200);
  Serial.print("PINOUTGROUP_LIB_VERSION: ");
  Serial.println(PINOUTGROUP_LIB_VERSION);

  test0();
  test1();
  test2();
  test3();
  test4();
  test5();
  test6();
  test7();
  test8();

  Serial.println("done...");
}

void loop()
{
}

// TEST1 verifies and times basic working
void test0()
{
  int i = 3;
  // CHANGE 1 PINS
  pinMode(2, OUTPUT);
  uint32_t t1 = micros();
  digitalWrite(2, i++ % 2);
  digitalWrite(2, i++ % 2);
  digitalWrite(2, i++ % 2);
  digitalWrite(2, i++ % 2);
  uint32_t t2 = micros();

  Serial.println(t2 - t1);
  Serial.println("Test0 done...");
  Serial.println();
}


void test1()
{
  uint8_t n1, n2, n3, n4;
  PinOutGroup POG;
  POG.add(2);
  POG.add(4);
  POG.add(5);
  POG.add(13);

  Serial.print("size: ");
  Serial.println(POG.size());

  // CHANGE 1 PINS
  uint32_t t1 = micros();
  n1 = POG.set(B1000);
  uint32_t t2 = micros();

  // CHANGE 2 PINS
  uint32_t t3 = micros();
  n2 = POG.set(B0100);
  uint32_t t4 = micros();

  // CHANGE 3 PINS
  uint32_t t5 = micros();
  n3 = POG.set(B1010);
  uint32_t t6 = micros();

  // CHANGE 4 PINS
  uint32_t t7 = micros();
  n4 = POG.set(B0101);
  uint32_t t8 = micros();

  // RESET ALL
  POG.set(B0000);

  Serial.print(n1);
  Serial.print('\t');
  Serial.println(t2 - t1);
  Serial.print(n2);
  Serial.print('\t');
  Serial.println(t4 - t3);
  Serial.print(n3);
  Serial.print('\t');
  Serial.println(t6 - t5);
  Serial.print(n4);
  Serial.print('\t');
  Serial.println(t8 - t7);
  Serial.println("Test1 done...");
  Serial.println();
}

// TEST2 tests if a set() always matches a subsequent get().
void test2()
{
  PinOutGroup POG;
  POG.add(2);
  POG.add(4);
  POG.add(5);
  POG.add(13);
  POG.add(2);
  POG.add(4);
  POG.add(5);
  POG.add(13);

  for (int i = 0; i < 256; i++)
  {
    POG.set(i);
    int x = POG.get();
    if (x != i) Serial.println("fail test 2");
  }
  Serial.println("Test2 done...");
  Serial.println();
}

// TEST3 tests the adding of an array of pins
void test3()
{
  PinOutGroup POG;
  POG.add(4, ar );
  Serial.print("size: ");
  Serial.println(POG.size());
  Serial.println("Test3 done...");
  Serial.println();
}


// TEST 4 shows that a pin can be added multiple times
void test4()
{
  PinOutGroup POG;
  for (int i = 0; i < 8; i++)
  {
    POG.add(13);
  }
  POG.set(B01010101);
  Serial.print("size: ");
  Serial.println(POG.size());
  Serial.println("Test4 done...");
  Serial.println();
}


// TEST 5 simulates a LCD display
void test5()
{
  PinOutGroup POG;
  POG.add(4, ar);
  POG.add(4, ar);
  Serial.print("size: ");
  Serial.println(POG.size());
  int cnt = 0;
  char str[] = "Hello world. This is a test. The quick brown fox jumps over the lazy dog!";
  for (uint8_t i = 0; i < strlen(str); i++)
  {
    cnt += POG.set((uint8_t)str[i]);
  }
  Serial.print(" Printing: ");
  Serial.println(str);
  Serial.print("     Bits: ");
  Serial.println(strlen(str) * 8);         
  Serial.print("  Changed: ");
  Serial.println(cnt);         
  Serial.print("      AVG: ");
  Serial.println(1.0 * cnt / (strlen(str) * 8), 3);
  Serial.println("Test5 done...");
  Serial.println("footnote: test 5 uses ascii that only change in 5-6 bits max, which decreases the average");
  Serial.println("          That said, it is a real life application e.g. updating an LCD screen.");
  Serial.println();
}

//
// wrapper for test 6
//
void dw(const uint8_t pin, const uint8_t val)
{
  static uint8_t preVal = -1;
  if (preVal != val)
  {
    preVal = val;
    digitalWrite(pin, val);
  }
}


// TEST6 checks if cache trick works for digitalWrite too
void test6()
{
  uint8_t a[1000];
  randomSeed(1);
  for (int i = 0; i < 1000; i++) a[i] = random(2);

  pinMode(2, OUTPUT);
  uint32_t t1 = micros();
  for (int i = 0; i < 1000; i++)
  {
    digitalWrite(2, a[i]);
  }
  uint32_t t2 = micros();

  uint32_t t3 = micros();
  for (int i = 0; i < 1000; i++)
  {
    dw(2, a[i]);
  }
  uint32_t t4 = micros();

  Serial.println("random: average case");
  Serial.print("ORG: ");
  Serial.println(t2 - t1);
  Serial.print("NEW: ");
  Serial.println(t4 - t3);

  uint32_t t5 = micros();
  for (int i = 0; i < 1000; i++)
  {
    digitalWrite(2, LOW);
  }
  uint32_t t6 = micros();

  uint32_t t7 = micros();
  for (int i = 0; i < 1000; i++)
  {
    dw(2, LOW);
  }
  uint32_t t8 = micros();

  Serial.println("same: best case");
  Serial.print("ORG: ");
  Serial.println(t6 - t5);
  Serial.print("NEW: ");
  Serial.println(t8 - t7);

  t5 = micros();
  for (int i = 0; i < 1000; i++)
  {
    digitalWrite(2, i % 2);
  }
  t6 = micros();

  t7 = micros();
  for (int i = 0; i < 1000; i++)
  {
    dw(2, i % 2);
  }
  t8 = micros();

  Serial.println("toggle: worst case");
  Serial.print("ORG: ");
  Serial.println(t6 - t5);
  Serial.print("NEW: ");
  Serial.println(t8 - t7);

  Serial.println("Test6 done...");
  Serial.println();
}


// TEST7 tests average gain
void test7()
{
  PinOutGroup POG;
  // effectively 16 pins...
  POG.add(4, ar);
  POG.add(4, ar);
  POG.add(4, ar);
  POG.add(4, ar);
  
  uint8_t a[1000];
  randomSeed(1);
  for (int i = 0; i < 1000; i++) a[i] = random(32768);

  uint32_t t1 = micros();
  for (int i = 0; i < 1000; i++)
  {
    for (uint16_t b = 1; b; b <<= 1)
    {
      digitalWrite(2, a[i] & b);
    }
  }
  uint32_t t2 = micros();

  uint32_t t3 = micros();
  for (int i = 0; i < 1000; i++)
  {
    POG.set(a[i]);
  }
  uint32_t t4 = micros();

  Serial.println("1000x random bit: average case");
  Serial.print("ORG: ");
  Serial.println(t2 - t1);
  Serial.print("NEW: ");
  Serial.println(t4 - t3);

  Serial.println("Test7 done...");
  Serial.println();
}

// TEST8 tests free() 
void test8()
{
  PinOutGroup POG;
  Serial.print("size: ");
  Serial.println(POG.size());
  Serial.print("free: ");
  Serial.println(POG.free());
  
  POG.add(4, ar );
  
  Serial.print("size: ");
  Serial.println(POG.size());
  Serial.print("free: ");
  Serial.println(POG.free());
  
  Serial.println("Test8 done...");
  Serial.println();
}

// END OF FILE
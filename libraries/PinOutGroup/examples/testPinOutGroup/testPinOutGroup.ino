//    FILE: testPinOutGroup.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo PinOutGroup library for Arduino


#include "PinOutGroup.h"


uint8_t ar[4] = {2, 3, 4, 13};


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print(F("PINOUTGROUP_LIB_VERSION: "));
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

  Serial.println(F("done..."));
}


void loop()
{
}


void test0()
{
  Serial.println(__FUNCTION__);
  Serial.println(F("Time reference functionality.\n"));

  int i = 3;
  // CHANGE 1 PINS
  pinMode(2, OUTPUT);
  uint32_t t1 = micros();
  digitalWrite(2, i++ % 2);
  digitalWrite(2, i++ % 2);
  digitalWrite(2, i++ % 2);
  digitalWrite(2, i++ % 2);
  uint32_t t2 = micros();

  Serial.print(F("Time: "));
  Serial.println(t2 - t1);
  Serial.print(__FUNCTION__);
  Serial.println(F(" done..."));
  Serial.println();
}


void test1()
{
  Serial.println(__FUNCTION__);
  Serial.println(F("Time to change # pins.\n"));
  uint8_t n1, n2, n3, n4;
  PinOutGroup POG;
  POG.add(2);
  POG.add(4);
  POG.add(5);
  POG.add(13);

  Serial.print(F("size: "));
  Serial.println(POG.size());

  Serial.println("\n#PINS\tTIME");
  // CHANGE 1 PINS
  uint32_t t1 = micros();
  n1 = POG.write(B1000);
  uint32_t t2 = micros();

  // CHANGE 2 PINS
  uint32_t t3 = micros();
  n2 = POG.write(B0100);
  uint32_t t4 = micros();

  // CHANGE 3 PINS
  uint32_t t5 = micros();
  n3 = POG.write(B1010);
  uint32_t t6 = micros();

  // CHANGE 4 PINS
  uint32_t t7 = micros();
  n4 = POG.write(B0101);
  uint32_t t8 = micros();

  // RESET ALL
  POG.write(B0000);

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

  Serial.print(__FUNCTION__);
  Serial.println(F(" done..."));
  Serial.println();
}


void test2()
{
  Serial.println(__FUNCTION__);
  Serial.println(F("Does write() match subsequent read()."));
  Serial.println(F("No output is good!\n"));

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
    POG.write(i);
    int x = POG.read();
    if (x != i)
    {
      Serial.print("failed value: ");
      Serial.println(i);
    }
  }

  Serial.print(__FUNCTION__);
  Serial.println(F(" done..."));
  Serial.println();
}


void test3()
{
  Serial.println(__FUNCTION__);
  Serial.println(F("Test adding an array of pins."));

  PinOutGroup POG;
  POG.add(4, ar );
  Serial.print(F("size: "));
  Serial.println(POG.size());
  POG.add(4, ar );
  Serial.print(F("size: "));
  Serial.println(POG.size());

  Serial.print(__FUNCTION__);
  Serial.println(F(" done..."));
  Serial.println();
}


void test4()
{
  Serial.println(__FUNCTION__);
  Serial.println(F("Test adding a pin multiple times.\n"));

  PinOutGroup POG;
  Serial.print(F("size: "));
  Serial.println(POG.size());
  for (int i = 0; i < 8; i++)
  {
    POG.add(13);
    Serial.print(F("size: "));
    Serial.println(POG.size());
  }
  POG.write(B01010101);

  Serial.print(__FUNCTION__);
  Serial.println(F(" done..."));
  Serial.println();
}


void test5()
{
  Serial.println(__FUNCTION__);
  Serial.println(F("Simulates a 8 bit channel to LCD display.\n"));

  PinOutGroup POG;
  POG.add(4, ar);
  POG.add(4, ar);
  Serial.print(F("size: "));
  Serial.println(POG.size());
  int cnt = 0;
  char str[] = "Hello world. This is a test. The quick brown fox jumps over the lazy dog!";
  int len = strlen(str);
  for (uint8_t i = 0; i < len; i++)
  {
    cnt += POG.write((uint8_t)str[i]);
  }
  Serial.print(F("  Printing: "));
  Serial.println(str);
  Serial.print(F("Bits total: "));
  Serial.println(strlen(str) * 8);
  Serial.print(F("   Changed: "));
  Serial.println(cnt);
  Serial.print(F("     ratio: "));
  Serial.println(1.0 * cnt / (len * 8), 3);
  Serial.println();
  Serial.println(F("footnote: test 5 uses ascii that only change in 5-6 bits max, which decreases the average"));
  Serial.println(F("          That said, it is a real life application e.g. updating an LCD screen."));

  Serial.print(__FUNCTION__);
  Serial.println(F(" done..."));
  Serial.println();
}


// wrapper for test6()
void dw(const uint8_t pin, const uint8_t val)
{
  static uint8_t preVal = -1;
  if (preVal != val)
  {
    preVal = val;
    digitalWrite(pin, val);
  }
}


void test6()
{
  Serial.println(__FUNCTION__);
  Serial.println(F("Check if cache trick works for digitalWrite.\n"));

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

  Serial.println(F("random: average case"));
  Serial.print(F("ORG: "));
  Serial.println(t2 - t1);
  Serial.print(F("NEW: "));
  Serial.println(t4 - t3);
  Serial.print(F("  %: "));
  Serial.println(1.0 * (t4 - t3) / (t2 - t1));
  Serial.println();

  t1 = micros();
  for (int i = 0; i < 1000; i++)
  {
    digitalWrite(2, LOW);
  }
  t2 = micros();

  t3 = micros();
  for (int i = 0; i < 1000; i++)
  {
    dw(2, LOW);
  }
  t4 = micros();

  Serial.println(F("same: best case"));
  Serial.print(F("ORG: "));
  Serial.println(t2 - t1);
  Serial.print(F("NEW: "));
  Serial.println(t4 - t3);
  Serial.print(F("  %: "));
  Serial.println(1.0 * (t4 - t3) / (t2 - t1));
  Serial.println();

  t1 = micros();
  for (int i = 0; i < 1000; i++)
  {
    digitalWrite(2, i % 2);
  }
  t2 = micros();

  t3 = micros();
  for (int i = 0; i < 1000; i++)
  {
    dw(2, i % 2);
  }
  t4 = micros();

  Serial.println(F("toggle: worst case"));
  Serial.print(F("ORG: "));
  Serial.println(t2 - t1);
  Serial.print(F("NEW: "));
  Serial.println(t4 - t3);
  Serial.print(F("  %: "));
  Serial.println(1.0 * (t4 - t3) / (t2 - t1));
  Serial.println();

  Serial.print(__FUNCTION__);
  Serial.println(F(" done..."));
  Serial.println();
}


void test7()
{
  Serial.println(__FUNCTION__);
  Serial.println(F("Test average gain indication (simplified).\n"));

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
    POG.write(a[i]);
  }
  uint32_t t4 = micros();

  Serial.println(F("1000x random bit: average case"));
  Serial.print(F("ORG: "));
  Serial.println(t2 - t1);
  Serial.print(F("NEW: "));
  Serial.println(t4 - t3);
  Serial.print(F("  %: "));
  Serial.println(1.0 * (t4 - t3) / (t2 - t1));
  Serial.println();

  Serial.print(__FUNCTION__);
  Serial.println(F(" done..."));
  Serial.println();
}


void test8()
{
  Serial.println(__FUNCTION__);
  Serial.println(F("Test available()...\n"));

  PinOutGroup POG;
  Serial.print(F("size: "));
  Serial.println(POG.size());
  Serial.print(F("available: "));
  Serial.println(POG.available());

  POG.add(4, ar );

  Serial.print(F("size: "));
  Serial.println(POG.size());
  Serial.print(F("available: "));
  Serial.println(POG.available());

  Serial.print(__FUNCTION__);
  Serial.println(F(" done..."));
  Serial.println();
}


// -- END OF FILE --


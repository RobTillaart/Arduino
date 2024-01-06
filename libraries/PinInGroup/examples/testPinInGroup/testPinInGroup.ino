//    FILE: testPinInGroup.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo PinInGroup library for Arduino
//     URL: https://github.com/RobTillaart/PinInGroup


#include "PinInGroup.h"


uint8_t ar[4] = {2, 3, 4, 23};
uint8_t alt[] = {23, 22, 1, 3, 21, 19, 18, 5, 23, 22, 1, 3, 21, 19, 18, 5};


//  TEST0 verifies and times basic working
void test0()
{
  Serial.println();
  Serial.println(__FUNCTION__);
  delay(20);

  uint16_t n1 = 0;

  uint32_t t1 = micros();
  n1 = digitalRead(2) > 0;
  n1 <<= 1;
  n1 |= digitalRead(3) > 0;
  n1 <<= 1;
  n1 |= digitalRead(4) > 0;
  n1 <<= 1;
  n1 |= digitalRead(13) > 0;
  uint32_t t2 = micros();

  Serial.print(F(" val: "));
  Serial.println(n1, BIN);
  Serial.print(F("time: "));
  Serial.println(t2 - t1);
  Serial.print(F("time: "));
  Serial.println((1.0 * (t2 - t1)) / 4, 1);
  Serial.println(F("Test0 done..."));
  Serial.println();
}


void test1()
{
  Serial.println();
  Serial.println(__FUNCTION__);
  uint16_t n1;

  PinInGroup PIG;
  PIG.add(2);
  PIG.add(4);
  PIG.add(5);
  PIG.add(13);

  Serial.print("size: ");
  Serial.println(PIG.size());
  Serial.print("available: ");
  Serial.println(PIG.available());
  delay(20);

  uint32_t t1 = micros();
  n1 = PIG.read();
  uint32_t t2 = micros();

  Serial.print(F(" val: "));
  Serial.println(n1, BIN);
  Serial.print(F("time: "));
  Serial.println(t2 - t1);
  Serial.print(F("time: "));
  Serial.println((1.0 * (t2 - t1)) / PIG.size(), 1);
  Serial.println(F("Test1 done..."));
  Serial.println();
}


void test2()
{
  Serial.println();
  Serial.println(__FUNCTION__);

  uint16_t n1;

  PinInGroup PIG;

#if defined(ESP32) || defined(ESP8266)
  //  be careful which pins you use for ESP32  (and probably 8266 too, not tested)
  //  note: GPIO06 through GPIO11 are reserved for the FLASH.
  //        You cannot use them.  ==> pinMode() fails.
  //  https://github.com/espressif/arduino-esp32/issues/1411
  //
  for (uint8_t p = 20; p < 36; p++) PIG.add(p);
#else
  for (uint8_t p = 2; p < 14; p++) PIG.add(p);
#endif

  Serial.print(F("size: "));
  Serial.println(PIG.size());
  Serial.print(F("available: "));
  Serial.println(PIG.available());
  delay(20);

  uint32_t t1 = micros();
  n1 = PIG.read();
  uint32_t t2 = micros();

  Serial.print(F(" val: "));
  Serial.println(n1, BIN);
  Serial.print(F("time: "));
  Serial.println(t2 - t1);
  Serial.print(F("time: "));
  Serial.println((1.0 * (t2 - t1)) / PIG.size(), 1);
  Serial.println(F("Test2 done..."));
  Serial.println();
}


void test3()
{
  Serial.println();
  Serial.println(__FUNCTION__);

  uint16_t n1;

  PinInGroup PIG;
  PIG.add(4, ar, INPUT_PULLUP);
  PIG.add(4, ar, INPUT_PULLUP);
  PIG.add(4, ar, INPUT_PULLUP);
  PIG.add(4, ar, INPUT_PULLUP);

  Serial.print(F("size: "));
  Serial.println(PIG.size());
  Serial.print(F("available: "));
  Serial.println(PIG.available());

  PIG.add(4, ar, INPUT_PULLUP);  //  should not be added

  Serial.print(F("size: "));
  Serial.println(PIG.size());
  Serial.print(F("available: "));
  Serial.println(PIG.available());
  Serial.println();
  delay(20);
  PIG.clear();

  for (int i = 1; i <= 16; i++)
  {
    PIG.add(23);
    uint32_t t1 = micros();
    n1 = PIG.read();
    uint32_t t2 = micros();
    float timePerPin2 = (1.0 * t2 - t1) / i;

    Serial.print(i);
    Serial.print('\t');
    Serial.print(t2 - t1);
    Serial.print('\t');
    Serial.print(timePerPin2);
    Serial.print('\t');
    Serial.println(n1, BIN);
    delay(20);
  }

  Serial.println(F("Test3 done..."));
  Serial.println();
}


void test4()
{
  Serial.println();
  Serial.println(__FUNCTION__);

  uint16_t n1;

  PinInGroup PIG;
  PIG.add(4, ar, INPUT_PULLUP);
  PIG.add(4, ar, INPUT_PULLUP);
  PIG.add(4, ar, INPUT_PULLUP);
  PIG.add(4, ar, INPUT_PULLUP);

  Serial.print(F("size: "));
  Serial.println(PIG.size());
  Serial.print(F("available: "));
  Serial.println(PIG.available());

  PIG.clear();
  PIG.add(4, ar, INPUT_PULLUP);  //  should not be added

  Serial.print(F("size: "));
  Serial.println(PIG.size());
  Serial.print(F("available: "));
  Serial.println(PIG.available());
  delay(20);

  uint32_t t1 = micros();
  n1 = PIG.read();
  uint32_t t2 = micros();

  Serial.print(F(" val: "));
  Serial.println(n1, BIN);
  Serial.print(F("time: "));
  Serial.println(t2 - t1);
  Serial.print(F("time: "));
  Serial.println((1.0 * (t2 - t1)) / PIG.size(), 1);
  Serial.println(F("Test4 done..."));
  Serial.println();
}


void test5()
{
  Serial.println();
  Serial.println(__FUNCTION__);

  uint16_t n1 = 0;

  uint32_t t1 = micros();
  n1 = digitalRead(2) > 0;
  n1 <<= 1;
  n1 |= digitalRead(3) > 0;
  n1 <<= 1;
  n1 |= digitalRead(4) > 0;
  n1 <<= 1;
  n1 |= digitalRead(13) > 0;
  uint32_t t2 = micros();
  float timePerPin = (1.0 * t2 - t1) / 4;

  Serial.print(F(" val: "));
  Serial.println(n1, BIN);
  Serial.print(F("time: "));
  Serial.println(t2 - t1);
  Serial.print(F("time: "));
  Serial.println(timePerPin);
  Serial.println();

  PinInGroup PIG;

  for (int i = 1; i <= 16; i++)
  {
    PIG.add(2);
    t1 = micros();
    n1 = PIG.read();
    t2 = micros();
    float timePerPin2 = (1.0 * t2 - t1) / i;

    Serial.print(i);
    Serial.print('\t');
    Serial.print(t2 - t1);
    Serial.print('\t');
    Serial.print(timePerPin2);
    Serial.print('\t');
    Serial.println(timePerPin2 / timePerPin * 100.0);
    delay(20);
  }

  Serial.println(F("Test5 done..."));
  Serial.println();
}


void test6()
{
  Serial.println();
  Serial.println(__FUNCTION__);

  uint16_t n1 = 0;

  PinInGroup PIG;

  //  verify pin stays same place in output.
  //  connect selected pin to GND and it should stay on same spot.
  //  even when pins are added.
  for (int i = 1; i <= 10; i++)
  {
    PIG.add(i, INPUT_PULLUP);
    n1 = PIG.read() + 32768;

    Serial.print(i);
    Serial.print('\t');
    Serial.print(n1, BIN);
    Serial.print('\n');
  }

  Serial.println(F("Test6 done..."));
  Serial.println();
}


///////////////////////////////////////////////////////////////////////////////////

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  Serial.print(F("\nPININGROUP_LIB_VERSION: "));
  Serial.println(PININGROUP_LIB_VERSION);
  Serial.println();

  test0();
  test1();
  test2();
  test3();
  test4();
  test5();
  test6();

  Serial.println(F("done..."));
}


void loop()
{
}


//  -- END OF FILE --


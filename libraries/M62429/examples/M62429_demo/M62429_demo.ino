//
//    FILE: M62429_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo volume IC FM62429
//    DATE: 2020-08-02


#include "M62429.h"

uint32_t start, stop;

M62429  AMP;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println("\nTest takes a ~2 minutes.\n");

  AMP.begin(4, 5);

  start = millis();

  test_channel(0);
  test_channel(1);
  test_channel(2); // both
  test_mute(0);
  test_mute(1);
  test_average();

  stop = millis();
  Serial.print("\nTest duration (s) : ");
  Serial.println((stop - start) * 0.001);

  Serial.println("\nDone...");
}


void loop()
{
}


void test_channel(uint8_t ch)
{
  Serial.print(__FUNCTION__);
  Serial.print('\t');
  Serial.println(ch);
  Serial.println("0..max in ~10 seconds");
  for (int i = 0; i < 255; i += 10)
  {
    AMP.setVolume(ch, i);
    Serial.print(i); Serial.print(' ');
    delay(200);
  }
  Serial.println();
  Serial.println("max..0 in ~10 seconds");
  for (int i = 255; i > 0; i -= 10)
  {
    AMP.setVolume(ch, i);
    Serial.print(i); Serial.print(' ');
    delay(200);
  }
  Serial.println();

  Serial.println("0..max..0 ");
  float v = 1;
  float factor = 1.3;
  AMP.setVolume(ch, v);
  while (v  < 255 / factor)
  {
    AMP.setVolume(ch, v);
    v *= factor;
    Serial.print(v, 0); Serial.print(' ');
    delay(100);
  }
  while (v > 1)
  {
    AMP.setVolume(ch, v);
    Serial.print(v, 0); Serial.print(' ');
    v /= factor;
    delay(100);
  }
  Serial.println();

  Serial.println("getVolume()");
  for (int i = 0; i < 255; i++)
  {
    AMP.setVolume(ch, i);
    if (AMP.getVolume(ch) != i)
    {
      Serial.print("FAIL GETVOLUME: ");
      Serial.println(i);
    }
    delay(10);
  }
  AMP.setVolume(ch, 0);
  Serial.println();

  Serial.println("incr()");
  AMP.setVolume(ch, 0);
  for (int i = 0; i < 255; i++)
  {
    AMP.incr();
    delay(10);
  }
  Serial.println("decr()");
  for (int i = 0; i < 255; i++)
  {
    AMP.decr();
    delay(10);
  }
  AMP.setVolume(2, 0);
  Serial.println();
  Serial.println();
}


void test_mute(uint8_t ch)
{
  Serial.print(__FUNCTION__);
  Serial.print('\t');
  Serial.println(ch);
  Serial.println("mute");
  for (int i = 0; i < 255; i++)
  {
    if (i % 20 == 0) Serial.print('.');
    AMP.setVolume(ch, i);
    delay(10);
    AMP.muteOn();
    if (AMP.isMuted() == false)
    {
      Serial.print("FAIL muteOn(): ");
      Serial.println(i);
    }
    delay(10);
    AMP.muteOff();
    if (AMP.isMuted() == true)
    {
      Serial.print("FAIL muteOff(): ");
      Serial.println(i);
    }
    if (AMP.getVolume(ch) != i)
    {
      Serial.print("FAIL getVolume(): ");
      Serial.println(i);
    }
    delay(10);
  }
  AMP.setVolume(2, 0);
  Serial.println();
  Serial.println();
}


void test_average()
{
  Serial.println(__FUNCTION__);
  Serial.println("average");

  for (int i = 0; i < 100; i++)
  {
    AMP.setVolume(0, random(255));
    AMP.setVolume(1, random(255));
    Serial.print(AMP.getVolume(0));
    Serial.print(" + ");
    Serial.print(AMP.getVolume(1));
    Serial.print("\t=> ");
    delay(100);
    AMP.average();
    Serial.println(AMP.getVolume(0));
    if (AMP.getVolume(0) != AMP.getVolume(1))
    {
      Serial.println("FAIL average()");
    }
    delay(100);
  }
  AMP.setVolume(2, 0);
  Serial.println();
  Serial.println();
}


//  -- END OF FILE --


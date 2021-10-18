//
//    FILE: averageAngle.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2017-11-21
// PURPOSE: demonstrates the usage of the AverageAngle Class
//

#include "AverageAngle.h"


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  test0();
  test1();
  test2(1000);
  test3(1000);
  test4();
  test5();
  test6();
  test7();
  test8();
  test9();
  test10(1000);
}

void loop()
{
}

void test0()
{
  AverageAngle AA(AverageAngle::DEGREES);

  AA.reset();
  AA.add(10, 10);
  int cnt = AA.count();
  float avg = AA.getAverage();
  float len = AA.getAverageLength();

  Serial.println(__FUNCTION__);
  Serial.print("COUNT:\t");
  Serial.println(cnt);
  Serial.print("AVG:\t");
  Serial.println(avg, 6);
  Serial.print("LEN:\t");
  Serial.println(len, 6);
  Serial.println("EXPECT:\t10, 10");
  Serial.println();
}

void test1()
{
  AverageAngle AA(AverageAngle::DEGREES);

  AA.reset();
  for (int i = 0; i < 10; i++)
  {
    AA.add(i, i);
  }
  int cnt = AA.count();
  float avg = AA.getAverage();
  float len = AA.getAverageLength();

  Serial.println(__FUNCTION__);
  Serial.print("COUNT:\t");
  Serial.println(cnt);
  Serial.print("AVG:\t");
  Serial.println(avg, 6);
  Serial.print("LEN:\t");
  Serial.println(len, 6);
  Serial.println("EXPECT:\t6.33, 4.5");
  Serial.println();
}

void test2(int count)
{
  AverageAngle AA(AverageAngle::DEGREES);

  AA.reset();
  for (int i = 0; i < count; i++)
  {
    AA.add(random(180), random(10));
  }
  int cnt = AA.count();
  float avg = AA.getAverage();
  float len = AA.getAverageLength();

  Serial.println(__FUNCTION__);
  Serial.print("COUNT:\t");
  Serial.println(cnt);
  Serial.print("AVG:\t");
  Serial.println(avg, 6);
  Serial.print("LEN:\t");
  Serial.println(len, 6);
  Serial.println("EXPECT:\t~90, 2.85");
  Serial.println();
}

void test3(int count)
{
  AverageAngle AA(AverageAngle::RADIANS);

  AA.reset();
  for (int i = 0; i < count; i++)
  {
    AA.add( PI / 180 * random(180), random(10));
  }
  int cnt = AA.count();
  float avg = AA.getAverage();
  float len = AA.getAverageLength();

  Serial.println(__FUNCTION__);
  Serial.print("COUNT:\t");
  Serial.println(cnt);
  Serial.print("AVG:\t");
  Serial.println(avg, 6);
  Serial.print("LEN:\t");
  Serial.println(len, 6);
  Serial.println("EXPECT:\t~PI/2, 2.93");
  Serial.println();
}

void test4()
{
  AverageAngle AA(AverageAngle::DEGREES);

  AA.reset();

  AA.add(358, 1);
  AA.add(359, 2);
  AA.add(0, 3);
  AA.add(1, 2);
  AA.add(2, 1);

  int cnt = AA.count();
  float avg = AA.getAverage();
  float len = AA.getAverageLength();

  Serial.println(__FUNCTION__);
  Serial.print("COUNT:\t");
  Serial.println(cnt);
  Serial.print("AVG:\t");
  Serial.println(avg, 6);
  Serial.print("LEN:\t");
  Serial.println(len, 6);
  Serial.println("EXPECT:\t~0, 1.8");
  Serial.println();
}

void test5()
{
  AverageAngle AA(AverageAngle::DEGREES);

  AA.reset();

  AA.add(357, 3);
  AA.add(358, 1);
  AA.add(359, 5);
  AA.add(360, 1);
  AA.add(1, 3);

  int cnt = AA.count();
  float avg = AA.getAverage();
  float len = AA.getAverageLength();

  Serial.println(__FUNCTION__);
  Serial.print("COUNT:\t");
  Serial.println(cnt);
  Serial.print("AVG:\t");
  Serial.println(avg, 6);
  Serial.print("LEN:\t");
  Serial.println(len, 6);
  Serial.println("EXPECT:\t~359, 2.6");
  Serial.println();
}

void test6()
{
  AverageAngle AA(AverageAngle::DEGREES);

  AA.reset();

  AA.add(359, 5);
  AA.add(360, 3);
  AA.add(361, 2);
  AA.add(362, 3);
  AA.add(363, 5);

  int cnt = AA.count();
  float avg = AA.getAverage();
  float len = AA.getAverageLength();

  Serial.println(__FUNCTION__);
  Serial.print("COUNT:\t");
  Serial.println(cnt);
  Serial.print("AVG:\t");
  Serial.println(avg, 6);
  Serial.print("LEN:\t");
  Serial.println(len, 6);
  Serial.println("EXPECT:\t~1, 3.6");
  Serial.println();
}

void test7()
{
  AverageAngle AA(AverageAngle::DEGREES);
  AverageAngle BB(AverageAngle::RADIANS);
  Serial.println(__FUNCTION__);
  Serial.print("AA:\t");
  Serial.println(AA.type());
  Serial.print("BB:\t");
  Serial.println(BB.type());
  Serial.println("EXPECT:\tAA=0 BB=1");
  Serial.println();
}

void test8()
{
  AverageAngle AA(AverageAngle::DEGREES);

  AA.reset();
  int cnt = AA.count();
  float avg = AA.getAverage();
  float len = AA.getAverageLength();

  Serial.println(__FUNCTION__);
  Serial.print("COUNT:\t");
  Serial.println(cnt);
  Serial.print("AVG:\t");
  Serial.println(avg, 6);
  Serial.print("LEN:\t");
  Serial.println(len, 6);
  Serial.println("EXPECT:\t0, 0");
  Serial.println();
}

void test9()
{
  AverageAngle AA(AverageAngle::DEGREES);

  AA.reset();
  AA.add(0);
  int cnt = AA.count();
  float avg = AA.getAverage();
  float len = AA.getAverageLength();

  Serial.println(__FUNCTION__);
  Serial.print("COUNT:\t");
  Serial.println(cnt);
  Serial.print("AVG:\t");
  Serial.println(avg, 6);
  Serial.print("AVGLEN:\t");
  Serial.println(len, 6);
  Serial.println("EXPECT:\t0, 1");
  Serial.println();
}

void test10(int count)
{
  AverageAngle AA(AverageAngle::DEGREES);

  AA.reset();
  for (int i = 0; i < count; i++)
  {
    AA.add(random(180), random(10));
  }
  int cnt = AA.count();
  float avg = AA.getAverage();
  float len = AA.getTotalLength();

  Serial.println(__FUNCTION__);
  Serial.print("COUNT:\t");
  Serial.println(cnt);
  Serial.print("AVG:\t");
  Serial.println(avg, 6);
  Serial.print("TOTLEN:\t");
  Serial.println(len, 6);
  Serial.println("EXPECT:\t90, ~2500-3000");
  Serial.println();
}

// END OF FILE
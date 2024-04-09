//
//    FILE: averageAngle.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demonstrates the usage of the AverageAngle Class
//     URL: https://github.com/RobTillaart/AverageAngle


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
}


void loop()
{
}


void test0()
{
  AverageAngle AA(AverageAngle::DEGREES);

  AA.reset();
  AA.add(10);
  int cnt = AA.count();
  float avg = AA.getAverage();

  Serial.println(__FUNCTION__);
  Serial.print("COUNT:\t");
  Serial.println(cnt);
  Serial.print("AVG:\t");
  Serial.println(avg, 6);
  Serial.println("EXPECT:\t10");
  Serial.println();
}


void test1()
{
  AverageAngle AA(AverageAngle::DEGREES);

  AA.reset();
  for (int i = 0; i < 10; i++)
  {
    AA.add(i);
  }
  int cnt = AA.count();
  float avg = AA.getAverage();

  Serial.println(__FUNCTION__);
  Serial.print("COUNT:\t");
  Serial.println(cnt);
  Serial.print("AVG:\t");
  Serial.println(avg, 6);
  Serial.println("EXPECT:\t4.5");
  Serial.println();
}


void test2(int count)
{
  AverageAngle AA(AverageAngle::DEGREES);

  AA.reset();
  for (int i = 0; i < count; i++)
  {
    AA.add(random(180));
  }
  int cnt = AA.count();
  float avg = AA.getAverage();

  Serial.println(__FUNCTION__);
  Serial.print("COUNT:\t");
  Serial.println(cnt);
  Serial.print("AVG:\t");
  Serial.println(avg, 6);
  Serial.println("EXPECT:\t~90");
  Serial.println();
}


void test3(int count)
{
  AverageAngle AA(AverageAngle::RADIANS);

  AA.reset();
  for (int i = 0; i < count; i++)
  {
    AA.add( PI / 180 * random(180));
  }
  int cnt = AA.count();
  float avg = AA.getAverage();

  Serial.println(__FUNCTION__);
  Serial.print("COUNT:\t");
  Serial.println(cnt);
  Serial.print("AVG:\t");
  Serial.println(avg, 6);
  Serial.println("EXPECT:\t~PI/2");
  Serial.println();
}


void test4()
{
  AverageAngle AA(AverageAngle::DEGREES);

  AA.reset();

  AA.add(358);
  AA.add(359);
  AA.add(0);
  AA.add(1);
  AA.add(2);

  int cnt = AA.count();
  float avg = AA.getAverage();

  Serial.println(__FUNCTION__);
  Serial.print("COUNT:\t");
  Serial.println(cnt);
  Serial.print("AVG:\t");
  Serial.println(avg, 6);
  Serial.println("EXPECT:\t~0");
  Serial.println();
}


void test5()
{
  AverageAngle AA(AverageAngle::DEGREES);

  AA.reset();

  AA.add(357);
  AA.add(358);
  AA.add(359);
  AA.add(360);
  AA.add(1);

  int cnt = AA.count();
  float avg = AA.getAverage();

  Serial.println(__FUNCTION__);
  Serial.print("COUNT:\t");
  Serial.println(cnt);
  Serial.print("AVG:\t");
  Serial.println(avg, 6);
  Serial.println("EXPECT:\t~359");
  Serial.println();
}


void test6()
{
  AverageAngle AA(AverageAngle::DEGREES);

  AA.reset();

  AA.add(359);
  AA.add(360);
  AA.add(361);
  AA.add(362);
  AA.add(363);

  int cnt = AA.count();
  float avg = AA.getAverage();

  Serial.println(__FUNCTION__);
  Serial.print("COUNT:\t");
  Serial.println(cnt);
  Serial.print("AVG:\t");
  Serial.println(avg, 6);
  Serial.println("EXPECT:\t~1");
  Serial.println();
}


void test7()
{
  AverageAngle AA(AverageAngle::DEGREES);
  AverageAngle BB(AverageAngle::RADIANS);
  AverageAngle CC(AverageAngle::GRADIANS);

  Serial.println(__FUNCTION__);
  Serial.print("AA:\t");
  Serial.println(AA.type());
  Serial.print("BB:\t");
  Serial.println(BB.type());
  Serial.println("CC:\t");
  Serial.println(CC.type());
  Serial.println("EXPECT:\tAA=0 BB=1 CC=2");
  Serial.println();
}

//  -- END OF FILE --

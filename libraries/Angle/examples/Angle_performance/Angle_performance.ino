//
//    FILE: Angle_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo sketch to test angle class
//     URL: https://github.com/RobTillaart/Angle.git


#include "Angle.h"


Angle a(1, 2, 3, 4);
Angle b(45, 30);
Angle c(2, 3, 4, 5);
Angle n(0);
Angle z(5.5);

Angle aa(-1, 2, 3, 45);
Angle bb(0, -2, 3, 45);
Angle cc(0, 0, -3, 45);
Angle dd(0, 0, 0, -45);

uint32_t start, stop;


void testConstructors()
{
  Serial.println(__FUNCTION__);
  char str1[] = "-45.987654321";

  delay(100);
  start = micros();
  Angle s(str1);
  stop = micros();
  Serial.println(stop - start);
  Serial.println(s);

  delay(100);
  start = micros();
  Angle t = str1;
  stop = micros();
  Serial.println(stop - start);
  Serial.println(t);

  Serial.println();
}


void testToDouble()
{
  Serial.println(__FUNCTION__);

  delay(100);
  start = micros();
  float s = a.toDouble();
  stop = micros();
  Serial.println(stop - start);
  Serial.println(s, 7);

  delay(100);
  start = micros();
  s = aa.toDouble();
  stop = micros();
  Serial.println(stop - start);
  Serial.println(s, 7);

  delay(100);
  start = micros();
  aa.fromRadians(2 * PI);
  stop = micros();
  Serial.println(stop - start);
  Serial.println(aa);

  Serial.println();
}


void testParts()
{
  Serial.println(__FUNCTION__);

  delay(100);
  start = micros();
  float s = c.sign();
  stop = micros();
  Serial.println(stop - start);
  Serial.println(s, 7);
  
  delay(100);
  start = micros();
  s = c.degree();
  stop = micros();
  Serial.println(stop - start);
  Serial.println(s, 7);
  
  delay(100);
  start = micros();
  s = c.minute();
  stop = micros();
  Serial.println(stop - start);
  Serial.println(s, 7);
  
  delay(100);
  start = micros();
  s = c.second();
  stop = micros();
  Serial.println(stop - start);
  Serial.println(s, 7);
  
  delay(100);
  start = micros();
  s = c.tenthousand();
  stop = micros();
  Serial.println(stop - start);
  Serial.println(s, 7);

  Serial.println();
}


void testCompare()
{
  Serial.println(__FUNCTION__);

  delay(100);
  start = micros();
  bool b = (a == a);
  stop = micros();
  Serial.println(stop - start);
  Serial.println(b);


  Serial.println();
}


void testNegate()
{
  Serial.println(__FUNCTION__);

  delay(100);
  start = micros();
  a = -a;
  stop = micros();
  Serial.println(stop - start);
  Serial.println(b);

  Serial.println();
}


void testAdd()
{
  Serial.println(__FUNCTION__);

  delay(100);
  start = micros();
  Angle d = a + b;
  stop = micros();
  Serial.println(stop - start);
  Serial.println(d);

  float rnd = random(36000) / 100.0 - 180;
  delay(100);
  start = micros();
  d = a + rnd;
  stop = micros();
  Serial.println(stop - start);
  Serial.println(d);

  Serial.println();
}


void testMultiply()
{
  Serial.println(__FUNCTION__);

  a = 5.25;
  delay(100);
  start = micros();
  a = a * 5.5;
  stop = micros();
  Serial.println(stop - start);
  Serial.println(a);

  float rnd = random(36000) / 100.0 - 180;
  delay(100);
  start = micros();
  a = a * rnd;
  stop = micros();
  Serial.println(stop - start);
  Serial.println(a);

  Serial.println();
}




void testDivide()
{
  Serial.println(__FUNCTION__);

  a = 5.25;
  delay(100);
  start = micros();
  a = a / 5.5;
  stop = micros();
  Serial.println(stop - start);
  Serial.println(a);

  float rnd = random(36000) / 100.0 - 180;
  delay(100);
  start = micros();
  a = a / rnd;
  stop = micros();
  Serial.println(stop - start);
  Serial.println(a);

  Serial.println();
}


void testRatio()
{
  Serial.println(__FUNCTION__);

  a = 7.50;
  b = 57.456789;
  delay(100);
  start = micros();
  float s = a / b;
  stop = micros();
  Serial.println(stop - start);
  Serial.println(s);

  Serial.println();
}


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("ANGLE_LIB_VERSION: ");
  Serial.println(ANGLE_LIB_VERSION);

  testConstructors();
  testToDouble();
  testParts();
  testNegate();
  testCompare();
  testAdd();
  testMultiply();
  testDivide();
  testRatio();

  Serial.println("\nDone...");
}


void loop()
{
}


//  -- END OF FILE --

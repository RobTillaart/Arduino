//
//    FILE: test_angle01.ino
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


void testConstructors()
{
  Serial.println("\n1. print -- Angle(d, m, s, t)");
  Serial.println(a);
  Serial.println(b);
  Serial.println(c);
  Serial.println(n);
  Serial.println(z);

  Serial.println("\n1. print -- negative angles");

  Serial.println(aa);
  Serial.println(bb);
  Serial.println(cc);
  Serial.println(dd);

  Serial.println("\n1. Constructor(char *)");
  char str1[] = "179.999999999";
  Angle s(str1);
  Angle t = str1;
  Serial.println(str1);
  Serial.println(s);
  Serial.println(s.toDouble(), 9);
  Serial.println(t);
  t = s.toDouble();
  Serial.println(t);

  char str2[] = "-45.987654321";
  Angle u(str2);
  Angle v = str2;
  Serial.println(u);
  Serial.println(u.toDouble(), 9);
  Serial.println(v);

  char str3[] = "-0.987654321";
  Angle uu(str3);
  Angle vv = str2;
  Serial.println(uu);
  Serial.println(uu.toDouble(), 9);
  Serial.println(vv);
}


void testToDouble()
{
  Serial.println("\n2.1 toDouble  -- Angle(double)   toRadians()");
  Serial.println(a.toDouble(), 7);
  Serial.println(b.toDouble(), 7);
  Serial.println(c.toDouble(), 7);
  Serial.println();
  Angle d(c.toDouble());
  Serial.println(c);
  Serial.println(d);
  Serial.println(c.toDouble(), 7);
  Serial.println(d.toDouble(), 7);
  Serial.println(c.toRadians(), 7);
  d = 180;
  Serial.println(d.toRadians(), 7);

  Serial.println("\n2.2 toDouble  -- negative angles");
  Serial.println(aa);
  Serial.println(aa.toDouble(), 7);
  Serial.println(bb);
  Serial.println(bb.toDouble(), 7);
  Serial.println(cc);
  Serial.println(cc.toDouble(), 7);
  Serial.println(dd);
  Serial.println(dd.toDouble(), 7);
  Serial.println();

  Serial.println("\n2.3 toDouble - fromRadians");
  aa.fromRadians(2 * PI);
  Serial.println(aa);
  aa.fromRadians(PI);
  Serial.println(aa);
  aa.fromRadians(PI / 2);
  Serial.println(aa);
  aa.fromRadians(PI / 3);
  Serial.println(aa);
  aa.fromRadians(PI / 4);
  Serial.println(aa);
  aa.fromRadians(PI / 6);
  Serial.println(aa);
  aa.fromRadians(PI / 12);
  Serial.println(aa);
  aa.fromRadians(PI / 18);
  Serial.println(aa);
  aa.fromRadians(PI / 36);
  Serial.println(aa);
  aa.fromRadians(PI / 180);
  Serial.println(aa);

  Serial.println();
}


void testParts()
{
  Serial.println("\n3. degrees, minutes, seconds, thousands");
  Serial.println(c);
  Serial.println(c.sign());
  Serial.println(c.degree());
  Serial.println(c.minute());
  Serial.println(c.second());
  Serial.println(c.tenthousand());

  Serial.println(cc);
  Serial.println(cc.sign());
  Serial.println(cc.degree());
  Serial.println(cc.minute());
  Serial.println(cc.second());
  Serial.println(cc.tenthousand());
}


void testCompare()
{
  Serial.println("\n4. Compare: a op a  op:  ==  !=  <  <=  >  >=");
  Serial.println("   should be 100101");
  Serial.println(a);
  Serial.print(a == a);
  Serial.print(a != a);
  Serial.print(a <  a);
  Serial.print(a <= a);
  Serial.print(a >  a);
  Serial.print(a >= a);
  Serial.println();

  Serial.println("\n4. Compare: a op c  op:  ==  !=  <  <=  >  >=");
  Serial.println("   should be 011100");  // A < C
  Serial.println(a);
  Serial.println(c);
  Serial.print(a == c);
  Serial.print(a != c);
  Serial.print(a <  c);
  Serial.print(a <= c);
  Serial.print(a >  c);
  Serial.print(a >= c);
  Serial.println();

  Serial.println("\n4. Compare: -a op c  op:  ==  !=  <  <=  >  >=");
  Serial.println("   should be 011100");  // A < C
  a = -a;
  Serial.println(a);
  Serial.println(c);
  Serial.print(a == c);
  Serial.print(a != c);
  Serial.print(a <  c);
  Serial.print(a <= c);
  Serial.print(a >  c);
  Serial.print(a >= c);
  Serial.println();

  Serial.println("\n4. Compare: -a op -c  op:  ==  !=  <  <=  >  >=");
  Serial.println("   should be 010011");  // C < A
  c = -c;
  Serial.println(a);
  Serial.println(c);
  Serial.print(a == c);
  Serial.print(a != c);
  Serial.print(a <  c);
  Serial.print(a <= c);
  Serial.print(a >  c);
  Serial.print(a >= c);
  Serial.println();
}


void testNegate()
{
  Serial.println("\n6. negate  ");
  Serial.println(a);
  a = -a;
  Serial.println(a);
  a = -a;
  Serial.println(a);
  Angle tt(0, 1, 2, 3);
  Serial.println(-tt);
  Angle uu(0, 0, 2, 3);
  Serial.println(-uu);
  Angle vv(0, 0, 0, 3);
  Serial.println(-vv);
  Angle ww(0, 0, 0, 0);
  Serial.println(-ww);
}


void testAdd()
{
  Serial.println("\n7.1 Add  +");
  for (int x = -1; x < 2; x++)
    for (int y = -1; y < 2; y++)
    {
      a = x;
      b = y;
      Angle d = a + b;
      Serial.print(a);
      Serial.print("\t+\t");
      Serial.print(b);
      Serial.print("\t=\t");
      Serial.println(d);
    }

  Serial.println("\n7.2 Add  +=");
  for (int x = -1; x < 2; x++)
    for (int y = -1; y < 2; y++)
    {
      a = x;
      b = y;
      Serial.print(a);
      Serial.print("\t+=\t");
      Serial.print(b);
      Serial.print("\tresults in\t");
      a += b;
      Serial.println(a);
    }

  Serial.println("\n7.3 Add  - 1000 random tests - no output is ok");
  for (int i = 0; i < 1000; i++)
  {
    double x = random(36000) / 100.0 - 180;
    double y = random(36000) / 100.0 - 180;
    double z = x + y;
    a = x;
    b = y;
    Angle d = a + b;
    if ( abs(d.toDouble() - z) > 0.001)
    {
      Serial.print(i);
      Serial.print("\t");
      Serial.print(Angle(x));
      Serial.print("\t");
      Serial.print(Angle(y));
      Serial.print("\t");
      Serial.print(z);
      Serial.print("\t");
      Serial.print(Angle(z));
      Serial.print("\t");
      Serial.print(d.toDouble());
      Serial.print("\t");
      Serial.print(d);
      Serial.println();
    }
  }

  Serial.println("\n7.4 Add  - 1000 random tests - no output is ok");
  for (int i = 0; i < 1000; i++)
  {
    double x = random(200) / 100.0 - 1;
    double y = random(200) / 100.0 - 1;
    double z = x + y;
    a = x;
    b = y;
    Angle d = a + b;
    if ( abs(d.toDouble() - z) > 0.00001)
    {
      Serial.print(i);
      Serial.print("\t");
      Serial.print(Angle(x));
      Serial.print("\t");
      Serial.print(Angle(y));
      Serial.print("\t");
      Serial.print(z);
      Serial.print("\t");
      Serial.print(Angle(z));
      Serial.print("\t");
      Serial.print(d.toDouble());
      Serial.print("\t");
      Serial.print(d);
      Serial.println();
    }
  }

  Serial.println("\n7.5 Add a double to an angle ");
  for (int i = 0; i < 10; i++)
  {
    double x = random(36000) / 100.0 - 180;
    double y = random(36000) / 100.0 - 180;
    a = x;
    b = y;
    Angle d = a + y;
    Serial.print(i);
    Serial.print("\t");
    Serial.print(x);
    Serial.print("\t");
    Serial.print(y);
    Serial.print("\t");
    Serial.print(d);
    Serial.println();
  }
}


void testSubtract()
{
  Serial.println("\n8.1 Subtract  -");
  for (int x = -1; x < 2; x++)
    for (int y = -1; y < 2; y++)
    {
      a = x;
      b = y;
      Angle d = a - b;
      Serial.print(a);
      Serial.print("\t-\t");
      Serial.print(b);
      Serial.print("\t=\t");
      Serial.println(d);
    }

  Serial.println("\n8.2 Subtract  -=");
  for (int x = -1; x < 2; x++)
    for (int y = -1; y < 2; y++)
    {
      a = x;
      b = y;
      Serial.print(a);
      Serial.print("\t-=\t");
      Serial.print(b);
      Serial.print("\tresults in\t");
      a -= b;
      Serial.println(a);
    }

  Serial.println("\n8.3 Sub - 1000 random tests - no output is ok");
  for (int i = 0; i < 1000; i++)
  {
    double x = random(36000) / 100.0 - 180;
    double y = random(36000) / 100.0 - 180;
    double z = x - y;
    a = x;
    b = y;
    Angle d = a - b;
    if ( abs(d.toDouble() - z) > 0.001)
    {
      Serial.print(i);
      Serial.print("\t");
      Serial.print(Angle(x));
      Serial.print("\t");
      Serial.print(Angle(y));
      Serial.print("\t");
      Serial.print(z);
      Serial.print("\t");
      Serial.print(Angle(z));
      Serial.print("\t");
      Serial.print(d.toDouble());
      Serial.print("\t");
      Serial.print(d);
      Serial.println();
    }
  }

  Serial.println("\n8.4 Sub - 1000 random tests - no output is ok");
  for (int i = 0; i < 1000; i++)
  {
    double x = random(200) / 100.0 - 1;
    double y = random(200) / 100.0 - 1;
    double z = x - y;
    a = x;
    b = y;
    Angle d = a - b;
    if ( abs(d.toDouble() - z) > 0.00001)
    {
      Serial.print(i);
      Serial.print("\t");
      Serial.print(Angle(x));
      Serial.print("\t");
      Serial.print(Angle(y));
      Serial.print("\t");
      Serial.print(z);
      Serial.print("\t");
      Serial.print(Angle(z));
      Serial.print("\t");
      Serial.print(d.toDouble());
      Serial.print("\t");
      Serial.print(d);
      Serial.println();
    }
  }

}


void testMultiply()
{
  Serial.println("\n9. Multiply  *  *=");
  a = 5.25;
  Serial.println(a);
  a = a * 5.5;
  Serial.println(a);
  a *= 3.1;
  Serial.println(a);
}


void testDivide()
{
  Serial.println("\n10. Divide  /  /=");
  Serial.println(a);
  Angle d = a / 3.1;
  Serial.println(d);
  d /= 5.5;
  Serial.println(d);
  d /= PI;
  Serial.println(d);
}


void testRatio()
{
  Serial.println("\n11. Ratio");
  a = 7.50;
  b = 57.456789;
  Serial.println(a);
  Serial.println(b);
  Serial.println(b / a, 7);
  a = 180;
  b = 57.295779513082320876798154814105;  //  one radian
  Serial.println(a);
  Serial.println(b);
  Serial.println(a / b, 7);  //  should be PI
}


void setup()
{
  Serial.begin(115200);
  Serial.println("Start test_angle01");
  Serial.print("lib version: ");
  Serial.println(ANGLE_LIB_VERSION);

  testConstructors();
  testToDouble();
  testParts();
  testNegate();
  testCompare();
  testAdd();
  testSubtract();
  testMultiply();
  testDivide();
  testRatio();

  Serial.println("\nDone...");
}


void loop()
{
}


//  -- END OF FILE --


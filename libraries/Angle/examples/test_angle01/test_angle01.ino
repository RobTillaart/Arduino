//
//    FILE: test_angle01.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.02
// PURPOSE: demo sketch to test angle class
//    DATE: 2015-07-30
//     URL:
//
// Released to the public domain
//

#include "Angle.h"

Angle a(1, 2, 3, 4);
Angle b(45, 30);
Angle c(2, 3, 4, 5);
Angle n(0);
Angle z(5.5);

void setup()
{
  Serial.begin(115200);
  Serial.println("Start test_angle01");
  Serial.print("lib version: ");
  Serial.println(ANGLE_LIB_VERSION);

  Serial.println("\n1. print -- Angle(d, m, s, t)");
  Serial.println(a);
  Serial.println(b);
  Serial.println(c);
  Serial.println(n);
  Serial.println(z);

  Serial.println("\n2. toDouble  -- Angle(double)   toRadians()");
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

  Serial.println("\n3. degrees, minutes, seconds, thousands");
  Serial.println(c);
  Serial.println(c.degree());
  Serial.println(c.minute());
  Serial.println(c.second());
  Serial.println(c.tenthousand());

  Serial.println("\n4. Compare: a op a  op :  ==  !=  <  <=  >  >=  ");
  Serial.print(a == a);
  Serial.print(a != a);
  Serial.print(a <  a);
  Serial.print(a <= a);
  Serial.print(a >  a);
  Serial.print(a >= a);
  Serial.println();

  Serial.println("\n5. Compare: a op c  op :  ==  !=  <  <=  >  >=  ");
  Serial.print(a == c);
  Serial.print(a != c);
  Serial.print(a <  c);
  Serial.print(a <= c);
  Serial.print(a >  c);
  Serial.print(a >= c);
  Serial.println();

  Serial.println("\n6. negate  ");
  Serial.println(a);
  a = -a;
  Serial.println(a);
  a = -a;
  Serial.println(a);

  Serial.println("\n7.1 Add  +");
  for (int x = -1; x < 2; x++)
    for (int y = -1; y < 2; y++)
    {
      a = x;
      b = y;
      d = a + b;
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

  Serial.println("\n8.1 Subtract  -");
  for (int x = -1; x < 2; x++)
    for (int y = -1; y < 2; y++)
    {
      a = x;
      b = y;
      d = a - b;
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

  Serial.println("\n9. Multiply  *  *=");
  a = 5.25;
  Serial.println(a);
  a = a * 5.5;
  Serial.println(a);
  a *= 3.1;
  Serial.println(a);

  Serial.println("\n10. Divide  /  /=");
  Serial.println(a);
  d = a / 3.1;
  Serial.println(d);
  d /= 5.5;
  Serial.println(d);
  d /= PI;
  Serial.println(d);


  Serial.println("\n11. Ratio");
  a = 7.50;
  b = 57.456789;
  Serial.println(a);
  Serial.println(b);
  Serial.println(b / a, 7);
  a = 180;
  b = 57.295779513082320876798154814105; // one radian
  Serial.println(a);
  Serial.println(b);
  Serial.println(a / b, 7);  // should be PI

  Serial.println("\n12. Constructor(char *)");
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

  Serial.println("\nDone...");
  //
  //
  //  start = micros();
  //
  //  stop = micros();
  //  Serial.println(stop - start);
}

void loop()
{
}

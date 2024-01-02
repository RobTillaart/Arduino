//
//    FILE: complex.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2013-09-23
// PURPOSE: demo complex
//     URL: https://github.com/RobTillaart/Complex
//
//  Serial.print(Complex) supported since 0.1.05


#include "Complex.h"


void setup()
{
  Serial.begin(115200);
  Serial.print("\n  Complex numbers test for Arduino: ");
  Serial.println(COMPLEX_LIB_VERSION);
  Serial.println("\n1. Print Complex, set, real, imag");

  Complex c1(10.0, -2.0);
  Complex c2(3, 0);
  Complex c3(-10, 4);
  Complex c4(-5,-5);
  Complex c5(0, 0);

  Serial.println(one);
  Serial.println(c1);
  Serial.println(c2);
  Serial.println(c3);
  Serial.println(c4);
  c3.set(0,0);
  Serial.println(c3);
  Serial.println(c3.real());
  Serial.println(c3.imag());

  Serial.println("\n2. ==  != ");
  c5 = c1;
  if (c5 == c1) Serial.println("ok :)");
  else Serial.println(" fail :(");
  c5 = c1 + 1;
  if (c5 != c1) Serial.println("ok :)");
  else Serial.println(" fail :(");
  c5 = 3;
  if (c5 == 3) Serial.println("ok :)");
  else Serial.println(" fail :(");


  Serial.println("\n3. negation - ");
  c5 = -c1;
  Serial.println(c5);
  c5 = -c5;
  Serial.println(c5);
  if (c5 == c1) Serial.println("ok :)");
  else Serial.println(" fail :(");


  Serial.println("\n4. + - ");
  c5 = c1 + c2;
  Serial.println(c5);
  c5 = c1 + 3;
  Serial.println(c5);
  c5 = c1 - c2;
  Serial.println(c5);
  c5 = c1 - 3;
  Serial.println(c5);


  Serial.println("\n5. * / ");
  c5 = c1 * c2;
  Serial.println(c5);
  c5 = c5 * 3;
  Serial.println(c5);
  c5 = c5 / c2;
  Serial.println(c5);
  c5 = c5 / 3;
  Serial.println(c5);

  c5 = c1 / c2 * c2;
  Serial.println(c5);
  c5 = c1 * c4 / c4;
  Serial.println(c5);


  Serial.println("\n6. assign += -= *= /=");
  c5 = c1;
  c5 += c1;
  Serial.println(c5);
  c5 += 3;
  Serial.println(c5);
  c5 -= c1;
  Serial.println(c5);
  c5 -= 3;
  Serial.println(c5);
  c5 *= c1;
  Serial.println(c5);
  c5 *= 3;
  Serial.println(c5);
  c5 /= c1;
  Serial.println(c5);
  c5 /= 3;
  Serial.println(c5);


  Serial.println("\n7. phase modulus polar");
  Serial.println(c1);
  double m = c1.modulus();
  Serial.println(m);
  double p = c1.phase();
  Serial.println(p);
  c5.polar(m, p);
  Serial.println(c5);


  Serial.println("\n8. conjugate reciprocal");
  c5 = c1.conjugate();
  Serial.println(c5);
  c5 = c5.conjugate();
  Serial.println(c5);
  c5 = c1.reciprocal();
  Serial.println(c5);
  c5 = c5.reciprocal();
  Serial.println(c5);

  Serial.println("\n9. power: exp log pow sqrt sqr logn log10");
  c5 = c1.c_sqr();
  Serial.println(c5);
  c5 = c1.c_exp();
  Serial.println(c5);
  c5 = c5.c_log();
  Serial.println(c5);
  c5 = c1.c_pow(2);
  Serial.println(c5);
  c5 = c5.c_sqrt();
  Serial.println(c5);
  c5 = c5.c_sqr();
  Serial.println(c5);
  c5 = c1.c_pow(c2);
  Serial.println(c5);
  c5 = c5.c_pow(c2.reciprocal());
  Serial.println(c5);
  c5 = c5.c_logn(c4);
  Serial.println(c5);
  c5 = c4.c_pow(c5);
  Serial.println(c5);
  c5 = c5.c_log10();
  Serial.println(c5);

  Serial.println("\n10. gonio: sin cos tan asin acos atan");
  c1.set(0.5, 0.5);
  c5 = c1.c_sin();
  Serial.println(c5);
  c5 = c5.c_asin();
  Serial.println(c5);
  c5 = c1.c_cos();
  Serial.println(c5);
  c5 = c5.c_acos();
  Serial.println(c5);
  c5 = c1.c_tan();
  Serial.println(c5);
  c5 = c5.c_atan();
  Serial.println(c5);

  Serial.println("\n11. gonio csc sec cot acsc asec acot");
  c1.set(0.5, 0.5);
  c5 = c1.c_csc();
  Serial.println(c5);
  c5 = c5.c_acsc();
  Serial.println(c5);
  c5 = c1.c_sec();
  Serial.println(c5);
  c5 = c5.c_asec();
  Serial.println(c5);
  c5 = c1.c_cot();
  Serial.println(c5);
  c5 = c5.c_acot();
  Serial.println(c5);

  Serial.println("\n12. gonio hyperbolicus I ");
  c1.set(0.5, 0.5);
  c5 = c1.c_sinh();
  Serial.println(c5);
  c5 = c5.c_asinh();
  Serial.println(c5);
  c5 = c1.c_cosh();
  Serial.println(c5);
  c5 = c5.c_acosh();
  Serial.println(c5);
  c5 = c1.c_tanh();
  Serial.println(c5);
  c5 = c5.c_atanh();
  Serial.println(c5);

  Serial.println("\n13. gonio hyperbolicus II ");
  c1.set(0.5, 0.5);
  c5 = c1.c_csch();
  Serial.println(c5);
  c5 = c5.c_acsch();
  Serial.println(c5);
  c5 = c1.c_sech();
  Serial.println(c5);
  c5 = c5.c_asech();
  Serial.println(c5);
  c5 = c1.c_coth();
  Serial.println(c5);
  c5 = c5.c_acoth();
  Serial.println(c5);

  Serial.println("\n14. gonio bug fix (minimal) test");
  c1.set(3, 4);
  Serial.println(c1);
  c2 = c1.c_sin();
  c2 = c2 * c2;
  c3 = c1.c_cos();
  c3 = c3 * c3;
  Serial.println(c2 + c3);   // should print 1, 0i

  Serial.println("\n.. Complex done");

  uint32_t start = micros();
  for (int i = 0; i < 1000; i++)
  {
    c5 = c5.c_csc();
  }
  uint32_t dur = micros() - start;
  Serial.println(dur);
  Serial.println(one);
}


void loop()
{
}


//  -- END OF FILE --


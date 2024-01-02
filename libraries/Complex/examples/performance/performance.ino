//
//    FILE: performance.ino
//  AUTHOR: Rob Tillaart
//    DATE: 2013-09-23
// PURPOSE: test complex math
//     URL: https://github.com/RobTillaart/Complex
//
//  Serial.print(Complex) supported since 0.1.05


#include "Complex.h"

unsigned long start, stop, total;
double re, im, m, p;


void setup()
{
  Serial.begin(115200);
  Serial.print("\n  Complex numbers performance test for Arduino: ");
  Serial.println(COMPLEX_LIB_VERSION);
  Serial.println();

  start = micros();
  Complex c1(10.0, -2.0);
  Complex c2(3, 0);
  Complex c3(-10, 4);
  Complex c4(-5,-5);
  Complex c5(0, 0);
  stop = micros();
  Serial.print("5 constructors\t");
  Serial.println(stop - start);
  total += (stop - start);

  start = micros();
  for(uint8_t i=0; i< 100; i++) c3.set(0,0);
  stop = micros();
  Serial.print("set(0,0)\t");
  Serial.println(stop - start);
  total += (stop - start);

  start = micros();
  for(uint8_t i=0; i< 100; i++) c5 = c1 + 1;
  stop = micros();
  Serial.print("c1 + 1  \t");
  Serial.println(stop - start);
  total += (stop - start);

  start = micros();
  for(uint8_t i=0; i< 100; i++) c5 = c1 + c2;
  stop = micros();
  Serial.print("c1 + c2\t\t");
  Serial.println(stop - start);
  total += (stop - start);

  start = micros();
  for(uint8_t i=0; i< 100; i++) c5 += c2;
  stop = micros();
  Serial.print("+= c2\t\t");
  Serial.println(stop - start);
  total += (stop - start);

  start = micros();
  for(uint8_t i=0; i< 100; i++) c5 = -c1;
  stop = micros();
  Serial.print("c5 = -c1\t");
  Serial.println(stop - start);
  total += (stop - start);

  start = micros();
  for(uint8_t i=0; i< 100; i++) c5 = c1 - 3;
  stop = micros();
  Serial.print("c1 - 3\t\t");
  Serial.println(stop - start);
  total += (stop - start);

  start = micros();
  for(uint8_t i=0; i< 100; i++) c5 = c1 - c2;
  stop = micros();
  Serial.print("c1 - c2\t\t");
  Serial.println(stop - start);
  total += (stop - start);

  start = micros();
  for(uint8_t i=0; i< 100; i++) c5 -= c2;
  stop = micros();
  Serial.print("c5 -= c2\t");
  Serial.println(stop - start);
  total += (stop - start);

  start = micros();
  for(uint8_t i=0; i< 100; i++) c5 = c1 * 3;
  stop = micros();
  Serial.print("c1 * 3\t\t");
  Serial.println(stop - start);
  total += (stop - start);

  start = micros();
  for(uint8_t i=0; i< 100; i++) c5 = c1 * c2;
  stop = micros();
  Serial.print("c1 * c2\t\t");
  Serial.println(stop - start);
  total += (stop - start);

  start = micros();
  for(uint8_t i=0; i< 100; i++) c5 *= c2;
  stop = micros();
  Serial.print("c5 *= c2\t");
  Serial.println(stop - start);
  total += (stop - start);

  start = micros();
  for(uint8_t i=0; i< 100; i++) c5 = c1 / 3;
  stop = micros();
  Serial.print("c1 / 3\t\t");
  Serial.println(stop - start);
  total += (stop - start);

  start = micros();
  for(uint8_t i=0; i< 100; i++) c5 = c1 / c2;
  stop = micros();
  Serial.print("c1 / c2\t\t");
  Serial.println(stop - start);
  total += (stop - start);

  start = micros();
  for(uint8_t i=0; i< 100; i++) c5 /= c2;
  stop = micros();
  Serial.print("c5 /= c2\t");
  Serial.println(stop - start);
  total += (stop - start);

  Serial.println();

  start = micros();
  for(uint8_t i=0; i< 100; i++) re = c1.real();
  stop = micros();
  Serial.print("real()\t\t");
  Serial.println(stop - start);
  total += (stop - start);

  start = micros();
  for(uint8_t i=0; i< 100; i++) im = c1.imag();
  stop = micros();
  Serial.print("imag()\t\t");
  Serial.println(stop - start);
  total += (stop - start);

  start = micros();
  for(uint8_t i=0; i< 100; i++) m = c1.modulus();
  stop = micros();
  Serial.print("modulus()\t");
  Serial.println(stop - start);
  total += (stop - start);

  start = micros();
  for(uint8_t i=0; i< 100; i++) p = c1.phase();
  stop = micros();
  Serial.print("phase\t\t");
  Serial.println(stop - start);
  total += (stop - start);

  start = micros();
  for(uint8_t i=0; i< 100; i++) c5.polar(m, p);
  stop = micros();
  Serial.print("polar()\t\t");
  Serial.println(stop - start);
  total += (stop - start);

  start = micros();
  for(uint8_t i=0; i< 100; i++) c5 = c1.conjugate();
  stop = micros();
  Serial.print("conjugate()\t");
  Serial.println(stop - start);
  total += (stop - start);

  start = micros();
  for(uint8_t i=0; i< 100; i++) c5 = c1.reciprocal();
  stop = micros();
  Serial.print("reciprocal();\t");
  Serial.println(stop - start);
  total += (stop - start);

  Serial.println();

  start = micros();
  for(uint8_t i=0; i< 100; i++) c5 = c1.c_sqr();
  stop = micros();
  Serial.print("c_sqr()\t\t");
  Serial.println(stop - start);
  total += (stop - start);

  start = micros();
  for(uint8_t i=0; i< 100; i++) c5 = c1.c_exp();
  stop = micros();
  Serial.print("c_exp()\t\t");
  Serial.println(stop - start);
  total += (stop - start);

  start = micros();
  for(uint8_t i=0; i< 100; i++) c5 = c5.c_log();
  stop = micros();
  Serial.print("c_log()\t\t");
  Serial.println(stop - start);
  total += (stop - start);

  start = micros();
  for(uint8_t i=0; i< 100; i++) c5 = c1.c_pow(2);
  stop = micros();
  Serial.print("c_pow(2)\t");
  Serial.println(stop - start);
  total += (stop - start);

  start = micros();
  for(uint8_t i=0; i< 100; i++) c5 = c5.c_sqrt();
  stop = micros();
  Serial.print("c_sqrt()\t");
  Serial.println(stop - start);
  total += (stop - start);

  start = micros();
  for(uint8_t i=0; i< 100; i++) c5 = c5.c_logn(c4);
  stop = micros();
  Serial.print("c_logn(c4)\t");
  Serial.println(stop - start);
  total += (stop - start);

  start = micros();
  for(uint8_t i=0; i< 100; i++) c5 = c4.c_pow(c5);
  stop = micros();
  Serial.print("c_pow(c5)\t");
  Serial.println(stop - start);
  total += (stop - start);

  start = micros();
  for(uint8_t i=0; i< 100; i++) c5 = c5.c_log10();
  stop = micros();
  Serial.print("c_log10()\t");
  Serial.println(stop - start);
  total += (stop - start);

  Serial.println();
  c1.set(0.5, 0.5);

  start = micros();
  for(uint8_t i=0; i< 100; i++) c5 = c1.c_sin();
  stop = micros();
  Serial.print("c_sin()\t\t");
  Serial.println(stop - start);
  total += (stop - start);

  start = micros();
  for(uint8_t i=0; i< 100; i++) c5 = c5.c_asin();
  stop = micros();
  Serial.print("c_asin()\t");
  Serial.println(stop - start);

  start = micros();
  for(uint8_t i=0; i< 100; i++) c5 = c1.c_cos();
  stop = micros();
  Serial.print("c_cos()\t\t");
  Serial.println(stop - start);
  total += (stop - start);

  start = micros();
  for(uint8_t i=0; i< 100; i++) c5 = c5.c_acos();
  stop = micros();
  Serial.print("c_acos()\t");
  Serial.println(stop - start);
  total += (stop - start);

  start = micros();
  for(uint8_t i=0; i< 100; i++) c5 = c1.c_tan();
  stop = micros();
  Serial.print("c_tan()\t\t");
  Serial.println(stop - start);
  total += (stop - start);

  start = micros();
  for(uint8_t i=0; i< 100; i++) c5 = c5.c_atan();
  stop = micros();
  Serial.print("c_atan()\t");
  Serial.println(stop - start);
  total += (stop - start);

  Serial.println();
  c1.set(0.5, 0.5);

  start = micros();
  for(uint8_t i=0; i< 100; i++) c5 = c1.c_csc();
  stop = micros();
  Serial.print("c_csc()\t\t");
  Serial.println(stop - start);
  total += (stop - start);

  start = micros();
  for(uint8_t i=0; i< 100; i++) c5 = c5.c_acsc();
  stop = micros();
  Serial.print("c_acsc()\t");
  Serial.println(stop - start);
  total += (stop - start);

  start = micros();
  for(uint8_t i=0; i< 100; i++) c5 = c1.c_sec();
  stop = micros();
  Serial.print("c_sec()\t\t");
  Serial.println(stop - start);
  total += (stop - start);

  start = micros();
  for(uint8_t i=0; i< 100; i++) c5 = c5.c_asec();
  stop = micros();
  Serial.print("c_asec()\t");
  Serial.println(stop - start);
  total += (stop - start);

  start = micros();
  for(uint8_t i=0; i< 100; i++) c5 = c1.c_cot();
  stop = micros();
  Serial.print("c_cot()\t\t");
  Serial.println(stop - start);
  total += (stop - start);

  start = micros();
  for(uint8_t i=0; i< 100; i++) c5 = c5.c_acot();
  stop = micros();
  Serial.print("c_acot()\t");
  Serial.println(stop - start);
  total += (stop - start);

  Serial.println();
  c1.set(0.5, 0.5);

  start = micros();
  for(uint8_t i=0; i< 100; i++) c5 = c1.c_sinh();
  stop = micros();
  Serial.print("c_sinh()\t");
  Serial.println(stop - start);
  total += (stop - start);

  start = micros();
  for(uint8_t i=0; i< 100; i++) c5 = c5.c_asinh();
  stop = micros();
  Serial.print("c_asinh()\t");
  Serial.println(stop - start);
  total += (stop - start);

  start = micros();
  for(uint8_t i=0; i< 100; i++) c5 = c1.c_cosh();
  stop = micros();
  Serial.print("c_cosh()\t");
  Serial.println(stop - start);
  total += (stop - start);

  start = micros();
  for(uint8_t i=0; i< 100; i++) c5 = c5.c_acosh();
  stop = micros();
  Serial.print("c_acosh()\t");
  Serial.println(stop - start);
  total += (stop - start);

  start = micros();
  for(uint8_t i=0; i< 100; i++) c5 = c1.c_tanh();
  stop = micros();
  Serial.print("c_tanh()\t");
  Serial.println(stop - start);
  total += (stop - start);

  start = micros();
  for(uint8_t i=0; i< 100; i++) c5 = c5.c_atanh();
  stop = micros();
  Serial.print("c_atanh()\t");
  Serial.println(stop - start);
  total += (stop - start);

  Serial.println();
  c1.set(0.5, 0.5);

  start = micros();
  for(uint8_t i=0; i< 100; i++) c5 = c1.c_csch();
  stop = micros();
  Serial.print("c_csch()\t");
  Serial.println(stop - start);
  total += (stop - start);

  start = micros();
  for(uint8_t i=0; i< 100; i++) c5 = c5.c_acsch();
  stop = micros();
  Serial.print("c_acsch()\t");
  Serial.println(stop - start);
  total += (stop - start);

  start = micros();
  for(uint8_t i=0; i< 100; i++) c5 = c1.c_sech();
  stop = micros();
  Serial.print("c_sech()\t");
  Serial.println(stop - start);
  total += (stop - start);

  start = micros();
  for(uint8_t i=0; i< 100; i++) c5 = c5.c_asech();
  stop = micros();
  Serial.print("c_asech()\t");
  Serial.println(stop - start);
  total += (stop - start);

  start = micros();
  for(uint8_t i=0; i< 100; i++) c5 = c1.c_coth();
  stop = micros();
  Serial.print("c_coth()\t");
  Serial.println(stop - start);
  total += (stop - start);

  start = micros();
  for(uint8_t i=0; i< 100; i++) c5 = c5.c_acoth();
  stop = micros();
  Serial.print("c_acoth()\t");
  Serial.println(stop - start);
  total += (stop - start);

  Serial.println();
  Serial.println(total);
  Serial.println("\n.. Complex done");
}


void loop()
{
}


//  -- END OF FILE --


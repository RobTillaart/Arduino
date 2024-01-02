//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-16
// PURPOSE: unit tests for the Complex datatype Library
//          https://github.com/RobTillaart/Complex
//          https://github.com/Arduino-CI/arduino_ci/blob/master/REFERENCE.md
//

// supported assertions
// ----------------------------
// assertEqual(expected, actual)
// assertNotEqual(expected, actual)
// assertLess(expected, actual)
// assertMore(expected, actual)
// assertLessOrEqual(expected, actual)
// assertMoreOrEqual(expected, actual)
// assertTrue(actual)
// assertFalse(actual)
// assertNull(actual)
// assertNotNull(actual)


#include <ArduinoUnitTests.h>


#include "Complex.h"


unittest_setup()
{
  fprintf(stderr, "COMPLEX_LIB_VERSION: %s\n", (char *) COMPLEX_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constructor)
{
  Complex c1(10.0, -2.0);
  Complex c2(3, 0);
  Complex c3(-10, 4);
  Complex c4(-5,-5);
  Complex c5;        //  (0, 0)

  assertEqual(10.0, c1.real());
  assertEqual(-2.0, c1.imag());
  assertEqual( 3.0, c2.real());
  assertEqual( 0.0, c2.imag());
  assertEqual(-10,  c3.real());
  assertEqual(4.0,  c3.imag());
  assertEqual(-5.0, c4.real());
  assertEqual(-5.0, c4.imag());
  assertEqual(0.0, c5.real());
  assertEqual(0.0, c5.imag());

  //  one is a default available var.
  assertEqual(1.0, one.real());
  assertEqual(0.0, one.imag());

  //  polar notation setter.
  c1.polar(5, PI/4);
  assertEqualFloat(5, c1.modulus(), 0.0001);
  assertEqualFloat(PI/4, c1.phase(), 0.0001);
}


unittest(test_basic_math)
{
  Complex a(10.0, -2.5);
  Complex b(3, 1);

  Complex c1 = a + b;
  assertEqual(13, c1.real());
  assertEqual(-1.5, c1.imag());

  Complex c2 = a - b;
  assertEqual(7,  c2.real());
  assertEqual(-3.5, c2.imag());

  Complex c3 = a * b;
  assertEqual(32.5,  c3.real());
  assertEqual(2.5,  c3.imag());

  Complex c4 = a / b;
  assertEqual(2.75, c4.real());
  assertEqual(-1.75, c4.imag());

  Complex c5 = -a;
  assertEqual(-10, c5.real());
  assertEqual(2.5, c5.imag());

  a += b;
  assertEqual(13, a.real());
  assertEqual(-1.5, a.imag());

  a -= b;
  assertEqual(10,  a.real());
  assertEqual(-2.5, a.imag());

  a *= b;
  assertEqual(32.5,  a.real());
  assertEqual(2.5,  a.imag());

  a /= b;
  assertEqual(10, a.real());
  assertEqual(-2.5, a.imag());
}


unittest(test_basic_functions)
{
  Complex a;
  assertEqual(0, a.real());
  assertEqual(0, a.imag());

  a.set(5, 34);
  assertEqual(5, a.real());
  assertEqual(34, a.imag());

  a.setReal(10);
  assertEqual(10, a.real());
  assertEqual(34, a.imag());

  a.setImag(-2.5);
  assertEqual(10, a.real());
  assertEqual(-2.5, a.imag());

  float ph = a.phase();
  assertEqualFloat(-0.244979, ph, 0.0001);

  float mod = a.modulus();
  assertEqualFloat(10.3078, mod, 0.0001);

  Complex conj = a.conjugate();
  assertEqual(10, conj.real());
  assertEqual(2.5, conj.imag());

  Complex reci = a.reciprocal();
  assertEqualFloat(0.0941176, reci.real(), 0.0001);
  assertEqualFloat(0.0235294, reci.imag(), 0.0001);

  reci *= a;
  assertEqualFloat(1.0, reci.real(), 0.0001);
  assertEqualFloat(0, reci.imag(), 0.0001);
}


unittest(test_power_functions)
{
  Complex a(3, 4);
  Complex b;

  b = a.c_sqrt();
  assertEqual(2, b.real());
  assertEqual(1, b.imag());

  b = a.c_sqr();
  assertEqual(-7, b.real());
  assertEqual(24, b.imag());

  b = a.c_exp();
  assertEqualFloat(-13.1288, b.real(), 0.0001);
  assertEqualFloat(-15.2008, b.imag(), 0.0001);

  b = a.c_log();
  assertEqualFloat(1.60944, b.real(), 0.0001);
  assertEqualFloat(0.927295, b.imag(), 0.0001);

  b = a.c_log10();
  assertEqualFloat(0.69897, b.real(), 0.0001);
  assertEqualFloat(0.402719, b.imag(), 0.0001);

  b = a.c_pow(a);
  assertEqualFloat(-2.99799, b.real(), 0.0001);
  assertEqualFloat(0.623786, b.imag(), 0.0001);

  b = a.c_logn(a);
  assertEqual(1, b.real());
  assertEqual(0, b.imag());
}


unittest(test_gonio_functions_I)
{
  Complex a(3, 4);
  Complex b;

  b = a.c_sin();
  assertEqualFloat(3.85374, b.real(), 0.0001);
  assertEqualFloat(-27.0168, b.imag(), 0.0001);

  b = a.c_cos();
  assertEqualFloat(-27.0349, b.real(), 0.0001);
  assertEqualFloat(-3.85115, b.imag(), 0.0001);

  b = a.c_tan();
  assertEqualFloat(-0.000187318, b.real(), 0.0001);
  assertEqualFloat(0.999356, b.imag(), 0.0001);

  b = a.c_asin();
  assertEqualFloat(0.633984, b.real(), 0.0001);
  assertEqualFloat(2.30551, b.imag(), 0.0001);

  b = a.c_acos();
  assertEqualFloat(0.936813, b.real(), 0.0001);
  assertEqualFloat(-2.30551, b.imag(), 0.0001);

  b = a.c_atan();
  assertEqualFloat(1.44831, b.real(), 0.0001);
  assertEqualFloat(0.158997, b.imag(), 0.0001);
}


unittest_main()


//  -- END OF FILE --


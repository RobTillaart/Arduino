//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2020-12-23
// PURPOSE: unit tests for the FLE
//          https://github.com/RobTillaart/FLE
//          https://github.com/Arduino-CI/arduino_ci/blob/master/REFERENCE.md
//

// supported assertions
// https://github.com/Arduino-CI/arduino_ci/blob/master/cpp/unittest/Assertion.h#L33-L42
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


#include "Arduino.h"
#include "FLE.h"


unittest_setup()
{
  fprintf(stderr, "FLE_LIB_VERSION: %s\n", (char*) FLE_LIB_VERSION);
}


unittest_teardown()
{
}


unittest(test_constructor)
{
  FLE zero;
  assertEqualFloat(0.0, zero.value(), 0.001);
  assertEqualFloat(0.0, zero.error(), 0.001);

  FLE one(1);
  assertEqualFloat(1.0, one.value(), 0.001);
  assertEqualFloat(0.0, one.error(), 0.001);

  FLE PIE(PI);
  assertEqualFloat(PI, PIE.value(), 0.001);
  assertEqualFloat(0.0, PIE.error(), 0.001);

  FLE PIEP(22.0 / 7.0, PI - 22.0 / 7.0);
  assertEqualFloat(PI, PIEP.value(), 0.01);
  assertEqualFloat(0.0, PIEP.error(), 0.01);

  FLE PIEQ(355.0 / 113.0, PI - 355.0 / 113.0);
  assertEqualFloat(PI, PIEQ.value(), 0.001);
  assertEqualFloat(0.0, PIEQ.error(), 0.001);

  FLE EE(EULER);
  assertEqualFloat(EULER, EE.value(), 0.001);
  assertEqualFloat(0.0, EE.error(), 0.001);

  FLE x(2, 0.1);
  assertEqualFloat(2.0, x.value(), 0.001);
  assertEqualFloat(0.1, x.error(), 0.001);

  FLE y(7, 0.3);
  assertEqualFloat(7.0, y.value(), 0.001);
  assertEqualFloat(0.3, y.error(), 0.001);
}

///////////////////////////////////////////////

unittest(test_high_low)
{
  FLE a(2, 0.1);
  FLE b(3, 0.5);

  assertEqualFloat(2.1, a.high(), 0.001);
  assertEqualFloat(1.9, a.low(), 0.001);
  assertEqualFloat(3.5, b.high(), 0.001);
  assertEqualFloat(2.5, b.low(), 0.001);
  
  FLE c(a.high(), b.low());
  assertEqualFloat(a.high(), c.value(), 0.001);
  assertEqualFloat(b.low(), c.error(), 0.001);
}


///////////////////////////////////////////////

unittest(test_basic_math_zero_error_I)
{
  FLE a(2);
  FLE b(3);

  FLE c = a;
  assertEqualFloat(2, c.value(), 0.001);
  assertEqualFloat(0, c.error(), 0.001);
  assertEqualFloat(0, c.relError(), 0.001);

  c = b;
  assertEqualFloat(3, c.value(), 0.001);
  assertEqualFloat(0, c.error(), 0.001);
  assertEqualFloat(0, c.relError(), 0.001);

  c = -b;
  assertEqualFloat(-3, c.value(), 0.001);
  assertEqualFloat(0, c.error(), 0.001);
  assertEqualFloat(0, c.relError(), 0.001);

  c = 8;
  assertEqualFloat(8, c.value(), 0.001);
  assertEqualFloat(0, c.error(), 0.001);
  assertEqualFloat(0, c.relError(), 0.001);

  c = -9;
  assertEqualFloat(-9, c.value(), 0.001);
  assertEqualFloat(0, c.error(), 0.001);
  assertEqualFloat(0, c.relError(), 0.001);

  c = a + b;
  assertEqualFloat(5, c.value(), 0.001);
  assertEqualFloat(0, c.error(), 0.001);
  assertEqualFloat(0, c.relError(), 0.001);

  c = b + a;
  assertEqualFloat(5, c.value(), 0.001);
  assertEqualFloat(0, c.error(), 0.001);
  assertEqualFloat(0, c.relError(), 0.001);

  c = a - b;
  assertEqualFloat(-1, c.value(), 0.001);
  assertEqualFloat(0, c.error(), 0.001);
  assertEqualFloat(0, c.relError(), 0.001);

  c = b - a;
  assertEqualFloat(1, c.value(), 0.001);
  assertEqualFloat(0, c.error(), 0.001);
  assertEqualFloat(0, c.relError(), 0.001);

  c = a * b;
  assertEqualFloat(6, c.value(), 0.001);
  assertEqualFloat(0, c.error(), 0.001);
  assertEqualFloat(0, c.relError(), 0.001);

  c = b * a;
  assertEqualFloat(6, c.value(), 0.001);
  assertEqualFloat(0, c.error(), 0.001);
  assertEqualFloat(0, c.relError(), 0.001);

  c = a / b;
  assertEqualFloat(0.666666, c.value(), 0.001);
  assertEqualFloat(0, c.error(), 0.001);
  assertEqualFloat(0, c.relError(), 0.001);

  c = b / a;
  assertEqualFloat(1.5, c.value(), 0.001);
  assertEqualFloat(0, c.error(), 0.001);
  assertEqualFloat(0, c.relError(), 0.001);

}


unittest(test_basic_math_zero_error_II)
{
  FLE a(2);
  FLE b(3);

  FLE c = a;
  c += b;
  assertEqualFloat(5, c.value(), 0.001);
  assertEqualFloat(0, c.error(), 0.001);
  assertEqualFloat(0, c.relError(), 0.001);

  c = b;
  c += a;
  assertEqualFloat(5, c.value(), 0.001);
  assertEqualFloat(0, c.error(), 0.001);
  assertEqualFloat(0, c.relError(), 0.001);

  c = a;
  c -= b;
  assertEqualFloat(-1, c.value(), 0.001);
  assertEqualFloat(0, c.error(), 0.001);
  assertEqualFloat(0, c.relError(), 0.001);

  c = b;
  c -= a;
  assertEqualFloat(1, c.value(), 0.001);
  assertEqualFloat(0, c.error(), 0.001);
  assertEqualFloat(0, c.relError(), 0.001);

  c = a;
  c *= b;
  assertEqualFloat(6, c.value(), 0.001);
  assertEqualFloat(0, c.error(), 0.001);
  assertEqualFloat(0, c.relError(), 0.001);

  c = b;
  c *= a;
  assertEqualFloat(6, c.value(), 0.001);
  assertEqualFloat(0, c.error(), 0.001);
  assertEqualFloat(0, c.relError(), 0.001);

  c = a;
  c /= b;
  assertEqualFloat(0.666666, c.value(), 0.001);
  assertEqualFloat(0, c.error(), 0.001);
  assertEqualFloat(0, c.relError(), 0.001);

  c = b;
  c /= a;
  assertEqualFloat(1.5, c.value(), 0.001);
  assertEqualFloat(0, c.error(), 0.001);
  assertEqualFloat(0, c.relError(), 0.001);
}

///////////////////////////////////////////////

unittest(test_basic_math_with_error_I)
{
  FLE a(2, 0.1);
  FLE b(3, 0.1);

  FLE c = a;
  assertEqualFloat(2.0, c.value(), 0.001);
  assertEqualFloat(0.1, c.error(), 0.001);
  assertEqualFloat(0.05, c.relError(), 0.001);

  c = b;
  assertEqualFloat(3.0, c.value(), 0.001);
  assertEqualFloat(0.1, c.error(), 0.001);
  assertEqualFloat(0.0333333, c.relError(), 0.001);

  c = -b;
  assertEqualFloat(-3, c.value(), 0.001);
  assertEqualFloat(0.1, c.error(), 0.001);
  assertEqualFloat(0.0333333, c.relError(), 0.001);

  c = a + b;
  assertEqualFloat(5.0, c.value(), 0.001);
  assertEqualFloat(0.2, c.error(), 0.001);
  assertEqualFloat(0.04, c.relError(), 0.001);

  c = b + a;
  assertEqualFloat(5.0, c.value(), 0.001);
  assertEqualFloat(0.2, c.error(), 0.001);
  assertEqualFloat(0.04, c.relError(), 0.001);

  c = a - b;
  assertEqualFloat(-1.0, c.value(), 0.001);
  assertEqualFloat(0.2, c.error(), 0.001);
  assertEqualFloat(0.2, c.relError(), 0.001);

  c = b - a;
  assertEqualFloat(1.0, c.value(), 0.001);
  assertEqualFloat(0.2, c.error(), 0.001);
  assertEqualFloat(0.2, c.relError(), 0.001);

  c = a * b;
  assertEqualFloat(6.0, c.value(), 0.001);
  assertEqualFloat(0.5, c.error(), 0.001);
  assertEqualFloat(0.0833333, c.relError(), 0.001);

  c = b * a;
  assertEqualFloat(6.0, c.value(), 0.001);
  assertEqualFloat(0.5, c.error(), 0.001);
  assertEqualFloat(0.0833333, c.relError(), 0.001);

  c = a / b;
  assertEqualFloat(0.666666, c.value(), 0.001);
  assertEqualFloat(0.0555, c.error(), 0.001);
  assertEqualFloat(0.0833333, c.relError(), 0.001);

  c = b / a;
  assertEqualFloat(1.5, c.value(), 0.001);
  assertEqualFloat(0.125, c.error(), 0.001);
  assertEqualFloat(0.0833333, c.relError(), 0.001);
}


unittest(test_basic_math_with_error_II)
{
  FLE a(2, 0.1);
  FLE b(3, 0.1);

  FLE c = a;
  c += b;
  assertEqualFloat(5.0, c.value(), 0.001);
  assertEqualFloat(0.2, c.error(), 0.001);
  assertEqualFloat(0.04, c.relError(), 0.001);

  c = b;
  c += a;
  assertEqualFloat(5.0, c.value(), 0.001);
  assertEqualFloat(0.2, c.error(), 0.001);
  assertEqualFloat(0.04, c.relError(), 0.001);

  c = a;
  c -= b;
  assertEqualFloat(-1.0, c.value(), 0.001);
  assertEqualFloat(0.2, c.error(), 0.001);
  assertEqualFloat(0.2, c.relError(), 0.001);

  c = b;
  c -= a;
  assertEqualFloat(1.0, c.value(), 0.001);
  assertEqualFloat(0.2, c.error(), 0.001);
  assertEqualFloat(0.2, c.relError(), 0.001);

  c = a;
  c *= b;
  assertEqualFloat(6.0, c.value(), 0.001);
  assertEqualFloat(0.5, c.error(), 0.001);
  assertEqualFloat(0.0833333, c.relError(), 0.001);

  c = b;
  c *= a;
  assertEqualFloat(6.0, c.value(), 0.001);
  assertEqualFloat(0.5, c.error(), 0.001);
  assertEqualFloat(0.0833333, c.relError(), 0.001);

  c = a;
  c /= b;
  assertEqualFloat(0.666666, c.value(), 0.001);
  assertEqualFloat(0.0555, c.error(), 0.001);
  assertEqualFloat(0.0833333, c.relError(), 0.001);

  c = b;
  c /= a;
  assertEqualFloat(1.5, c.value(), 0.001);
  assertEqualFloat(0.125, c.error(), 0.001);
  assertEqualFloat(0.0833333, c.relError(), 0.001);
}


unittest(test_bool)
{
  FLE a(2, 0.1);
  FLE b(3, 0.1);
  FLE c(3, 0.1);
  FLE d(3, 1.0);

  assertFalse(a == b);
  assertFalse(b == a);
  assertTrue(a == a);
  assertTrue(b == c);
  assertTrue(c == b);

  assertTrue(a != b);
  assertTrue(b != a);
  assertFalse(b != c);
  assertFalse(c != b);
  assertFalse(a != a);

  assertTrue(c > a);
  assertTrue(a < c);
  assertFalse(d > d);
  assertFalse(d > a);
  assertFalse(a < a);
  assertFalse(a < d);

  // semantics unclear....
  // assertTrue(a >= a);
  // assertTrue(c >= a);
  // assertTrue(a <= a);
  // assertTrue(a <= c);
  // assertFalse(d >= a);
  // assertFalse(d <= a);
}


unittest(test_in)
{
  FLE a(2, 0.1);
  FLE b(3, 0.9);
  FLE c(3, 1.0);

  fprintf(stderr, "\nIN test\n");
  assertFalse(a.in(b));
  assertFalse(b.in(a));
  assertTrue(b.in(c));
  assertFalse(c.in(b));
}


unittest(test_shared)
{
  FLE a(2, 0.1);
  FLE b(3, 0.9);
  FLE c(3, 1.0);

  fprintf(stderr, "\nSHARED test\n");

  FLE x = a.shared(b);
  fprintf(stderr, "x.value: %f\n", x.value());
  fprintf(stderr, "x.error: %f\n", x.error());
  assertEqualFloat(2.1, x.value(), 0.001);
  assertEqualFloat(0.0, x.error(), 0.001);

  x = a.shared(c);
  fprintf(stderr, "x.value: %f\n", x.value());
  fprintf(stderr, "x.error: %f\n", x.error());
  assertEqualFloat(2.05, x.value(), 0.001);
  assertEqualFloat(0.05, x.error(), 0.001);

  x = b.shared(c);
  fprintf(stderr, "x.value: %f\n", x.value());
  fprintf(stderr, "x.error: %f\n", x.error());
  assertEqualFloat(3.00, x.value(), 0.001);
  assertEqualFloat(0.90, x.error(), 0.001);

  fprintf(stderr, "\nNAN test\n");
  
  FLE d(5, 0.9);
  x = c.shared(d);
  assertNAN(x.value());
  assertNAN(x.error());
  x = d.shared(c);
  assertNAN(x.value());
  assertNAN(x.error());
}


unittest(test_experimental)
{
  FLE a(2, 0.1);
  FLE b(3, 0.9);
  FLE c(3, 0.1);

  assertTrue(a.peq(a));
  assertTrue(a.peq(b));
  assertTrue(b.peq(c));
  assertTrue(c.peq(b));

  assertFalse(c.peq(a));
  assertFalse(a.peq(c));
}


unittest_main()

// --------

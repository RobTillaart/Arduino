//
//    FILE: fraction_accuracy.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test accuracy for fractionize with random floats.
//     URL: https://github.com/RobTillaart/Fraction


#include "fraction.h"
#include "printHelpers.h"


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("FRACTION_LIB_VERSION: ");
  Serial.println(FRACTION_LIB_VERSION);
  Serial.println();

  test_accuracy(0);
  test_accuracy(1);
  test_accuracy(0.5);
  test_accuracy(PI);
  test_accuracy(EULER);

  Serial.println("\ndone...");
  delay(1000);
}


void loop()
{
  float value = random(1000000) * 1e-6;
  test_accuracy(value);
  delay(100);
}


void test_accuracy(float value)
{
  Fraction a(value);
  Serial.print(value, 7);
  Serial.print("\t");
  Serial.print(a.toDouble(), 7);
  Serial.print("\t");
  Serial.print(sci(value - a.toDouble(), 2));
  Serial.print("\t");
  Serial.println(a.toString());
}


//  -- END OF FILE --

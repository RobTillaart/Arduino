//
//    FILE: ellipse_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: performance and accuracy test
//     URL: https://github.com/RobTillaart/ellipse


#include "ellipse.h"


ellipse E(1, 1);
uint32_t start, stop;
volatile float f;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("ELLIPSE_LIB_VERSION: ");
  Serial.println(ELLIPSE_LIB_VERSION);
  Serial.println();

  for (int B = 10; B > 0; B--)
  {
    Serial.println();
    Serial.print("Ellipse A=10, B=");
    Serial.println(B);
    E.setA(10);
    E.setB(B);
    test_circumference();
    test_perimeter_reference();
    test_perimeter_Kepler();
    test_perimeter_Parker();
    test_perimeter_Parker_fast();
    test_perimeter_polynome();
    test_perimeter_binomial();
    test_eccentricity();
  }

  Serial.println("\nDone...");
}


void loop()
{
}


void test_circumference()
{
  start = micros();
  f = E.circumference();
  stop = micros();
  Serial.print("\tTIME: ");
  Serial.print(stop - start);
  Serial.print("\tCIRCUMFERENCE: ");
  Serial.print(f, 4);
  Serial.print("\t");
  Serial.println(__FUNCTION__);
  delay(10);
}


void test_perimeter_reference()
{
  start = micros();
  f = E.perimeter_reference();
  stop = micros();
  Serial.print("\tTIME: ");
  Serial.print(stop - start);
  Serial.print("\tCIRCUMFERENCE: ");
  Serial.print(f, 4);
  Serial.print("\t");
  Serial.println(__FUNCTION__);
  delay(10);
}


void test_perimeter_Kepler()
{
  start = micros();
  f = E.perimeter_Kepler();
  stop = micros();
  Serial.print("\tTIME: ");
  Serial.print(stop - start);
  Serial.print("\tCIRCUMFERENCE: ");
  Serial.print(f, 4);
  Serial.print("\t");
  Serial.println(__FUNCTION__);
  delay(10);
}


void test_perimeter_Parker()
{
  start = micros();
  f = E.perimeter_Parker();
  stop = micros();
  Serial.print("\tTIME: ");
  Serial.print(stop - start);
  Serial.print("\tCIRCUMFERENCE: ");
  Serial.print(f, 4);
  Serial.print("\t");
  Serial.println(__FUNCTION__);
  delay(10);
}


void test_perimeter_Parker_fast()
{
  start = micros();
  f = E.perimeter_Parker_fast();
  stop = micros();
  Serial.print("\tTIME: ");
  Serial.print(stop - start);
  Serial.print("\tCIRCUMFERENCE: ");
  Serial.print(f, 4);
  Serial.print("\t");
  Serial.println(__FUNCTION__);
  delay(10);
}


void test_perimeter_polynome()
{
  start = micros();
  f = E.perimeter_polynome();
  stop = micros();
  Serial.print("\tTIME: ");
  Serial.print(stop - start);
  Serial.print("\tCIRCUMFERENCE: ");
  Serial.print(f, 4);
  Serial.print("\t");
  Serial.println(__FUNCTION__);
  delay(10);
}


void test_perimeter_binomial()
{
  start = micros();
  f = E.perimeter_binomial();
  stop = micros();
  Serial.print("\tTIME: ");
  Serial.print(stop - start);
  Serial.print("\tCIRCUMFERENCE: ");
  Serial.print(f, 4);
  Serial.print("\t");
  Serial.println(__FUNCTION__);
  delay(10);
}


void test_eccentricity()
{
  start = micros();
  f = E.eccentricity();
  stop = micros();
  Serial.print("\tTIME: ");
  Serial.print(stop - start);
  Serial.print("\t ECCENTRICITY: ");
  Serial.print(f, 6);
  Serial.print("\t");
  Serial.println(__FUNCTION__);
  delay(10);
}


//  -- END OF FILE --

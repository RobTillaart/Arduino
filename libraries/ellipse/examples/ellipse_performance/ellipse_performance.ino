//
//    FILE: ellipse_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: performance and accuracy test
//    DATE: 2021-10-31
//     URL: https://github.com/RobTillaart/ellipse


#include "ellipse.h"


ellipse E(1, 1);
uint32_t start, stop;
volatile float f;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println();

  Serial.println("Ellipse A=10, B=10");
  E.setA(10);
  E.setB(10);
  test_circumference();
  test_perimeter_ref();
  test_perimeter_keppler();
  test_perimeter_parker();
  test_eccentricity();

  Serial.println("\nEllipse A=10, B=5");
  E.setA(10);
  E.setB(5);
  test_circumference();
  test_perimeter_ref();
  test_perimeter_keppler();
  test_perimeter_parker();
  test_eccentricity();

  Serial.println("\nEllipse A=10, B=1");
  E.setA(10);
  E.setB(1);
  test_circumference();
  test_perimeter_ref();
  test_perimeter_keppler();
  test_perimeter_parker();
  test_eccentricity();


  Serial.println("\nDone...");
}


void loop()
{
}


void test_circumference()
{
  Serial.println(__FUNCTION__);
  start = micros();
  f = E.circumference();
  stop = micros();
  Serial.print("\tTIME: ");
  Serial.print(stop - start);
  Serial.print("\tCIRCUMFERENCE: ");
  Serial.println(f, 4);
  delay(100);
}


void test_perimeter_ref()
{
  Serial.println(__FUNCTION__);
  start = micros();
  f = E.perimeter_ref();
  stop = micros();
  Serial.print("\tTIME: ");
  Serial.print(stop - start);
  Serial.print("\tCIRCUMFERENCE: ");
  Serial.println(f, 4);
  delay(100);
}


void test_perimeter_keppler()
{
  Serial.println(__FUNCTION__);
  start = micros();
  f = E.perimeter_Keppler();
  stop = micros();
  Serial.print("\tTIME: ");
  Serial.print(stop - start);
  Serial.print("\tCIRCUMFERENCE: ");
  Serial.println(f, 4);
  delay(100);
}


void test_perimeter_parker()
{
  Serial.println(__FUNCTION__);
  start = micros();
  f = E.perimeter_Parker();
  stop = micros();
  Serial.print("\tTIME: ");
  Serial.print(stop - start);
  Serial.print("\tCIRCUMFERENCE: ");
  Serial.println(f, 4);
  delay(100);
}


void test_eccentricity()
{
  Serial.println(__FUNCTION__);
  start = micros();
  f = E.eccentricity();
  stop = micros();
  Serial.print("\tTIME: ");
  Serial.print(stop - start);
  Serial.print("\t ECCENTRICITY: ");
  Serial.println(f);
  delay(100);
}


// -- END OF FILE --

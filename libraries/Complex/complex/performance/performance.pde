//
//    FILE: complex.pde
//  AUTHOR: Rob Tillaart
//    DATE: 2012-03-11
//
// PUPROSE: test complex math
//

#include "complex.h"

void PrintComplex(Complex c)
{
  Serial.print(c.real(),3);
  Serial.print("\t ");
  Serial.print(c.imag(),3);
  Serial.println("i");
}

void setup()
{
  Serial.begin(115200);
  Serial.print("\n  COMPLEX_LIB_VERSION: ");
  Serial.println(COMPLEX_LIB_VERSION);
  Serial.println("\n  Complex numbers test for Arduino"); 
  Serial.println("\n1. Performance");

  Complex c1(10.0,-2.0);
  Complex c2(3, 0);
  Complex c3(-10,4);
  Complex c4(-5,-5);
  Complex c5(0,0);
  
  unsigned long start = micros();
  for (int i = 0; i< 1000; i++)
  {
    c5 = c3.c_log();
  }
  unsigned long stop = micros();
  Serial.println(stop - start);
  Serial.println("\n.. Complex done");  
}

void loop()
{
}



//
//    FILE: complex.pde
//  AUTHOR: Rob Tillaart
//    DATE: 2012-03-10
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
  Serial.println("\n1. PrintComplex");

  Complex c1(10.0,-2.0);
  Complex c2(3,0);
  Complex c3(-10,4);
  Complex c4(-5,-5);
  Complex c5(0,0);
  
  // c5 = csqr(c3);           PrintComplex(c5);
  
  PrintComplex(c1);        PrintComplex(c2);
  PrintComplex(c3);        PrintComplex(c4);
  c3.set(0,0);             PrintComplex(c3);

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
  c5 = -c1;                PrintComplex(c5);
  c5 = -c5;                PrintComplex(c5);
  if (c5 == c1) Serial.println("ok :)");
  else Serial.println(" fail :(");
  
  
  Serial.println("\n4. + - ");
  c5 = c1 + c2;            PrintComplex(c5);
  c5 = c1 + 3;             PrintComplex(c5);
  c5 = c1 - c2;            PrintComplex(c5);
  c5 = c1 - 3;             PrintComplex(c5);
  
  
  Serial.println("\n5. * / ");
  c5 = c1 * c2;            PrintComplex(c5);
  c5 = c5 * 3;             PrintComplex(c5);
  c5 = c5 / c2;            PrintComplex(c5);
  c5 = c5 / 3;             PrintComplex(c5);
  
  c5 = c1 / c2 * c2;       PrintComplex(c5);  
  c5 = c1 * c4 / c4;       PrintComplex(c5);  
  
  
  Serial.println("\n6. assign += -= etc");
  c5 = c1;
  c5 += c1;                PrintComplex(c5);
  c5 += 3;                 PrintComplex(c5);
  c5 -= c1;                PrintComplex(c5);
  c5 -= 3;                 PrintComplex(c5);
  c5 *= c1;                PrintComplex(c5);
  c5 *= 3;                 PrintComplex(c5);
  c5 /= c1;                PrintComplex(c5);
  c5 /= 3;                 PrintComplex(c5);
  
  
  Serial.println("\n7. phase modulus polar");
  double m = c1.modulus(); Serial.println(m);
  double p = c1.phase();   Serial.println(p);
  c5.polar(m, p);          PrintComplex(c5);
  
  
  Serial.println("\n8. conjugate & reciprocal");
  c5 = c1.conjugate();     PrintComplex(c5);
  c5 = c5.conjugate();     PrintComplex(c5);
  c5 = c1.reciprocal();    PrintComplex(c5);
  c5 = c5.reciprocal();    PrintComplex(c5);
  
  
  Serial.println("\n9. power: exp log pow sqrt logn log10");
  c5 = c1.c_exp();         PrintComplex(c5);
  c5 = c5.c_log();         PrintComplex(c5);
  c5 = c1.c_pow(2);        PrintComplex(c5);
  c5 = c5.c_sqrt();        PrintComplex(c5);
  c5 = c1.c_pow(c2);       PrintComplex(c5);
  c5 = c5.c_pow(c2.reciprocal());       PrintComplex(c5);
  c5 = c5.c_logn(c4);       PrintComplex(c5);
  c5 = c4.c_pow(c5);        PrintComplex(c5);
  c5 = c5.c_log10();        PrintComplex(c5);
  c5 = c4.c_sqr().c_sqrt(); PrintComplex(c5);
  
 
  Serial.println("\n10. gonio: sin cos tan asin acos atan");
  c1.set(0.5, 0.5);
  c5 = c1.c_sin();         PrintComplex(c5);
  c5 = c5.c_asin();        PrintComplex(c5); 
  c5 = c1.c_cos();         PrintComplex(c5);
  c5 = c5.c_acos();        PrintComplex(c5);
  c5 = c1.c_tan();         PrintComplex(c5);
  c5 = c5.c_atan();        PrintComplex(c5);
  
 
  Serial.println("\n11. gonio csc sec cot acsc asec acot");
  c1.set(0.5, 0.5);
  c5 = c1.c_csc();         PrintComplex(c5);
  c5 = c5.c_acsc();        PrintComplex(c5); 
  c5 = c1.c_sec();         PrintComplex(c5);
  c5 = c5.c_asec();        PrintComplex(c5);
  c5 = c1.c_cot();         PrintComplex(c5);
  c5 = c5.c_acot();        PrintComplex(c5);
  
  
  Serial.println("\n12. gonio hyperbolicus I ");
  c1.set(0.5, 0.5);
  c5 = c1.c_sinh();         PrintComplex(c5);
  c5 = c5.c_asinh();        PrintComplex(c5); 
  c5 = c1.c_cosh();         PrintComplex(c5);
  c5 = c5.c_acosh();        PrintComplex(c5);
  c5 = c1.c_tanh();         PrintComplex(c5);
  c5 = c5.c_atanh();        PrintComplex(c5);
 
  Serial.println("\n13. gonio hyperbolicus II ");
  c1.set(0.5, 0.5);
  c5 = c1.c_csch();         PrintComplex(c5);
  c5 = c5.c_acsch();        PrintComplex(c5); 
  c5 = c1.c_sech();         PrintComplex(c5);
  c5 = c5.c_asech();        PrintComplex(c5);
  c5 = c1.c_coth();         PrintComplex(c5);
  c5 = c5.c_acoth();        PrintComplex(c5);

  Serial.println("\n.. Complex done");  
}

void loop()
{
}



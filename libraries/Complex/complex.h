// 
//    FILE: Complex.h
//  AUTHOR: Rob Tillaart
// VERSION: see COMPLEX_LIB_VERSION
// PURPOSE: library for Complex math for Arduino
//     URL: 
// 
// Released to the public domain
//

#ifndef Complex_h
#define Complex_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define COMPLEX_LIB_VERSION 0.1.00


class Complex 
{
public:
	Complex(double, double);
	Complex(const Complex &);
	Complex(double);
	
	double real();
	double imag();
	
	double c_abs();
	double phase();
	Complex conjugate();
	Complex reciprocal();
	
	Complex operator + (Complex);
    Complex operator - (Complex);
	Complex operator * (Complex);
    Complex operator / (Complex);
	// Complex operator + (double);
    Complex operator - (double);
	Complex operator * (double);
    Complex operator / (double);
	
	Complex operator += (Complex);
	Complex operator -= (Complex);
	Complex operator *= (Complex);
	Complex operator /= (Complex);
	Complex operator += (double);
	Complex operator -= (double);
	Complex operator *= (double);
	Complex operator /= (double);
	
	bool operator == (Complex);
	bool operator == (double);

	Complex c_exp();
	Complex c_sin();
	Complex c_cos();
	Complex c_tan();
	
private:
	double re;
	double im;
};
#endif
// --- END OF FILE ---
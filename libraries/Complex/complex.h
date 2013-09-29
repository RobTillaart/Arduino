//
//    FILE: Complex.h
//  AUTHOR: Rob Tillaart
// VERSION: see COMPLEX_LIB_VERSION
// PURPOSE: library for Complex math for Arduino
//     URL: http://arduino.cc/playground/Main/ComplexMath
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

#define COMPLEX_LIB_VERSION "0.1.03"

class Complex
{
public:
	Complex(double, double);
	Complex(const Complex &);
	Complex(double);

	void set(double, double);
	double real();
	double imag();

	void polar(double, double);
	double phase();
	double modulus();

	Complex conjugate();
	Complex reciprocal();

	bool operator == (Complex);
	bool operator != (Complex);

    Complex operator - (); // negation

	Complex operator + (Complex);
    Complex operator - (Complex);
	Complex operator * (Complex);
    Complex operator / (Complex);

	void operator += (Complex);
	void operator -= (Complex);
	void operator *= (Complex);
	void operator /= (Complex);

	Complex c_sqrt();
	Complex c_sqr();
	Complex c_exp();
	Complex c_log();
	Complex c_log10();
	Complex c_pow(Complex);
	Complex c_logn(Complex);

	Complex c_sin();
	Complex c_cos();
	Complex c_tan();
	Complex c_asin();
	Complex c_acos();
	Complex c_atan();

	Complex c_csc();
	Complex c_sec();
	Complex c_cot();
	Complex c_acsc();
	Complex c_asec();
	Complex c_acot();

	Complex c_sinh();
	Complex c_cosh();
	Complex c_tanh();
	Complex c_asinh();
	Complex c_acosh();
	Complex c_atanh();

	Complex c_csch();
	Complex c_sech();
	Complex c_coth();
	Complex c_acsch();
	Complex c_asech();
	Complex c_acoth();

private:
	double re;
	double im;
	
	Complex gonioHelper1(int);
	Complex gonioHelper2(int);
};

#endif
// --- END OF FILE ---
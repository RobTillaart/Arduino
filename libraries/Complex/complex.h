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

#include "Printable.h"

#define COMPLEX_LIB_VERSION "0.1.05"

// five categories of functions can be switched per category
// by (un)commenting next lines.

#define COMPLEX_EXTENDED
#define COMPLEX_GONIO_1
#define COMPLEX_GONIO_2 
#define COMPLEX_GONIO_3 
#define COMPLEX_GONIO_4 

class Complex: public Printable 
{
public:
    Complex(double, double);
    Complex(const Complex &);
    Complex(double);

    size_t printTo(Print& p) const;
    
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

#ifdef COMPLEX_EXTENDED
    Complex c_sqrt();
    Complex c_sqr();
    Complex c_exp();
    Complex c_log();
    Complex c_log10();
    Complex c_pow(Complex);
    Complex c_logn(Complex);
#endif

#ifdef COMPLEX_GONIO_1
    Complex c_sin();
    Complex c_cos();
    Complex c_tan();
    Complex c_asin();
    Complex c_acos();
    Complex c_atan();
#endif

#ifdef COMPLEX_GONIO_2
    Complex c_csc();
    Complex c_sec();
    Complex c_cot();
    Complex c_acsc();
    Complex c_asec();
    Complex c_acot();
#endif

#ifdef COMPLEX_GONIO_3
    Complex c_sinh();
    Complex c_cosh();
    Complex c_tanh();
    Complex c_asinh();
    Complex c_acosh();
    Complex c_atanh();
#endif

#ifdef COMPLEX_GONIO_4
    Complex c_csch();
    Complex c_sech();
    Complex c_coth();
    Complex c_acsch();
    Complex c_asech();
    Complex c_acoth();
#endif

private:
    double re;
    double im;
    
    Complex gonioHelper1(int);
    Complex gonioHelper2(int);
};

static Complex one(1,0);

#endif
// --- END OF FILE ---
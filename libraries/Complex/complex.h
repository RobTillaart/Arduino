//
//    FILE: Complex.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.09
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

#define COMPLEX_LIB_VERSION "0.1.09"

class Complex: public Printable
{
public:
    Complex(const double r=0, const double i=0) : re(r), im(i) {};
    Complex(const Complex &c)   : re(c.re), im(c.im) {};

    void set(const double r, const double i ) { re = r; im = i; };
    double real() { return re; };
    double imag() { return im; };

    size_t printTo(Print& p) const;

    void polar(const double, const double);
    double phase()      { return atan2(im, re); };
    double modulus()    { return hypot(re, im); };
    // conjugate is the number mirrored in x-axis
    Complex conjugate() { return Complex(re,-im); };
    Complex reciprocal();

    bool operator == (const Complex&);
    bool operator != (const Complex&);

    Complex operator - (); // negation

    Complex operator + (const Complex&);
    Complex operator - (const Complex&);
    Complex operator * (const Complex&);
    Complex operator / (const Complex&);

    Complex& operator += (const Complex&);
    Complex& operator -= (const Complex&);
    Complex& operator *= (const Complex&);
    Complex& operator /= (const Complex&);

    Complex c_sqrt();
    Complex c_sqr();
    Complex c_exp();
    Complex c_log();
    Complex c_log10();
    Complex c_pow(const Complex &);
    Complex c_logn(const Complex &);

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

protected:
    double re;
    double im;

    Complex gonioHelper1(const byte);
    Complex gonioHelper2(const byte);
};

static Complex one(1, 0);

#endif
// --- END OF FILE ---
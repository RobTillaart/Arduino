#pragma once
//
//    FILE: Complex.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.1
// PURPOSE: Arduino library for Complex math
//     URL: https://github.com/RobTillaart/Complex
//          http://arduino.cc/playground/Main/ComplexMath
//

#include "Arduino.h"
#include "Printable.h"

#define COMPLEX_LIB_VERSION "0.2.1"

class Complex: public Printable
{
public:
    Complex(const float r = 0, const float i = 0) : re(r), im(i) {};
    Complex(const Complex &c)   : re(c.re), im(c.im) {};

    void set(const float r, const float i ) { re = r; im = i; };
    float real() { return re; };
    float imag() { return im; };

    size_t printTo(Print& p) const;

    void polar(const float, const float);
    float phase()      { return atan2(im, re); };
    float modulus()    { return hypot(re, im); };
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
    float re;
    float im;

    Complex gonioHelper1(const byte);
    Complex gonioHelper2(const byte);
};

static Complex one(1, 0);

// -- END OF FILE --

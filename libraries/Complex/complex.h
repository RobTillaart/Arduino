#pragma once
//
//    FILE: Complex.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.3.4
// PURPOSE: Arduino library for Complex math
//     URL: https://github.com/RobTillaart/Complex
//          http://arduino.cc/playground/Main/ComplexMath


#include "Arduino.h"
#include "Printable.h"


#define COMPLEX_LIB_VERSION                 (F("0.3.4"))


class Complex: public Printable
{
public:
    Complex(const float r = 0, const float i = 0) : re(r), im(i) {};
    Complex(const Complex &c) : re(c.re), im(c.im) {};


    void set(const float r, const float i ) { re = r; im = i; };
    void setReal(const float r)  { re = r; };
    void setImag(const float i ) { im = i; };
    float real() const { return re; };
    float imag() const { return im; };


    size_t printTo(Print& p) const;


    void polar(const float modulus, const float phase);
    float phase() const       { return atan2(im, re); };
    float modulus() const     { return hypot(re, im); };
    //  conjugate is the number mirrored in x-axis
    Complex conjugate() const { return Complex(re, -im); };
    Complex reciprocal() const;


    bool operator == (const Complex&) const;
    bool operator != (const Complex&) const;


    Complex operator - () const; // negation


    Complex operator + (const Complex&) const;
    Complex operator - (const Complex&) const;
    Complex operator * (const Complex&) const;
    Complex operator / (const Complex&) const;

    Complex& operator += (const Complex&);
    Complex& operator -= (const Complex&);
    Complex& operator *= (const Complex&);
    Complex& operator /= (const Complex&);


    Complex c_sqrt() const;
    Complex c_sqr() const;
    Complex c_exp() const;
    Complex c_log() const;
    Complex c_log10() const;
    Complex c_pow(const Complex &) const;
    Complex c_logn(const Complex &) const;


    Complex c_sin() const;
    Complex c_cos() const;
    Complex c_tan() const;
    Complex c_asin() const;
    Complex c_acos() const;
    Complex c_atan() const;


    Complex c_csc() const;
    Complex c_sec() const;
    Complex c_cot() const;
    Complex c_acsc() const;
    Complex c_asec() const;
    Complex c_acot() const;


    Complex c_sinh() const;
    Complex c_cosh() const;
    Complex c_tanh() const;
    Complex c_asinh() const;
    Complex c_acosh() const;
    Complex c_atanh() const;


    Complex c_csch() const;
    Complex c_sech() const;
    Complex c_coth() const;
    Complex c_acsch() const;
    Complex c_asech() const;
    Complex c_acoth() const;


protected:
    float re;
    float im;

    Complex gonioHelper1(const byte) const;
    Complex gonioHelper2(const byte) const;
};


static const Complex one(1, 0);


//  -- END OF FILE --


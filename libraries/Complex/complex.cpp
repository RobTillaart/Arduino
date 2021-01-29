//
//    FILE: Complex.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.2
// PURPOSE: Arduino library for Complex math
//     URL: https://github.com/RobTillaart/Complex
//          http://arduino.cc/playground/Main/ComplexMath
//
// 0.2.2    2020-12-16   add arduino-ci + unit test (starter)
//                       setReal, setImag
// 0.2.1    2020-06-05   fix library.json
// 0.2.0    2020-03-29   #pragma once, own repo
// 0.1.12 - 2018-04-02 - fix issue #33 double -> float
// 0.1.11 - 2018-01-29 - fix sin and cos formula - issue #91
// 0.1.10 - 2018-01-15 - uppercase #define COMPLEX_H
// 0.1.09 - 2016-10-15 - added (0,0) constructor
// 0.1.08 - 2015-06-03 - refactor
// 0.1.07 - 2015-06-03 - refactor interfaces

#include "Complex.h"

// PRINTING
size_t Complex::printTo(Print& p) const
{
  size_t n = 0;
  n += p.print(re, 3);
  n += p.print(' ');
  n += p.print(im, 3);
  n += p.print('i');
  return n;
};

void Complex::polar(const float modulus, const float phase)
{
  re = modulus * cos(phase);
  im = modulus * sin(phase);
}

Complex Complex::reciprocal()
{
  float f = 1.0 / (re * re + im * im);
  float r = re * f;
  float i = -im * f;
  return Complex(r, i);
}


// EQUALITIES
bool Complex::operator == (const Complex &c)
{
  return (re == c.re) && (im == c.im);
}

bool Complex::operator != (const Complex &c)
{
  return (re != c.re) || (im != c.im);
}

// NEGATE
Complex Complex::operator - ()
{
  return Complex(-re, -im);
}

// BASIC MATH
Complex Complex::operator + (const Complex &c)
{
  return Complex(re + c.re, im + c.im);
}

Complex Complex::operator - (const Complex &c)
{
  return Complex(re - c.re, im - c.im);
}

Complex Complex::operator * (const Complex &c)
{
  float r = re * c.re - im * c.im;
  float i = re * c.im + im * c.re;
  return Complex(r, i);
}

Complex Complex::operator / (const Complex &c)
{
  float f = 1.0/(c.re * c.re + c.im * c.im);
  float r = (re * c.re + im * c.im) * f;
  float i = (im * c.re - re * c.im) * f;
  return Complex(r, i);
}

Complex& Complex::operator += (const Complex &c)
{
  re += c.re;
  im += c.im;
  return *this;
}

Complex& Complex::operator -= (const Complex &c)
{
  re -= c.re;
  im -= c.im;
  return *this;
}

Complex& Complex::operator *= (const Complex &c)
{
  float r = re * c.re - im * c.im;
  float i = re * c.im + im * c.re;
  re = r;
  im = i;
  return *this;
}

Complex& Complex::operator /= (const Complex &c)
{
  float f = 1.0/(c.re * c.re + c.im * c.im);
  float r = (re * c.re + im * c.im) * f;
  float i = (im * c.re - re * c.im) * f;
  re = r;
  im = i;
  return *this;
}

//
// POWER FUNCTIONS
//
Complex Complex::c_sqr()
{
  float r = re * re - im * im;
  float i = 2 * re * im;
  return Complex(r, i);
}

Complex Complex::c_sqrt()
{
  float m = modulus();
  float r = sqrt(0.5 * (m + re));
  float i = sqrt(0.5 * (m - re));
  if (im < 0) i = -i;
  return Complex(r, i);
}

Complex Complex::c_exp()
{
  float e = exp(re);
  return Complex(e * cos(im), e * sin(im));
}

Complex Complex::c_log()
{
  float m = modulus();
  float p = phase();
  if (p > PI) p -= 2 * PI;
  return Complex(log(m), p);
}

Complex Complex::c_pow(const Complex &c)
{
  Complex t = c_log();
  t = t * c;
  return t.c_exp();
}

Complex Complex::c_logn(const Complex &c)
{
  Complex t = c;
  return c_log()/t.c_log();
}

Complex Complex::c_log10()
{
  return c_logn(10);
}

//
// GONIO I - SIN COS TAN
//
Complex Complex::c_sin()
{
  return Complex(sin(re) * cosh(im), cos(re) * sinh(im));
}

Complex Complex::c_cos()
{
  return Complex(cos(re) * cosh(im), -sin(re) * sinh(im));
}

Complex Complex::c_tan()
{
  /* faster but 350 bytes longer!!
    float s = sin(re);
    float c = cos(re);
    float sh = sinh(im);
    float ch = cosh(im);
    // return Complex(s*ch, c*sh) / Complex(c*ch, -s*sh);
    float r0 = s*ch;
    float i0 = c*sh;
    float cre = c*ch;
    float cim = -s*sh;
    float f = 1.0/(cre*cre + cim*cim);
    float r = r0 * cre + i0 * cim;
    float i = r0 * cim - i0 * cre;
    return Complex(r * f, -i * f);
    */
  return c_sin() / c_cos();
}

Complex Complex::gonioHelper1(const byte mode)
{
  Complex c = (one - this->c_sqr()).c_sqrt();
  if (mode == 0)
  {
    c = c + *this * Complex(0,-1);
  }
  else
  {
    c = *this + c * Complex(0,-1);
  }
  c = c.c_log() * Complex(0,1);
  return c;
}

Complex Complex::c_asin()
{
  return gonioHelper1(0);
}

Complex Complex::c_acos()
{
  return gonioHelper1(1);
}

Complex Complex::c_atan()
{
  return (Complex(0,-1) * (Complex(re, im - 1)/Complex(-re, -im - 1)).c_log()) * 0.5;
}

//
// GONIO II - CSC SEC COT
//
Complex Complex::c_csc()
{
  return one / c_sin();
}

Complex Complex::c_sec()
{
  return one / c_cos();
}

Complex Complex::c_cot()
{
  return one / c_tan();
}

Complex Complex::c_acsc()
{
  return (one / *this).c_asin();
}

Complex Complex::c_asec()
{
  return (one / *this).c_acos();
}

Complex Complex::c_acot()
{
  return (one / *this).c_atan();
}

//
// GONIO HYPERBOLICUS I
//
Complex Complex::c_sinh()
{
  return Complex(cos(im) * sinh(re), sin(im) * cosh(re));
}

Complex Complex::c_cosh()
{
  return Complex(cos(im) * cosh(re), sin(im) * sinh(re));
}

Complex Complex::c_tanh()
{
  return c_sinh() / c_cosh();
}

Complex Complex::gonioHelper2(const byte mode)
{
  Complex c = c_sqr();
  if (mode == 0)
  {
    c += 1;
  }
  else
  {
    c -= 1;
  }
  c = (*this + c.c_sqrt()).c_log();
  return c;
}

Complex Complex::c_asinh()
{
  return gonioHelper2(0);
}

Complex Complex::c_acosh()
{
  return gonioHelper2(1);
}

Complex Complex::c_atanh()
{
  Complex c = (*this + one).c_log();
  c = c - (-(*this - one)).c_log();
  return c * 0.5;
}

//
// GONIO HYPERBOLICUS II
//
Complex Complex::c_csch()
{
  return one / c_sinh();
}

Complex Complex::c_sech()
{
  return one / c_cosh();
}

Complex Complex::c_coth()
{
  return one / c_tanh();
}

Complex Complex::c_acsch()
{
  return (one / *this).c_asinh();
}

Complex Complex::c_asech()
{
  return (one / *this).c_acosh();
}

Complex Complex::c_acoth()
{
  return (one / *this).c_atanh();
}

// --- END OF FILE ---
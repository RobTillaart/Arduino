//
//    FILE: Complex.cpp
//  AUTHOR: Rob Tillaart
// VERSION: see COMPLEX_LIB_VERSION
// PURPOSE: library for Complex math for Arduino
//     URL: http://arduino.cc/playground/Main/ComplexMath
//
// Released to the public domain
//

#include "complex.h"

Complex::Complex(double real, double imag)
{
    re = real;
    im = imag;
}

Complex::Complex(const Complex &c)
{
    re = c.re;
    im = c.im;
}

Complex::Complex(double d)
{
    re = d;
    im = 0;
}

void Complex::set(double real, double imag)
{
    re = real;
    im = imag;
}

double Complex::real()
{
    return re;
}

double Complex::imag()
{
    return im;
}

// polar2cartesian
void Complex::polar(double modulus, double phase)
{
    re = modulus * cos(phase);
    im = modulus * sin(phase);
}

double Complex::phase()
{
    return atan2(im, re);
}

double Complex::modulus()
{
    return hypot(re, im);
}

// conjugate is the number mirrored in x-axis
Complex Complex::conjugate()
{
    return Complex(re,-im);
}

Complex Complex::reciprocal()
{
    double f = 1.0/(re*re + im*im);
    double r = re*f;
    double i = -im*f;
    return Complex(r,i);
}

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

// EQUALITIES
bool Complex::operator == (Complex c)
{
    return (re == c.re) && (im == c.im);
}

bool Complex::operator != (Complex c)
{
    return (re != c.re) || (im != c.im);
}

// NEGATE
Complex Complex::operator - ()
{
    return Complex(-re, -im);
}

// BASIC MATH
Complex Complex::operator + (Complex c)
{
    return Complex(re + c.re, im + c.im);
}

Complex Complex::operator - (Complex c)
{
    return Complex(re - c.re, im - c.im);
}

Complex Complex::operator * (Complex c)
{
    double r = re * c.re - im * c.im;
    double i = re * c.im + im * c.re;
    return Complex(r, i);	
}

Complex Complex::operator / (Complex c)
{
    double f = 1.0/(c.re*c.re + c.im*c.im); 
    double r = re * c.re + im * c.im;
    double i = im * c.re - re * c.im;
    return Complex(r * f, i * f);
}

void Complex::operator += (Complex c)
{
    re += c.re;
    im += c.im;
}

void Complex::operator -= (Complex c)
{
    re -= c.re;
    im -= c.im;
}

void Complex::operator *= (Complex c)
{
    double r = re * c.re - im * c.im;
    double i = re * c.im + im * c.re;
    re = r;
    im = i;
}

void Complex::operator /= (Complex c)
{
    double f = 1.0/(c.re*c.re + c.im*c.im);
    double r = re * c.re + im * c.im;
    double i = re * c.im - im * c.re;
    re = r*f;
    im = -i*f;
}

#ifdef COMPLEX_EXTENDED
//
// POWER FUNCTIONS
//
Complex Complex::c_sqr()
{
    double r = re * re - im * im;
    double i = 2 * re * im;
    return Complex(r,i);
}

Complex Complex::c_sqrt()
{
    double m = modulus();
    double r = sqrt(0.5 * (m+re));
    double i = sqrt(0.5 * (m-re));
    if (im < 0) i = -i;
    return Complex(r,i);
}

Complex Complex::c_exp()
{
    double e = exp(re);
    return Complex(e * cos(im), e * sin(im));
}

Complex Complex::c_log()
{
    double m = modulus();
    double p = phase();
    if (p > PI) p -= 2*PI;
    return Complex(log(m), p);
}

Complex Complex::c_pow(Complex c)
{
    Complex t = c * c_log();
    return t.c_exp();
}

Complex Complex::c_logn(Complex c)
{
    return c_log()/c.c_log();
}

Complex Complex::c_log10()
{
    return c_logn(10);
}
#endif

#ifdef COMPLEX_GONIO_1
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
    double s = sin(re);
    double c = cos(re);
    double sh = sinh(im);
    double ch = cosh(im);
    // return Complex(s*ch, c*sh) / Complex(c*ch, -s*sh);
    double r0 = s*ch;
    double i0 = c*sh;
    double cre = c*ch;
    double cim = -s*sh;
    double f = 1.0/(cre*cre + cim*cim);
    double r = r0 * cre + i0 * cim;
    double i = r0 * cim - i0 * cre;
    return Complex(r * f, -i * f);
    */
    return c_sin() / c_cos();
}

Complex Complex::gonioHelper1(int mode)
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
    return (Complex(0,-1) * (Complex(re, im - 1)/Complex(-re, -im - 1)).c_log())/2;
}
#endif

#ifdef COMPLEX_GONIO_2
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
#endif

#ifdef COMPLEX_GONIO_3
//
// GONIO HYPERBOLICUS I
//
Complex Complex::c_sinh()
{
    return Complex(sinh(re) * cos(im), cosh(re)* sin(im));
}

Complex Complex::c_cosh()
{
    return Complex(cosh(re) * cos(im), sinh(re)* sin(im));
}

Complex Complex::c_tanh()
{
    return c_sinh() / c_cosh();
}

Complex Complex::gonioHelper2(int mode)
{
    Complex c = c_sqr();
    if (mode==0)
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
    return c/2;
}
#endif

#ifdef COMPLEX_GONIO_4
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
#endif

// --- END OF FILE ---
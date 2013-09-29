//
//    FILE: Complex.cpp
//  AUTHOR: Rob Tillaart
// VERSION: see COMPLEX_LIB_VERSION
// PURPOSE: library for Complex math for Arduino
//     URL:
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
	double f = re*re + im*im;
	double r = re/f;
	double i = -im/f;
	return Complex(r,i);
}

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
	return Complex(r,i);
}

Complex Complex::operator / (Complex c)
{
	double f = c.re*c.re + c.im*c.im;
	double r = re * c.re + im * c.im;
	double i = re * c.im - im * c.re;
	return Complex(r / f, -i / f);
}

void Complex::operator += (Complex c)
{
	this->re += c.re;
	this->im += c.im;
	return;
}

void Complex::operator -= (Complex c)
{
	this->re -= c.re;
	this->im -= c.im;
	return;
}

void Complex::operator *= (Complex c)
{
	double r = re * c.re - im * c.im;
	double i = re * c.im + im * c.re;
	this->re = r;
	this->im = i;
	return;
}

void Complex::operator /= (Complex c)
{
	double f = c.re*c.re + c.im*c.im;
	double r = re * c.re + im * c.im;
	double i = re * c.im - im * c.re;
	this->re = r/f;
	this->im = -i/f;
	return;
}

//
// POWER FUNCTIONS
//
Complex Complex::c_sqrt()
{
	double m = modulus();
	double r = sqrt(0.5 * (m+this->re));
	double i = sqrt(0.5 * (m-this->re));
	if (this->im < 0) i = -i;
	return Complex(r,i);
}

Complex Complex::c_exp()
{
	double e = exp(re);
	return Complex(e * cos(im), e * sin(im));
}

Complex Complex::c_log()
{
	double m = this->modulus();
	double p = this->phase();
	if (p > PI) p -= 2*PI;
	return Complex(log(m), p);
}

Complex Complex::c_pow(Complex c)
{
	Complex t = c * this->c_log();
	return t.c_exp();
}

Complex Complex::c_logn(Complex c)
{
	return this->c_log()/c.c_log();
}

Complex Complex::c_log10()
{
	return this->c_logn(10);
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
	return c_sin() / c_cos();
}

Complex Complex::gonioHelper1(int mode)
{
	Complex c = (Complex(1,0) - (*this * *this)).c_sqrt();
	if (mode==0)
	{
		c = c + *this * Complex(0, -1);
	}
	else
	{
		c = *this + c * Complex(0, -1);
	}
	c = c.c_log() * Complex(0,1);
	return c;
}

Complex Complex::c_asin()
{
	return this->gonioHelper1(0);
}

Complex Complex::c_acos()
{
	return this->gonioHelper1(1);
}

Complex Complex::c_atan()
{
	return (Complex(0,-1) * (Complex(this->re, this->im - 1)/Complex(-this->re, -this->im - 1)).c_log())/2;
}

//
// GONIO II - CSC SEC COT
//
Complex Complex::c_csc()
{
	return Complex(1,0) / this->c_sin();
}

Complex Complex::c_sec()
{
	return Complex(1,0) / this->c_cos();
}

Complex Complex::c_cot()
{
	return Complex(1,0) / this->c_tan();
}

Complex Complex::c_acsc()
{
	return (Complex(1,0) / *this).c_asin();
}

Complex Complex::c_asec()
{
	return (Complex(1,0) / *this).c_acos();
}

Complex Complex::c_acot()
{
	return (Complex(1,0) / *this).c_atan();
}

//
// GONIO HYPERBOLICUS I
//
Complex Complex::c_sinh()
{
	return Complex(sinh(this->re) * cos(this->im), cosh(this->re)* sin(this->im));
}

Complex Complex::c_cosh()
{
	return Complex(cosh(this->re) * cos(this->im), sinh(this->re)* sin(this->im));
}

Complex Complex::c_tanh()
{
	return c_sinh() / c_cosh();
}

Complex Complex::gonioHelper2(int mode)
{
	Complex c = (*this * *this);
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
	Complex one(1,0);
	Complex c = (*this + one).c_log();
	c = c - (-(*this - one)).c_log();
	return c/2;
}

//
// GONIO HYPERBOLICUS II
//
Complex Complex::c_csch()
{
	return Complex(1,0) / this->c_sinh();
}

Complex Complex::c_sech()
{
	return Complex(1,0) / this->c_cosh();
}

Complex Complex::c_coth()
{
	return Complex(1,0) / this->c_tanh();
}

Complex Complex::c_acsch()
{
	return (Complex(1,0) / *this).c_asinh();
}

Complex Complex::c_asech()
{
	return (Complex(1,0) / *this).c_acosh();
}

Complex Complex::c_acoth()
{
	return (Complex(1,0) / *this).c_atanh();
}

// --- END OF FILE ---
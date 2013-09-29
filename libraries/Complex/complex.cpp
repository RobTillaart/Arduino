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

double Complex::real() 
{ 
	return re;
}

double Complex::imag() 
{ 
	return im;
}

double Complex::c_abs() 
{ 
	return hypot(re, im);
}  

double Complex::phase() 
{ 
	return atan2(im, re);
}

bool Complex::operator == (Complex c)
{
	return (re == c.re) && (im == c.im);
}

bool Complex::operator == (double d)
{
	return (re == d) && (im == 0.0);
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

Complex Complex::operator + (Complex c)
{
	return Complex(re + c.re, im + c.im);
}

/*
Complex Complex::operator + (double d)
{
	return Complex(re + d, im);
}*/

Complex Complex::operator - (Complex c)
{
	return Complex(re - c.re, im - c.im);
}

Complex Complex::operator - (double d)
{
	return Complex(re - d, im);
}

Complex Complex::operator * (Complex c)
{
	double r = re * c.re - im * c.im;
	double i = re * c.im + im * c.re;
	return Complex(r,i);
}

Complex Complex::operator * (double d)
{
	return Complex(re * d, im * d);
}

Complex Complex::operator / (Complex c)
{
	double f = c.re*c.re + c.im*c.im;
	double r = re * c.re + im * c.im;
	double i = re * c.im - im * c.re;
	return Complex(r / f, i / f);
}

Complex Complex::operator / (double d)
{
	return Complex(re / d, im / d);
}

Complex Complex::operator += (Complex c)
{
	return Complex(re + c.re, im + c.im);
}

Complex Complex::operator += (double d)
{
	return Complex(re + d, im);
}

Complex Complex::operator -= (Complex c)
{
	return Complex(re - c.re, im - c.im);
}

Complex Complex::operator -= (double d)
{
	return Complex(re - d, im);
}

Complex Complex::operator *= (Complex c)
{
	double r = re * c.re - im * c.im;
	double i = re * c.im + im * c.re;
	return Complex(r,i);
}

Complex Complex::operator *= (double d)
{
	return Complex(re * d, im * d);
}

Complex Complex::operator /= (Complex c)
{
	double f = c.re*c.re + c.im*c.im;
	double r = re * c.re + im * c.im;
	double i = re * c.im - im * c.re;
	return Complex(r / f, i / f);
}

Complex Complex::operator /= (double d)
{
	return Complex(re/d, im/d);
}

//
// More functions
//
Complex Complex::c_exp() 
{
	return Complex(exp(re) * cos(im), exp(re) * sin(im));
}

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




// --- END OF FILE ---

/*
----- http://www.dreamincode.net/code/snippet75.htm ----

#include <cmath>
#include <iostream>
#include <iomanip.h>

using namespace std;


class complex
{
private:
float real;               // Real Part
float imag;      //  Imaginary Part


public:
Complex::Complex(float,float);
Complex::Complex(complex&);
complex operator +(complex);
complex operator -(complex);
complex operator *(complex);
complex operator /(complex);
complex getconjugate();
complex getreciprocal();
float getmodulus();
void setdata(float,float);
void getdata();
float getreal();
float getimaginary();
bool operator ==(complex);
void operator =(complex);
friend ostream& operator <<(ostream &s,complex &c);
};

//                                        CONSTRUCTOR
complex::Complex::Complex(float r=0.0f,float im=0.0f)
{
real=r;
imag=im;
}

//                                 COPY CONSTRUCTOR
complex::Complex::Complex(complex &c)
{
this->real=c.real;
this->imag=c.imag;
}


void complex::operator =(complex c)
{
real=c.real;
imag=c.imag;
}


complex complex::operator +(complex c)
{
complex tmp;
tmp.real=this->real+c.real;
tmp.imag=this->imag+c.imag;
return tmp;
}

complex complex::operator -(complex c)
{
complex tmp;
tmp.real=this->real - c.real;
tmp.imag=this->imag - c.imag;
return tmp;
}

complex complex::operator *(complex c)
{
complex tmp;
tmp.real=(real*c.real)-(imag*c.imag);
tmp.imag=(real*c.imag)+(imag*c.real);
return tmp;
}

complex complex::operator /(complex c)
{
float div=(c.real*c.real) + (c.imag*c.imag);
complex tmp;
tmp.real=(real*c.real)+(imag*c.imag);
tmp.real/=div;
tmp.imag=(imag*c.real)-(real*c.imag);
tmp.imag/=div;
return tmp;
}

complex complex::getconjugate()
{
complex tmp;
tmp.real=this->real;
tmp.imag=this->imag * -1;
return tmp;
}

complex complex::getreciprocal()
{
complex t;
t.real=real;
t.imag=imag * -1;
float div;
div=(real*real)+(imag*imag);
t.real/=div;
t.imag/=div;
return t;
}

float complex::getmodulus()
{
float z;
z=(real*real)+(imag*imag);
z=sqrt(z);
return z;
}

void complex::setdata(float r,float i)
{
real=r;
imag=i;
}

void complex::getdata()
{
cout<<"Enter Real:";
cin>>this->real;
cout<<"Enter Imaginary:";
cin>>this->imag;

}

float complex::getreal()
{
return real;
}

float complex::getimaginary()
{
return imag;
}

bool complex::operator ==(complex c)
{
return (real==c.real)&&(imag==c.imag) ? 1 : 0;
}

ostream& operator <<(ostream &s,complex &c)
{
s<<"Real Part = "<<c.real<<endl
	<<"Imaginary Part = "<<c.imag<<endl;
s<<"z = "<<c.real<<setiosflags(ios::showpos)
	<<c.imag<<"i"<<endl<<resetiosflags(ios::showpos);
return s;
}

int main()
{
	complex a(10.0f,-2.f); // Calls Constructor
cout<<a<<endl;               // Calls the overloaded << operator
complex b(-2);         // Calls Constructor
complex c=b;                    // Calls Copy Constructor
c=a;                                   // calls overloaded = operator
b.getdata();                    // Calls Getdata()
c.getdata();
if(b==c)            // calls overloaded == operator
	cout<<"b == c";
	else
	cout<<"b != c";


cout<<endl<<c.getmodulus()<<endl; // calls getmodulus function()
complex d;
d=a+b;   // Calls overloaded +
cout<<d<<endl;
d=a-b;     // Calls overloaded -
cout<<d<<endl;
d=a*b;        // calls overloaded *
cout<<d<<endl;
d=a/b;        // calls overloaded /
cout<<d<<endl;

return 0;
}*/
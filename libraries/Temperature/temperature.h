//
//    FILE: temperature.h
// VERSION: 0.1.00
// PURPOSE: temperature functions
//
// HISTORY:
// see temperature.cpp file
//

#ifndef TEMPERATURE
#define TEMPERATURE

#include "WProgram.h"

#define TEMPERATURE_VERSION "0.1.00"

//Celsius to Fahrenheit conversion
double Fahrenheit(double celsius)
{
    return 1.8 * celsius + 32;
}

//Celsius to Kelvin conversion
double Kelvin(double celsius)
{
    return celsius + 273.15;
}

// dewPoint function NOAA
// reference: http://wahiduddin.net/calc/density_algorithms.htm
double dewPoint(double celsius, double humidity)
{
    double A0= 373.15/(273.15 + celsius);
    double SUM = -7.90298*(A0-1);
    SUM += 5.02808 * log10(A0);
    SUM += -1.3816e-7 * (pow(10, (11.344*(1-1/A0)))-1) ;
    SUM += 8.1328e-3*(pow(10,(-3.49149*(A0-1)))-1) ;
    SUM += log10(1013.246);
    double VP = pow(10, SUM-3) * humidity;
    double T = log(VP/0.61078);   // temp var
    return (241.88*T) / (17.558-T);
}

// delta max = 0.6544
// 5x faster than dewPoint()
// reference: http://en.wikipedia.org/wiki/Dew_point
double dewPointFast(double celsius, double humidity)
{
    double a = 17.271;
    double b = 237.7;
    double temp = (a * celsius) / (b + celsius) + log(humidity/100);
    double Td = (b * temp) / (a - temp);
    return Td;
}

//  http://www.ccacac.com/wp-content/uploads/2010/06/Humidex-Graph.pdf - 
double humidex(double celsius, double DewPoint)
{
    double e = 19.833625 - 5417.753 /(273.16 + DewPoint);
    double h = celsius + 3.3941 * exp(e) - 5.555;
    return h;
}


// TF = temp in F
// R = humidity in %
double heatIndex(double TF, double R)
{
    const double c1 = -42.379;
    const double c2 =  2.04901523;
    const double c3 = 10.14333127;
    const double c4 = -0.22475541;
    const double c5 = -0.00683783;
    const double c6 = -0.05481717;
    const double c7 =  0.00122874;
    const double c8 =  0.00085282;
    const double c9 = -0.00000199;

    double A = (( c5 * TF) + c2) * TF + c1;
    double B = (((c7 * TF) + c4) * TF + c3) * R;
    double C = (((c9 * TF) + c8) * TF + c6) * R * R;

    return A + B + C;
}

// less constants => faster but slightly inaccurate
// TF = temp in F
// R = humidity in %
double heatIndexFast(double TF, double R)
{
    const double c1 = -42.379;
    const double c2 =  2.04901523;
    const double c3 = 10.14333127;
    const double c4 = -0.22475541;

    double A = c2 * TF + c1;
    double B = (c4 * TF + c3) * R;

    return A + B;
}

// integer version
// TF = temp in F
// R = humidity in %
int heatIndexFastInt(int TF, int R)
{
    // consts multiplied by 1024
    long c1 = -43396;
    long c2 = 2098;
    long c3 = 10387;
    long c4 = -230;

    long A = c2 * TF + c1;  // so A is x 1024
    long B = (c4 * TF + c3) * R;  // and B too

    return (A + B + 512) / 1024; // division becomes a shift; +512 is for rounding
}

#endif
//
// END OF FILE
//
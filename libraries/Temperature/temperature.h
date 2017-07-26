//
//    FILE: temperature.h
// VERSION: 0.1.1
// PURPOSE: temperature functions
//
// HISTORY:
// 0.1.0 - 2015-03-29 initial version
// 0.1.1 - 2017-07-26 double to float (issue #33)
//

#ifndef TEMPERATURE
#define TEMPERATURE

#include "WProgram.h"

#define TEMPERATURE_VERSION "0.1.1"

//Celsius to Fahrenheit conversion
float Fahrenheit(float celsius)
{
    return 1.8 * celsius + 32;
}

//Celsius to Kelvin conversion
float Kelvin(float celsius)
{
    return celsius + 273.15;
}

// dewPoint function NOAA
// reference: http://wahiduddin.net/calc/density_algorithms.htm
float dewPoint(float celsius, float humidity)
{
    float A0= 373.15/(273.15 + celsius);
    float SUM = -7.90298*(A0-1);
    SUM += 5.02808 * log10(A0);
    SUM += -1.3816e-7 * (pow(10, (11.344*(1-1/A0)))-1) ;
    SUM += 8.1328e-3*(pow(10,(-3.49149*(A0-1)))-1) ;
    SUM += log10(1013.246);
    float VP = pow(10, SUM-3) * humidity;
    float T = log(VP/0.61078);   // temp var
    return (241.88*T) / (17.558-T);
}

// delta max = 0.6544
// 5x faster than dewPoint()
// reference: http://en.wikipedia.org/wiki/Dew_point
float dewPointFast(float celsius, float humidity)
{
    float a = 17.271;
    float b = 237.7;
    float temp = (a * celsius) / (b + celsius) + log(humidity/100);
    float Td = (b * temp) / (a - temp);
    return Td;
}

//  http://www.ccacac.com/wp-content/uploads/2010/06/Humidex-Graph.pdf - 
float humidex(float celsius, float DewPoint)
{
    float e = 19.833625 - 5417.753 /(273.16 + DewPoint);
    float h = celsius + 3.3941 * exp(e) - 5.555;
    return h;
}


// TF = temp in F
// R = humidity in %
float heatIndex(float TF, float R)
{
    const float c1 = -42.379;
    const float c2 =  2.04901523;
    const float c3 = 10.14333127;
    const float c4 = -0.22475541;
    const float c5 = -0.00683783;
    const float c6 = -0.05481717;
    const float c7 =  0.00122874;
    const float c8 =  0.00085282;
    const float c9 = -0.00000199;

    float A = (( c5 * TF) + c2) * TF + c1;
    float B = (((c7 * TF) + c4) * TF + c3) * R;
    float C = (((c9 * TF) + c8) * TF + c6) * R * R;

    return A + B + C;
}

// less constants => faster but slightly inaccurate
// TF = temp in F
// R = humidity in %
float heatIndexFast(float TF, float R)
{
    const float c1 = -42.379;
    const float c2 =  2.04901523;
    const float c3 = 10.14333127;
    const float c4 = -0.22475541;

    float A = c2 * TF + c1;
    float B = (c4 * TF + c3) * R;

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
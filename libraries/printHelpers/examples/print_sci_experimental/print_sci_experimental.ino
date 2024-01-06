//
//    FILE: print_sci_experimental.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test program SCI
//     URL: https://github.com/RobTillaart/printHelpers


#include "printHelpers.h"

uint32_t start, stop, duration;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PRINTHELPERS_VERSION: ");
  Serial.println(PRINTHELPERS_VERSION);
  Serial.println();

  Serial.println(sizeof(float));
  Serial.println(sizeof(double));
  Serial.println();

  double n = 6.072832E+37;

  delay(100);
  start = micros();
  char * b = sci(n, 6);
  stop = micros();
  Serial.print("TIME: ");
  Serial.println(stop - start);
  Serial.println(b);
  delay(100);
  //  duration = stop - start;

  start = micros();
  b = newsci(n, 6);
  stop = micros();
  Serial.print("TIME: ");
  Serial.println(stop - start);
  //   Serial.println((stop - start) *1.0 / duration);
  Serial.println(b);
  delay(100);

  Serial.println();
  Serial.println();
  n = PI;

  for (int i = 0; i < 75; i++)
  {
    Serial.print(i);
    Serial.print("\t");
    Serial.print(sci(n, 6));
    Serial.print("\t");
    Serial.print(newsci(n, 6));
    Serial.println();
    n *= PI;
  }
  Serial.println();

  Serial.println("\ndone...");
}


char * newsci(double n, uint8_t decimals)
{
  static char buffer[20];
  if (isnan(n))
  {
    strcpy(buffer, "nan");
    return buffer;
  }
  if (isinf(n))
  {
    if (n < 0) strcpy(buffer, "-inf");
    strcpy(buffer, "inf");
    return buffer;
  }
  bool neg = (n < 0);
  if (neg)
  {
    n = -n;
  }
  // int     exponent = int(log(n) * (1.0 / log(10)));
  int     exponent = int(log10(n));
  double  factor   = pow(10, -exponent);
  double  mantissa = n * factor;
  if (mantissa < 1)
  {
    mantissa *= 10;
    exponent--;
  }
  int     mantInt  = mantissa;
  long    mantDec  = (mantissa - mantInt) * pow(10, decimals);
  if (neg)
  {
    mantInt = -mantInt;
  }

  char format[24];
  sprintf(format, "%%d.%%0%dldE%%+02d", decimals);

  sprintf(buffer, format, mantInt, mantDec, exponent);
  //  sprintf(buffer, "%d.%06ldE%+02d", mantInt, mantDec, exponent);
  return buffer;
}


void loop()
{
}


//  -- END OF FILE --

//
//    FILE: fraction_extensive_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: reasonable extensive fraction test
//     URL: https://github.com/RobTillaart/Fraction


//  step size to test, typical 100000
//  for 100.000 tests
//  - AVR UNO 16 MHz takes ~500 seconds at 115200 baud
//  - ESP32 240 MHz takes ~400 seconds at 115200 baud
//  - ESP32 240 MHz takes ~85 seconds at 500000 baud


const uint32_t N = 100000;


#include "fraction.h"

uint32_t start, stop;
float maxError = 0;
uint32_t pos = 0;

void setup()
{
  //  NOTE BAUDRATE!
  Serial.begin(115200);
  Serial.print(__FILE__);
  Serial.print("FRACTION_LIB_VERSION: ");
  Serial.println(FRACTION_LIB_VERSION);
  Serial.println();
  delay(100);


  Fraction pi(PI);
  Serial.println(pi.toString());
  delay(1000);

  start = millis();

  for (uint32_t n = 100; n <= N; n++)
  {
    float g = n * (1.0 / N);
    Fraction frac( g );
    float f = frac.toFloat();

    //  find the maxError so far.
    float relError = abs(abs(f / g) - 1);
    if (relError > maxError)
    {
      maxError = relError;
      pos = n;
    }
    Serial.print(n);
    Serial.print("\t");
    Serial.print(g, 6);
    Serial.print("\t");
    Serial.print(f, 6);
    Serial.print("\t");
    Serial.print(100 * relError, 3);  //  as percentage
    Serial.print("\t");
    Serial.print(frac.toString());
    Serial.println();
  }
  stop = millis();
  Serial.println();
  Serial.print("MILLIS: ");
  Serial.println(stop - start);
  Serial.print("MAXERR: ");
  Serial.println(maxError);
  Serial.print("   POS: ");
  Serial.println(pos);
}


void loop()
{
}


//  -- END OF FILE --

//
//    FILE: ellipse_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: performance and accuracy test
//    DATE: 2021-10-31
//     URL: https://github.com/RobTillaart/ellipse


#include "ellipse.h"


ellipse E(1, 1);
uint32_t start, stop;
volatile float f;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println();

  Serial.println("  A      B      t  ECC       t  circum     t  Ramanu    t  Keppler    t  Parker");
  Serial.println("================================================================================");

  float A = 10;
  float B = 10;
  while (B > 0)
  {
    E.setA(A);
    E.setB(B);
    Serial.print(A);
    Serial.print(", ");
    Serial.print(B);
    Serial.print(", ");
    delay(100);

    start = micros();
    f = E.eccentricity();
    stop = micros();
    Serial.print(stop - start);
    Serial.print(", ");
    Serial.print(f, 4);
    Serial.print(", ");
    delay(100);

    start = micros();
    f = E.circumference();
    stop = micros();
    Serial.print(stop - start);
    Serial.print(", ");
    Serial.print(f, 4);
    Serial.print(", ");
    delay(100);

    start = micros();
    f = E.perimeter_ref();
    stop = micros();
    Serial.print(stop - start);
    Serial.print(", ");
    Serial.print(f, 4);
    Serial.print(", ");
    delay(100);

    start = micros();
    f = E.perimeter_Keppler();
    stop = micros();
    Serial.print(stop - start);
    Serial.print(", ");
    Serial.print(f, 4);
    Serial.print(", ");
    delay(100);

    start = micros();
    f = E.perimeter_Parker();
    stop = micros();
    Serial.print(stop - start);
    Serial.print(", ");
    Serial.print(f, 4);
    delay(100);

    Serial.println();
    B = B - 0.5;
  }

  Serial.println("\nDone...");
}


void loop()
{
}


//  -- END OF FILE --

//
//    FILE: float16_test_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test float16 performance
//     URL: https://github.com/RobTillaart/float16


#include "float16.h"

uint32_t start, stop;
volatile float f;
volatile bool b;


void setup()
{
  while (!Serial);
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("FLOAT16_LIB_VERSION: ");
  Serial.println(FLOAT16_LIB_VERSION);
  Serial.println();


  Serial.println("CONSTRUCTORS");
  f = random(1000000) * 0.001;
  start = micros();
  float16 f16(f);
  stop = micros();
  Serial.print("Constructor: \t");
  Serial.println(stop - start);
  delay(10);

  float16 f17(f + 1);
  start = micros();
  f16 = f17;
  stop = micros();
  Serial.print("a = b: \t");
  Serial.println(stop - start);
  delay(10);
  Serial.println();


  Serial.println("CONVERSION");
  start = micros();
  f = f16.toDouble();
  stop = micros();
  Serial.print("toDouble(): \t");
  Serial.println(stop - start);
  delay(10);
  Serial.println();


  Serial.println("COMPARE");
  f17 = f16.toDouble() + 1;

  start = micros();
  b = f16 == f17;
  stop = micros();
  Serial.print("compare == : \t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  b = f16 != f17;
  stop = micros();
  Serial.print("compare != : \t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  b = f16 < f17;
  stop = micros();
  Serial.print("compare <  : \t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  b = f16 <= f17;
  stop = micros();
  Serial.print("compare <= : \t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  b = f16 >= f17;
  stop = micros();
  Serial.print("compare >= : \t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  b = f16 > f17;
  stop = micros();
  Serial.print("compare >  : \t");
  Serial.println(stop - start);
  delay(10);
  Serial.println();


  Serial.println("MATH I");
  float16 f18;
  start = micros();
  f18 = f16 + f17;
  stop = micros();
  Serial.print("math +  : \t");
  Serial.println(stop - start);
  delay(10);
  //  Serial.println(f16);
  //  Serial.println(f17);
  //  Serial.println(f18);

  start = micros();
  f18 = f16 - f17;
  stop = micros();
  Serial.print("math -  : \t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  f18 = f16 * f17;
  stop = micros();
  Serial.print("math *  : \t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  f18 = f16 + f17;
  stop = micros();
  Serial.print("math /  : \t");
  Serial.println(stop - start);
  delay(10);
  Serial.println();

  Serial.println("MATH II");
  start = micros();
  f18 += f16;
  stop = micros();
  Serial.print("math += : \t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  f18 -= f16;
  stop = micros();
  Serial.print("math -= : \t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  f18 *= f16;
  stop = micros();
  Serial.print("math *= : \t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  f18 /= f16;
  stop = micros();
  Serial.print("math /= : \t");
  Serial.println(stop - start);
  delay(10);
  Serial.println();

  Serial.println(f16.toString(4));

  Serial.println("MATH III - negation");
  start = micros();
  f18 = -f16;
  stop = micros();
  Serial.print("negation : \t");
  Serial.println(stop - start);
  delay(10);
  Serial.println();

  Serial.println(f18.toString(4));

  Serial.println("\ndone");
}


void loop()
{
}


//  -- END OF FILE --

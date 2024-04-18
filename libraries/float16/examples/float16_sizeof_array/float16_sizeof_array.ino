//
//    FILE: float16_sizeof_array.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test float16 size
//     URL: https://github.com/RobTillaart/float16
//  See #12

#include "Arduino.h"
#include "float16.h"


float16 test16[100];
float test32[100];

void setup()
{
  Serial.begin(115200);

  Serial.println("FLOAT16");
  Serial.println(sizeof(test16) / sizeof(test16[0]));
  Serial.println(sizeof(test16));
  Serial.println(sizeof(test16[0]));
  Serial.println();

  Serial.println("FLOAT32");
  Serial.println(sizeof(test32) / sizeof(test32[0]));
  Serial.println(sizeof(test32));
  Serial.println(sizeof(test32[0]));
  Serial.println();

  // set some values to make sure the compiler doesn't optimise out the arrays.
  test16[5] = 32;
  test32[4] = 32;

//  Serial.println(test16[5].toDouble(), 3);
//  Serial.println(test16[5].toFloat(), 3);
//  Serial.println(test16[5].toString());
//  Serial.println(test16[5].toString(1));
//  Serial.println(test16[5].toString(3));
};

void loop()
{
};

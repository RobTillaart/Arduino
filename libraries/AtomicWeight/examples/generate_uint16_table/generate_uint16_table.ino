//    FILE: generate_uint16_table.ino
//  AUTHOR: Rob Tillaart
//     URL: https://github.com/RobTillaart/AtomicWeight
// PURPOSE: generate the 16 bit table for the AtomicWeight library
//          instead of a float per element it uses an uint16_t
//          and a weight factor. The error is less than 0.3%.


#include "Arduino.h"
#include "elements_float.h"


//  VERSION   FACTOR    DESCRIPTION
//  0.1.x     222.909   based op mapping max range 65535 == weight(118)
//  0.2.x     201.3868  searched for minimal relative error.

//  const float WEIGHT_FACTOR = 222.909;
const float WEIGHT_FACTOR = 201.3868;


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);

  //  HEADER
  Serial.println();
  Serial.println();
  Serial.println("//////////////////////////////////////////////");
  Serial.println("//");
  Serial.println("//  list of elements (scaled to uint16_t)");
  Serial.print("//  weight = weight * (1.0 / ");
  Serial.print(WEIGHT_FACTOR, 4);
  Serial.println(")");
  Serial.println("//");
  Serial.print("const float ATOMIC_WEIGHT_FACTOR = (1.0 / ");
  Serial.print(WEIGHT_FACTOR, 4);
  Serial.println(");");
  Serial.println();
  Serial.println("struct element");
  Serial.println("{");
  Serial.println("  char     name[3];");
  Serial.println("  uint16_t weight;");
  Serial.println("}");
  Serial.println("elements[119] =");

  //  ELEMENTS
  Serial.println("{");
  for (int i = 0; i < 119; i++)
  {
    Serial.print("  {\"");
    Serial.print(elements[i].name);
    Serial.print("\", ");
    Serial.print(round(elements[i].weight * WEIGHT_FACTOR));
    Serial.println("},");
  }
  Serial.println("};");
  Serial.println();
  Serial.println();
}


void loop()
{
}


//  -- END OF FILE --


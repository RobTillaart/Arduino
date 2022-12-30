//    FILE: generate_uint16_table.ino
//  AUTHOR: Rob Tillaart
//     URL: https://github.com/RobTillaart/AtomicWeight
// PURPOSE: generate the 16 bit table for the AtomicWeight library
//          instead of a float per element it uses an uint16_t 
//          and a weight factor. The error is less than 0.3%.


#include "Arduino.h"
#include "elements_float.h"


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);

  /////////////////////////////////////////////////////////
  //
  // generate 16 bit table
  //

  // HEADER
  Serial.println();
  Serial.println();
  Serial.println("/////////////////////////////////////////");
  Serial.println("//");
  Serial.println("// list of elements ");
  Serial.println("// weight = weight * (1.0/ 222.909)");
  Serial.println("//");
  Serial.println("struct element");
  Serial.println("{");
  Serial.println("  // uint8_t  nr;");
  Serial.println("  char     name[3];");
  Serial.println("  uint16_t weight;");
  Serial.println("}");
  Serial.println("elements[118] =");

  // ELEMENTS
  Serial.println("{");
  for (int i = 0; i < 118; i++)
  {
    Serial.print("  {\"");
    Serial.print(elements[i].name);
    Serial.print("\", ");
    Serial.print(round(elements[i].weight * 222.909));
    Serial.println("},");
  }
  Serial.println("};");
  Serial.println();
  Serial.println();
}

void loop()
{
}

// -- END OF FILE --

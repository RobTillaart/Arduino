//
//    FILE: fastTrig_generate_tables.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: generate look up tables for goniometry functions (and others)
//          these are not optimized for interpolation.
//    DATE: 2020-09-08
//     URL: https://github.com/RobTillaart/FastTrig

//  TODO
//  tables might have some trouble at "max values" CHECK


#include "Arduino.h"
#include "FastTrig.h"


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println();
  Serial.println(__FILE__);
  Serial.println("FAST_TRIG_LIB_VERSION: ");
  Serial.println(FAST_TRIG_LIB_VERSION);
  Serial.println();

  //  generate any # bits you want.
  generate_bit_sin(32);  //  works is possible
  generate_bit_sin(24);  //  TODO is this better than 16 bit?
  generate_bit_sin(20);  //  for serious math 1 digit better than 16 bit.
  generate_bit_sin(16);  //  for serious math
  generate_bit_sin(12);  //  for 12 bit DAC
  generate_bit_sin(10);  //  for 10 bit DAC
  generate_bit_sin(8);   //  for LED

  //  for LED
  //  need to patch data type in output,
  //  TODO: pack 2 values in one byte ==> would ~half the array size.
  generate_bit_sin(4);  //  interpolating makes no sense


  generate_bit_cos(16);  //  note the fastTrig reuses the isin table.
  generate_bit_cos(8);

  generate_bit_tan(16);
  generate_bit_tan(8);

  Serial.println("\n//done...");
}


void loop()
{
}


void generate_header()
{
  Serial.println();
  Serial.println();
  Serial.println("#include \"Arduino.h\"");
  Serial.println();
  Serial.println();
}


void generate_bit_sin(int t)
{
  uint64_t nr = (1ULL << t ) - 1;

  Serial.print("// use ");
  Serial.print(int32_t(nr));
  Serial.println(".0 as divider.");

  Serial.print("uint");
  Serial.print(t > 16 ? 32 : t > 8 ? 16 : 8);
  Serial.print("_t sinTable");
  Serial.print(t);
  Serial.print("[] = {\n  ");
  for (int i = 0; i <= 90; i++)
  {
    uint32_t  x;
    if (i < 90) x = sin(i * PI / 180) * nr + 0.5;
    else x = nr;
    Serial.print(x);
    Serial.print(", ");
    if (i % 10 == 0) {
      Serial.println();
      Serial.print("  ");
    }
  }
  Serial.println(" };\n");
  Serial.println();
  Serial.println();
}


void generate_bit_cos(int t)
{
  uint64_t nr = (1ULL << t ) - 1;

  Serial.print("// use ");
  Serial.print(int32_t(nr));
  Serial.println(".0 as divider.");

  Serial.print("uint");
  Serial.print(t > 16 ? 32 : t > 8 ? 16 : 8);
  Serial.print("_t cosTable");
  Serial.print(t);
  Serial.print("[] = {\n  ");
  for (int i = 0; i <= 90; i++)
  {
    uint32_t  x;
    if (i > 0) x = cos(i * PI / 180) * nr + 0.5;
    else x = nr;
    Serial.print(x);
    Serial.print(", ");
    if (i % 10 == 0) {
      Serial.println();
      Serial.print("  ");
    }
  }
  Serial.println(" };\n");
  Serial.println();
  Serial.println();
}


void generate_bit_tan(int t)
{
  uint64_t nr = (1ULL << t ) - 1;

  Serial.print("// use ");
  Serial.print(int32_t(nr));
  Serial.println(".0 as divider.");

  Serial.print("uint");
  Serial.print(t > 16 ? 32 : t > 8 ? 16 : 8);
  Serial.print("_t tanTable");
  Serial.print(t);
  Serial.print("[] = {\n  ");
  for (int i = 0; i <= 90; i++)
  {
    uint32_t x = tan(i * PI / 180) * nr + 0.5;
    if (i == 90) x--;
    Serial.print(x);
    Serial.print(", ");
    if (i % 10 == 0) {
      Serial.println();
      Serial.print("  ");
    }
  }
  Serial.println(" };\n");
  Serial.println();
  Serial.println();
}


//  -- END OF FILE --


//
//    FILE: print_toRoman.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo program toRoman
//     URL: https://github.com/RobTillaart/printHelpers


#include "printHelpers.h"

uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PRINTHELPERS_VERSION: ");
  Serial.println(PRINTHELPERS_VERSION);
  Serial.println();

  Serial.println(sizeof(float));
  Serial.println(sizeof(double));

  uint8_t maxlen = 0;

  for (uint32_t i = 1; i <= 5000; i++)
  {
    uint8_t len = strlen(toRoman(i));
    if (maxlen < len)
    {
      maxlen = len;
      Serial.print(i);
      Serial.print("\t");
      Serial.println(toRoman(i));
    }
  }
  Serial.println();
  Serial.print("MAXLEN: ");
  Serial.println(maxlen);
  Serial.println();
  delay(1000);

  start = micros();
  char * b;
  for (int i = 1; i <= 5000; i++)
  {
    b = toRoman(i);
  }
  stop = micros();
  Serial.println((stop - start) / 5000.0);
  Serial.println(b);
  delay(1000);

  //  for (int i = 1; i <= 5000; i++)
  //  {
  //    Serial.print(i);
  //    Serial.print('\t');
  //    Serial.println(toRoman(i));
  //  }
  //  delay(1000);

  Serial.println("\ndone...");
}


void loop()
{
}

//  -- END OF FILE --

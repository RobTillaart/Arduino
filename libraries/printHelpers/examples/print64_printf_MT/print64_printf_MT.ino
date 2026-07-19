//
//    FILE: print64_printf_MT.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo print 64 bit integers with printf("%s"))
//          printf needs explicit casting to (char *) - see issue #32 GitHub
//     URL: https://github.com/RobTillaart/printHelpers


#include "printHelpersMT.h"


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("PRINTHELPERS_LIB_VERSION: ");
  Serial.println(PRINTHELPERS_LIB_VERSION);
  Serial.println();
  delay(100);

  int64_t a = -4;
  int64_t b = -5;
  int64_t c = -6;

  Serial.println(print64(a));
  delay(100);

  Serial.println(print64(b));
  delay(100);

  Serial.println(print64(c));
  delay(100);

  char bigBuf[200];

  sprintf(bigBuf, "%s\n", (char *)print64(a));
  Serial.print(bigBuf);

  sprintf(bigBuf, "%s %s\n", (char *)print64(a), (char *)print64(b));
  Serial.print(bigBuf);

  sprintf(bigBuf, "%s %s %s\n", (char *)print64(a), (char *)print64(b), (char *)print64(c));
  Serial.print(bigBuf);

  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --

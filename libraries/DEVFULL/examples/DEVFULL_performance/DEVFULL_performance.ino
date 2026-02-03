//
//    FILE: DEVFULL_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/DEVFULL
//
//  this shows that a print can be split up in many write calls
//  that all return -28. Print will add these together.
//  (is a limit of the Arduino environment)


#include "DEVFULL.h"

DEVFULL df;

uint32_t start, stop;
int n;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("DEVFULL_LIB_VERSION: ");
  Serial.println(DEVFULL_LIB_VERSION);
  Serial.println();
  delay(100);


  start = micros();
  n = df.println("it is dark in here...");
  stop = micros();
  Serial.print("PRINTLN: \t");
  Serial.print(stop - start);
  Serial.print('\t');
  Serial.println(n / -28);   //  # of ENOSPC == #write calls.
  delay(10);


  start = micros();
  n = df.write((const uint8_t *) "it is dark in here...", 22);
  stop = micros();
  Serial.print("WRITE: \t\t");
  Serial.print(stop - start);
  Serial.print('\t');
  Serial.println(n / -28);   //  # of ENOSPC == #write calls.
  delay(10);


  start = micros();
  n = df.print(123456789L);
  stop = micros();
  Serial.print("long: \t\t");
  Serial.print(stop - start);
  Serial.print('\t');
  Serial.println(n / -28);   //  # of ENOSPC == #write calls.
  delay(10);


  start = micros();
  n = df.print(PI, 0);
  stop = micros();
  Serial.print("float0: \t");
  Serial.print(stop - start);
  Serial.print('\t');
  Serial.println(n / -28);   //  # of ENOSPC == #write calls.
  delay(10);


  start = micros();
  n = df.print(PI, 5);
  stop = micros();
  Serial.print("float1: \t");
  Serial.print(stop - start);
  Serial.print('\t');
  Serial.println(n / -28);   //  # of ENOSPC == #write calls.
  delay(10);


  start = micros();
  n = df.print(PI, 10);
  stop = micros();
  Serial.print("float2: \t");
  Serial.print(stop - start);
  Serial.print('\t');
  Serial.println(n / -28);   //  # of ENOSPC == #write calls.
  delay(10);


  start = micros();
  n = df.print(PI, 15);
  stop = micros();
  Serial.print("float3: \t");
  Serial.print(stop - start);
  Serial.print('\t');
  Serial.println(n / -28);   //  # of ENOSPC == #write calls.
  delay(10);


  start = micros();
  n = df.print(PI, 20);
  stop = micros();
  Serial.print("float4: \t");
  Serial.print(stop - start);
  Serial.print('\t');
  Serial.println(n / -28);   //  # of ENOSPC == #write calls.
  delay(10);


  //  NOTE: THIS WILL NEVER STOP as it is always full.
  start = micros();
  df.find((char *)"hello");
  stop = micros();
  Serial.print("find: \t");
  Serial.println(stop - start);
  delay(10);


  Serial.println("\nDone...");
}


void loop()
{
}


//  -- END OF FILE --

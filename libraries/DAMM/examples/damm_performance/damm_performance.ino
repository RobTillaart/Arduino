//
//    FILE: DAMM_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour
//     URL: https://github.com/RobTillaart/DAMM


#include "DAMM.h"

DAMM damm;
DAMM_small ds;

uint32_t start, stop;

//  132 digits
char pi[] = "3141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825";

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("DAMM_LIB_VERSION: ");
  Serial.println(DAMM_LIB_VERSION);
  Serial.println();
  delay(100);

  //////////////////
  Serial.println("\nDAMM\n");
  delay(100);

  damm.reset();
  start = micros();
  bool b = damm.isValid("5724");
  stop = micros();
  Serial.print("test 1: \t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println(b);
  delay(100);

  start = micros();
  char c = damm.generateChecksum("572");
  stop = micros();
  Serial.print("test 2: \t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println(c);
  delay(100);

  start = micros();
  c = damm.generateChecksum(pi);
  stop = micros();
  Serial.print("test 3: \t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print((stop - start) * 1.0 / strlen(pi));
  Serial.print("\t");
  Serial.println(c);
  delay(100);

  //  STREAM MODE
  damm.reset();
  start = micros();
  damm.add('5');
  damm.add('7');
  char z = damm.add('2');
  stop = micros();
  Serial.print("test 4: \t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println(z);
  delay(100);

  damm.reset();
  start = micros();
  for (int i = 0; i < strlen(pi); i++)
  {
    z = damm.add(pi[i]);
  }
  stop = micros();
  Serial.print("test 5: \t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print((stop - start) * 1.0 / strlen(pi));
  Serial.print("\t");
  Serial.println(z);
  delay(100);

  //////////////////
  Serial.println("\nDAMM_SMALL\n");
  delay(100);

  ds.reset();
  start = micros();
  b = ds.isValid("5724");
  stop = micros();
  Serial.print("test 1: \t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println(b);
  delay(100);

  start = micros();
  c = ds.generateChecksum("572");
  stop = micros();
  Serial.print("test 2: \t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println(c);
  delay(100);

  start = micros();
  c = ds.generateChecksum(pi);
  stop = micros();
  Serial.print("test 3: \t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print((stop - start) * 1.0 / strlen(pi));
  Serial.print("\t");
  Serial.println(c);
  delay(100);

  //  STREAM MODE
  ds.reset();
  start = micros();
  ds.add('5');
  ds.add('7');
  z = ds.add('2');
  stop = micros();
  Serial.print("test 4: \t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println(z);
  delay(100);

  ds.reset();
  start = micros();
  for (int i = 0; i < strlen(pi); i++)
  {
    z = ds.add(pi[i]);
  }
  stop = micros();
  Serial.print("test 5: \t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print((stop - start) * 1.0 / strlen(pi));
  Serial.print("\t");
  Serial.println(z);
  delay(100);

}


void loop()
{
}


//  -- END OF FILE --

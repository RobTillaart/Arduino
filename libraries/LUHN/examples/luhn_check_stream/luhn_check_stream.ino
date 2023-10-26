//    FILE: luhn_check_stream.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/LUHN


#include "Arduino.h"
#include "LUHN.h"


uint32_t start, stop;

LUHN checker;

//  example https://en.wikipedia.org/wiki/Luhn_algorithm
char ID[20] = "79927398713";

char c;

void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("LUHN_LIB_VERSION: ");
  Serial.println(LUHN_LIB_VERSION);

  Serial.println("run I: add() per character");
  for (uint8_t i = 0; i < strlen(ID) - 1; i++)
  {
    c = checker.add(ID[i]);
    //  debug info
    Serial.print(ID[i]);
    Serial.print('\t');
    Serial.print(c);     //  should print 3 as last digit.
    Serial.println();
  }
  checker.reset();
  Serial.println();
  delay(10);

  start = micros();
  for (uint8_t i = 0; i < strlen(ID) - 1; i++)
  {
    checker.add(ID[i]);
  }
  c = checker.reset();
  stop = micros();
  Serial.print("LUHN:\t");
  Serial.println(c);     //  should print 3.
  Serial.print("time:\t");
  Serial.print(stop - start);
  Serial.println();
  Serial.println();
  delay(10);

  Serial.println("run II: should have same 2nd column as run 1.");
  for (uint8_t i = 0; i < strlen(ID); i++)
  {
    char tmp[32];
    strcpy(tmp, ID);
    tmp[i] = 0;
    c = checker.generateChecksum(tmp);
    Serial.print(tmp);
    Serial.print("\t");
    Serial.println(c);
  }
  Serial.println();
  delay(10);


  char tmp[32];
  strcpy(tmp, ID);
  tmp[strlen(ID)-1] = 0;
  start = micros();
  c = checker.generateChecksum(tmp);
  stop = micros();
  Serial.println();
  Serial.println("run III: generateChecksum()");
  Serial.print("LUHN:\t");
  Serial.println(c);     //  should print 3.
  Serial.print("time:\t");
  Serial.print(stop - start);
  Serial.println();
  Serial.println();
  delay(10);


  Serial.println("\ndone...");
}

void loop()
{

}


// -- END OF FILE --

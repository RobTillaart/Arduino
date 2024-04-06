//
//    FILE: analogKeypad_values.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: helper for adjust 4x4 analogue keypad MAGIC numbers


#define ANALOGPORT    A0

#include "AnalogKeypad.h"

AnalogKeypad AKP(ANALOGPORT);
uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("ANALOGKEYPAD_LIB_VERSION:\t");
  Serial.println(ANALOGKEYPAD_LIB_VERSION);

  Serial.println();
  Serial.println("Press keys to get the ADC values for the _rawRead() function");
  Serial.println();

  testChar("0");
  testChar("1");
  testChar("2");
  testChar("3");
  testChar("4");
  testChar("5");
  testChar("6");
  testChar("7");
  testChar("8");
  testChar("9");
  testChar("A");
  testChar("B");
  testChar("C");
  testChar("D");
  testChar("#");
  testChar("*");

  Serial.println("\ndone...");
}

void loop()
{
}


//
void testChar(const char * str)
{
  int x = analogRead(ANALOGPORT);
  int y = 0;
  Serial.print("Press ");
  Serial.print(str);
  Serial.print("\t\t");
  do
  {
    y = analogRead(ANALOGPORT);
  }
  while (abs(x - y) < 4);      //  ADAPT THRESHOLD IF NEEDED
  Serial.print(y);
  Serial.print("\t");
  Serial.println(y / 4);       //  assume 10 bits.
  delay(1000);
}


//  -- END OF FILE --

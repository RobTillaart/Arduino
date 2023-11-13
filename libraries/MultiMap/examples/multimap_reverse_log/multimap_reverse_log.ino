//
//    FILE: multimap_reverse_logarithmic.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2023-06-23


#include "MultiMap.h"


long in[10] = { 0, 150, 300, 550, 850, 970, 1009, 1017, 1021, 1023 };
long rlog10[10] = { 1023, 1000, 972, 909, 761, 586, 390, 264, 102, 0};


volatile int x;


//  as formula
int revlog10(int raw)
{
  return round((1023 / 3.01) *  log10(1023 - raw));
}


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MULTIMAP_LIB_VERSION: ");
  Serial.println(MULTIMAP_LIB_VERSION);
  Serial.println();
  delay(100);

  //  determine gain
  performance();
  delay(5000);

  //  test range input values
  for (int i = 0; i < 1024; i++)
  {
    int y = multiMap<long>(i, in, rlog10, 10);
    Serial.print(i);
    Serial.print("\t");
    Serial.print(y);
    Serial.print("\t");
    Serial.print(revlog10(i));
    Serial.println();
  }
  Serial.println();
  delay(5000);
}


void loop()
{
  int raw = analogRead(A0);
  int val = multiMap<long>(raw, in, rlog10, 10);
  Serial.print(raw);
  Serial.print("\t");
  Serial.print(val);
  Serial.println();
  delay(10);
}


void performance()
{
  uint32_t start, dur1, dur2;

  start = micros();
  for (int i = 0; i < 1024; i++)
  {
    x = multiMap<long>(i, in, rlog10, 10);
  }
  dur1 = micros() - start;
  Serial.print("TIME MM: \t");
  Serial.println(dur1);
  delay(100);

  start = micros();
  for (int i = 0; i < 1024; i++)
  {
    x = revlog10(i);
  }
  dur2 = micros() - start;
  Serial.print("TIME FUNC: \t");
  Serial.println(dur2);
  Serial.print("FACTOR: \t");
  Serial.println(1.0 * dur2 / dur1);
  Serial.println();
  delay(100);
}


//  -- END OF FILE --

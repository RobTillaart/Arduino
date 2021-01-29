//
//    FILE: DEVRANDOM_demo.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo
//    DATE: 2020-06-23
//    (c) : MIT
//

#include "DEVRANDOM.h"

DEVRANDOM dr;

uint32_t i = 0, start, stop;
volatile int x;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println();

  Serial.println("SOFTWARE:\t");
  dr.useSW();
  start = millis();
  while (millis() - start < 1000)
  {
    x = dr.read();
    i++;
  }
  Serial.print("nrs per second:");
  Serial.println(i);
  Serial.println(x);
  delay(1000);

  Serial.println("HW PULSES:\t");
  dr.useHW(4);
  start = millis();
  while (millis() - start < 1000)
  {
    x = dr.read();
    i++;
  }
  Serial.print("nrs per second: ");
  Serial.println(i);
  Serial.println(x);
  delay(1000);

  Serial.println("ANALOG:\t");
  dr.useAR(A0);
  start = millis();
  while (millis() - start < 1000)
  {
    x = dr.read();
    i++;
  }
  Serial.print("nrs per second: ");
  Serial.println(i);
  Serial.println(x);
  delay(1000);

  dr.useSW();
  i = 0;

  uint32_t x;
  fscanf((FILE*)&dr, "%lu", &x);
  Serial.print("UINT32: ");
  Serial.println(x, HEX);
  
  uint16_t y;
  fscanf((FILE*)&dr, "%u", &y);
  Serial.print("UINT16: ");
  Serial.println(y, HEX);

//  float f;
//  fscanf((FILE*)&dr, "%e", &f);  // does not work on UNO.
//  Serial.print("FLOAT: ");
//  Serial.println(f, 4);
//
//  char str[24];
//  fscanf((FILE*)&dr, "%20s", str); // "works, but unusable garbage"
//  Serial.print("STRING: ");
//  Serial.println(str);

  delay(1000);
}

void loop()
{
  i++;
  if (dr.available())
  {
    Serial.print("\t");
    Serial.print(dr.read());
    if ((i % 10) == 9 ) Serial.println();
  }
  delay(100);
}

// -- END OF FILE --
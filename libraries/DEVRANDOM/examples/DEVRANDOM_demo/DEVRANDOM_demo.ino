//
//    FILE: DEVRANDOM_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2020-06-23
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

  Serial.println("Reseeding compile time");
  start = micros();
  dr.print(__FILE__);
  dr.print(__DATE__);
  dr.print(__TIME__);
  dr.print(PI);
  stop = micros();
  Serial.print("reseeding: ");
  Serial.println(stop - start);
  Serial.println();
  delay(1000);


  Serial.println("Build in random");
  dr.useRandom();
  i = 0;
  start = millis();
  while (millis() - start < 1000)
  {
    x = dr.read();
    i++;
  }
  Serial.print("nrs per second: ");
  Serial.println(i);
  Serial.println(x);
  Serial.println();
  delay(1000);

  Serial.println("DigitalRead");
  dr.useDigitalRead(4);
  i = 0;
  start = millis();
  while (millis() - start < 1000)
  {
    x = dr.read();
    i++;
  }
  Serial.print("nrs per second: ");
  Serial.println(i);
  Serial.println(x);
  Serial.println();
  delay(1000);

  Serial.println("AnalogRead");
  dr.useAnalogRead(A0);
  i = 0;
  start = millis();
  while (millis() - start < 1000)
  {
    x = dr.read();
    i++;
  }
  Serial.print("nrs per second: ");
  Serial.println(i);
  Serial.println(x);
  Serial.println();
  delay(1000);

  Serial.println("MARSAGLIA");
  dr.useMarsaglia();
  i = 0;
  start = millis();
  while (millis() - start < 1000)
  {
    x = dr.read();
    i++;
  }
  Serial.print("nrs per second: ");
  Serial.println(i);
  Serial.println(x);
  Serial.println();
  delay(1000);

  //  uint32_t x;
  //  fscanf((FILE*)&dr, "%lu", &x);  //  fails on ESP32
  //  Serial.print("UINT32: ");
  //  Serial.println(x, HEX);

  //  uint16_t y;
  //  fscanf((FILE*)&dr, "%u", &y);  //  fails on ESP32
  //  Serial.print("UINT16: ");
  //  Serial.println(y, HEX);

  //  float f;
  //  fscanf((FILE*)&dr, "%e", &f);  // does not work on UNO.
  //  Serial.print("FLOAT: ");
  //  Serial.println(f, 4);
  //
  //  char str[24];
  //  fscanf((FILE*)&dr, "%20s", str); // "works, but unusable garbage"
  //  Serial.print("STRING: ");
  //  Serial.println(str);


  //  reset i counter for loop()
  Serial.println();
  i = 0;
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


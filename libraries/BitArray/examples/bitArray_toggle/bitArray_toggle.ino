//
//    FILE: bitArray_toggle.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo performance toggle bitarray
//     URL: https://github.com/RobTillaart/BitArray
//     URL: https://forum.arduino.cc/index.php?topic=361167.0


#include "BitArray.h"


BitArray b;

uint32_t start;
uint32_t stop;
volatile int32_t x = 0;


void setup()
{
  Serial.begin(115200);
  Serial.print("Start ");
  Serial.println(__FILE__);
  Serial.print("LIB VERSION:\t");
  Serial.println(BITARRAY_LIB_VERSION);
  delay(100);

  b.begin(5, 1000);

  start = micros();
  b.set(100, 17);
  stop = micros();
  Serial.print("SET: ");
  Serial.println(stop - start);
  delay(100);

  start = micros();
  int x = b.get(100);
  stop = micros();
  Serial.print("GET: ");
  Serial.println(stop - start);
  Serial.println(x);
  delay(100);

  start = micros();
  x = b.toggle(100);
  stop = micros();
  Serial.print("TOGGLE: ");
  Serial.println(stop - start);
  Serial.println(x);
  delay(100);

  start = micros();
  x = b.get(100);
  stop = micros();
  Serial.print("GET: ");
  Serial.println(stop - start);
  Serial.println(x);
  delay(100);


  Serial.println("Done...");
}


void loop()
{
}


//  -- END OF FILE --

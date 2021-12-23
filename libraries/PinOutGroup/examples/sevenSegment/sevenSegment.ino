//    FILE: sevenSegment.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo PinOutGroup library for Arduino


#include "PinOutGroup.h"

// connect Arduino UNO pins 2.. 8 to pins A..G of a 7 segments display


uint8_t ar[7] = {2, 3, 4, 5, 6, 7, 8};

int ssc[16] = // seven segment char
{
  63, 6, 91, 79, 102, 109, 125, 7, 127, 111,  // 0 .. 9
  119, 124, 57, 94, 121, 113                  // A .. F
};

PinOutGroup display;

uint32_t start, stop, t1, t2;


void setup()
{ 
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print(F("PINOUTGROUP_LIB_VERSION: "));
  Serial.println(PINOUTGROUP_LIB_VERSION);
  Serial.println();

  Serial.println("Without PinOutGroup");
  delay(10);
  start = micros();
  for (int i = 0; i < 16; i++)
  {
    digitalWrite(2, ssc[i] & 0x01);
    digitalWrite(3, ssc[i] & 0x02);
    digitalWrite(4, ssc[i] & 0x04);
    digitalWrite(5, ssc[i] & 0x08);
    digitalWrite(6, ssc[i] & 0x10);
    digitalWrite(7, ssc[i] & 0x20);
    digitalWrite(8, ssc[i] & 0x40);
  }
  stop = micros();  
  Serial.println("cycling through 16 chars");
  Serial.print("Time: ");
  t1 = stop - start;
  Serial.println(stop - start);
  Serial.println();
  delay(10);

  Serial.println("With PinOutGroup");
  delay(10);
  display.add(7, ar);
  
  start = micros();
  for (int i = 0; i < 16; i++)
  {
    display.write(ssc[i]);
  }
  stop = micros();  
  Serial.println("cycling through 16 chars");
  Serial.print("Time: ");
  t2 = stop - start;
  Serial.println(stop - start);
  Serial.println();
  
  Serial.print("Percentage: ");
  Serial.println((100.0 * t2)/ t1);
  Serial.println();
}


void loop()
{
  for (int i = 0; i < 16; i++)
  {
    display.write(ssc[i]);
    delay(250);
  }
}


// -- END OF FILE --


//
//    FILE: shiftOutSlow_print.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test sketch for print interface
//     URL: https://github.com/RobTillaart/ShiftOutSlow


#include "ShiftOutSlow.h"


ShiftOutSlow SOS(12, 13, LSBFIRST);

volatile int x = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println(SHIFTOUTSLOW_LIB_VERSION);

  Serial.println("\nwrite(byte)");
  Serial.println("delay\tus/byte");
  delay(10);                                // extra time to flush serial buffer
  for (uint16_t d = 0; d < 100; d += 10)
  {
    SOS.setDelay(d);
    uint32_t start = micros();
    x = SOS.write(0x55);
    uint32_t stop = micros();
    float duration = stop - start;
    Serial.print(d);
    Serial.print("\t");
    Serial.println(duration / x, 2);
    delay(10);
  }

  char str[24] = "hello world!";
  Serial.println("\nwrite(buffer, size)");
  Serial.println("delay\tus/byte");
  delay(10);
  for (uint16_t d = 0; d < 100; d += 10)
  {
    SOS.setDelay(d);
    uint32_t start = micros();
    x = SOS.write((const uint8_t*) str, 12);
    uint32_t stop = micros();
    float duration = stop - start;
    Serial.print(d);
    Serial.print("\t");
    Serial.println(duration / x, 2);
    delay(10);
  }

  Serial.println("\nprint(str)");
  Serial.println("delay\tus/byte");
  delay(10);
  for (uint16_t d = 0; d < 100; d += 10)
  {
    SOS.setDelay(d);
    uint32_t start = micros();
    x = SOS.print(str);
    uint32_t stop = micros();
    float duration = stop - start;
    Serial.print(d);
    Serial.print("\t");
    Serial.println(duration / x, 2);
    delay(10);
  }

  Serial.println("\nprintln(str)");
  Serial.println("delay\tus/byte");
  delay(10);
  for (uint16_t d = 0; d < 100; d += 10)
  {
    SOS.setDelay(d);
    uint32_t start = micros();
    x = SOS.println(str);
    uint32_t stop = micros();
    float duration = stop - start;
    Serial.print(d);
    Serial.print("\t");
    Serial.println(duration / x, 2);
    delay(10);
  }

  Serial.println(LSBFIRST);
  Serial.println(MSBFIRST);
  Serial.println("done...");
}


void loop()
{
}


// -- END OF FILE --


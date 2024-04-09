//
//    FILE: bitArrayDemo2.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo performance bit array
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

    test(1, 10000);
    test(2, 5000);
    test(3, 3333);
    test(4, 2500);
}


void test(uint8_t bits, uint16_t cnt)
{
    b.begin(bits, cnt);
    Serial.print("CAPACITY:\t");
    Serial.println(b.capacity());
    Serial.print("  MEMORY:\t");
    Serial.println(b.memory());
    Serial.print("    BITS:\t");
    Serial.println(b.bits());
    Serial.print("SEGMENTS:\t");
    Serial.println(b.segments());
    delay(100);

    start = micros();
    for (uint16_t i = 0; i < cnt; i++)
    {
        x += b.get(i);
    }
    stop = micros();
    Serial.print("DURATION:\t");
    Serial.println(stop - start);
    delay(100);

    start = micros();
    for (uint16_t i = 0; i < cnt; i++)
    {
        x += b.get(i);
        x += b.get(i);
    }
    stop = micros();
    Serial.print("DURATION:\t");
    Serial.println(stop - start);
    Serial.print("       X:\t");
    Serial.println(x);
    delay(100);

    start = micros();
    for (uint16_t i = 0; i < cnt; i++)
    {
        b.set(i, 0);
    }
    stop = micros();
    Serial.print("DURATION:\t");
    Serial.println(stop - start);
    delay(100);

    start = micros();
    for (uint16_t i = 0; i < cnt; i++)
    {
        b.set(i, 0);
        b.set(i, 0);
    }
    stop = micros();
    Serial.print("DURATION:\t");
    Serial.println(stop - start);
    delay(100);

    start = micros();
    b.clear();
    stop = micros();
    Serial.print("DURATION:\t");
    Serial.println(stop - start);
    delay(100);

    Serial.println("Done...");
}


void loop()
{
}


//  -- END OF FILE --


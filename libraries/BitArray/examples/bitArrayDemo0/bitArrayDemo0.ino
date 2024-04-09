//
//    FILE: bitArrayDemo0.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo - store 2000 dice rolls
//     URL: https://github.com/RobTillaart/BitArray


#include "BitArray.h"


#define SAMPLES 2000

BitArray diceRolls;
int count[7] = { 0, 0, 0, 0, 0, 0, 0 };


void setup()
{
    Serial.begin(115200);
    Serial.print("Start ");
    Serial.println(__FILE__);
    Serial.print("LIB VERSION:\t");
    Serial.println(BITARRAY_LIB_VERSION);

    //  3 bits can hold any value 1..6
    int x = diceRolls.begin(3, SAMPLES);
    if (x == BA_NO_MEMORY_ERR) Serial.println("no memory");

    diceRolls.clear();

    Serial.print("CAPACITY:\t");
    Serial.println(diceRolls.capacity());
    Serial.print("  MEMORY:\t");
    Serial.println(diceRolls.memory());
    Serial.print("    BITS:\t");
    Serial.println(diceRolls.bits());
    Serial.print("SEGMENTS:\t");
    Serial.println(diceRolls.segments());

    for (int i = 0; i < SAMPLES; i++)
    {
        byte roll = random(6) + 1;
        diceRolls.set(i, roll);

        if (i % 40 == 0)
        {
            Serial.println();
            Serial.print(i, DEC);
            Serial.print(")\t");
        }
        Serial.print(roll, DEC);
        Serial.print(" ");
    }
    Serial.println();


    Serial.println();
    for (int i = 0; i < SAMPLES; i++)
    {
        if (i % 40 == 0)
        {
            Serial.println();
            Serial.print(i, DEC);
            Serial.print(")\t");
        }
        Serial.print(diceRolls.get(i), DEC);
        Serial.print(" ");
    }
    Serial.println();
    Serial.println();

    diceRolls.clear();

    Serial.println();
    for (int i = 0; i < SAMPLES; i++)
    {
        if (i % 40 == 0)
        {
            Serial.println();
            Serial.print(i, DEC);
            Serial.print(")\t");
        }
        Serial.print(diceRolls.get(i), DEC);
        Serial.print(" ");
    }
    Serial.println();
    Serial.println();


    for (int i = 0; i < SAMPLES; i++)
    {
        count[diceRolls.get(i)]++;
    }
    for (int i = 0; i < 7; i++)
    {
        Serial.print(i, DEC);
        Serial.print(")\t");
        Serial.println(count[i]);
    }
    Serial.println("\n finish test...\n");
}


void loop()
{
}


//  -- END OF FILE --


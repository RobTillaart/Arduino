//
//    FILE: bitArrayDemo0.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.02
// PURPOSE: demo - store 2000 dice rolls
//    DATE: 14-11-2015
//     URL:
//
// Released to the public domain
//

#include "BitArray.h"

//#include "avrheap.h"

#define SAMPLES 2000

BitArray diceRolls;
int count[7] = { 0, 0, 0, 0, 0, 0, 0 };

//Avrheap myheap;

void setup()
{
    Serial.begin(115200);
    Serial.print("Start ");
    Serial.println(__FILE__);
    Serial.print("LIB VERSION:\t");
    Serial.println(BITARRAY_LIB_VERSION);

    int x = diceRolls.begin(3, SAMPLES);  // 3 bits can hold any value 1..6
    if (x == BA_NO_MEMORY_ERR) Serial.println("no mem");
    diceRolls.clear();

    // myheap.followHeap();

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

    // myheap.followHeap();

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

    dicerolls.clear();

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


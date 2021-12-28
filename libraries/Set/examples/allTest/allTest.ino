//
//    FILE: allTest.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo/test Set class
//    DATE: 2014-11-16
//     URL: https://github.com/RobTillaart/SET


#include "set.h"


Set setA, setB;
volatile bool b;

uint32_t start, stop;

void setup()
{
    Serial.begin(115200);
    Serial.print("Start set_demo : ");
    Serial.println(SET_LIB_VERSION);
    Serial.println();

    timingTest();
    equalTest();
    intersectionTest();
    intersection2Test();
    subsetTest();
    iterationTest();

    Serial.println("done...");
    Serial.println();
}


void loop()
{
}


void timingTest()
{
    Set myset;

    Serial.println("TIMING TEST");
    Serial.print("100x clear():\t");
    start = micros();
    for (uint8_t i = 0; i < 100; i++) myset.clear();
    stop = micros();
    Serial.println(stop - start);

    Serial.print("100x add():\t");
    start = micros();
    for (uint8_t i = 0; i < 100; i++) myset.add(i);
    stop = micros();
    Serial.println(stop - start);

    Serial.print("100x sub():\t");
    start = micros();
    for (uint8_t i = 0; i < 100; i++) myset.sub(i);
    stop = micros();
    Serial.println(stop - start);

    Serial.print("100x has():\t");
    start = micros();
    for (uint8_t i = 0; i < 100; i++) b = myset.has(i);
    stop = micros();
    Serial.println(stop - start);

    Serial.print("100x invert(v):\t");
    start = micros();
    for (uint8_t i = 0; i < 100; i++) myset.invert(i);
    stop = micros();
    Serial.println(stop - start);

    Serial.print("invert():\t");
    start = micros();
    myset.invert();
    stop = micros();
    Serial.println(stop - start);

    Serial.print("count() empty:\t");
    myset.clear();
    start = micros();
    myset.count();
    stop = micros();
    Serial.println(stop - start);

    Serial.print("count() full:\t");
    myset.clear();
    myset.invert();
    start = micros();
    myset.count();
    stop = micros();
    Serial.println(stop - start);
    Serial.println();

    Serial.print("100x isEmpty(): empty\t");
    myset.clear();
    start = micros();
    for (uint8_t i = 0; i < 100; i++) b = myset.isEmpty();
    stop = micros();
    Serial.println(stop - start);

    Serial.print("100x isEmpty(): full\t");
    myset.clear();
    myset.invert();
    start = micros();
    for (uint8_t i = 0; i < 100; i++) b = myset.isEmpty();
    stop = micros();
    Serial.println(stop - start);

    Serial.print("100x isFull(): empty\t");
    myset.clear();
    start = micros();
    for (uint8_t i = 0; i < 100; i++) b = myset.isFull();
    stop = micros();
    Serial.println(stop - start);

    Serial.print("100x isFull(): full\t");
    myset.clear();
    myset.invert();
    start = micros();
    for (uint8_t i = 0; i < 100; i++) b = myset.isFull();
    stop = micros();
    Serial.println(stop - start);
    Serial.println();


    randomSeed(1);
    setA.clear();
    setB.clear();
    for (int i = 0; i<150; i++)
    {
      setA.add(random(256));
      setB.add(random(256));
    }

    Serial.print("a = b + c:\t");
    start = micros();
    myset = setA + setB;
    stop = micros();
    Serial.println(stop - start);

    Serial.print("a = b - c:\t");
    start = micros();
    myset = setA - setB;
    stop = micros();
    Serial.println(stop - start);

    Serial.print("a = b * c:\t");
    start = micros();
    myset = setA * setB;
    stop = micros();
    Serial.println(stop - start);

    Serial.print("a += b:\t");
    start = micros();
    myset += setA;
    stop = micros();
    Serial.println(stop - start);

    Serial.print("a -= b:\t");
    start = micros();
    myset -= setA;
    stop = micros();
    Serial.println(stop - start);

    Serial.print("a *= b:\t");
    start = micros();
    myset *= setA;
    stop = micros();
    Serial.println(stop - start);

    Serial.print("a == b:\t");
    start = micros();
    b = (setA == setB);
    stop = micros();
    Serial.println(stop - start);

    Serial.print("a != b:\t");
    start = micros();
    b = (setA != setB);
    stop = micros();
    Serial.println(stop - start);

    Serial.print("a <= b:\t");
    start = micros();
    b = (setA <= setB);
    stop = micros();
    Serial.println(stop - start);

    Serial.println();
    Serial.println("iteration 10 elements");
    Serial.print("first:\t");
    setA.clear();
    randomSeed(1);
    for (int i = 0; i < 10; i++)
    {
      setA.add(random(256));
    }
    start = micros();
    int n = setA.first();
    stop = micros();
    Serial.println(stop - start);

    Serial.print("next:\t");
    start = micros();
    n = setA.next();
    stop = micros();
    Serial.println(stop - start);

    Serial.print("100x first + next until -1 :\t");
    start = micros();
    for (uint8_t i = 0; i < 100; i++)
    {
      n = setA.first();
      while (n != -1)
      {
        n = setA.next();
      }
    }
    stop = micros();
    Serial.println(stop - start);

    Serial.print("100x  last + prev until -1 :\t");
    start = micros();
    for (uint8_t i = 0; i < 100; i++)
    {
      n = setA.last();
      while (n != -1)
      {
        n = setA.prev();
      }
    }
    stop = micros();
    Serial.println(stop - start);
    Serial.println();

    Serial.println();
}


void equalTest()
{
    Serial.println("EQUAL TEST");
    randomSeed(1);
    setA.clear();
    setB.clear();
    Serial.println(setA == setB?"true":"false");
    setB.add(0);
    Serial.println(setA == setB?"true":"false");
    Serial.println(setA == setA?"true":"false");

    Set setC(setB);
    Serial.println(setC == setB?"true":"false");
    Serial.println(setC.count());

    Set setD = setB;
    Serial.println(setD != setB?"unequal":"equal");
    Serial.println(setD == setB?"true":"false");
    Serial.println(setD.count());

    setD = setA;
    Serial.println(setD == setB?"true":"false");
    Serial.println(setD.count());

    Serial.println();
}


void intersectionTest()
{
    Serial.println("INTERSECTION TEST");
    randomSeed(1);
    setA.clear();
    setB.clear();
    for (int i = 0; i < 150; i++)
    {
      setA.add(random(256));
      setB.add(random(256));
    }
    Serial.println(setA.count());
    Serial.println(setB.count());
    setA *= setB;
    Serial.println(setA.count());
    Serial.println();

    Serial.println("union test");
    randomSeed(1);
    setA.clear();
    setB.clear();
    for (int i = 0; i < 150; i++)
    {
      setA.add(random(256));
      setB.add(random(256));
    }
    Serial.println(setA.count());
    Serial.println(setB.count());
    setA += setB;
    Serial.println(setA.count());
    Serial.println();

    Serial.println("diff test");
    randomSeed(1);
    setA.clear();
    setB.clear();
    for (int i = 0; i < 150; i++)
    {
      setA.add(random(256));
      setB.add(random(256));
    }
    Serial.println(setA.count());
    Serial.println(setB.count());
    setA -= setB;
    Serial.println(setA.count());

    Serial.println();
}


void intersection2Test()
{
    Serial.println("INTERSECTION2 TEST");
    randomSeed(1);
    setA.clear();
    setB.clear();
    for (int i = 0; i < 150; i++)
    {
      setA.add(random(256));
      setB.add(random(256));
    }
    Set setC;
    setC = setA * setB;
    Serial.println(setA.count());
    Serial.println(setB.count());
    Serial.println(setC.count());
    Serial.println();

    Serial.println("union2 test");
    setC = setA + setB;
    Serial.println(setA.count());
    Serial.println(setB.count());
    Serial.println(setC.count());
    Serial.println();

    Serial.println("diff2 test");
    setC = setA - setB;
    Serial.println(setA.count());
    Serial.println(setB.count());
    Serial.println(setC.count());
    Serial.println();
}


void subsetTest()
{
    Serial.println("SUBSET TEST");
    Set setE;
    for (int i = 0; i < 5; i++) setE.add(i);

    Set setF(setE);

    Serial.println(setE.count());
    Serial.println(setF.count());

    Serial.println(setE <= setF?"subset":"no subset");
    Serial.println(setF <= setE?"subset":"no subset");

    setF.add(6);
    Serial.println(setE <= setF?"subset":"no subset");
    Serial.println(setF <= setE?"subset":"no subset");

    setF.sub(3);
    Serial.println(setE <= setF?"subset":"no subset");
    Serial.println(setF <= setE?"subset":"no subset");

    Serial.println();
}


void iterationTest()
{
    Serial.println("10x ITERATE OVER SET TEST");
    randomSeed(1);
    setA.clear();
    for (int i = 0; i < 10; i++)
    {
      setA.add(random(256));
    }
    Serial.println(setA.count());
    start = micros();
    for (int i = 0; i < 10; i++)
    {
      int n = setA.first();
      while (n != -1)
      {
        Serial.print(n);
        Serial.print('\t');
        n = setA.next();
      }
      Serial.println();
    }
    stop = micros();
    Serial.println();
    Serial.println(stop - start);
    Serial.println();

    start = micros();
    for (int i = 0; i < 10; i++)
    {
      int n = setA.last();
      while (n != -1)
      {
        Serial.print(n);
        Serial.print('\t');
        n = setA.prev();
      }
      Serial.println();
    }
    stop = micros();
    Serial.println();
    Serial.println(stop - start);
    Serial.println();
}


// -- END OF FILE --


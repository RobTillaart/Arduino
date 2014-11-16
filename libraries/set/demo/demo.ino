//
//    FILE: set_demo.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.00
// PURPOSE: demo
//    DATE: 2014-11-09
//     URL:
//
// Released to the public domain
//

#include "set.h"

set myset;
set setA, setB;

uint32_t start;
uint32_t stop;

volatile bool b;

void setup()
{
  Serial.begin(115200);
  Serial.print("Start set_demo : ");
  Serial.println(SET_LIB_VERSION);
  Serial.println();

  Serial.print("myset.clr():\t");
  start = micros();
  myset.clr();
  stop = micros();
  Serial.println(stop-start);

  Serial.print("myset.add():\t");
  start = micros();
  for (int i=0; i<256; i++) myset.add(i);
  stop = micros();
  Serial.println(stop-start);

  Serial.print("myset.sub():\t");
  start = micros();
  for (int i=0; i<256; i++) myset.sub(i);
  stop = micros();
  Serial.println(stop-start);

  Serial.print("myset.has():\t");
  start = micros();
  for (int i=0; i<256; i++) b = myset.has(i);
  stop = micros();
  Serial.println(stop-start);

  Serial.print("myset.invert(v):\t");
  start = micros();
  for (int i=0; i<256; i++) myset.invert(i);
  ;
  stop = micros();
  Serial.println(stop-start);

  Serial.print("myset.invert():\t");
  start = micros();
  myset.invert();
  stop = micros();
  Serial.println(stop-start);

  Serial.print("myset.count():\t");
  start = micros();
  myset.count();
  stop = micros();
  Serial.println(stop-start);


  Serial.println("\nrandom test");
  randomSeed(1);
  setA.clr();
  for (int i=0; i<150; i++)
  {
    setA.add(random(256));
  }
  for (int i=0; i<4; i++)
  {
    for (int j=0; j<64; j++)
    {
      Serial.print(setA.has(i*64+j));
    }
    Serial.println();
  }
  Serial.println(setA.count());
  Serial.println();

  Serial.println("\nintersection test");
  randomSeed(1);
  setA.clr();
  setB.clr();
  for (int i=0; i<150; i++)
  {
    setA.add(random(256));
    setB.add(random(256));
  }
  Serial.println(setA.count());
  Serial.println(setB.count());
  setA.is(setB);
  for (int i=0; i<4; i++)
  {
    for (int j=0; j<64; j++)
    {
      Serial.print(setA.has(i*64+j));
    }
    Serial.println();
  }
  Serial.println(setA.count());
  Serial.println();

  Serial.println("\nunion test");
  randomSeed(1);
  setA.clr();
  setB.clr();
  for (int i=0; i<150; i++)
  {
    setA.add(random(256));
    setB.add(random(256));
  }
  Serial.println(setA.count());
  Serial.println(setB.count());
  setA.un(setB);
  for (int i=0; i<4; i++)
  {
    for (int j=0; j<64; j++)
    {
      Serial.print(setA.has(i*64+j));
    }
    Serial.println();
  }
  Serial.println(setA.count());
  Serial.println();


  Serial.println("\ndiff test");
  randomSeed(1);
  setA.clr();
  setB.clr();
  for (int i=0; i<150; i++)
  {
    setA.add(random(256));
    setB.add(random(256));
  }
  Serial.println(setA.count());
  Serial.println(setB.count());
  setA.df(setB);
  for (int i=0; i<4; i++)
  {
    for (int j=0; j<64; j++)
    {
      Serial.print(setA.has(i*64+j));
    }
    Serial.println();
  }
  Serial.println(setA.count());
  Serial.println();

  Serial.println("\nequal test");
  randomSeed(1);
  setA.clr();
  setB.clr();
  Serial.println(setA == setB?"true":"false");
  setB.add(0);
  Serial.println(setA == setB?"true":"false");
  Serial.println(setA == setA?"true":"false");

  set setC(setB);
  Serial.println(setC == setB?"true":"false");
  Serial.println(setC.count());

  set setD = setB;
  Serial.println(setD == setB?"true":"false");
  Serial.println(setD.count());

  setD = setA;
  Serial.println(setD == setB?"true":"false");
  Serial.println(setD.count());

  Serial.println("done...");
  Serial.println();
}

void loop()
{
}


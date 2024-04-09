//
//    FILE: heapdemo2.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo AvrHeap class
//     URL: http://forum.arduino.cc/index.php?topic=355660
//          https://github.com/RobTillaart/avrheap


#if !defined(ARDUINO_ARCH_AVR)


void setup()
{
}


void loop()
{
}

#else


#include "avrheap.h"

Avrheap myheap;

int *par[10];


void setup()
{
  int seed = analogRead(A0) + analogRead(A3) + analogRead(A2);
  seed ^= (int)micros();
  randomSeed(seed);
  Serial.begin(115200);
  Serial.print(F("Start "));
  Serial.print(F(__FILE__));
  Serial.print(F("\nLibVersion "));
  Serial.println(AVRHEAP_LIB_VERSION);

  Serial.println();
  Serial.print(F("HEAP ADDR: "));
  hWord(Serial, myheap.startAddress());
  Serial.println();

  Serial.println(F("\nallocate 10 chunks\n"));
  for (int i = 0; i < 10; i++)
  {
    int mSize = random(1, 40) * sizeof(int);
    par[i] = (int*) malloc(mSize); // all different sizes
    *par[i] = 0;
    dumpAlloced((byte*)par[i], false);
  }
  Serial.println();

  myheap.dumpHeap(80);
  Serial.println();
  Serial.println(myheap);
  myheap.freeListWalk();

  Serial.println(F("free 3 pointers"));
  free(par[3]);
  free(par[5]);
  free(par[7]);

  myheap.freeListWalk();

  Serial.println(F("1 malloc"));
  par[3] = (int*) malloc(10);

  myheap.freeListWalk();
  myheap.dumpHeap(80);
  Serial.println();
  Serial.println(myheap);

  Serial.println(F("done"));
}


void loop()
{
}


#endif

// -- END OF FILE --

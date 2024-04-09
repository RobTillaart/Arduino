//
//    FILE: heapdemo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: heapdemo
//     URL: https://github.com/RobTillaart/avrheap


#include "avrheap.h"

Avrheap myheap;

int *par[10];


void setup()
{
  Serial.begin(115200);
  Serial.print("Start ");
  Serial.println(__FILE__);
  Serial.println(AVRHEAP_LIB_VERSION);

  /* works only with old version KEEP CI happy

  Serial.println();
  Serial.print("HEAP ADDR:\t");
  Serial.println(myheap.startAddress());
  Serial.println();

  // allocate 10 chunks
  Serial.println("ptr\taddr");
  for (int i = 0; i < 10; i++)
  {
    par[i] = (int*) malloc(i * 3);  // all different sizes
    *par[i] = 0;
    Serial.print(i);
    Serial.print('\t');
    Serial.println((int)par[i], DEC);
  }
  Serial.println();
  Serial.println();
  myheap.dump(80);
  Serial.println("\nfollowHeap");
  myheap.followHeap();


  Serial.print("fragmented: ");
  Serial.println(myheap.isFragmented() ? "True" : "False");
  Serial.print("count: ");
  Serial.println(myheap.freeListCount());
  Serial.print("size: ");
  Serial.println(myheap.freeListSize());
  Serial.println("dump: ");
  myheap.freeListDump();

  Serial.println("free 3 pointers");
  free(par[3]);
  free(par[5]);
  free(par[7]);

  Serial.print("fragmented: ");
  Serial.println(myheap.isFragmented() ? "True" : "False");
  Serial.print("count: ");
  Serial.println(myheap.freeListCount());
  Serial.print("size: ");
  Serial.println(myheap.freeListSize());
  Serial.println("dump: ");
  myheap.freeListDump();

  Serial.println("1 malloc");
  par[3] = (int*) malloc(10);

  Serial.print("fragmented:\t");
  Serial.println(myheap.isFragmented() ? "True" : "False");
  Serial.print("count:\t");
  Serial.println(myheap.freeListCount());
  Serial.print("size:\t");
  Serial.println(myheap.freeListSize());
  Serial.println("dump: ");
  myheap.freeListDump();

  Serial.println();
  myheap.dump(80);
  Serial.println("\nfollowHeap");
  myheap.followHeap();
  */

  Serial.println("\ndone");
}


void loop()
{
}


//  -- END OF FILE --

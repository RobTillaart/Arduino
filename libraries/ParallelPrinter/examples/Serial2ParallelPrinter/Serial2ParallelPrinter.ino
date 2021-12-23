//
//    FILE: Serial2ParPrinter.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2020-05-26


#include "ParallelPrinter.h"

// uses defaults
// uint8_t p[] = {3, 4, 5, 6, 7, 8, 9, 10};
// ParPrinter(13, 2, 12, p );

ParallelPrinter PP;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  
  PP.begin();
}


void loop()
{
  if (Serial.available()) PP.write(Serial.read());
}


// -- END OF FILE --


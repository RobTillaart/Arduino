//
//    FILE: FastShiftOut_scope_test.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test sketch for scope
//     URL: https://github.com/RobTillaart/FastShiftOut
//
//  Connect scope to pins mentioned in constructor (12, 13)

#include "FastShiftOut.h"

FastShiftOut FSO(12, 13, LSBFIRST);

uint32_t start, duration1, duration2;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("FASTSHIFTOUT_LIB_VERSION: ");
  Serial.println(FASTSHIFTOUT_LIB_VERSION);
  Serial.println();

  // test1();
  pinMode(12, OUTPUT);
}


void test1()
{
  for (int i = 0; i < 1000; i++)
  {
    FSO.write(0x55);
  }
}


void test2()
{
  for (int i = 0; i < 1000; i++)
  {
    FSO.writeLSBFIRST(0x88);
  }
}


void test3()
{
  for (int i = 0; i < 1000; i++)
  {
    FSO.write32(0x55555555);
  }
}

void loop()
{
  //  ~ 1000 Hz test
  //  digitalWrite(12, HIGH);
  //  delayMicroseconds(1000);
  //  digitalWrite(12, LOW);
  //  delayMicroseconds(1000);

  //  reference
  //  shiftOut(12, 13, MSBFIRST, 0x55);

  FSO.write(0x55);
  delayMicroseconds(50);
}


//  -- END OF FILE --

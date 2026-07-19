//
//    FILE: print_hexDumpLine16.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo program hexDump
//     URL: https://github.com/RobTillaart/printHelpers


#include "printHelpers.h"


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("PRINTHELPERS_LIB_VERSION: ");
  Serial.println(PRINTHELPERS_LIB_VERSION);
  Serial.println();

  for (uint32_t addr = 0; addr < 1000; addr += 16)
  {
    //  fill array with your data (here random)
    uint8_t arr[16];
    for (int i = 0; i < 16; i++) arr[i] = random(128);

    //  empty line in dump
    if (addr % 160 == 0) Serial.println();
    hexDumpLine16(Serial, addr, arr, 16, true);
  }

  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --

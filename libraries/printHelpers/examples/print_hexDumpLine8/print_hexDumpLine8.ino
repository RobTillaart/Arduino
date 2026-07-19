//
//    FILE: print_hexDumpLine8.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo program hexDump8
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

  for (uint32_t addr = 0; addr < 200; addr += 8)
  {
    //  fill array with your data (here random)
    uint8_t arr[8];
    for (int i = 0; i < 8; i++) arr[i] = random(128);

    //  empty line in dump
    if (addr % 80 == 0) Serial.println();
    hexDumpLine8(Serial, addr, arr, 8, true);
  }


  for (uint32_t addr = 0; addr < 100; addr += 8)
  {
    //  fill array with your data (here random)
    uint8_t arr[8];
    for (int i = 0; i < 8; i++) arr[i] = random(128);

    //  empty line in dump
    if (addr % 80 == 0) Serial.println();
    hexDumpLine8(Serial, addr, arr, 8, false);
  }

  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --

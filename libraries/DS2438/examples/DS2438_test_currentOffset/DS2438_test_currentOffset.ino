//
//    FILE: DS2438_test_currentOffset.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test DS2438 library battery monitor
//     URL: https://github.com/RobTillaart/DS2438

#include "DS2438.h"

#define ONE_WIRE_BUS          2

OneWire   oneWire(ONE_WIRE_BUS);
DS2438    bm(&oneWire);

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("DS2438_LIB_VERSION: ");
  Serial.println(DS2438_LIB_VERSION);
  Serial.println();

  bm.begin();
  Serial.println(bm.isConnected());

  for (int offset = -100; offset < 100; offset += 5)
  {
    bm.writeCurrentOffset(offset);
    int x = bm.readCurrentOffset();
    Serial.print(offset);
    Serial.print("\t");
    Serial.print(x);
    Serial.print("\t");
    Serial.println(x == offset);
  }
  Serial.println("\ndone...");
}

void loop()
{
}


//  -- END OF FILE --

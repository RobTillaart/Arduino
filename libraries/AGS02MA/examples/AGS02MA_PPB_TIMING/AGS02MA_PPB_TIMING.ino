//
//    FILE: AGS02MA_PPB_TIMING.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test application
//     URL: https://github.com/RobTillaart/AGS02MA
//

#include "AGS02MA.h"


AGS02MA AGS(26);


void setup()
{
  //  ESP devices typically miss the first serial log lines after flashing.
  //  Delay somewhat to include all output.
  delay(1000);

  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("AGS02MA_LIB_VERSION: ");
  Serial.println(AGS02MA_LIB_VERSION);
  Serial.println();

  Wire.begin();

  bool b = AGS.begin();
  Serial.print("BEGIN:\t");
  Serial.println(b);

  Serial.print("VERS:\t");
  Serial.println(AGS.getSensorVersion());

  //  pre-heating improves measurement quality
  //  can be skipped
  Serial.println("\nWarming up (120 seconds = 24 dots)");
  while (AGS.isHeated() == false)
  {
    delay(5000);
    Serial.print(".");
  }
  Serial.println();

  b = AGS.setPPBMode();
  uint8_t m = AGS.getMode();
  Serial.print("MODE:\t");
  Serial.print(b);
  Serial.print("\t");
  Serial.println(m);
}


void loop()
{
  delay(1500);
  uint32_t start = millis();
  uint32_t value = AGS.readPPB();
  uint32_t stop = millis();

  uint32_t duration = stop - start;
  Serial.print(duration);
  Serial.print("\t");
  Serial.print(value);
  Serial.print("\t");
  Serial.print(AGS.lastStatus(), HEX);
  Serial.print("\t");
  Serial.print(AGS.lastError(), HEX);
  Serial.println();
}


//  -- END OF FILE --


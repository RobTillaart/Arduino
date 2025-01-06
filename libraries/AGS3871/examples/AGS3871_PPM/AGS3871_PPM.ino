//
//    FILE: AGS3871_PPM.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test application
//     URL: https://github.com/RobTillaart/AGS3871
//

#include "AGS3871.h"


AGS3871 AGS;


void setup()
{
  //  ESP devices typically miss the first serial log lines after flashing.
  //  Delay somewhat to include all output.
  delay(1000);

  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("AGS3871_LIB_VERSION: ");
  Serial.println(AGS3871_LIB_VERSION);
  Serial.println();

  Wire.begin();

  bool b = AGS.begin();
  Serial.print("BEGIN:\t");
  Serial.println(b);
  Serial.print("VERSION:\t");
  Serial.println(AGS.getVersion());
  Serial.print("ADDRESS:\t");
  Serial.println(AGS.getAddress());

  //  pre-heating improves measurement quality
  //  can be skipped
  Serial.println("\nWarming up (120 seconds = 24 dots)");
  while (AGS.isHeated() == false)
  {
    delay(5000);
    Serial.print(".");
  }
  Serial.println();
}


void loop()
{
  //  time between measurements at least 2 seconds.
  delay(3000);
  Serial.print("PPM:\t");
  Serial.print(AGS.readPPM());
  Serial.print("\t");
  Serial.print("\t");
  Serial.print(AGS.dataReady(), HEX);
  Serial.print("\t");
  Serial.print(AGS.lastError(), HEX);
  Serial.println();
}


//  -- END OF FILE --

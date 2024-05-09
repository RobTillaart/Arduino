//
//    FILE: LTR390_getLux.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/LTR390_DFR
//
//  can be used with plotter.

#include "LTR390_DFR.h"


LTR390_DFR uv;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.println();
  Serial.print("LTR390_DFR_LIB_VERSION: ");
  Serial.println(LTR390_DFR_LIB_VERSION);
  Serial.println();

  Wire.begin();

  uv.begin();

  while (uv.isConnected() == false)
  {
    Serial.println("Could not connect, fix and reboot");
    delay(1000);
  }
  Serial.println("Device found.");

  uv.setALSMode();

  Serial.println("RAW, LUX");
}


void loop()
{
  delay(1000);
  Serial.print(uv.getALSData());
  Serial.print("\t");
  Serial.println(uv.getLux());
}


//  -- END OF FILE --

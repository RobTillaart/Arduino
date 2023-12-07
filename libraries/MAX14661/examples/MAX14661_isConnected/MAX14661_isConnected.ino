//
//    FILE: MAX14661_isConnected.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test MAX14661 lib
//    DATE: 2021-01-29
//     URL: https://github.com/RobTillaart/MAX14661
//
// test behaviour when device is not connected and reconnected again.
// E.g. simulate loose wires..


#include "Wire.h"
#include "MAX14661.h"


MAX14661 mux(0x4C);  // 0x4C..0x4F

bool connected = false;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MAX14661_LIB_VERSION: ");
  Serial.println(MAX14661_LIB_VERSION);

  Wire.begin();
  if (mux.begin() == false)
  {
    Serial.println("Could not find MAX14661");
  }

  Serial.println("end of setup()");
}


void loop()
{
  if (!connected && mux.isConnected())
  {
    connected = true;
    Serial.print(millis());
    Serial.println("\tconnected");
  }
  if (connected && !mux.isConnected())
  {
    connected = false;
  }
  delay(1000);
}


//  -- END OF FILE --


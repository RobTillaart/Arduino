//
//    FILE: DS3502_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/DS3502


#include "DS3502.h"


DS3502 myPot(0x28);  //  default address, A1, A0 == GND.

uint8_t val = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("DS3502_LIB_VERSION: ");
  Serial.println(DS3502_LIB_VERSION);
  Serial.println();

  Wire.begin();
  while (myPot.begin() == false)
  {
    Serial.print("Error:\t");
    Serial.println(myPot.getLastError());
    delay(100);
  }

  Serial.print("Addr:\t");
  Serial.println(myPot.getAddress());

  Serial.print("NVRAM:\t");
  Serial.println(myPot.isEnabledNVRAM());
}


void loop()
{
  //  sort of sawtooth
  if (myPot.setValue(val++) == false)
  {
    Serial.print("Error:\t");
    Serial.print(millis());
    Serial.print("\t");
    Serial.println(myPot.getLastError());
  }
  if (val > 127) val = 0;
  delay(100);
}


//  -- END OF FILE --

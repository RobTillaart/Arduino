//
//    FILE: DS3502_nvram.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour
//     URL: https://github.com/RobTillaart/DS3502
//
//  NOTE: running this programm for days may exhaust the NVRAM.


#include "DS3502.h"


DS3502 myPot(0x28);  //  default address, A1, A0 == GND.

uint8_t val = 0;
uint32_t counter = 0;
uint32_t nvramThreshold = 60000;


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
  counter++;
  //  now and then store the value in EEPROM.
  if (counter >= nvramThreshold)
  {
    counter = 0;
    myPot.enableNVRAM(true);
  }

  //  sine wave
  uint8_t val = 64 + 63 * sin(millis() * 0.001);
  myPot.setValue(val);
  Serial.println(val);
  delay(20);
}


//  -- END OF FILE --

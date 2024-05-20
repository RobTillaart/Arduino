//
//    FILE: DS3232_test_SRAM.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic write function
//     URL: https://github.com/RobTillaart/DS3232
//
//  NOTE: does NOT work for DS3231
//        (only for DS3232)

#include "DS3232.h"

DS3232 rtc;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("DS3232_LIB_VERSION: ");
  Serial.println(DS3232_LIB_VERSION);
  Serial.println();

  Wire.begin();
  if (rtc.begin() != DS3232_OK)
  {
    Serial.println("could not connect, check wires etc");
    // while (1);
  }

  //  CLEAR SRAM
  for (uint32_t i = 0; i < 236; i++)
  {
    rtc.SRAMwrite8(i, 0);
    Serial.print(i);
    Serial.print('\t');
    Serial.println(rtc.SRAMread8(i));
  }

  //  write values / read back  8 bit
  for (uint32_t i = 0; i < 236; i++)
  {
    rtc.SRAMwrite8(i, i);
    Serial.print(i);
    Serial.print('\t');
    Serial.println(rtc.SRAMread8(i));
  }

  //  write values / read back 16 bit
  for (uint32_t i = 0; i < 236; i += 2)
  {
    rtc.SRAMwrite16(i, 1000 + i);
    Serial.print(i);
    Serial.print('\t');
    Serial.println(rtc.SRAMread16(i));
  }

  //  write values / read back 32 bit
  for (uint32_t i = 0; i < 236; i += 4)
  {
    rtc.SRAMwrite32(i, 2000 + i);
    Serial.print(i);
    Serial.print('\t');
    Serial.println(rtc.SRAMread32(i));
  }
}


void loop()
{

}


//  --  END OF FILE  --

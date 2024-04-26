//
//    FILE: oneWireScanner.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: scan for 1-Wire devices
//    DATE: 2016-01-10
//     URL: https://github.com/RobTillaart/DS18B20_RT

//  HISTORY
//  2024-01-03  refactored, + extend list.


#include "OneWire.h"


struct DSdevice
{
  byte id;
  char type[12];
} DSdevices[] = {
  { 0x01, "DS2401"},     //  Silicon Serial Number
  { 0x05, "DS2405"},     //  switch
  { 0x10, "DS18S20" },   //  Temperature sensor
  { 0x22, "DS18B20" },   //  Temperature sensor
  { 0x26, "DS2438" },    //  Battery monitor
  { 0x28, "DS1822" },    //  Temperature sensor
  { 0x2D, "DS2807" },    //  EEPROM
  { 0x38, "DS1825" },    //  Temperature sensor
  { 0x3B, "MAX31850" },  //  Temperature sensor
  { 0x42, "DS28EA00" },  //  Temperature sensor
};

int DStypeCount = sizeof(DSdevices)/sizeof(DSdevice);


//  Defined for Arduino UNO, adjust if needed.
const int startPin = 2;
const int endPin = 20;


uint8_t findDevices(int pin)
{
  OneWire ow(pin);

  uint8_t address[8];
  uint8_t count = 0;

  while (ow.search(address))
  {
    Serial.print("\nscanning pin:\t ");
    Serial.println(pin, DEC);
    {
      count++;
      // PRINT ADDRESS FOUND
      for (uint8_t i = 0; i < 8; i++)
      {
        Serial.print("0x");
        if (address[i] < 0x10) Serial.print("0");
        Serial.print(address[i], HEX);
        if (i < 7) Serial.print(", ");
      }
      Serial.print("\t");
      // CHECK CRC
      if (ow.crc8(address, 7) == address[7])
      {
        Serial.print("CRC OK  \t");
      }
      else
      {
        Serial.println("CRC FAIL\t");
      }
      // PRINT TYPE
      bool unknown = true;
      for (uint8_t i = 0; i < DStypeCount; i++)
      {
        if (address[0] == DSdevices[i].id)
        {
          Serial.print(DSdevices[i].type);
          unknown = false;
          break;
        }
      }
      if (unknown) Serial.print("unknown");
    }
    Serial.println();
  }

  Serial.print("nr devices found: ");
  Serial.println(count);
  return count;
}


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  for (uint8_t pin = startPin; pin < endPin; pin++)
  {
    findDevices(pin);
  }
  Serial.println("\nDone...\n");
}

void loop()
{
}


//  -- END OF FILE --


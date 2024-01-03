//
//    FILE: DS18B20_getAddress.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: DS18B20 lib getAddress demo
//     URL: https://github.com/RobTillaart/DS18B20_INT


#include "DS18B20_INT.h"


#define ONE_WIRE_BUS          2

OneWire     oneWire(ONE_WIRE_BUS);
DS18B20_INT sensor(&oneWire);

DeviceAddress da;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("DS18B20_INT_LIB_VERSION: ");
  Serial.println(DS18B20_INT_LIB_VERSION);

  Serial.print("\ngetAddress: ");
  Serial.println(sensor.getAddress(da));

  sensor.begin();

  Serial.print("\ngetAddress: ");
  Serial.println(sensor.getAddress(da));

  if (!sensor.getAddress(da))
  {
    Serial.println("No address found!");
    return;
  }

  Serial.print("Address: ");
  for (uint8_t i = 0; i < 8; i++)
  {
    if (da[i] < 0x10) Serial.print('0');
    Serial.print(da[i], HEX);
  }
  Serial.println();
}


void loop()
{
}


//  -- END OF FILE --


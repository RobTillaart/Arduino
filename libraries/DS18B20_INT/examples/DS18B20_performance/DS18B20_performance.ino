//
//    FILE: DS18B20_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: DS18B20 lib getAddress demo
//     URL: https://github.com/RobTillaart/DS18B20_INT


#include "DS18B20_INT.h"


#define ONE_WIRE_BUS          2

OneWire     oneWire(ONE_WIRE_BUS);
DS18B20_INT sensor(&oneWire);

DeviceAddress da;


uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("DS18B20_INT_LIB_VERSION: ");
  Serial.println(DS18B20_INT_LIB_VERSION);
  delay(10);

  start = micros();
  bool b = sensor.getAddress(da);
  stop = micros();
  Serial.print("\ngetAddress: \t");
  Serial.println(b);
  Serial.print("Time: \t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  sensor.begin();
  stop = micros();
  Serial.print("\nbegin: \t");
  Serial.println(b);
  Serial.print("Time: \t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  b = sensor.getAddress(da);
  stop = micros();
  Serial.print("\ngetAddress: \t");
  Serial.println(b);
  Serial.print("Time: \t");
  Serial.println(stop - start);
  delay(10);

  if (b == false)
  {
    Serial.println("No address found!");
  }

  Serial.print("Address: ");
  for (uint8_t i = 0; i < 8; i++)
  {
    if (da[i] < 0x10) Serial.print('0');
    Serial.print(da[i], HEX);
  }
  Serial.println();
  delay(10);

  start = micros();
  sensor.requestTemperatures();
  stop = micros();
  Serial.print("\nrequestTemperatures: \t");
  Serial.println();
  Serial.print("Time: \t");
  Serial.println(stop - start);
  delay(10);

  delay(750);

  start = micros();
  b = sensor.isConversionComplete();
  stop = micros();
  Serial.print("\nisConversionComplete: \t");
  Serial.println(b);
  Serial.print("Time: \t");
  Serial.println(stop - start);
  delay(10);

  start = micros();
  int temp = sensor.getTempC();
  stop = micros();
  Serial.print("\ngetTempC: \t");
  Serial.println(temp);
  Serial.print("Time: \t");
  Serial.println(stop - start);
  delay(10);


  start = micros();
  temp = sensor.getTempC(false);
  stop = micros();
  Serial.print("\ngetTempC(false): \t");
  Serial.println(temp);
  Serial.print("Time: \t");
  Serial.println(stop - start);
  delay(10);

}


void loop()
{
}


//  -- END OF FILE --

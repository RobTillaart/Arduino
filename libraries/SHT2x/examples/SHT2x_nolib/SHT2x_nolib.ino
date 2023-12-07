//
//    FILE: SHT2x_nolib.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test sensor without library
//     URL: https://github.com/RobTillaart/SHT2x


#include "Wire.h"

uint8_t status = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  Wire.begin();
  Wire.setClock(100000);

  testConnected();
}


void loop()
{
  delay(1000);
  float t = getTemperature();
  Serial.print(t, 2);
  Serial.print("\t");
  Serial.println(status, HEX);
  delay(1000);
  float h = getHumidity();
  Serial.print(h, 2);
  Serial.print("\t");
  Serial.println(status, HEX);
}


///////////////////////////////////////////////////


void testConnected()
{
  Wire.beginTransmission(0x40);
  int rv = Wire.endTransmission();
  if (rv != 0) Serial.println("CONNECT FAILED");
  else Serial.println("CONNECTED");
}


float getTemperature()
{
  uint16_t raw = 0;

  Wire.beginTransmission(0x40);
  Wire.write(0xF3);
  if (Wire.endTransmission() != 0)
  {
    Serial.println("ERR 1");
    return 0.0;
  }
  delay(90);
  Wire.requestFrom(0x40, 3);
  uint32_t start = millis();
  while (Wire.available() < 3)
  {
    if (millis() - start > 90)
    {
      Serial.println("ERR 2");
      return 0.0;
    }
    yield();
  }

  raw = Wire.read() << 8;
  raw += Wire.read();
  status = raw & 0x0003;
  raw &= 0xFFFC;

  Serial.print("RAW TEM: ");
  Serial.println(raw, HEX);
  return -46.85 + (175.72 / 65536.0) * raw;
}


float getHumidity()
{
  uint16_t raw = 0;

  Wire.beginTransmission(0x40);
  Wire.write(0xF5);
  if (Wire.endTransmission() != 0)
  {
    Serial.println("ERR 11");
    return 0.0;
  }
  delay(30);
  Wire.requestFrom(0x40, 3);
  uint32_t start = millis();
  while (Wire.available() < 3)
  {
    if (millis() - start > 30)
    {
      Serial.println("ERR 12");
      return 0.0;
    }
    yield();
  }

  raw = Wire.read() << 8;
  raw += Wire.read();
  status = raw & 0x0003;
  raw &= 0xFFFC;

  Serial.print("RAW HUM: ");
  Serial.println(raw, HEX);
  return -6.0 + (125.0 / 65536.0) * raw;
}


//  -- END OF FILE --


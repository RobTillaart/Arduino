


#include "Wire.h"

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

}


void loop()
{
  uint8_t x = 0;
  for (int i = 0; i < 8; i++)
  {
    x = readSwitch(i);
    Serial.print(x);
  }
  Serial.println();
  delay(1000);
}

uint8_t readSwitch(uint8_t i)
{
  Wire.beginTransmission(0x46);
  Wire.write(0x60 + i);
  Wire.endTransmission();

  Wire.requestFrom(0x46, 1);
  uint8_t x = Wire.read();
  return x;
}


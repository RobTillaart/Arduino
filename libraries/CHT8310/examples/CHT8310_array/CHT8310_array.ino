//
//    FILE: CHT8310_array.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: Demo for CHT8310 I2C humidity & temperature sensor
//     URL: https://github.com/RobTillaart/CHT8310

//  Always check datasheet - front view
//
//          +---------------+
//  VCC ----| VCC           |
//  SDA ----| SDA  CHT8310  |   CHECK DATASHEET.
//  GND ----| GND           |
//  SCL ----| SCL           |
//   ?  ----| AD0           |
//          |               |
//      ----|               |
//          +---------------+
//
//  check datasheet
//  VCC     RED
//  GND     BLACK
//  SDA     YELLOW
//  SCL     WHITE


#include "CHT8310.h"

//  all valid addresses
//  if not connected ==> fail
CHT8310 CHT[4] = { CHT8310(0x40), CHT8310(0x44), CHT8310(0x48), CHT8310(0x4C) };


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("CHT8310_LIB_VERSION: ");
  Serial.println(CHT8310_LIB_VERSION);
  Serial.println();

  Wire.begin();
  Wire.setClock(100000);

  for (int i = 0; i < 4; i++)
  {
    CHT[i].begin();
    delay(1000);
    Serial.print(CHT[i].getAddress());
    Serial.print("\t");
    Serial.print(CHT[i].isConnected());
    Serial.print("\t");
    Serial.println(CHT[i].getManufacturer());
  }
}


void loop()
{
  for (int i = 0; i < 4; i++)
  {
    Serial.print(millis());
    Serial.print("\t");
    Serial.print(CHT[i].getAddress());
    Serial.print("\t");

    if (CHT[i].isConnected() == false)
    {
      Serial.println("not connected.");
      continue;
    }
    else
    {
      CHT[i].read();
      Serial.print(CHT[i].getHumidity());
      Serial.print("\t");
      Serial.println(CHT[i].getTemperature());
    }
  }

  delay(2000);
}


//  -- END OF FILE --

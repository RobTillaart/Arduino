//
//    FILE: CHT8310_isConnected.ino
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

//  check all valid addresses 
//  if not connected ==> fail
CHT8310 CHT(0x40);    //  CHT8310_DEFAULT_ADDRESS = 0x40
CHT8310 CHT1(0x44);
CHT8310 CHT2(0x48);
CHT8310 CHT3(0x4C);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("CHT8310_LIB_VERSION: ");
  Serial.println(CHT8310_LIB_VERSION);
  Serial.println();

  Wire.begin();
  Wire.setClock(100000);
  CHT.begin();
  CHT1.begin();
  CHT2.begin();
  CHT3.begin();

  Serial.print("Connect:\t");
  Serial.println(CHT.isConnected());
  Serial.print("Address:\t");
  Serial.println(CHT.getAddress());
  Serial.print("Manufac:\t");
  Serial.println(CHT.getManufacturer());
  delay(1000);
  
  Serial.print("Connect:\t");
  Serial.println(CHT1.isConnected());
  Serial.print("Address:\t");
  Serial.println(CHT1.getAddress());
  Serial.print("Manufac:\t");
  Serial.println(CHT1.getManufacturer());
  delay(1000);
  
  Serial.print("Connect:\t");
  Serial.println(CHT2.isConnected());
  Serial.print("Address:\t");
  Serial.println(CHT2.getAddress());
  Serial.print("Manufac:\t");
  Serial.println(CHT2.getManufacturer());
  delay(1000);
  
  Serial.print("Connect:\t");
  Serial.println(CHT3.isConnected());
  Serial.print("Address:\t");
  Serial.println(CHT3.getAddress());
  Serial.print("Manufac:\t");
  Serial.println(CHT3.getManufacturer());
  delay(1000);
}


void loop()
{
  if (millis() - CHT.lastRead() >= 2000)
  {
    //  READ DATA
    CHT.read();

    Serial.print(millis());
    Serial.print('\t');
    Serial.print(CHT.getHumidity());
    Serial.print('\t');
    Serial.println(CHT.getTemperature());
  }
}


//  -- END OF FILE --

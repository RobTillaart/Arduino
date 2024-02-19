//
//    FILE: CHT8310_softwareReset.ino
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

CHT8310 CHT(0x40);   //  CHT8310_DEFAULT_ADDRESS = 0x40 TODO


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

  // set register to non default
  CHT.setConvertRate(7);
  Serial.println(CHT.getConvertRate());  // should print 7
  
  CHT.softwareReset();
  delay(1000);

  //  read back register
  int cr = CHT.getConvertRate();
  if (cr == 4)
  {
    Serial.print("Device reset success: \t");
    Serial.println(cr);  //  should print 4
  }
  else
  {
    Serial.print("Device reset failed: \t");
    Serial.println(cr);
  }
}


void loop()
{

}


//  -- END OF FILE --

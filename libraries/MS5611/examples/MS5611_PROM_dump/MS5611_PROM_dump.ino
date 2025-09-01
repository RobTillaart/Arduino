//
//    FILE: MS5611_PROM_dump.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: developer tool
//     URL: https://github.com/RobTillaart/MS5611


#include "MS5611.h"


//  BREAKOUT  MS5611  aka  GY63 - see datasheet
//
//  SPI    I2C
//              +--------+
//  VCC    VCC  | o      |
//  GND    GND  | o      |
//         SCL  | o      |
//  SDI    SDA  | o      |
//  CSO         | o      |
//  SDO         | o L    |   L = led
//          PS  | o    O |   O = opening  PS = protocol select
//              +--------+
//
//  PS to VCC  ==>  I2C  (GY-63 board has internal pull up, so not needed)
//  PS to GND  ==>  SPI  (not supported in library)
//  CS to VCC  ==>  0x76
//  CS to GND  ==>  0x77


MS5611 MS5611(0x77);


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("MS5611_LIB_VERSION: ");
  Serial.println(MS5611_LIB_VERSION);
  Serial.println();

  Wire.begin();
  if (MS5611.begin() == true)
  {
    Serial.print("MS5611 found: ");
    Serial.println(MS5611.getAddress());
  }
  else
  {
    Serial.println("MS5611 not found. halt.");
    while (1);
  }
  Serial.println();

  Serial.println("REG\tHEX\tDEC");

  for (int reg = 0; reg < 8; reg++)
  {
    uint16_t value = MS5611.getProm(reg);
    Serial.print(reg);
    Serial.print('\t');
    Serial.print(value, HEX);
    Serial.print('\t');
    Serial.println(value);
  }

  Serial.println("\ndone...");
}


void loop()
{

}


//  -- END OF FILE --

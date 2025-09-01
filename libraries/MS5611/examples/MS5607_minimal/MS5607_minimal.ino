//
//    FILE: MS5607_minimal.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo application
//     URL: https://github.com/RobTillaart/MS5611


#include "MS5611.h"


//  (TODO: check if 5607 has same breakout)
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


MS5607 MS5607(0x77);


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
  if (MS5607.begin() == true)
  {
    Serial.print("MS5607 found: ");
    Serial.println(MS5607.getAddress());
  }
  else
  {
    Serial.println("MS5607 not found. halt.");
    while (1);
  }
  Serial.println();
}


void loop()
{
  MS5607.read();           //  note no error checking => "optimistic".
  Serial.print("T:\t");
  Serial.print(MS5607.getTemperature(), 2);
  Serial.print("\tP:\t");
  Serial.print(MS5607.getPressure(), 2);
  Serial.println();
  delay(1000);
}


//  -- END OF FILE --

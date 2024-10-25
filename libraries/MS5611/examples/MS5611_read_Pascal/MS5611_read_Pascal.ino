//
//    FILE: MS5611_read_Pascal.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo application
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
//  PS to GND  ==>  SPI
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
    //  while (1);
  }
  Serial.println();
  Serial.println("Celsius\tmBar\tPascal");
}


void loop()
{
  MS5611.read();           //  note no error checking => "optimistic".
  Serial.print(MS5611.getTemperature(), 2);
  Serial.print('\t');
  Serial.print(MS5611.getPressure(), 2);
  Serial.print('\t');
  Serial.print(MS5611.getPressurePascal(), 2);
  Serial.println();
  delay(1000);
}


//  -- END OF FILE --

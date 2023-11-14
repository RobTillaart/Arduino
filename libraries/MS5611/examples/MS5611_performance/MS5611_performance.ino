//
//    FILE: MS5611_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo application
//    DATE: 2020-06-21
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


uint32_t start, stop, count;


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
  //  Wire.setClock(100000);
  if (MS5611.begin() == true)
  {
    Serial.println("MS5611 found.");
  }
  else
  {
    Serial.println("MS5611 not found. halt.");
    while (1);
  }
  Serial.println();

  count = 0;
}


void loop()
{
  delay(1000);

  start = micros();
  int result = MS5611.read();   //  uses default OSR_ULTRA_LOW  (fastest)
  stop = micros();

  if (count % 20 == 0)
  {
    Serial.println();
    Serial.println("CNT\tDUR\tRES\tTEMP\tPRES");
  }

  Serial.print(count);
  count++;
  Serial.print("\t");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.print(result);
  Serial.print("\t");
  Serial.print(MS5611.getTemperature(), 2);
  Serial.print("\t");
  Serial.print(MS5611.getPressure(), 2);
  Serial.println();
}


//  -- END OF FILE --

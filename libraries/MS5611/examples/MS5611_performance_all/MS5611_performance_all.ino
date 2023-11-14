//
//    FILE: MS5611_performance_all.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo application
//    DATE: 2021-12-24
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


uint32_t start, stop;


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
    Serial.println("MS5611 found.");
  }
  else
  {
    Serial.println("MS5611 not found. halt.");
    while (1);
  }
  Serial.println();

  Serial.println("OSR \t TIME");


  start = micros();
  MS5611.read();   // uses default OSR_ULTRA_LOW  (fastest)
  stop = micros();
  Serial.print( (uint8_t) MS5611.getOversampling());
  Serial.print("\t");
  Serial.println(stop - start);
  delay(10); // to flush serial.


  MS5611.setOversampling(OSR_LOW);
  start = micros();
  MS5611.read();
  stop = micros();
  Serial.print( (uint8_t) MS5611.getOversampling());
  Serial.print("\t");
  Serial.println(stop - start);
  delay(10); // to flush serial.


  MS5611.setOversampling(OSR_STANDARD);
  start = micros();
  MS5611.read();
  stop = micros();
  Serial.print( (uint8_t) MS5611.getOversampling());
  Serial.print("\t");
  Serial.println(stop - start);
  delay(10); // to flush serial.


  MS5611.setOversampling(OSR_HIGH);
  start = micros();
  MS5611.read();
  stop = micros();
  Serial.print( (uint8_t) MS5611.getOversampling());
  Serial.print("\t");
  Serial.println(stop - start);
  delay(10); // to flush serial.


  MS5611.setOversampling(OSR_ULTRA_HIGH);
  start = micros();
  MS5611.read();
  stop = micros();
  Serial.print( (uint8_t) MS5611.getOversampling());
  Serial.print("\t");
  Serial.println(stop - start);
  delay(10); // to flush serial.


  Serial.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --


//
//    FILE: MS5611_test_plotter.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo application
//    DATE: 2022-01-15
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
  Serial.begin(115200);
  while (!Serial);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("MS5611_LIB_VERSION: ");
  Serial.println(MS5611_LIB_VERSION);
  Serial.println();

  pinMode(LED_BUILTIN, OUTPUT);

  Wire.begin();
  if (MS5611.begin() == true)
  {
    Serial.println("MS5611 found.");
  }
  else
  {
    Serial.println("MS5611 not found. halt.");
    while (1)
    {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(1000);
      digitalWrite(LED_BUILTIN, LOW);
      delay(1000);
    }
  }
  Serial.println("TEMP\tPRESSURE");

  //  scale T & P to same range :)
  MS5611.setPressureOffset(-1000);
}

void loop()
{
  digitalWrite(LED_BUILTIN, HIGH);
  MS5611.read();
  Serial.print(MS5611.getTemperature(), 2);
  Serial.print("\t");
  Serial.print(MS5611.getPressure(), 2);
  Serial.println();
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}


//  -- END OF FILE --

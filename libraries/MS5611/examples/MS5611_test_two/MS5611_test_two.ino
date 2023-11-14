//
//    FILE: MS5611_test_two.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo application for two sensors
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


MS5611 ONE(0x76);   //  0x76 = CSB to VCC
MS5611 TWO(0x77);   //  0x77 = CSB to GND


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

  pinMode(LED_BUILTIN, OUTPUT);

  Wire.begin();
  if (ONE.begin() == true)
  {
    Serial.println("MS5611 0x76 found.");
  }
  else
  {
    Serial.println("MS5611 0x76 not found.");
  }

  if (TWO.begin() == true)
  {
    Serial.println("MS5611 0x77 found.");
  }
  else
  {
    Serial.println("MS5611 0x77 not found.");
  }

}


void loop()
{
  digitalWrite(LED_BUILTIN, HIGH);
  int result = ONE.read();
  stop = micros();
  if (result != MS5611_READ_OK)
  {
    Serial.print("0x76 Error in read: ");
    Serial.println(result);
  }

  result = TWO.read();
  stop = micros();
  if (result != MS5611_READ_OK)
  {
    Serial.print("0x77 Error in read: ");
    Serial.println(result);
  }
  digitalWrite(LED_BUILTIN, LOW);

  Serial.print("T: ");
  Serial.print(ONE.getTemperature(), 2);
  Serial.print("\tP: ");
  Serial.print(ONE.getPressure(), 2);
  Serial.print("\tT: ");
  Serial.print(TWO.getTemperature(), 2);
  Serial.print("\tP: ");
  Serial.print(TWO.getPressure(), 2);
  Serial.print("\tT: ");
  Serial.print(ONE.getTemperature() - TWO.getTemperature(), 2);
  Serial.print("\tP: ");
  Serial.print(ONE.getPressure() - TWO.getPressure(), 2);
  Serial.println();

  delay(1000);
}


//  -- END OF FILE --

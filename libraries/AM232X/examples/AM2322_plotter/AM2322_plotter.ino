//
//    FILE: AM2322_plotter.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo sketch for AM2322 I2C humidity & temperature sensor
//
// HISTORY:
// 0.1.0   2020-09-01 simple program to dump for plotter.
//
//  Bottom view 
//       +---+
//  VDD  |o  |
//  SDA  |o  |
//  GND  |o  |
//  SCL  |o  |
//       +---+
//
// do not forget pull up resistors between SDA, SCL and VDD.

#include <AM232X.h>

AM232X AM2322;

void setup()
{
  Wire.begin();

  Serial.begin(115200);
  Serial.println("Humidity(%),\tTemperature(C)");
}

void loop()
{
  AM2322.read();
  Serial.print(AM2322.getHumidity(), 1);
  Serial.print(",\t");
  Serial.println(AM2322.getTemperature(), 1);

  delay(100);
}

// -- END OF FILE --

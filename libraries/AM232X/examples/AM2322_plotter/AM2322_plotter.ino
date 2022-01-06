//
//    FILE: AM2322_plotter.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo sketch for AM2322 I2C humidity & temperature sensor
//
//  AM232X PIN layout             AM2315 COLOR
//  ============================================
//   bottom view  DESCRIPTION     COLOR
//       +---+
//       |o  |       VDD          RED
//       |o  |       SDA          YELLOW
//       |o  |       GND          BLACK
//       |o  |       SCL          GREY
//       +---+
//
// do not forget pull up resistors between SDA, SCL and VDD.


#include "AM232X.h"

AM232X AM2322;


void setup()
{
  Serial.begin(115200);

  if (! AM2322.begin() )
  {
    Serial.println("Sensor not found");
    while (1);
  }
  AM2322.wakeUp();
  delay(2000);

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

//
//    FILE: max31855_array.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo of array of thermocouples
//    DATE: 2020-08-26
//     URL: https://github.com/RobTillaart/MAX31855_RT
//
// kudos to FabioBrondo for the idea.


#include "MAX31855.h"


// note: pins are slightly different than other examples!
MAX31855 A(7, 6, 5);
MAX31855 B(8, 6, 5);
MAX31855 C(9, 6, 5);

MAX31855 sensors[] = 
{
  A, B, C
};


const uint8_t sensorCount = sizeof(sensors) / sizeof(MAX31855);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MAX31855_VERSION : ");
  Serial.println(MAX31855_VERSION);
  Serial.println();
  delay(250);

  SPI.begin();

  Serial.println(sensorCount);

  for (int i = 0; i < sensorCount; i++)
  {
    sensors[i].begin();
  }
}


void loop()
{
  Serial.print("\tTime:\t");
  Serial.println(millis());

  for (int i = 0; i < sensorCount; i++)
  {
    int status = sensors[i].read();
    if (status != STATUS_OK)
    {
      Serial.print(i);
      Serial.print("\tstatus:\t");
      Serial.println(status);
    }
    else
    {
      float temp = sensors[i].getTemperature();
      Serial.print(i);
      Serial.print("\ttemp:\t");
      Serial.println(temp);
    }
  }
  Serial.println();

  delay(1000);
}


//  -- END OF FILE --


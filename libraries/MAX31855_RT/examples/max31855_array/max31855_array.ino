//
//    FILE: max31855_array.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.1
// PURPOSE: demo of array of thermocouples
//    DATE: 2020-08-26
//     URL: https://github.com/RobTillaart/MAX31855_RT
//
// kudos to FabioBrondo for the idea.
//

#include "MAX31855.h"

// note: pins are slightly different than other examples!
const int dataPin  = 7;
const int clockPin = 6;


MAX31855 A, B, C;

MAX31855 sensors[] = 
{
  A, B, C
};


const uint8_t sensorCount = sizeof(sensors) / sizeof(MAX31855);


void setup()
{
  Serial.begin(115200);
  Serial.print("Start max31855_array.ino : ");
  Serial.println(MAX31855_VERSION);
  Serial.println();

  Serial.println(sensorCount);

  for (int i = 0; i < sensorCount; i++)
  {
    sensors[i].begin(clockPin, 3 + i, dataPin);  //  three different select pins.
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


// -- END OF FILE --


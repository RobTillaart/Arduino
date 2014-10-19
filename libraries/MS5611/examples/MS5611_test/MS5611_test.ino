//
//    FILE: MS5611.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.02
// PURPOSE: demo application
//    DATE: 2014-okt-16
//     URL:
//
// Released to the public domain
//

#include "MS5611.h"
#include <Wire.h>

MS5611 MS5611(0x77);

void setup()
{
    Wire.begin();

    Serial.begin(115200);
    Serial.print("MS5611 test version: ");
    Serial.println(MS5611_LIB_VERSION);

    MS5611.init();
}

void loop()
{
    int result = MS5611.read();
    if (result != 0)
    {
        Serial.print("Error in read: ");
        Serial.println(result);
    }
    else
    {
        Serial.println("T:\t");
        Serial.println(MS5611.getTemperature() * 0.01, 2);  // print as float
        Serial.println("P:\t");
        Serial.println(MS5611.getPressure() * 0.01, 2);   // print as float
    }

    delay(5000);
}
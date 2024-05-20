//
//    FILE: DS3232_demo_getTemperature.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic getTemperature function
//     URL: https://github.com/RobTillaart/DS3232


#include "DS3232.h"


DS3232 rtc;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("DS3232_LIB_VERSION: ");
  Serial.println(DS3232_LIB_VERSION);
  Serial.println();

  Wire.begin();
  if (rtc.begin() != DS3232_OK)
  {
    Serial.println("could not connect, check wires etc");
    while (1);
  }
}


void loop()
{
  rtc.read();

  Serial.print(rtc.hours());
  Serial.print(':');
  Serial.print(rtc.minutes());
  Serial.print(':');
  Serial.print(rtc.seconds());
  Serial.print('\t');
  Serial.print(rtc.getTemperature());
  Serial.print('\n');

  delay(2000);
}


//  --  END OF FILE  --

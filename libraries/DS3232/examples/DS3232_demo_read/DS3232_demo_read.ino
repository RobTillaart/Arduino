//
//    FILE: DS3232_demo_read.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic read function
//     URL: https://github.com/RobTillaart/DS3232


#include "DS3232.h"


DS3232 rtc;


void setup()
{
  while(!Serial);
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

  Serial.print(rtc.lastRead());
  Serial.print("\t");
  if (rtc.year() < 10) Serial.print(0);
  Serial.print(rtc.year());

  Serial.print('-');
  if (rtc.month() < 10) Serial.print(0);
  Serial.print(rtc.month());

  Serial.print('-');
  if (rtc.day() < 10) Serial.print(0);
  Serial.print(rtc.day());

  Serial.print(' ');
  if (rtc.hours() < 10) Serial.print(0);
  Serial.print(rtc.hours());

  Serial.print(':');
  if (rtc.minutes() < 10) Serial.print(0);
  Serial.print(rtc.minutes());

  Serial.print(':');
  if (rtc.seconds() < 10) Serial.print(0);
  Serial.print(rtc.seconds());
  Serial.print("\t");

  Serial.print(rtc.weekDay());
  Serial.print('\n');

  delay(2000);
}


//  --  END OF FILE  --

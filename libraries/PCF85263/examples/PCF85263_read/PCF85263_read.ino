//
//    FILE: PCF85263_read.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: read date time from RTC
//     URL: https://github.com/RobTillaart/PCF85263


#include "PCF85263.h"


PCF85263 rtc;


void setup()
{
  while (!Serial);
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("PCF85263_LIB_VERSION: ");
  Serial.println(PCF85263_LIB_VERSION);
  Serial.println();

  Wire.begin();
  if (rtc.begin() != PCF85263_OK)
  {
    Serial.println("could not connect, check wires etc");
    while (1);
  }

  rtc.setRTCmode(0);

}


void loop()
{
  rtc.readDateTime();

  Serial.print(rtc.lastRead());
  Serial.print("\t\t");
  Serial.print(rtc.year());
  Serial.print('-');
  Serial.print(rtc.month());
  Serial.print('-');
  Serial.print(rtc.day());
  Serial.print(' ');
  Serial.print(rtc.hours());
  Serial.print(':');
  Serial.print(rtc.minutes());
  Serial.print(':');
  Serial.print(rtc.seconds());
  Serial.print('\n');
  Serial.print(rtc.weekDay());
  Serial.print('\n');

  delay(2000);
}


//  -- END OF FILE --

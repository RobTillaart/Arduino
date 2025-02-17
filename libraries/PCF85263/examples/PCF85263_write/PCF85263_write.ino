//
//    FILE: PCF85263_write.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: write a new date time to RTC
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

  //  adjust to your date-time.
  rtc.setSeconds(00);
  rtc.setMinutes(59);
  rtc.setHours(12);
  rtc.setWeekDay(4);   //  4 = Thursday
  rtc.setDay(5);
  rtc.setMonth(12);
  rtc.setYear(24);
  rtc.writeDateTime();


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
}


void loop()
{
}


//  -- END OF FILE --

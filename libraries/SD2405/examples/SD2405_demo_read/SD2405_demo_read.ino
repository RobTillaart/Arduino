//
//    FILE: SD2405_demo_read.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic read function
//     URL: https://github.com/RobTillaart/SD2405


#include "SD2405.h"


SD2405 rtc;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("SD2405_LIB_VERSION: ");
  Serial.println(SD2405_LIB_VERSION);
  Serial.println();

  Wire.begin();
  if (rtc.begin() != SD2405_OK)
  {
    Serial.println("could not connect, check wires etc");
    while (1);
  }

  //  comment
  //  rtc.setSeconds(00);
  //  rtc.setMinutes(07);
  //  rtc.setHours(21);
  //  rtc.setWeekDay(5);   //  4 = Thursday
  //  rtc.setDay(3);
  //  rtc.setMonth(1);
  //  rtc.setYear(25);
  //
  //  rtc.enableWriteRTC();
  //  int rv = rtc.write();
  //  Serial.println(rv);
}


void loop()
{
  int rv = rtc.read();

  Serial.print(rv);
  Serial.print("\t");
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
  Serial.print(' ');
  Serial.print(rtc.weekDay());
  Serial.print('\n');

  delay(1000);
}


//  --  END OF FILE  --
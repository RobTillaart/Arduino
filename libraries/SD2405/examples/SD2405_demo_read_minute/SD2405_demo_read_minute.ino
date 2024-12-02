//
//    FILE: SD2405_demo_read_minute.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test read once per minute trick
//     URL: https://github.com/RobTillaart/SD2405
//
//  The trick in this sketch is meant to minimize the read() calls
//  to minimize I2C.
//  Might be included in the library in the future.


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

  rtc.read();
}


void loop()
{
  //  only read once per minute to save I2C traffic.
  uint32_t seconds = (millis() - rtc.lastRead()) / 1000;
  if (rtc.seconds() + seconds > 59)
  {
    Serial.println("r");
    rtc.read();
    seconds = 0;
  }

  Serial.print(rtc.lastRead());
  Serial.print("\t\t");

  //  DATE
  Serial.print(rtc.year());
  Serial.print('-');
  if (rtc.month() < 10) Serial.print(0);
  Serial.print(rtc.month());
  Serial.print('-');
  if (rtc.day() < 10) Serial.print(0);
  Serial.print(rtc.day());

  Serial.print(' ');
  //  TIME
  if (rtc.hours() < 10) Serial.print(0);
  Serial.print(rtc.hours());
  Serial.print(':');
  if (rtc.minutes() < 10) Serial.print(0);
  Serial.print(rtc.minutes());
  Serial.print(':');
  if (rtc.seconds() + seconds < 10) Serial.print(0);
  Serial.print(rtc.seconds() + seconds);
  Serial.print('\n');

  delay(1000);
}


//  --  END OF FILE  --
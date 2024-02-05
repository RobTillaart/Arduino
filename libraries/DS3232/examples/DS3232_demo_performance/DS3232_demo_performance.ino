//
//    FILE: DS3232_demo_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic read function
//     URL: https://github.com/RobTillaart/DS3232


#include "DS3232.h"


DS3232 rtc;

uint32_t start, stop;


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

  //  up to 400K is official supported.
  for (uint32_t sp = 50000; sp <= 400000; sp += 50000)
  {
    performance(sp);
  }
  Serial.print('\n');

}


void loop()
{
  rtc.read();

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
  if (rtc.seconds() < 10) Serial.print(0);
  Serial.print(rtc.seconds());
  Serial.print('\n');

  delay(2000);
}


void performance(uint32_t speed)
{
  Wire.setClock(speed);
  delay(100);
  uint32_t start = millis();
  for (int i = 0; i < 1000; i++)
  {
    rtc.read();
  }
  uint32_t stop = millis();
  Serial.print(speed);
  Serial.print("\t");
  Serial.println(stop - start);
}


//  --  END OF FILE  --

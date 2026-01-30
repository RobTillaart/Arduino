//
//    FILE: DS3232_demo_performance_fast.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test read(fast = true)
//     URL: https://github.com/RobTillaart/DS3232


#include "DS3232.h"


DS3232 rtc;

uint32_t start, stop;


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

  Serial.print("FAST: false: ");
  duration(false);
  Serial.print("FAST: true:  ");
  duration(true);
  
  Serial.println('\n');
}


void loop()
{
  rtc.read(true);

  Serial.print(rtc.lastRead());
  Serial.print("\t\t");

  //  DATE
  if (rtc.year() < 10) Serial.print(0);
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


void duration(bool fast)
{
  delay(100);
  uint32_t start = millis();
  for (int i = 0; i < 1000; i++)
  {
    rtc.read(fast);
  }
  uint32_t stop = millis();
  Serial.println(stop - start);
}


//  --  END OF FILE  --

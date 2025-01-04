//
//    FILE: SD2405_demo_write.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic write function
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
    // while (1);
  }

  //  parse compiler __DATE__ and __TIME__ ?

  //  adjust to your needs.
  rtc.setSeconds(00);
  rtc.setMinutes(25);
  rtc.setHours(20);
  rtc.setWeekDay(5);   //  4 = Thursday
  rtc.setDay(3);
  rtc.setMonth(01);
  rtc.setYear(25);

  rtc.enableWriteRTC();
  rtc.write();
}


void loop()
{
  rtc.read();

  Serial.print(rtc.lastRead());
  Serial.print("\t");
  printDate(Serial);
  Serial.print(" ");
  printTime(Serial);
  Serial.println();

  delay(2000);
}


void printDate(Stream &str)
{
  char buffer[16];
  sprintf(buffer, "%04d-%02d-%02d",
          2000 + rtc.year(), rtc.month(), rtc.day());
  str.print(buffer);
}


void printTime(Stream &str)
{
  char buffer[16];
  sprintf(buffer, "%02d:%02d:%02d",
          rtc.hours(), rtc.minutes(), rtc.seconds());
  str.print(buffer);
}


//  --  END OF FILE  --
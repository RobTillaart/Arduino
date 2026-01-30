//
//    FILE: DS3232_test_setSeconds.ino
//  AUTHOR: axtar
// PURPOSE: test setSeconds function
//     URL: https://github.com/RobTillaart/DS3232


#include <Arduino.h>
#include <DS3232.h>

DS3232 rtc;

void printTime(Stream &str)
{
  char buffer[16];
  sprintf(buffer, "%02d:%02d:%02d",
          rtc.hours(), rtc.minutes(), rtc.seconds());
  str.print(buffer);
}

void setup()
{
  Serial.begin(115200);
  Serial.println();

  Wire.begin();
  if (rtc.begin() != DS3232_OK)
  {
    Serial.println("could not connect, check wires etc");
    while (true)
      ;
  }

  for (uint8_t i = 0; i < 60; i++)
  {
    //  set time
    rtc.setSeconds(i);
    rtc.setMinutes(59);
    rtc.setHours(12);
    rtc.setWeekDay(6);  //  6 = Saturday
    rtc.setDay(31);
    rtc.setMonth(05);
    rtc.setYear(25);
    rtc.write();

    // read back
    rtc.read();
    Serial.print(String(i) + ": ");
    printTime(Serial);
    Serial.println();
  }
}

void loop()
{
}


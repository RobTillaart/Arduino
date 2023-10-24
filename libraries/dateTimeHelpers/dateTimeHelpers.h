#pragma once
//
//    FILE: datetimeHelpers.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.3
// PURPOSE: Arduino library with date time helper functions.
//    DATE: 2020-07-01
//     URL: https://github.com/RobTillaart/dateTimeHelpers


#include "Arduino.h"


#define DATETIMEHELPER_LIB_VERSION      (F("0.1.3"))

#define SECONDS_MINUTE                  60UL
#define SECONDS_HOUR                    3600UL
#define SECONDS_DAY                     86400UL
#define SECONDS_WEEK                    604800UL


//  shared internal buffer.
//  increase size to 20 or 24 if needed.
static char __dateTimeHelperBuffer[16];


///////////////////////////////////////////////////////////////////////////
//
//  DISPLAY seconds as a date time string.
//
void secondsSplit( uint32_t seconds, uint16_t * days, uint8_t * hours, uint8_t * minutes, uint8_t * sec)
{
  //  strips the days max 65535 days ~179yrs
  *days    = seconds / SECONDS_DAY;
  seconds -= (*days * SECONDS_DAY);
  *hours   = seconds / SECONDS_HOUR;
  seconds -= (*hours * SECONDS_HOUR);
  *minutes = seconds / SECONDS_MINUTE;
  seconds -= (*minutes * SECONDS_MINUTE);
  *sec     = seconds;
}


//  (true)  days 00:00:00 .. 23:59:59
//  (false) days 00:00 ..    23:59
char * seconds2duration(uint32_t seconds, bool displaySeconds = false)
{
  char * buf = __dateTimeHelperBuffer;

  uint16_t days;
  uint8_t hours, minutes, sec;
  secondsSplit(seconds, &days, &hours, &minutes, &sec);

  uint8_t pos = 0;
  itoa(days, buf, 10);
  pos = strlen(buf);
  buf[pos++]  = ' ';

  uint8_t t = hours / 10;
  buf[pos++] = t + '0';
  buf[pos++] = hours - (t * 10) + '0';
  buf[pos++]  = ':';

  t = minutes / 10;
  buf[pos++] = t + '0';
  buf[pos++] = minutes - (t * 10) + '0';
  if (displaySeconds)
  {
    buf[pos++]  = ':';
    t = sec / 10;
    buf[pos++] = t + '0';
    buf[pos++] = sec - (t * 10) + '0';
  }
  buf[pos]  = '\0';

  return buf;
}


//  (true)   00:00:00 .. 23:59:59
//  (false)  00:00 ..    23:59
char * seconds2clock24(uint32_t seconds, bool displaySeconds = false)
{
  char * buf = __dateTimeHelperBuffer;
  uint8_t pos = 0;

  uint16_t days;
  uint8_t hours, minutes, sec;
  secondsSplit(seconds, &days, &hours, &minutes, &sec);

  uint8_t t = hours / 10;
  buf[pos++] = t + '0';
  buf[pos++] = hours - (t * 10) + '0';
  buf[pos++]  = ':';

  t = minutes / 10;
  buf[pos++] = t + '0';
  buf[pos++] = minutes - (t * 10) + '0';
  if (displaySeconds)
  {
    buf[pos++]  = ':';
    t = sec / 10;
    buf[pos++] = t + '0';
    buf[pos++] = sec - (t * 10) + '0';
  }
  buf[pos]  = '\0';

  return buf;
}


//  for completeness shows no AM/PM or 13-23.
char * seconds2clock12(uint32_t seconds, bool displaySeconds = false)
{
  char * buf = __dateTimeHelperBuffer;
  uint8_t pos = 0;

  uint16_t days;
  uint8_t hours, minutes, sec;
  secondsSplit(seconds, &days, &hours, &minutes, &sec);

  if (hours > 12) hours -= 12;
  uint8_t t = hours / 10;
  buf[pos++] = t + '0';
  buf[pos++] = hours - (t * 10) + '0';
  buf[pos++]  = ':';

  t = minutes / 10;
  buf[pos++] = t + '0';
  buf[pos++] = minutes - (t * 10) + '0';
  if (displaySeconds)
  {
    buf[pos++]  = ':';
    t = sec / 10;
    buf[pos++] = t + '0';
    buf[pos++] = sec - (t * 10) + '0';
  }
  buf[pos]  = '\0';

  return buf;
}


//  (true)   00:00:00 .. 12:59:59 AM/PM
//  (false)  00:00 ..    12:59 AM/PM
char * seconds2clockAMPM(uint32_t seconds, bool displaySeconds = false)
{
  bool PMflag = false;
  char * buf = __dateTimeHelperBuffer;
  uint8_t pos = 0;

  uint16_t days;
  uint8_t hours, minutes, sec;
  secondsSplit(seconds, &days, &hours, &minutes, &sec);

  if (hours >= 12)
  {
    PMflag = true;
    if (hours > 12) hours -= 12;
  }
  uint8_t t = hours / 10;
  buf[pos++] = t + '0';
  buf[pos++] = hours - (t * 10) + '0';
  buf[pos++]  = ':';

  t = minutes / 10;
  buf[pos++] = t + '0';
  buf[pos++] = minutes - (t * 10) + '0';
  if (displaySeconds)
  {
    buf[pos++]  = ':';
    t = sec / 10;
    buf[pos++] = t + '0';
    buf[pos++] = sec - (t * 10) + '0';
  }

  buf[pos++] = ' ';
  if (PMflag == true) buf[pos++] = 'P';
  else buf[pos++] = 'A';
  buf[pos++] = 'M';
  buf[pos]  = '\0';

  return buf;
}


char * millis2duration(uint32_t millis)
{
  char * buf = __dateTimeHelperBuffer;

  uint32_t t = millis / 1000;
  seconds2duration(t, true);
  uint8_t pos = strlen(buf);

  uint16_t m = millis - t * 1000;
  buf[pos++]  = '.';
  uint8_t d = m / 100;
  buf[pos++] = d + '0';
  m = m - d * 100;
  d = m / 10;
  buf[pos++] = d + '0';
  d = m - d * 10;
  buf[pos++] = d + '0';
  buf[pos++]  = '\0';

  return buf;
}


char * millis2clock(uint32_t millis)
{
  char * buf = __dateTimeHelperBuffer;

  uint32_t t = millis / 1000;
  seconds2clock24(t, true);
  uint8_t pos = strlen(buf);

  uint16_t m = millis - t * 1000;
  buf[pos++]  = '.';
  uint8_t d = m / 100;
  buf[pos++] = d + '0';
  m = m - d * 100;
  d = m / 10;
  buf[pos++] = d + '0';
  d = m - d * 10;
  buf[pos++] = d + '0';
  buf[pos++]  = '\0';

  return buf;
}


///////////////////////////////////////////////////////////////////////////
//
//  CONVERTORS
//
float seconds2weeks(uint32_t seconds)
{
  return seconds * 1.653439153439e-6;  //  /604800
}

float seconds2days(uint32_t seconds)
{
  return seconds * 1.157407407407e-5;  //  /86400
}

float seconds2hours(uint32_t seconds)
{
  return seconds * 2.777777777778e-4;  //  /3600
}

float seconds2minutes(uint32_t seconds)
{
  return seconds * 1.666666666667e-2;  //  /60
}


//  -- END OF FILE --

//
//    FILE: GUID_diff.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test difference two consecutive GUID's
//     URL: https://github.com/RobTillaart/UUID
//
//  minimum same chars is 4 or 5 depending on mode by design.
//  Think the '-' chars and the '4' in byte 7.


#include "Arduino.h"
#include "UUID.h"


GUID guid;

char buf[2][37];

void setup()
{
  Serial.begin(115200);
  while (!Serial);

  Serial.println();
  Serial.println(__FILE__);
  Serial.print("UUID_LIB_VERSION: ");
  Serial.println(UUID_LIB_VERSION);
  Serial.println();
  delay(100);

  strcpy(buf[0], guid.toCharArray());
}


void loop()
{
  guid.generate();
  strcpy(buf[1], guid.toCharArray());
  int count = 0;
  Serial.println();
  Serial.println(buf[0]);
  Serial.println(buf[1]);
  for (int i = 0; i < 36; i++)
  {
    if (buf[0][i] != buf[1][i]) Serial.print('-');
    else
    {
      Serial.print('^');
      count++;
    }
  }
  Serial.print("\t");
  Serial.println(count);

  strcpy(buf[0], buf[1]);
}


//  -- END OF FILE --

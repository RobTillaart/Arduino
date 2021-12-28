//
//    FILE: randomFromSet.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo random playlist with set
//    DATE: 2021-05-04
//     URL: https://github.com/RobTillaart/SET
//          https://github.com/RobTillaart/Prandom/issues/3


#include "set.h"


Set playList;

int SONGS = 15;

uint32_t start, stop ;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
}


void loop()
{
  start = micros();
  for (int i = 0; i < SONGS; i++)
  {
    int s = getRandomSong();
    Serial.print(i);
    Serial.print('\t');
    Serial.println(s);
  }
  stop = micros();
  Serial.print("TIME: ");
  Serial.println(stop - start);
  delay(1000);
}


int getRandomSong()
{
  if (playList.isEmpty())
  {
    Serial.println("FILL THE ARRAY");
    for (int i = 0; i < SONGS; i++)
    {
      playList.add(i);
    }
  }
  int rv = random(SONGS);
  if (playList.has(rv) == false)
  {
    for (int i = rv; i < rv + SONGS; i++)
    {
      int idx = i % SONGS;
      if (playList.has(idx))
      {
        rv = idx;
        break;
      }
    }
  }
  playList.sub(rv);
  return rv;
}


// -- END OF FILE --


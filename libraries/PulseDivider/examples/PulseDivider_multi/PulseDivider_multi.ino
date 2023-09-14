//
//    FILE: PulseDivider_multi.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: Test multi pulse dividers parallel
//    DATE: 2023-09-13
//     URL: https://github.com/RobTillaart/PulseDivider


#include "PulseDivider.h"


PulseDivider PDiv1(6, 7, 17, 5);
PulseDivider PDiv2(8, 9, 10, 3);
PulseDivider PDiv3(10, 11, 7, 2);

uint32_t last2 = 0;
uint32_t last3 = 0;

void setup()
{
  Serial.begin(115200);

  Serial.print("PULSEDIVIDER_LIB_VERSION: ");
  Serial.println(PULSEDIVIDER_LIB_VERSION);

  PDiv1.start();
  PDiv2.start();
  PDiv3.start();
}

//  check every input equally often
//void loop()
//{
//  //  more software dividers imply a lower maximum frequency.
//  //  or more time to do a million checks.
//
//  PDiv1.check();  //  as often as possible
//  PDiv2.check();  //  as often as possible
//  PDiv3.check();  //  as often as possible
//}


//  alternative with an optimized scheduling scheme.
//  assume input 1 has a higher frequency than
//         input 2 and input 3
void loop()
{
  uint32_t now = micros();
  PDiv1.check();  //  as often as possible

  //  frequency of line 2 is less than 1 KHz
  if (now - last2 >= 1000)
  {
    last2 = now;
    PDiv2.check();
  }

  //  frequency of line 3 is less than 300 Hz
  if (now - last3 >= 3000)
  {
    last3 = now;
    PDiv3.check();
  }
}


//  -- END OF FILE --

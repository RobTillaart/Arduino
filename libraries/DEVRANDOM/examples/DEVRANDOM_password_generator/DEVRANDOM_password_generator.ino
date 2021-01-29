//
//    FILE: DEVRANDOM_password_generator.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo
//    DATE: 2020-06-25
//    (c) : MIT
//

// To use this as a real password generator one needs a use
// a hardware random noise generator to have some level of quality
// this example is merely a proof of concept.


#include "DEVRANDOM.h"


#define PASSWORD_SIZE 8


char pw[PASSWORD_SIZE + 1];

DEVRANDOM dr;

char c1[] = "QWERTYUIOPLMKJNBHGVCFDXSZA";
char c2[] = "zaqwertyuioplmnbvcxsdfghjk";
char c3[] = "1598746230";
char c4[] = "!@#$%^&*()_+-={}|[]\\:;<>?,./";

int mx = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println();

  // dr.useDR(5);
  // dr.useAR(A0);
  dr.useSW();  // for proof of concept this is OK
}

void loop()
{
  Serial.print('\t');

  uint32_t start = micros();
  int cnt = generatePassword();
  uint32_t stop = micros();
  mx = max(cnt, mx);

  Serial.print('\t');
  Serial.print(stop - start);
  Serial.print('\t');
  Serial.print(cnt);
  Serial.print('\t');
  Serial.print(mx);
  Serial.println();
  delay(5);
}

int generatePassword()
{
  int idx = 0;
  bool b[4] = { false, false, false, false };
  bool done = false;
  int count = 0;

  while (! done)
  {
    count++;
    idx = 0;
    b[0] = b[1] = b[2] = b[3] = false;

    while (idx < PASSWORD_SIZE)
    {
      uint8_t x = dr.read() % 4;
      switch (x)
      {
        case 0 :
          pw[idx++] = c1[dr.read() % 26];
          break;
        case 1 :
          pw[idx++] = c2[dr.read() % 26];
          break;
        case 2 :
          pw[idx++] = c3[dr.read() % 10];
          break;
        case 3 :
          pw[idx++] = c4[dr.read() % 28];
          break;
      }
      b[x] = true;
    }
    done = b[0] && b[1] && b[2] && b[3];
    pw[idx] = 0;
  }
  Serial.print(pw);
  return count;
}

// -- END OF FILE --
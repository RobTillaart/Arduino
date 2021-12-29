//
//    FILE: seconds.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/timing


#include "timing.h"


#if defined(ESP32)
#define MAXPRIMES  800
const uint32_t mx = 1000000;
#else
#define MAXPRIMES  800
const uint32_t mx = 15000;
#endif


uint16_t primes[MAXPRIMES];
uint16_t idx = 0;
uint32_t x   = 1;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println("UNO    (16Mhz) takes ~ 30 seconds...");
  Serial.println("ESP32 (240MHz) takes ~ 10 seconds...");

  delay(10);
  seconds sec;     // starts at zero
  while (x < mx)
  {
    nextPrime();
  }
  Serial.print("Seconds:\t");
  Serial.println(sec.now());

  delay(10);
  x = 1;
  sec.set();     // starts at zero
  while (x < mx)
  {
    nextPrime();
  }
  Serial.print("Seconds:\t");
  Serial.println(sec.now());

  Serial.println("\nDone...");
}


void loop()
{
}


// sort of sieve.
int nextPrime()
{
  bool prime = true;
  do
  {
    prime = true;
    x++;
    for (uint16_t i = 0; i < idx; i++)
    {
      if ( (x % primes[i]) == 0)
      {
        prime = false;
        break;
      }
    }
  } while (!prime);
  if (idx < MAXPRIMES) primes[idx++] = x;

  return x;
}


// -- END OF FILE --


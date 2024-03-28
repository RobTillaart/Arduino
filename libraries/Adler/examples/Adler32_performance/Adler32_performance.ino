//
//    FILE: Adler32_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/Adler


#include "Arduino.h"
#include "Adler32.h"


Adler32 ad;

volatile uint8_t z;
uint32_t start, stop, randomtime;

char lorem[] = "Lorem ipsum dolor sit amet, \
consectetuer adipiscing elit. Aenean commodo ligula eget dolor. \
Aenean massa. Cum sociis natoque penatibus et magnis dis parturient \
montes, nascetur ridiculus mus. Donec quam felis, ultricies nec, \
pellentesque eu, pretium quis, sem. Nulla consequat massa quis enim. \
Donec pede justo, fringilla vel, aliquet nec, vulputate eget, arcu. \
In enim justo, rhoncus ut, imperdiet a, venenatis vitae, justo. \
Nullam dictum felis eu pede mollis pretium. Integer tincidunt. \
Cras dapibus. Vivamus elementum semper nisi. \
Aenean vulputate eleifend tellus. Aenean leo ligula, porttitor eu, \
consequat vitae, eleifend ac, enim. Aliquam lorem ante, dapibus in, \
viverra quis, feugiat a, tellus. Phasellus viverra nulla ut metus \
varius laoreet. Quisque rutrum. Aenean imperdiet. Etiam ultricies \
nisi vel augue. Curabitur ullamcorper ultricies nisi. Nam eget dui.";


char hello[] = "hello world";


void setup()
{
  Serial.begin(115200);
  while (!Serial);

  Serial.println();
  Serial.println("Adler32_performance");
  Serial.print("ADLER32_LIB_VERSION: ");
  Serial.println(ADLER32_LIB_VERSION);

  start = micros();
  for (uint16_t x = 0; x < 10000; x++)
  {
    z = random(255);
  }
  stop = micros();
  randomtime = stop - start;
  Serial.print("randomtime: ");
  Serial.println(randomtime);
  delay(100);

  ad.begin();
  start = micros();
  for (uint16_t x = 0; x < 10000; x++)
  {
    z = random(255);
    ad.add(z);
  }
  stop = micros();
  Serial.print("     total: ");
  Serial.println(stop - start);
  Serial.print(" 1e4 x add: ");
  Serial.println(stop - start - randomtime);
  delay(100);

  Serial.print("  checksum: ");
  Serial.println(ad.getAdler());
  Serial.println();
  delay(100);

  ad.begin();
  start = micros();
  for (uint32_t x = 0; x < 1000000; x++)
  {
    z = x & 0xFF;
    ad.add(z);
  }
  stop = micros();
  Serial.print("     total: ");
  Serial.println(stop - start);
  Serial.print(" 1e6 x add: ");
  Serial.println(stop - start - randomtime);
  delay(100);
  Serial.print("  checksum: ");
  Serial.println(ad.getAdler());
  Serial.println();
  delay(100);

  /////////////////////////////////////////////////////////////////

  ad.begin();
  Serial.print("LENGTH LOREM: ");
  Serial.println(strlen(lorem));
  Serial.println();
  delay(100);
  start = micros();
  for (int i = 0; lorem[i] != 0; i++)
  {
    ad.add(lorem[i]);
  }
  stop = micros();
  Serial.print("   lorem 1: ");
  Serial.print(stop - start);
  Serial.print("\tchecksum: ");
  Serial.println(ad.getAdler());
  delay(100);

  ad.begin();
  start = micros();
  ad.add(lorem, strlen(lorem));
  stop = micros();
  Serial.print("   lorem 2: ");
  Serial.print(stop - start);
  Serial.print("\tchecksum: ");
  Serial.println(ad.getAdler());
  delay(100);

  ad.begin();
  start = micros();
  ad.addFast(lorem, strlen(lorem));
  stop = micros();
  Serial.print("   lorem 3: ");
  Serial.print(stop - start);
  Serial.print("\tchecksum: ");
  Serial.println(ad.getAdler());
  Serial.println();
  delay(100);

  /////////////////////////////////////////////////////////////////

  ad.begin();
  Serial.print("LENGTH HELLO: ");
  Serial.println(strlen(hello));
  Serial.println();
  delay(100);
  start = micros();
  for (int i = 0; hello[i] != 0; i++)
  {
    ad.add(hello[i]);
  }
  stop = micros();
  Serial.print("   hello 1: ");
  Serial.print(stop - start);
  Serial.print("\tchecksum: ");
  Serial.println(ad.getAdler());
  delay(100);

  ad.begin();
  start = micros();
  ad.add(hello, strlen(hello));
  stop = micros();
  Serial.print("   hello 2: ");
  Serial.print(stop - start);
  Serial.print("\tchecksum: ");
  Serial.println(ad.getAdler());
  delay(100);

  ad.begin();
  start = micros();
  ad.addFast(hello, strlen(hello));
  stop = micros();
  Serial.print("   hello 3: ");
  Serial.print(stop - start);
  Serial.print("\tchecksum: ");
  Serial.println(ad.getAdler());
  Serial.println();

}


void loop()
{
}


//  -- END OF FILE --

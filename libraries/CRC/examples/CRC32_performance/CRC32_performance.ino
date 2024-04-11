//
//    FILE: CRC32_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/CRC


#include "CRC32.h"
#include "FastCRC32.h"

char str[] = "Lorem ipsum dolor sit amet, \
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

uint32_t start, stop;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  test();
}


void loop()
{
}


void test()
{
  crc_size_t length = strlen(str);

  CRC32 crc;
  start = micros();
  crc.add((uint8_t*)str, length);
  stop = micros();
  Serial.print("DATA: \t");
  Serial.println(length);
  Serial.print(" CRC:\t");
  Serial.println(crc.calc(), HEX);
  Serial.print("TIME: \t");
  Serial.println(stop - start);
  Serial.println();
  delay(100);

  CRC32 nonReversedCrc(CRC32_POLYNOME, CRC32_INITIAL, CRC32_XOR_OUT, false, false);
  start = micros();
  nonReversedCrc.add((uint8_t*)str, length);
  stop = micros();
  Serial.print("DATA: \t");
  Serial.println(length);
  Serial.print(" CRC:\t");
  Serial.println(nonReversedCrc.calc(), HEX);
  Serial.print("TIME: \t");
  Serial.println(stop - start);
  Serial.println();
  delay(100);

  FastCRC32 FCRC32;
  start = micros();
  FCRC32.add((uint8_t*)str, length);
  stop = micros();
  Serial.print("DATA: \t");
  Serial.println(length);
  Serial.print("FCRC:\t");
  Serial.println(FCRC32.calc(), HEX);
  Serial.print("TIME: \t");
  Serial.println(stop - start);
  Serial.println();
  delay(100);
}


// -- END OF FILE --

//
//    FILE: CRC32_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2022-01-28
//    (c) : MIT


#include "CRC32.h"

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

CRC32 crc;

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
  uint16_t length = strlen(str);

  crc.reset();
  crc.setPolynome(0x04C11DB7);
  start = micros();
  crc.add((uint8_t*)str, length);
  stop = micros();
  Serial.print("DATA: \t");
  Serial.println(length);
  Serial.print(" CRC:\t");
  Serial.println(crc.getCRC(), HEX);
  Serial.print("TIME: \t");
  Serial.println(stop - start);
  Serial.println();
  delay(100);

  crc.reset();
  crc.setPolynome(0x04C11DB7);
  crc.setReverseIn(true);
  start = micros();
  crc.add((uint8_t*)str, length);
  stop = micros();
  Serial.print("DATA: \t");
  Serial.println(length);
  Serial.print(" CRC:\t");
  Serial.println(crc.getCRC(), HEX);
  Serial.print("TIME: \t");
  Serial.println(stop - start);
  delay(100);

  

}


// -- END OF FILE --

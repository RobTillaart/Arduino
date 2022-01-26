//
//    FILE: Fletcher_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo

#include "Arduino.h"
#include "Fletcher.h"
#include "printHelpers.h"


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
  while (!Serial);

  Serial.println();
  Serial.print("FLETCHER_LIB_VERSION: ");
  Serial.println(FLETCHER_LIB_VERSION);

  for (int i = 0; i < 60; i++)
  {
    Serial.print(str[i]);
  }
  Serial.println("...");

  uint16_t len = strlen(str);
  Serial.print("LENGTH STR: ");
  Serial.println(len);
  delay(100);

  start = micros();
  volatile uint16_t x = fletcher16((uint8_t *) str, len);
  stop = micros();
  Serial.print("FLETCHER16: ");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println(x);
  delay(100);

  start = micros();
  volatile uint32_t y = fletcher32((uint16_t *) str, (len + 1) / 2);
  stop = micros();
  Serial.print("FLETCHER32: ");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println(y);
  delay(100);

  start = micros();
  volatile uint64_t z = fletcher64((uint32_t *) str, (len + 3) / 4);
  stop = micros();
  Serial.print("FLETCHER64: ");
  Serial.print(stop - start);
  Serial.print("\t");
  Serial.println(print64(z));
  delay(100);
}


void loop()
{
}


// -- END OF FILE --

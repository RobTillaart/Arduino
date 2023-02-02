//
//    FILE: soundex_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo


#include "Arduino.h"
#include "Soundex.h"

Soundex SDX;

uint32_t start, stop, total;
char    *token;
uint16_t words;


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



void setup()
{
  Serial.begin(115200);
  while (!Serial);

  Serial.println();
  Serial.print("SOUNDEX_LIB_VERSION: ");
  Serial.println(SOUNDEX_LIB_VERSION);
  delay(100);

  //  SOUNDEX PER WORD
  token = strtok(str, " ,");
  words = 0;
  total = 0;

  while (token != NULL)
  {
    start = micros();
    char * key = SDX.soundex(token);
    stop = micros();

    Serial.print(stop - start);
    total += (stop - start);
    Serial.print("\t");
    Serial.print(key);
    Serial.print("\t");
    Serial.print(token);
    Serial.print("\n");
    token = strtok(NULL, " ,");
    words++;

    delay(10);
  }

  //  TOTAL TIME
  Serial.print("\nTOTAL: \t");
  Serial.print(total);
  Serial.print("\t");
  Serial.print(words);
  Serial.print("\t");
  Serial.print(1.0 * total / words, 4);
  Serial.print(" per word\n");
  delay(100);

  Serial.println("\ndone...");
}


void loop()
{
}


// -- END OF FILE --

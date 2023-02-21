//
//    FILE: SHEXA_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo SHEX hex dump class
//    DATE: 2022-05-28


#include "SHEX.h"

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


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("SHEX_LIB_VERSION: ");
  Serial.println(SHEX_LIB_VERSION);

  Serial.println("\nNORMAL\n");
  for (int i = 0; i < 64; i++)
  {
    Serial.print(random(127));
    Serial.print('\t');
    if ((i % 16) == 0) Serial.println();
  }

  Serial.println("\n\nSHEX ASCII TEST");
  SHEXA shex(&Serial, 16);
  shex.setCountDigits(5);
  shex.print("abcdefghijklmnopqrstuvwxyz");
  shex.flushASCII();
  shex.restartOutput();

  shex.print("abcdefghijklmnopqrstuv");
  shex.flushASCII();
  shex.restartOutput();

  //  LONG TEXT
  shex.print(lorem);
  shex.flushASCII();
  shex.restartOutput();

  Serial.println("\n Done...\n");
}


void loop()
{
}


// -- END OF FILE --

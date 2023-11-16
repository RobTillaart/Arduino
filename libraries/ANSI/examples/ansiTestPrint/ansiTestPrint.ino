//
//    FILE: ansiTestPrint.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/ANSI


#include "ansi.h"

ANSI ansi(&Serial);

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
  ansi.println(__FILE__);
  ansi.print("ANSI_LIB_VERSION: ");
  ansi.println(ANSI_LIB_VERSION);
  ansi.println();

  ansi.println("\nTest invisible");
  ansi.invisible();
  ansi.println("INVISIBLE?");
  ansi.normal();
  ansi.println("VISIBLE?");
  delay(1000);

  ansi.println("\nTest printMode");
  ansi.clearScreen();
  ansi.setPrintingMode(true);
  ansi.println(lorem);
  ansi.setPrintingMode(false);
  delay(1000);

  ansi.println("\nTest printScreen");
  ansi.clearScreen();
  ansi.println("Hello World");
  ansi.printScreen();
  ansi.println("done");
  delay(1000);

  ansi.println("\nTest printLine");
  ansi.clearScreen();
  ansi.println("Hello 1");
  ansi.println("Hello 2");
  ansi.printLine();
  ansi.println("Hello 3");
  ansi.println("Hello 4");
  ansi.println("done");
  delay(1000);


  ansi.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --

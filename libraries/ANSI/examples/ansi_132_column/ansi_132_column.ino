//
//    FILE: ansi_132_column.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: display 132 columns
//     URL: https://github.com/RobTillaart/ANSI
//
//  use Tera Term to view 132 columns.


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



#include "ansi.h"

ANSI ansi(&Serial);


void setup()
{
  Serial.begin(115200);
  ansi.println();
  ansi.println(__FILE__);
  ansi.print("ANSI_LIB_VERSION: ");
  ansi.println(ANSI_LIB_VERSION);
  ansi.println();

  // SPLASH SCREEN
  ansi.set80columns();
  ansi.clearScreen();
  ansi.gotoXY(8, 10);
  ansi.bold();
  ansi.print("DEMO ANSI TERMINAL 132 COLUMN");
  ansi.normal();
  delay(3000);
  ansi.clearScreen();
}


void loop()
{
  ansi.set132columns();
  ansi.println(lorem);
  ansi.println();
  delay(5000);

  ansi.set80columns();
  ansi.println(lorem);
  ansi.println();
  delay(5000);
}


//  -- END OF FILE --

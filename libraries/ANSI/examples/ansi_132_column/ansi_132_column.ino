//
//    FILE: ansi_132_column.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo clock
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

  // SPLASH SCREEN
  ansi.set80columns();
  ansi.clearScreen();
  ansi.gotoXY(8, 10);
  ansi.bold();
  ansi.print("DEMO ANSI TERMINAL 132 COLUMN");
  ansi.normal();
  delay(3000);
  ansi.clearScreen();

  ansi.set132columns();
  ansi.println(lorem);
  ansi.println();

  delay(5000);
  ansi.set80columns();
  ansi.println(lorem);
  ansi.println();

  delay(5000);
  ansi.set132columns();
  ansi.println(lorem);
  ansi.println();
}


void loop()
{
}


//  -- END OF FILE --

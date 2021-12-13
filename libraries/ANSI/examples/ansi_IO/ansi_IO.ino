//
//    FILE: ansi_IO.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo
//    DATE: 2021-10-18
//     URL: https://github.com/RobTillaart/ANSI
//    (c) : MIT
//


#include "ansi.h"

ANSI ansi(&Serial);

String user = "";
String password = "";


void setup()
{
  Serial.begin(115200);

  ansi.clearScreen();

  ansi.print("ANSI_LIB_VERSION: ");
  ansi.print(ANSI_LIB_VERSION);

  ansi.gotoXY(4, 2);
  ansi.print("Username: ");
  char c = '\0';
  while (c != '\r')
  {
    if (ansi.available() )
    {
      c = ansi.read();
      if (c != '\r')
      {
        user += c;
        ansi.print(c);
      }
    }
  }

  ansi.gotoXY(5, 2);
  ansi.print("Password: ");
  c = '\0';
  while (c != '\r')
  {
    if (ansi.available() )
    {
      c = ansi.read();
      if (c != '\r')
      {
        password += c;
        ansi.print('.');
      }
    }
  }

  ansi.gotoXY(10, 2);
  ansi.print(user);
  ansi.print("\t\t");
  ansi.print(password);

  ansi.println("\ndone...");
}


void loop()
{
}

// -- END OF FILE --

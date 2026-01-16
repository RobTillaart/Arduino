//
//    FILE: ansi_IO.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/ANSI


#include "ansi.h"

ANSI ansi(&Serial);

String user = "";
String password = "";


void setup()
{
  Serial.begin(115200);
  ansi.println();
  ansi.println(__FILE__);
  ansi.print("ANSI_LIB_VERSION: ");
  ansi.println(ANSI_LIB_VERSION);
  ansi.println();
  delay(1000);

  ansi.clearScreen();

  ansi.gotoXY(2, 4);
  ansi.print("Username: ");
  char c = '\0';
  while (c != '\r' && c != '\n')
  {
    if (ansi.available() )
    {
      c = ansi.read();
      if (c != '\r' && c != '\n')
      {
        user += c;
        ansi.print(c);
      }
    }
  }
  while (ansi.available()) ansi.read();  //  flush input

  ansi.gotoXY(2, 5);
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

  ansi.gotoXY(2, 10);
  ansi.print(user);
  ansi.print("\t\t");
  ansi.print(password);

  ansi.println("\ndone...");
}


void loop()
{
}


//  -- END OF FILE --

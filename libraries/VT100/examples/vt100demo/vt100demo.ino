//
//    FILE: VT100.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.00
// PURPOSE: demo vt100 codes
//    DATE: 2013-09-30
//     URL:
//
// Released to the public domain
//

#include "VT100.h"

void setup()
{
  Serial.begin(115200);
  Serial.println("VT100 demo sketch");
  delay(1000);
  
  Serial.print(CLS);
  Serial.println("Hello World");
  Serial.print(OFF);
  Serial.println("Goodbye");
  delay(100);
  
  Serial.print(BOLD);
  Serial.println("bold - Hello World");
  Serial.print(OFF);
  Serial.println("Goodbye");
  delay(100);
  
  Serial.print(LOWINTENS);
  Serial.println("lowintense - Hello World");
  Serial.print(OFF);
  Serial.println("Goodbye");
  delay(100);
  
  Serial.print(UNDERLINE);
  Serial.println("underline - Hello World");
  Serial.print(OFF);
  Serial.println("Goodbye");
  delay(100);
  
  Serial.print(BLINK);
  Serial.println("blink - Hello World");
  Serial.print(OFF);
  Serial.println("Goodbye");
  delay(100);
  
  Serial.print(REVERSE);
  Serial.println("reverse - Hello World");
  Serial.print(OFF);
  Serial.println("Goodbye");
  delay(100);
  
  // experimental section (does not work yet)
  Serial.print(CUD(3));
  Serial.println("Cursor Down 3 - Hello World");
  Serial.print(OFF);
  Serial.println("Goodbye");  
  delay(100);
  
  Serial.print(GOTOXY(3,3));
  Serial.println("gotoxy 3,3 - Hello World");
  Serial.print(OFF);
  Serial.println("Goodbye");  
  delay(100);  
}

void loop()
{
}
// END OF FILE
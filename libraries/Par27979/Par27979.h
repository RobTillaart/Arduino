/*
  Par27979.h - library for Arduino & Parallax 27979 serial display
  Copyright (c) 2010.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it as long as you leave this copyright notice intact

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
*/

#ifndef Par27979_h
#define Par27979_h

#define DISPLAYOFF	    Serial.print((char)21)
#define DISPLAYON	    Serial.print((char)22)
#define DISPLAYCLR	    Serial.print((char)12); delay(10)
#define BACKLIGHTOFF	Serial.print((char)18)
#define BACKLIGHTON	    Serial.print((char)17)
#define GOTOXY(x,y)	    Serial.print((char)(128 + y*20 + x))
#define LEFT		    Serial.print((char)8)
#define RIGHT		    Serial.print((char)9)
#define LINEFEED	    Serial.print((char)10)
#define FORMFEED	    Serial.print((char)12)
#define RETURN		    Serial.print((char)13)

#endif

/*
void setup()
{
  Serial.begin(9600);
  DISPLAYON;
  GOTOXY(2,3);
  Serial.print("hello");
}

void loop()
{
}
*/

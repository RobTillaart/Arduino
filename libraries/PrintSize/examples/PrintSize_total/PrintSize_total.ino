//
//    FILE: PrintSize_total.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo printSize total counter
//     URL: https://github.com/RobTillaart/PrintSize
//
/*
  Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed mattis eget odio ut
  tempor. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Proin consectetur,
  massa nec eleifend aliquet, tellus nulla dapibus magna, eu pharetra dolor turpis
  sit amet mauris. Quisque tempor luctus nisl. Donec nisi quam, gravida id urna quis,
  vestibulum placerat ex. Etiam auctor odio nisl, at molestie arcu gravida et.
  Integer rutrum enim ligula, eget commodo lorem dapibus nec. Ut bibendum sapien at
  tellus posuere, lobortis vestibulum magna blandit. Curabitur aliquam, massa sit
  amet aliquet ullamcorper, dui metus sollicitudin purus, luctus tempor nisi enim
  commodo justo. Nullam tempus, nunc finibus hendrerit mollis, purus odio mattis
  nisl, porttitor malesuada erat urna eu neque. Phasellus ultricies ante tortor,
  ac facilisis diam dignissim sit amet. Donec accumsan ac orci a malesuada.
*/


#include "PrintSize.h"

char woord[24];
int idx = 0;

PrintSize ps;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("PRINTSIZE_VERSION: ");
  Serial.println(PRINTSIZE_VERSION);
  Serial.println();

  Serial.println("\nType words < 20 chars in the Serial monitor\n");
  ps.reset();
}


void loop()
{
  if (Serial.available() > 0)
  {
    char c = Serial.read();
    if (c == ' ' || c == '\n')
    {
      process(woord, 60);
      woord[0] = '\0';
      idx = 0;
    }
    else
    {
      woord[idx++] = c;
      woord[idx] = '\0';
    }
  }
}


// split the stream of words in lines of maxLength
void process(char * w, uint8_t maxLength)
{
  // skip empty words.
  if (strlen(w) == 0) return;

  // remember position
  uint8_t prev = ps.total();

  // does the word fit on the line
  ps.print(w);
  ps.print(' ');
  if (ps.total() >= maxLength)
  {
    // if not, fill line with -
    for (; prev < maxLength; prev++) Serial.print('-');
    Serial.println();

    // start counter for new line.
    ps.reset();
    ps.print(w);
    ps.print(' ');
  }
  Serial.print(w);
  Serial.print(' ');
}


//  -- END OF FILE --


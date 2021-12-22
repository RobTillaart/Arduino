//
//    FILE: MT8870_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//    DATE: 2020-08-13


#include "MT8870.h"

MT8870 DTMF;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MT8870_LIB_VERSION: ");
  Serial.println(MT8870_LIB_VERSION);

  DTMF.begin(2, 4, 5, 6, 7);
}


void loop()
{
  if (DTMF.available())
  {
    int raw = DTMF.readRaw();
    char ch = DTMF.read();
    Serial.print(raw);
    Serial.print('\t');
    Serial.print(ch);
    Serial.println();
  }

  // do something else
}


// -- END OF FILE --


//
//    FILE: functionGenerator.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.02
// PURPOSE: demo function generators
//    DATE: 2015-01-03
//     URL:
//
// Released to the public domain
//

#include "functionGenerator.h"

uint32_t lastTime = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println("Start ");

}

void loop()
{
  uint32_t now = millis();
  int choice = analogRead(A0) / 200; // signal selection potMeter

  int period = 1000; // in milliseconds
  float val;

  if (now != lastTime)
  {
    lastTime = now;
    int p = now % period;
    switch (choice)
    {
      case 0: val = fgsqr(p, period); break;
      case 1: val = fgsaw(p, period); break;
      case 2: val = fgtri(p, period); break;
      case 3: val = fgstr(p, period); break;
      default: val = fgsin(p, period); break;
    }
    Serial.println(val);
  }
}

// END OF FILE

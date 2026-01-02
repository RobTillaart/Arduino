//
//    FILE: optoma_Serial1.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo vertical keystone.
//     URL: https://github.com/RobTillaart/Optoma
//
//  Test with TeraTerm or an Optoma beamer)
//  TeraTerm: Newline Receive mode = CR + LF + 9600 baud.
//  Note: the optoma class uses Serial1 => use e.g. MEGA


#include "optoma.h"

Optoma beamer(&Serial1);


void setup()
{
  Serial1.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("OPTOMA_LIB_VERSION:");
  Serial.println(OPTOMA_LIB_VERSION);
  Serial.println();

  beamer.init(22);

  beamer.switchOn();
  delay(10000);         //  wait until lamp is warm

  for (int i = 0; i < 20; i++)
  {
    beamer.increaseVKS();
    delay(100);         //  give beamer some time to adjust
  }
  for (int i = 0; i < 20; i++)
  {
    beamer.decreaseVKS();
    delay(100);         //  give beamer some time to adjust
  }
  delay(5000);
  beamer.switchOff();
}


void loop()
{
}


//  -- END OF FILE --

//
//    FILE: TLC5947_percentage.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/TLC5947


#include "TLC5947.h"


TLC5947 tlc(13, 12, 11, 10);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("TLC5947_LIB_VERSION: \t");
  Serial.println(TLC5947_LIB_VERSION);

  if (tlc.begin() == false)
  {
    Serial.println("error");
    while (1);
  }

  for (int ch = 0; ch < 24; ch++)
  {
    int p = random(4096);
    tlc.setPWM(ch, p);
    Serial.print(ch);
    Serial.print('\t');
    Serial.print(p);
    Serial.print('\t');
    Serial.print(tlc.getPWM(ch));
    Serial.println();
  }
  Serial.println();

  for (int ch = 0; ch < 24; ch++)
  {
    float p = random(10000) * 0.01;
    tlc.setPercentage(ch, p);
    Serial.print(ch);
    Serial.print('\t');
    Serial.print(p);
    Serial.print('\t');
    Serial.print(tlc.getPercentage(ch));
    Serial.println();
  }
  tlc.write();

  Serial.println("\ndone...");
}


void loop()
{

}


//  -- END OF FILE --

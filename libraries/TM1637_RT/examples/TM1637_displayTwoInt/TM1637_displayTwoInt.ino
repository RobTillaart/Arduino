//
//    FILE: TM1637_displayTwoInt.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo TM1637 library
//     URL: https://github.com/RobTillaart/TM1637_RT


#include "TM1637.h"

TM1637 TM;

int temperature = -9;
int humidity = 0;

void setup()
{
  while(!Serial);
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("TM1637_LIB_VERSION: ");
  Serial.println(TM1637_LIB_VERSION);
  Serial.println();

  TM.begin(7, 6, 4);       //  clock pin, data pin, #digits
}


void loop()
{
  //  simulate temperature and humidity
  TM.displayTwoInt(temperature, humidity);  //  default colon on.
  temperature++;
  if (temperature == 100) temperature = -9;
  humidity++;
  if (humidity == 100) humidity = 0;
  delay(250);
}


//  -- END OF FILE --

//
//    FILE: GP8403_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/GP8403

#include "Arduino.h"
#include "Wire.h"
#include "GP8403.h"


GP8403 myDAC(0x40, &Wire);
uint32_t start, stop;


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("GP8403_LIB_VERSION: ");
  Serial.println(GP8403_LIB_VERSION);
  Serial.println();
  delay(100);

  Wire.begin();

  for (uint32_t speed = 100000; speed <= 800000; speed += 50000)
  {
    Wire.setClock(speed);
    if (myDAC.begin() == false) break;

    start = micros();
    myDAC.setValue(1, 255);
    stop = micros();

    Serial.print("| ");
    Serial.print(speed);
    Serial.print(" | ");
    Serial.print(stop - start);
    Serial.print(" |");
    Serial.println();
    delay(100);
  }

  Serial.println("done...");
}


void loop()
{
}


//  -- END OF FILE --

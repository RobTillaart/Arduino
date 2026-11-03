//
//    FILE: SLF3S_performance.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic performance
//     URL: https://github.com/RobTillaart/SLF3S


#include "SLF3S.h"


SLF3S slf;
uint32_t start, stop;

void setup()
{
  while(!Serial);
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("SLF3S_LIB_VERSION: ");
  Serial.println(SLF3S_LIB_VERSION);
  Serial.println();

  Wire.begin();

  //  SLF3S-0600F
  if (slf.begin(600) == false)
  {
    Serial.print("Error: ");
    Serial.println(slf.getLastError());
    while(1);
  }

  slf.requestH2O();

  //  wait for stable up to 60 ms
  //  or timeout...
  uint32_t start = millis();
  while (slf.isReady() == false)
  {
    if (millis() - start > 1000)
    {
      Serial.print("Error: ");
      Serial.println(slf.getLastError());
      break;
    }
  }

  for (uint32_t speed = 100000; speed < 1000000; speed += 100000)
  {
    Wire.setClock(speed);

    delay(100);

    start = micros();
    slf.readFlow();
    stop = micros();
    uint32_t d1 = stop - start;

    start = micros();
    slf.readFlowTemp();
    stop = micros();
    uint32_t d2 = stop - start;

    Serial.print("| ");
    Serial.print(speed);
    Serial.print(" | ");
    Serial.print(d1);
    Serial.print(" | ");
    Serial.print(d2);
    Serial.print(" |");
    Serial.println();
  }

  Serial.println("done...");
}


void loop()
{

}


//  -- END OF FILE --

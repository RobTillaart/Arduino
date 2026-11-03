//
//    FILE: SLF3S_demo.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour
//     URL: https://github.com/RobTillaart/SLF3S


#include "SLF3S.h"


SLF3S slf;


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
}


void loop()
{
  slf.readFlowTemp();
  if (slf.getLastError() == SLF3S_OK)
  {
    float flow = slf.getFlow();
    float temp = slf.getTemperature();
    Serial.print(millis());
    Serial.print("\t");
    Serial.print(flow);
    Serial.print("\t");
    Serial.println(temp);
  }
  else
  {
    Serial.print(millis());
    Serial.print("\tError: ");
    Serial.println(slf.getLastError());
  }
  delay(1000);
}


//  -- END OF FILE --

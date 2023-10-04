//
//    FILE: Max44007_setAutomaticMode.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo of Max44007 library
//    DATE: 2022-01-04


#include "Wire.h"
#include "Max44007.h"

Max44007 myLux(0x5A);

uint32_t lastDisplay = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MAX44007_LIB_VERSION: ");
  Serial.println(MAX44007_LIB_VERSION);

  Wire.begin();

  myLux.setAutomaticMode();
}


void loop()
{
  uint32_t interval = 100;
  if (millis() - lastDisplay >= interval)
  {
    lastDisplay += interval;
    float lux = myLux.getLux();
    int err = myLux.getError();

    // in automatic mode TIM & CDR are automatic generated
    // and read only (in manual mode they are set by the user
    int conf = myLux.getConfiguration();
    int CDR = (conf & 0x80) >> 3;
    int TIM = (conf & 0x07);
    int integrationTime = myLux.getIntegrationTime();

    if (err != 0)
    {
      Serial.print("Error:\t");
      Serial.println(err);
    }
    else
    {
      Serial.print("lux:\t");
      Serial.print(lux);
      Serial.print("\tCDR:\t");
      Serial.print(CDR);
      Serial.print("\tTIM:\t");
      Serial.print(TIM);
      Serial.print("\t");
      Serial.print(integrationTime);
      Serial.print(" ms");
      Serial.println();
    }
  }
}


// -- END OF FILE --

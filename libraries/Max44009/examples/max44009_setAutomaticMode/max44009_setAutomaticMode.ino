//
//    FILE: max44009_setAutomaticMode.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo of max44009 library
//     URL: https://github.com/RobTillaart/MAX44009


#include "Max44009.h"


Max44009 myLux(0x4A);

uint32_t lastDisplay = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MAX44009_LIB_VERSION: ");
  Serial.println(MAX44009_LIB_VERSION);
  Serial.println();

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
    int error = myLux.getError();

    //  In automatic mode TIM and CDR are automatic generated
    //  and read only.
    //  In manual mode they are set by the user.
    int config = myLux.getConfiguration();
    int CDR = (config & 0x80) >> 3;
    int TIM = (config & 0x07);
    int integrationTime = myLux.getIntegrationTime();

    if (error != 0)
    {
      Serial.print("Error:\t");
      Serial.println(error);
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


//  -- END OF FILE --


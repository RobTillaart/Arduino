//
//    FILE: max44007_test_manualmode.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo of max44007 library
//     URL: https://github.com/RobTillaart/MAX44007


#include "Max44007.h"


Max44007 myLux(MAX44007_DEFAULT_ADDRESS, &Wire);


uint32_t lastDisplay = 0;
uint32_t lastChangeCDRTIM = 0;

uint8_t CDR = 0;
uint8_t TIM = 0;


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("MAX44007_LIB_VERSION: ");
  Serial.println(MAX44007_LIB_VERSION);
  Serial.println();

  Wire.begin();

  myLux.setManualMode(CDR, TIM);
}


void loop()
{
  uint32_t interval = 100;
  if (millis() - lastDisplay >= interval)
  {
    lastDisplay += interval;
    float lux = myLux.getLux();
    int err = myLux.getError();
    if (err != 0)
    {
      Serial.print("Error:\t");
      Serial.println(err);
    }
    else
    {
      Serial.print("lux:\t");
      Serial.println(lux);
    }
  }

  //  Change CDR and TIM every 5 seconds
  //  Note that the value of getLux() is affected
  //  for up to about a second.
  if (millis() - lastChangeCDRTIM >= 5000)
  {
    lastChangeCDRTIM += 5000;
    TIM++;
    if (TIM == 4)
    {
      TIM = 0;
      CDR = (CDR + 1) & 1;
    }
    myLux.setManualMode(CDR, TIM);
    Serial.print("CDR:\t");
    Serial.print((int)CDR);
    Serial.print("\t");
    Serial.print(myLux.getCurrentDivisorRatio());  //  read from config
    Serial.print("\tTIM:\t");
    Serial.print((int)TIM);
    Serial.print("\t");
    Serial.print(myLux.getIntegrationTime());  //  read from config
    Serial.print(" ms\n");
  }
}


//  -- END OF FILE --

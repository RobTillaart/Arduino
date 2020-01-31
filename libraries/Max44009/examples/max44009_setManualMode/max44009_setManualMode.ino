//
//    FILE: max44009_setManualMode.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo of max44009 library
//    DATE: 2020-01-30
//
// Released to the public domain
//

#include "Wire.h"
#include "Max44009.h"

Max44009 myLux(0x4A);

uint32_t lastDisplay = 0;
uint32_t lastChangeCDRTIM = 0;

uint8_t CDR = 0;
uint8_t TIM = 0;

void setup()
{
  Serial.begin(115200);
  Serial.print("\nStart max44009_setManualMode : ");
  Serial.println(MAX44009_LIB_VERSION);

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

  // Change CDR and TIM every 5 seconds
  // Note that the value of getLux() is affected
  // for up to about a second.
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
	Serial.print("\tTIM:\t");
	Serial.println((int)TIM);
  }
}

// END OF FILE

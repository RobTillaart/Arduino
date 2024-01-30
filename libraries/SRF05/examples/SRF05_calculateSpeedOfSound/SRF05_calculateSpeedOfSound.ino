//
//    FILE: SRF05_calculateSpeedOfSound.txt
//  AUTHOR: Rob Tillaart
// PURPOSE: demo distance sensor
//     URL: https://github.com/RobTillaart/SRF05


#include "SRF05.h"

const int trigger = 7;
const int echo    = 6;

SRF05 SRF(trigger, echo);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("SRF05_LIB_VERSION: ");
  Serial.println(SRF05_LIB_VERSION);
  Serial.println();
  

  for (int temp = -40; temp <= 60; temp += 5)
  {
    Serial.print(temp);
    Serial.print("\t");
    for (int hum = 0; hum <= 100; hum += 10)
    {
      float sos = SRF.calculateSpeedOfSound(temp, hum);
      Serial.print(sos, 2);
      Serial.print("\t");
    }
    Serial.println();
  }
}


void loop()
{

}


//  -- END OF FILE --

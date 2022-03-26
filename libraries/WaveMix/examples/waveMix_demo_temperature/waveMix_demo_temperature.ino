//
//    FILE: waveMix_demo_temperature.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/WaveMix
//
// needs 2x DHT22 sensors

#include "WaveMix.h"
#include "dhtnew.h"

WaveMix wm;
DHTNEW living(5);
DHTNEW kitchen(6);


void setup()
{
  while(!Serial);
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("WAVEMIX_LIB_VERSION: ");
  Serial.println(WAVEMIX_LIB_VERSION);

  wm.setPercentage(75);   // inside counts for 75%
}


void loop()
{
  living.read();
  kitchen.read();
  float mixed = wm.mix(living.getTemperature(), kitchen.getTemperature());
  Serial.println(mixed);
  delay(2000);
}


// -- END OF FILE --

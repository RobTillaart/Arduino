//
//    FILE: DMM_noise.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo DMM 
//     URL: https://github.com/RobTillaart/DMM


#include "DMM.h"


DMM dmm;


void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println(__FILE__);
  Serial.print("DMM_LIB_VERSION: ");
  Serial.println(DMM_LIB_VERSION);

  dmm.begin(A0, 5.000, 1023);
}


void loop()
{
  //  noise over 5 samples
  float noise = dmm.readNoise(5);  
  Serial.print("Noise: ");
  Serial.print(noise, 3);
  Serial.println();

  delay(1000);
}


//  -- END OF FILE --

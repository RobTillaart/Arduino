//
//    FILE: AD5684_sinus.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/AD5684


#include "AD5684.h"


AD5684 AD16_HW(8, &SPI);
AD5684 AD16_SW(5, 6, 7);

float frequency = 10.0;
float amplitude = 2047;  //  50% of 12 bits

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AD5684_LIB_VERSION: ");
  Serial.println(AD5684_LIB_VERSION);

  SPI.begin();
  AD16_HW.begin();
  AD16_SW.begin();

  Serial.print("HWSPI: ");
  Serial.println(AD16_HW.usesHWSPI());
  Serial.print("HWSPI: ");
  Serial.println(AD16_SW.usesHWSPI());
}


void loop()
{
  float phase  = fmod(micros() * (frequency * (TWO_PI * 1e-6)), TWO_PI);
  float x = (1 + sin(phase)) * amplitude;
  float y = (1 + sin(phase + PI * 0.6666)) * amplitude;
  float z = (1 + sin(phase + PI * 1.3333)) * amplitude;
  AD16_HW.setValue(0, x);
  AD16_HW.setValue(1, y);
  AD16_HW.setValue(2, z);
  AD16_HW.setValue(3, amplitude);
  Serial.print(x);
  Serial.print("\t");
  Serial.print(y);
  Serial.print("\t");
  Serial.print(z);
  Serial.print("\t");
  Serial.print(amplitude);
  Serial.print("\n");

}


//  -- END OF FILE --

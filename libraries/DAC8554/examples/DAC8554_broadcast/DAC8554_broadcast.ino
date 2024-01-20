//
//    FILE: DAC8554_broadcast.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo DAC8554 library Arduino with hardware SPI
//     URL: https://github.com/RobTillaart/Arduino/DAC8554


#include "DAC8554.h"


//  note address as parameter
DAC8554 DAC_A(10, &SPI, 0);
DAC8554 DAC_B(11, &SPI, 1);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.println(DAC8554_LIB_VERSION);

  SPI.begin();

  DAC_A.begin();
  DAC_B.begin();

  Serial.println("Buffer initial values");
  for (uint8_t channel = 0; channel < 4; channel++)
  {
    DAC_A.bufferValue(channel, channel * 1000);
    DAC_B.bufferValue(channel, 60000 - channel * 1000);
  }
  delay(2000);
  Serial.println("Set initial values");
  DAC_A.broadcastBuffer();

  Serial.println("Buffer new values");
  for (uint8_t channel = 0; channel < 4; channel++)
  {
    DAC_A.bufferValue(channel, channel * 5000);
    DAC_B.bufferValue(channel, 60000 - channel * 5000);
  }
  delay(2000);
  Serial.println("Set new values");
  DAC_A.broadcastBuffer();

  delay(2000);
  Serial.println("Set all values");
  DAC_A.broadcastValue(32000);

  delay(2000);
  Serial.println("PowerDown 100K");
  DAC_A.broadcastPowerDown(DAC8554_POWERDOWN_100K);

  Serial.println("Done...");
}


void loop()
{
}


//  -- END OF FILE --


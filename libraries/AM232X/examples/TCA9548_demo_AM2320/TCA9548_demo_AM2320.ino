//
//    FILE: TCA9548_demo_AM2320.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo TCA9548 I2C multiplexer
//     URL: https://github.com/RobTillaart/TCA9548


#include "AM232X.h"
#include "TCA9548.h"


PCA9546 MP(0x70);
uint8_t channels = 0;

AM232X living;    //  channel 0
AM232X kitchen;   //  channel 1
AM232X outside;   //  channel 2

uint32_t lastTime = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("TCA9548_LIB_VERSION: ");
  Serial.println(TCA9548_LIB_VERSION);
  Serial.print("AM232X_LIB_VERSION: ");
  Serial.println(AM232X_LIB_VERSION);
  Serial.println();

  Wire.begin();
  //  initialize multiplexer
  if (MP.begin() == false)
  {
    Serial.println("Multiplexer error");
  }
  channels = MP.channelCount();

  //  initialize the temperature sensors
  MP.selectChannel(0);
  if (living.begin() == false)
  {
    Serial.println("living error");
  }
  MP.selectChannel(1);
  if (kitchen.begin() == false )
  {
    Serial.println("kitchen error");
  }
  MP.selectChannel(2);
  if (outside.begin() == false )
  {
    Serial.println("outside error");
  }
}


void loop()
{
  if ((millis() - lastTime) > 5000)
  {
    lastTime = millis();

    MP.selectChannel(0);
    living.read();
    Serial.print(living.getTemperature(), 1);
    Serial.print("\t");

    MP.selectChannel(1);
    kitchen.read();
    Serial.print(kitchen.getTemperature(), 1);
    Serial.print("\t");

    MP.selectChannel(2);
    outside.read();
    Serial.print(outside.getTemperature(), 1);
    Serial.print("\n");
  }
}


//  -- END OF FILE --
